#include "../lib/calendar.h"


//=====================
Calendar::Calendar() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    /*
        tm_day returns month day from 1 to 31
        tm_mon returns month from 0 to 11
        tm_year returns year since 1900
    */
    highlightDay = now->tm_mday - 1;
    highlightMon = now->tm_mon;
    highlightYear = now->tm_year + 1900;
    Interface::day = highlightDay + 1;
    Interface::mon = highlightMon + 1;
    Interface::year = highlightYear;
    Interface::date.tm_mday = Interface::day;
    Interface::date.tm_mon = Interface::mon;
    Interface::date.tm_year = Interface::year;

    height = termHeight/2;
    width = termWidth/3;
    window = newwin (height, width, 0, 0);
    box (window, 0, 0);
    printHeader();
}
//---------------------
Calendar::~Calendar() {

}
//---------------------
void Calendar::Run () {
    wday = findFirstDay();
    char c;
    /* y is row coordinates, x is column coordinates,
       starts with the first day of the month 
    */
    int y = 5, x = wday;
    int daysGap = 4, leftGap = 4;
    bool dateChanged = false;
    do {
        clearScreen();
        printMonth ();
        x = wday; y = 5;
        if (!x) x = 7;
        for (int i = 0; i < days[highlightMon]; i++) {
            if (i == highlightDay) wattron (window, A_REVERSE);
            mvwprintw (window, y, x*daysGap + leftGap, "%d", i+1);
            wattroff (window, A_REVERSE);
            if (x % 7 == 0) {
                x = 1;
                y++;
            } else x++;
        }
        wrefresh (window);
        c = getch();
        switch (c) {
            case 'q':
            case 'Q':
                throw exit_exc();
            case 'h': {
                highlightDay--;
                dateChanged = true;
                break;
            }
            case 'l': {
                highlightDay++;
                dateChanged = true;
                break;
            }
            case 'j': {
                highlightDay += 7;
                dateChanged = true;
                break;
            }
            case 'k': {
                highlightDay -= 7;
                dateChanged = true;
                break;
            }
        }
        if (highlightDay > days[highlightMon] - 1) {
            highlightDay -= days[highlightMon];
            highlightMon ++;
            if (highlightMon > 11) {
                highlightMon = 0;
                highlightYear++;
            }
            wday = findFirstDay();
        }
        if (highlightDay < 0) {
            highlightMon --;
            if (highlightMon < 0) {
                highlightMon = 11;
                highlightYear--;
            }
            highlightDay += days[highlightMon];
            wday = findFirstDay();
        }
        if (dateChanged) throw date_change(highlightDay + 1, highlightMon + 1, highlightYear);
    } while (c != '\t');
}
//---------------------
void Calendar::printMonth() {
    mvwprintw (window, 3, width/6, "%s", months[highlightMon].data());
}
//---------------------
int Calendar::findFirstDay() {
    unsigned a, y, m;
    a = (14 - highlightMon+1) / 12;
    y  = highlightYear - a;
    m = highlightMon+1 + (12 * a) - 2;
    // Gregorian:
    /*
        1 for the first day of the each month
        returns 1-6 for mo - sa, 0 for su
    */ 
    return (1 + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}
//---------------------
void Calendar::printHeader() {
    mvwprintw (window, 1,3 , "Calendar:");
    for (int i = 1; i < width - 1; i++) {
        mvwprintw (window, 2, i, "-");
    }
}
//---------------------
void Calendar::printHeaderBold() {
    wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "Calendar:");
    wattroff (window, A_REVERSE);
    for (int i = 1; i < width/2 - 1; i++) {
        mvwprintw (window, 2, i, "-");
    }
}