#include "../lib/App.h"

void CApplication::start() {

    setUp();

    //--------------------
    // windows[0] = calendar;
    // windows[1] = todo;
    // windows[2] = done;
    highlight = 0;
    
    do {
        ///reprints "highlighted area"
        for (int i = 0; i < interfaces.size(); i++) {
            if (i == highlight) interfaces[highlight]->reprintBold();
            else interfaces[i]->reprint();
            interfaces[i]->refresh();
        }
        // wattron (windows[highlight], A_REVERSE);
        // mvwprintw(calendar, 1,3 , "Calendar:");
        // mvwprintw(todo, 1,3 , "ToDo:");
        // mvwprintw(done, 1,3 , "Done:");
        // wattroff (windows[highlight], A_REVERSE);
        
        try {
            interfaces[highlight]->Run();
            highlight ++;
            if (highlight > 2) highlight = 0;
        } catch (exit_exc & exit) {
            break;
        }


        mvwprintw(calendar, 2, 3, "%d", highlight);
        mvwprintw(calendar, 3, 3, "%d", list.size());
        refresh();
    } while (1);
    endwin();
}

void CApplication::setUp() {
    initscr();
    noecho();
    
    interfaces.push_back(new Calendar());
    interfaces.push_back(new ToDo());
    interfaces.push_back(new Done());

    getmaxyx (stdscr, height, width);
    Interface::height = height;
    Interface::width = width;

    //prepare each of the interfaces:
    for (auto interface: interfaces) {
        interface->setUp();
    }

    highlight = 0;

    int height, width;

    refresh();

    for (auto interface: interfaces) {
        interface->refresh();
    }

    // wrefresh (calendar);
    // wrefresh (todo);
    // wrefresh (done);
    // setUpCal();
    // setUpTodo();
    // setUpDone();

}

//----------------------------
// void CApplication::setUpCal()
// {
//     calendar = newwin (height/2, width/2, 0, 0);
//     // refresh();
//     box (calendar,0,0);
//     mvwprintw(calendar, 1,3 , "Calendar:");
// }
//----------------------------
// void CApplication::setUpTodo()
// {
//     todo = newwin (height/2, width/2, 0, width/2);
//     // refresh();
//     box (todo,0,0);
//     mvwprintw(todo, 1,3 , "ToDo:");
//     readToDo();
//     writeToDo();
// }
//----------------------------
// void CApplication::setUpDone()
// {
//     done = newwin (height/2, width, height/2, 0);
//     // refresh();
//     box (done,0,0);
//     mvwprintw(done, 1,3 , "Done:");
// }
//----------------------------
// void CApplication::runCalendar(){
//     char c;
//     int i = 3;
//     do {
//         c = getch();
//         if (c == 'q' || c == 'Q') throw exit_exc();
//         mvwprintw (calendar, 2, i++, "%c", c);
//         wrefresh (calendar);
//     } while (c != '\t');
//     // highlight++;
// }
//----------------------------
// void CApplication::runDone(){
//     char c;
//     int i = 3;
//     do {
//         c = getch();
//         if (c == 'q' || c == 'Q') throw exit_exc();
//         mvwprintw (done, 2, i++, "%c", c);
//         wrefresh (done);
//     } while (c != '\t');
//     // highlight++;
// }
//----------------------------
// void CApplication::runTodo(){
    // char c;
    // int i = 3;
    // highlightTodo = 0;
    // do {
    //     c = getch();
    //     if (c == 'q' || c == 'Q') throw exit_exc();
    //     else if (c == 'n') {
    //         highlightTodo++;
    //         if (highlightTodo >= list.size()) highlightTodo = 0;
    //     }
    //     else if (c == '-') {
    //         mvwprintw (done, 2, 3, "do you want to delete thing?");
    //         wrefresh(done);
    //         c = getch();
    //         if (c == 'y' || c == 'Y') list.erase (list.begin() + highlightTodo);
    //     }
    //     else if (c == '+') {
    //         std::string toAdd;
    //         int i = 3;
    //         int ifadd = 1;
    //         do {
    //             c = getch();
    //             if (c == 27) {
    //                 ifadd = 0;
    //                 break;
    //             }
    //             mvwprintw (done, 2, i++, "%c", c);
    //             wrefresh(done);
    //             toAdd.push_back(c);
    //         } while (c != '\n');
    //         if (ifadd) list.push_back(toAdd);
    //     }
    //     writeToDo();
    //     wrefresh(todo);
    // } while (c != '\t');
    // highlightTodo = -1;
    // writeToDo();
    // wrefresh(todo);
    // highlight++;
// }
//----------------------------
CApplication::~CApplication (){
    for (auto interface : interfaces) {
        delete interface;
    }
    endwin();
}
