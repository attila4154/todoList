#include "../lib/App.h"

void CApplication::start() {

    setUp();
    
    do {
        /// reprints "highlighted area"
        for (long unsigned i = 0; i < interfaces.size(); i++) {
            if ((int) i == highlight) interfaces[highlight]->printHeaderBold();
            else interfaces[i]->printHeader();
            interfaces[i]->refresh();
        }
        
        try {
            interfaces[highlight++]->Run();
            if (highlight > 3) highlight = 0;
        } catch (exit_exc & exit) {
            break;
        } catch (date_change & change) {
            Interface::day = change.day;
            Interface::mon = change.mon;
            Interface::year = change.year;
            Interface::date.tm_mday = change.day;
            Interface::date.tm_mon = change.mon;
            Interface::date.tm_year = change.year;
            highlight = 0;
        } catch (task_done & done) {
            interfaces[2]->addTask (done.task);
            highlight = 1;
        }

    } while (1);
}

void CApplication::setUp() {
    initscr();
    noecho();
    cbreak();
    curs_set (0);
    highlight = 0;
    
    /* create instances for interface:
        1.calendar
        2.todo list 
        3.done
        4.spent
    */

    getmaxyx (stdscr, Interface::termHeight, Interface::termWidth);
    interfaces.push_back(new Calendar());
    interfaces.push_back(new ToDo());
    interfaces.push_back(new Done());
    interfaces.push_back(new Spent());

    refresh();

    for (auto interface: interfaces) {
        interface->refresh();
    }
}
//----------------------------
CApplication::~CApplication () {
    for (auto interface : interfaces) {
        delete interface;
    }
    endwin();
}
