#include "../lib/calendar.h"


//=====================
Calendar::Calendar() {

}
//---------------------
Calendar::~Calendar() {

}
//---------------------
void Calendar::Run () {
    char c;
    int i = 3;
    do {
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
        mvwprintw (window, 2, i++, "%c", c);
        wrefresh (window);
    } while (c != '\t');
}
//---------------------
void Calendar::setUp () {
    window = newwin (height/2, width/2, 0, 0);
    box (window, 0, 0);
    mvwprintw (window, 1,3 , "Calendar:");
}
//---------------------
void Calendar::reprint () {
    // wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "Calendar:");
    // wattroff (window, A_REVERSE);
}
//---------------------
void Calendar::reprintBold () {
    wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "Calendar:");
    wattroff (window, A_REVERSE);
}