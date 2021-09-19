#include "../lib/spent.h"

Spent::Spent() {
    height = termHeight/2;
    width = termWidth/3;
    window = newwin (height, width, height, 0);
    box (window, 0, 0);
    printHeader();
}
//----------------------
Spent::~Spent() {

}
//----------------------
void Spent::Run() {
    char c;
    int i = 3;
    do {
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
        mvwprintw (window, 2, i++, "%c", c);
        wrefresh (window);
    } while (c != '\t');
}
//----------------------
void Spent::printHeader() {
    mvwprintw (window, 1,3 , "Spent:");
}
//----------------------
void Spent::printHeaderBold() {
    wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "Spent:");
    wattroff (window, A_REVERSE);
}
//----------------------
// void Spent::readActivities () {

// }
//----------------------