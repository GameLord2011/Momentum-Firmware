#include "../power_settings_app.h"
#include <dolphin/dolphin.h>

void power_settings_scene_power_off_dialog_callback(DialogExResult result, void* context) {
    furi_assert(context);
    PowerSettingsApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, result);
}

void power_settings_scene_power_off_on_enter(void* context) {
    PowerSettingsApp* app = context;
    DialogEx* dialog = app->dialog;
    Dolphin* dolphin = furi_record_open(RECORD_DOLPHIN);
    DolphinSettings settings;
    dolphin_get_settings(dolphin, &settings);
    furi_record_close(RECORD_DOLPHIN);

    dialog_ex_set_header(
        dialog,
        "Turn Off Device?",
        64,
        settings.happy_mode ? 32 : 0,
        AlignCenter,
        settings.happy_mode ? AlignCenter : AlignTop);
    if(!settings.happy_mode) {
        dialog_ex_set_text(
            dialog, "   I will be\nwaiting for\n you here...", 78, 14, AlignLeft, AlignTop);
        dialog_ex_set_icon(dialog, 14, 10, &I_dolph_cry_49x54);
    }
    dialog_ex_set_left_button_text(dialog, "Battery");
    dialog_ex_set_right_button_text(dialog, "Power Off");
    dialog_ex_set_result_callback(dialog, power_settings_scene_power_off_dialog_callback);
    dialog_ex_set_context(dialog, app);

    view_dispatcher_switch_to_view(app->view_dispatcher, PowerSettingsAppViewDialog);
}

bool power_settings_scene_power_off_on_event(void* context, SceneManagerEvent event) {
    PowerSettingsApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == DialogExResultLeft) {
            scene_manager_next_scene(app->scene_manager, PowerSettingsAppSceneBatteryInfo);
        } else if(event.event == DialogExResultRight) {
            power_off(app->power);
        }
        consumed = true;
    }
    return consumed;
}

void power_settings_scene_power_off_on_exit(void* context) {
    PowerSettingsApp* app = context;
    dialog_ex_reset(app->dialog);
}