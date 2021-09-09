#include "../lib/interface.h"

int Interface::termHeight = 40;
int Interface::termWidth = 70;

void Interface::clearRow(int row) {
    for (int i = 1; i < width-1; i++)
        mvwprintw (window, row, i, " ");
}

void Interface::refresh() {
    wrefresh(window);
}