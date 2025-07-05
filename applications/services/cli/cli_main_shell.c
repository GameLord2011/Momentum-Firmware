#include "cli_main_shell.h"
#include "cli_main_commands.h"
#include <toolbox/cli/cli_ansi.h>
#include <toolbox/cli/shell/cli_shell.h>
#include <furi_hal_version.h>

void cli_main_motd(void* context) {
    UNUSED(context);
    printf(ANSI_FLIPPER_BRAND_ORANGE
<<<<<<< HEAD
           "__/\\\\\\\\____________/\\\\\\\\_________\r\n"
           "__\\/\\\\\\\\\\\\________/\\\\\\\\\\\\________\r\n"
           "___\\/\\\\\\//\\\\\\____/\\\\\\//\\\\\\_______\r\n"
           "____\\/\\\\\\\\///\\\\\\/\\\\\\/_\\/\\\\\\______\r\n"
           "_____\\/\\\\\\__\\///\\\\\\/___\\/\\\\\\_____\r\n"
           "______\\/\\\\\\____\\///_____\\/\\\\\\____\r\n"
           "_______\\/\\\\\\_____________\\/\\\\\\___\r\n"
           "________\\/\\\\\\_____________\\/\\\\\\__\r\n"
           "_________\\///______________///___\r\n"
           "\r\n"
           "Welcome to Flipper Zero Command Line Interface!\r\n"
           "Read the manual: https://docs.flipper.net/development/cli\r\n"
           "Run `help` or `?` to list available commands\r\n"
           "This is running " ANSI_GMLRD_RED "@GameLord2011" ANSI_END_GMLRD_RED
           "'s fork of momentum fw\r\n" ANSI_BLINKY_RED
           "https://gamelord2011.vercel.app" ANSI_END_BLINKY_RED "\r\n"
=======
           "\r\n"
           "              _.-------.._                    -,\r\n"
           "          .-\"```\"--..,,_/ /`-,               -,  \\ \r\n"
           "       .:\"          /:/  /'\\  \\     ,_...,  `. |  |\r\n"
           "      /       ,----/:/  /`\\ _\\~`_-\"`     _;\r\n"
           "     '      / /`\"\"\"'\\ \\ \\.~`_-'      ,-\"'/ \r\n"
           "    |      | |  0    | | .-'      ,/`  /\r\n"
           "   |    ,..\\ \\     ,.-\"`       ,/`    /\r\n"
           "  ;    :    `/`\"\"\\`           ,/--==,/-----,\r\n"
           "  |    `-...|        -.___-Z:_______J...---;\r\n"
           "  :         `                           _-'\r\n"
           " _L_  _     ___  ___  ___  ___  ____--\"`___  _     ___\r\n"
           "| __|| |   |_ _|| _ \\| _ \\| __|| _ \\   / __|| |   |_ _|\r\n"
           "| _| | |__  | | |  _/|  _/| _| |   /  | (__ | |__  | |\r\n"
           "|_|  |____||___||_|  |_|  |___||_|_\\   \\___||____||___|\r\n"
           "\r\n" ANSI_FG_BR_WHITE "Welcome to Flipper Zero Command Line Interface!\r\n"
           "Read the manual: https://docs.flipper.net/development/cli\r\n"
           "Run `help` or `?` to list available commands\r\n"
>>>>>>> 2a5679dd09f09c7b21a6a76c3bd953aae0d6b2a5
           "\r\n" ANSI_RESET);

    const Version* firmware_version = furi_hal_version_get_firmware_version();
    if(firmware_version) {
        printf(
            "Firmware version: %s %s (%s%s built on %s)\r\n",
            version_get_gitbranch(firmware_version),
            version_get_version(firmware_version),
            version_get_githash(firmware_version),
            version_get_dirty_flag(firmware_version) ? "-dirty" : "",
            version_get_builddate(firmware_version));
    }
}

const CliCommandExternalConfig cli_main_ext_config = {
    .search_directory = "/ext/apps_data/cli/plugins",
    .fal_prefix = "cli_",
    .appid = CLI_APPID,
};
