#include "../nfc_maker.h"

enum TextInputResult {
    TextInputResultOk,
};

static void nfc_maker_scene_https_text_input_callback(void* context) {
    NfcMaker* app = context;

    view_dispatcher_send_custom_event(app->view_dispatcher, TextInputResultOk);
}

void nfc_maker_scene_https_on_enter(void* context) {
    NfcMaker* app = context;
    TextInput* text_input = app->text_input;

    text_input_set_header_text(text_input, "Enter Https Link:");

    strlcpy(
        app->big_buf,
#ifdef FW_ORIGIN_Momentum
        "momentum-fw.dev",
#else
        "flipperzero.one",
#endif
        sizeof(app->big_buf));

    text_input_set_result_callback(
        text_input,
        nfc_maker_scene_https_text_input_callback,
        app,
        app->big_buf,
        sizeof(app->big_buf),
        true);

    text_input_show_illegal_symbols(text_input, true);

    view_dispatcher_switch_to_view(app->view_dispatcher, NfcMakerViewTextInput);
}

bool nfc_maker_scene_https_on_event(void* context, SceneManagerEvent event) {
    NfcMaker* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        consumed = true;
        switch(event.event) {
        case TextInputResultOk:
            scene_manager_next_scene(app->scene_manager, NfcMakerSceneSaveGenerate);
            break;
        default:
            break;
        }
    }

    return consumed;
}

void nfc_maker_scene_https_on_exit(void* context) {
    NfcMaker* app = context;
    text_input_reset(app->text_input);
}