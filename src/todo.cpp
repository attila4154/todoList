#include "../lib/todo.h"

ToDo::ToDo() {

}
//---------------------
ToDo::~ToDo() {

}
//---------------------
void ToDo::Run () {
    char c;
    int i = 3;
    highlight = 0;
    do {
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
        else if (c == 'n') {
            highlight++;
            if (highlight >= list.size()) highlight = 0;
        }
        else if (c == '-') {
            //change 8th row to half or sth
            mvwprintw (window, 8, 3, "do you want to delete thing?");
            wrefresh (window);
            c = getch();
            if (c == 'y' || c == 'Y') list.erase (list.begin() + highlight);
        }
        else if (c == '+') {
            std::string toAdd;
            int i = 3;
            int ifadd = 1;
            do {
                c = getch();
                if (c == 27) {
                    ifadd = 0;
                    break;
                }
                mvwprintw (window, 2, i++, "%c", c);
                wrefresh(window);
                toAdd.push_back(c);
            } while (c != '\n');
            if (ifadd) list.push_back(toAdd);
        }
        writeToDo();
        wrefresh(window);
    } while (c != '\t');
    highlight = -1;
    writeToDo();
    wrefresh(window);
}
//---------------------
void ToDo::setUp () {
    window = newwin (height/2, width/2, 0, width/2);
    box (window,0,0);
    mvwprintw(window, 1,15 , "%d  %d", Interface::height, Interface::width);
    mvwprintw(window, 1,3 , "ToDo:");
    readToDo();
    writeToDo();
}
//---------------------
void ToDo::reprint () {
    mvwprintw (window, 1,3 , "ToDo:");
}
void ToDo::reprintBold () {
    wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "ToDo:");
    wattroff (window, A_REVERSE);
}
//---------------------
void ToDo::readToDo(){
    std::ifstream file ("/home/daniel/Documents/git/todoList/todo.txt");
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            list.push_back(line);
        }
    }

    file.close();
}
//----------------------------
void ToDo::writeToDo() {
    // werase (todo);
    int i = 2;
    for (auto const & x : list) {
        if (highlight == i - 2) wattron (window, A_REVERSE);
        mvwprintw (window, i++, 3 , "%d.%s", i-2, x.data());
        wattroff (window, A_REVERSE);
    }
}