#include "../lib/App.h"

void CApplication::start() {
    setUp();
    windows[0] = calendar;
    windows[1] = todo;
    windows[2] = done;
    highlight = 0;
    do {
        wattron (windows[highlight], A_REVERSE);
        mvwprintw(calendar, 1,3 , "Calendar:");
        mvwprintw(todo, 1,3 , "ToDo:");
        mvwprintw(done, 1,3 , "Done:");
        wattroff (windows[highlight], A_REVERSE);
        wrefresh(calendar);
        wrefresh(todo);
        wrefresh(done);
        try {
            switch (highlight) {
                case 0:
                    runCalendar();
                    break;
                case 1:
                    runTodo();
                    break;
                case 2:
                    runDone();
                    break;
                default:
                break;
            }
            highlight ++;
            if (highlight > 2) highlight = 0;
        } catch (exit_exc) {
            break;
        }


        // mvwprintw(calendar, 2, 3, "%d", highlight);
        // refresh();
    } while (1);
    endwin();
}

void CApplication::setUp() {
    initscr();
    noecho();
    x = 0, y = 0;
    highlight = 0;
    getmaxyx (stdscr, height, width);
    setUpCal();
    setUpTodo();
    setUpDone();

    refresh();
    wrefresh (calendar);
    wrefresh (todo);
    wrefresh (done);
}

//----------------------------
void CApplication::setUpCal()
{
    calendar = newwin (height/2, width/2, 0, 0);
    // refresh();
    box (calendar,0,0);
    mvwprintw(calendar, 1,3 , "Calendar:");
}
//----------------------------
void CApplication::setUpTodo()
{
    todo = newwin (height/2, width/2, 0, width/2);
    // refresh();
    box (todo,0,0);
    mvwprintw(todo, 1,3 , "ToDo:");
}
//----------------------------
void CApplication::setUpDone()
{
    done = newwin (height/2, width, height/2, 0);
    // refresh();
    box (done,0,0);
    mvwprintw(done, 1,3 , "Done:");
}
//----------------------------
void CApplication::runCalendar(){
    char c;
    int i = 3;
    do {
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
        mvwprintw (calendar, 2, i++, "%c", c);
        wrefresh (calendar);
    } while (c != '\t');
    // highlight++;
}
//----------------------------
void CApplication::runDone(){
    char c;
    int i = 3;
    do {
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
        mvwprintw (done, 2, i++, "%c", c);
        wrefresh (done);
    } while (c != '\t');
    // highlight++;
}
//----------------------------
void CApplication::runTodo(){
    char c;
    int i = 3;
    do {
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
        mvwprintw (todo, 2, i++, "%c", c);
        wrefresh (todo);
    } while (c != '\t');
    // highlight++;
}
//----------------------------
