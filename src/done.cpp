#include "../lib/done.h"

Done::Done () {
    setUp();
}

Done::~Done () {
    
}

void Done::setUp() {
    height = termHeight/2;
    width = termWidth;
    window = newwin (height, width, height, 0);
    box (window, 0, 0);
    mvwprintw (window, 1,3 , "Done:");
}
//----------------------
void Done::reprint() {
    mvwprintw (window, 1,3 , "Done:");
}
//----------------------
void Done::reprintBold() {
    wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "Done:");
    wattroff (window, A_REVERSE);
}
//----------------------
void Done::Run() {
    char c;
    int i = 3;
    do {
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
        mvwprintw (window, 2, i++, "%c", c);
        wrefresh (window);
    } while (c != '\t');
}