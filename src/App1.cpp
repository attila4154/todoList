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
            highlight--;
            if (highlight < 0) highlight = interfaces.size() - 1;
        }

    } while (1);
}

void CApplication::setUp() {
    initscr();
    noecho();
    cbreak();
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
