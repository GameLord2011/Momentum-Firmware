#include "../cli_main_commands.h"
#include <toolbox/cli/cli_ansi.h>

static void execute(PipeSide* pipe, FuriString* args, void* context) {
    UNUSED(pipe);
    UNUSED(args);
    UNUSED(context);
    puts("\r\n" ANSI_FG_BLUE "+-----------------+" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET
         "     Credits     " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE
         "+-----------------+" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET
         "Original Code By:" ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET
         "                 " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET
         "    " CREDITS_ANSI_FLIPPER_BRAND_ORANGE "@WillyJL" ANSI_RESET "     " ANSI_FG_BLUE
         "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET "                 " ANSI_FG_BLUE
         "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET "    " CREDITS_ANSI_FLIPPER_BRAND_ORANGE
         "@HaxSam" ANSI_RESET "      " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE
         "|" ANSI_RESET "                 " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE
         "|" ANSI_RESET "    " CREDITS_ANSI_FLIPPER_BRAND_ORANGE "@Sil333033" ANSI_RESET
         "   " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET
         "                 " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET
         "" CREDITS_ANSI_FLIPPER_BRAND_ORANGE "@MatthewKuKanich" ANSI_RESET " " ANSI_FG_BLUE
         "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET "                 " ANSI_FG_BLUE
         "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET "   " CREDITS_ANSI_FLIPPER_BRAND_ORANGE
         "@KlaraCrazy" ANSI_RESET "   " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE
         "|" ANSI_RESET "                 " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE
         "+-----------------+" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET
         "     Assets:     " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET
         "                 " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET
         "    " CREDITS_ANSI_FLIPPER_BRAND_ORANGE "@Kuronons" ANSI_RESET "    " ANSI_FG_BLUE
         "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET "                 " ANSI_FG_BLUE
         "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "+-----------------+" ANSI_RESET "\r\n" ANSI_FG_BLUE
         "|" ANSI_RESET "   Modded by:    " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE
         "|" ANSI_RESET "                 " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE
         "|" ANSI_RESET "  " ANSI_BLINKY_RED "@GameLord2011" ANSI_RESET "  " ANSI_FG_BLUE
         "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "|" ANSI_RESET "                 " ANSI_FG_BLUE
         "|" ANSI_RESET "\r\n" ANSI_FG_BLUE "+-----------------+\r\n" ANSI_RESET "" ANSI_FG_BLUE
         "|" ANSI_RESET "      EOF        " ANSI_FG_BLUE "|" ANSI_RESET "\r\n" ANSI_FG_BLUE
         "+-----------------+\r\n" ANSI_RESET ""
         "\r\n");
}

CLI_COMMAND_INTERFACE(credits, execute, CliCommandFlagParallelSafe, 768, CLI_APPID);
