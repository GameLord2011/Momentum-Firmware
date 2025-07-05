#include "../cli_main_commands.h"
#include <toolbox/version.h>
#include <furi_hal.h>
#include <furi_hal_info.h>

static void execute(PipeSide* pipe, FuriString* args, void* context) {
    UNUSED(pipe);
    UNUSED(args);
    UNUSED(context);
    printf(
        "you@"
        "%s",
        furi_hal_version_get_name_ptr());
    puts("\r\n");
}

CLI_COMMAND_INTERFACE(whoami, execute, CliCommandFlagParallelSafe, 768, CLI_APPID);
