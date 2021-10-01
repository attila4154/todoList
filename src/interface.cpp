#include "../lib/interface.h"

int Interface::termHeight = 40;
int Interface::termWidth = 70;
int Interface::day = 1;
int Interface::mon = 9;
int Interface::year = 2021;
int date_compare::daysInMonths[12] = {31, 28, 30, 30, 31, 30, 31, 31, 30, 31, 30, 31};
tm Interface::date = tm {};


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

void Interface::addTask (const Task & task) {

}

void Interface::redrawHighlightedBox() {
    wattron (window, COLOR_PAIR(BLUE_BLACK));
    box (window, 0,0 );
    wattroff (window, COLOR_PAIR(BLUE_BLACK));
}

void Interface::redrawBox(){
    box (window, 0,0);
}