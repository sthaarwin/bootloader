#include "util.h"
#include "../drivers/display.h"

void display_logo()
{
    char *logo[] = {
        " ==================================== ",
        "|       ##   ##   ##   ##   ###      |",
        "|      #  #   ## ##   #  # #         |",
        "|      ####    ###    #  #  ##       |",
        "|      #  #   ## ##   #  #    #      |",
        "|      #  #  ##   ##   ##  ###       |",
        " ==================================== ",
        "",
        "     [[ A Custom OS ]]     ",
        "",
        "    >> Created by Arwin <<    ",
        "",
        "______________________________________"};

    print_string_centered_color(logo[0], MAKE_COLOR(YELLOW, BLACK));
    print_nl();

    for (int i = 1; i <= 5; i++)
    {
        print_string_centered_color(logo[i], MAKE_COLOR(CYAN, BLACK));
        print_nl();
    }

    print_string_centered_color(logo[6], MAKE_COLOR(YELLOW, BLACK));
    print_nl();
    print_nl();

    print_string_centered_color(logo[8], MAKE_COLOR(LIGHT_GREEN, BLACK));
    print_nl();
    print_nl();

    print_string_centered_color(logo[10], MAKE_COLOR(LIGHT_MAGENTA, BLACK));
    print_nl();
    print_nl();

    print_string_centered_color(logo[12], MAKE_COLOR(YELLOW, BLACK));
    print_nl();
}

void kernel_main(void)
{
    clear_screen();
    display_logo();
}