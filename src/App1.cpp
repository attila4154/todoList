#include "../lib/App.h"

void CApplication::start() {

    setUp();
    //--------------------
    highlight = 0;
    
    do {
        /// reprints "highlighted area"
        for (long unsigned i = 0; i < interfaces.size(); i++) {
            if ((int) i == highlight) interfaces[highlight]->reprintBold();
            else interfaces[i]->reprint();
            interfaces[i]->refresh();
        }
        
        try {
            interfaces[highlight]->Run();
            highlight ++;
            if (highlight > 2) highlight = 0;
        } catch (exit_exc & exit) {
            break;
        }

        // refresh();
    } while (1);
    endwin();
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
    */

    getmaxyx (stdscr, Interface::termHeight, Interface::termWidth);
    interfaces.push_back(new Calendar());
    interfaces.push_back(new ToDo());
    interfaces.push_back(new Done());

    refresh();

    for (auto interface: interfaces) {
        interface->refresh();
    }
}
//----------------------------
CApplication::~CApplication (){
    // dynamic_cast <ToDo *> (interface[1])->writeToFile();
    for (auto interface : interfaces) {
        delete interface;
    }
    endwin();
}
