#include "../lib/calendar.h"


//=====================
Calendar::Calendar() {
    setUp();
}
//---------------------
Calendar::~Calendar() {

}
//---------------------
void Calendar::Run () {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    highlightDay = now->tm_mday - 1;
    highlightMon = now->tm_mon;
    highlightYear = now->tm_year + 1900;
    wday = findWDay();

    // start_color();
    // init_pair (1, COLOR_RED, COLOR_BLACK);

    char c;
    // int i = 3;
    int y = 5;
    int x = wday;
    do {
        for (int i = 3; i < 11; i++)
            clearRow (i);
        mvwprintw (window, 3, width/6, "%s", months[highlightMon].data());
        // mvwprintw (window, 3, width/2, "%d", highlightDay);
        // mvwprintw (window, 3, width/2 + 3, "%d", highlightMon);

        x = wday; y = 5;
        for (int i = 0; i < days[highlightMon]; i++) {
            // mvwprintw (window, 10, 3, "%d", wday);
            if (i == highlightDay) wattron (window, A_REVERSE);
//            if ()
            mvwprintw (window, y, x*4 + 4, "%d", i+1);
            wattroff (window, A_REVERSE);
            // x++;
            if ((x) % 7 == 0) {
                x = 1;
                y++;
            } else x++;
        }
        wrefresh (window);
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
        if (c == 'n') {
            highlightDay++;
            if (highlightDay > days[highlightMon] - 1) {
                wday = findWDay();

                highlightDay = 0;
                highlightMon++;
                if (highlightMon == 12) highlightMon = 0;
            }
        }
    } while (c != '\t');
}
//---------------------
int Calendar::findWDay() {
    unsigned a, y, m;
    a = (14 - highlightMon+1) / 12;
    y  = highlightYear - a;
    m = highlightMon+1 + (12 * a) - 2;
    // Gregorian:
    return (highlightDay+1 + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}
//---------------------
void Calendar::setUp () {
    height = termHeight/2;
    width = termWidth/2;
    window = newwin (height, width, 0, 0);
    box (window, 0, 0);
    printHead();
    highlightDay = 8;
    highlightMon = 8;
}
//---------------------
void Calendar::printHead () {
    mvwprintw (window, 1,3 , "Calendar:");
    for (int i = 1; i < width - 1; i++) {
        mvwprintw (window, 2, i, "-");
    }
}
//---------------------
void Calendar::reprint () {
    // wattron (window, A_REVERSE);
    printHead();
    // wattroff (window, A_REVERSE);
}
//---------------------
void Calendar::reprintBold () {
    wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "Calendar:");
    wattroff (window, A_REVERSE);
    for (int i = 1; i < width/2 - 1; i++) {
        mvwprintw (window, 2, i, "-");
    }
}