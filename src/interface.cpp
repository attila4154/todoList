#include "../lib/interface.h"

int Interface::termHeight = 40;
int Interface::termWidth = 70;
int Interface::day = 1;
int Interface::mon = 9;
int Interface::year = 2021;


void Interface::clearRow(int row) {
    for (int i = 1; i < width-1; i++)
        mvwprintw (window, row, i, " ");
}

void Interface::refresh() {
    wrefresh(window);
}

void Interface::clearScreen() {
    for (int i = 3; i < height-1; i++)
        clearRow(i);
}