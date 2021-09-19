#include "../lib/todo.h"

ToDo::ToDo() {
    /*
        setting up dimensions of todoList
    */
    height = termHeight/2;
    width = 2 * termWidth/3;
    dateWidth = 12;
    themeWidth = (width - dateWidth)/2;
    taskWidth = width - themeWidth - dateWidth;
    /*
        setting up dimensions of addList
    */
    addHeight = 5;
    addWidth = width;

    window = newwin (height, width, 0, width/2);
    box (window,0,0);
    mvwprintw(window, 1,3 , "ToDo:");
    
    add = newwin (addHeight, addWidth, height, width/2);
    box (add, 0,0);
    mvwprintw (add, 1, 2, "Add:");
    
    readToDo();
    writeToDo();
}

//---------------------
ToDo::~ToDo() {
    writeToFile();
}
//---------------------
void ToDo::Run () {
    char c;
    highlight = 0;
    do {
        writeToDo();
        printHeader();
        c = getch();
        switch (c) {
            case 'q':
            case 'Q':
                throw exit_exc();
                break;
            case 'n':
                changeHighlight();
                break;
            case '-':
                deleteTask();
                break;
            case 'd':
            case 'D':
                moveTask();
                break;
        }
    } while (c != '\t');
    highlight = -1;
    writeToDo();
    wrefresh(window);
    ///next interface is not "done" but "add" which is not a different class:
    addRun();
}
//---------------------
void ToDo::addRun() {
    wattron(add, A_REVERSE);
    mvwprintw (add, 1, 2, "Add:");
    wattroff(add, A_REVERSE);
    wrefresh(add);
    /*
        1.taskName
        2.theme.
        3.due date (optionally)
    */
    char c;
    do {
        clearAddRow (1);
        std::string name;
        std::string theme;
        try {
            mvwprintw (add, 1, 8, "enter task name:");
            wrefresh(add);
            name = readString ();
            clearAddRow (1);
            clearAddRow (2);
            mvwprintw (add, 1, 8, "enter theme name:");
            wrefresh(add);
            theme = readString ();
            clearAddRow (1);
            clearAddRow (2);
            mvwprintw (add, 1, 8, "enter due date (n if no date)");
            wrefresh(add);
            c = getch ();
            if (c == 'n' || c == 'N') 
                list.emplace_back (Task {name, theme, 0, 0, 0});
            else {
                int day = 0, mon = 0, year = 0;
                readDate (day, mon, year);
                list.emplace_back (Task {name, theme, day, mon, year});
            }

        } catch (exit_exc & e) {
            break;
        }
    } while (1);
    mvwprintw(add, 1, 2, "Add:");
    clearAddRow (1);
    clearAddRow (2);
    wrefresh(add);
}
//---------------------
void ToDo::deleteTask () {
    if (list.size()) {
        char c;
        mvwprintw (window, height - 2, 3, "do you want to delete this task?");
        wrefresh (window);
        do {
            c = getch();
            if (c == 'y' || c == 'Y') list.erase (list.begin() + highlight);
            if (c == 'n' || c == 'N') break;
        } while (!(c == 'y' || c == 'y' || c == 'n' || c == 'N'));
        writeToDo();
    }
    else {
        mvwprintw (window, height - 2, 3, "nothing to delete");
    }
        wrefresh (window);
}
//---------------------
void ToDo::moveTask () {
    if (list.size()) {
        char c;
        mvwprintw (window, height - 2, 3, "have you accomplished this task?");
        wrefresh (window);
        do {
            c = getch();
            if (c == 'y' || c == 'Y') {
                // task_done done = new task_done (list[highlight]);
                // list.erase (list.begin() + highlight);
                // mvwprintw (add, 2, 3, "%s %s" ,list[highlight].task, list[highlight].theme);
                wrefresh (add);
                throw task_done (list[highlight]);
            }
            if (c == 'n' || c == 'N') break;
        } while (!(c == 'y' || c == 'y' || c == 'n' || c == 'N'));
        writeToDo();
    }
    else {
        mvwprintw (window, height - 2, 3, "no tasks");
    }
        wrefresh (window);
}
//---------------------
void ToDo::changeHighlight () {
    if (highlight++ >= (int) list.size()-1) highlight = 0;
}
//---------------------
std::string ToDo::readString () {
    // for (int i = 1; i < addWidth; i++) mvwprintw (add, 2, i, " ");
    // char c;
    // std::string read;
    // do {
    //     c = getch();
    //     if (c == '\n') return read;
    //     if (c == 27 || c == '\t') throw exit_exc();
    //     if (c == 127) {
    //         if (read.size()) {
    //             mvwprintw (add, 2, read.size()+1, " ");
    //             read.pop_back();
    //             wrefresh(add);
    //         }
    //         continue;
    //     }
    //     read.push_back(c);
    //     mvwprintw (add, 2, read.size () + 1, "%c", c);
    //     wrefresh(add);
    // } while (1);

    clearAddRow (2);
    char c;
    std::string read;
    wmove (add, 2, 2);
    wrefresh (add);
    curs_set (1);
    do {
        c = getch();
        if (c == '\n') return read;
        if (c == 27 || c == '\t') throw exit_exc();
        if (c == 127) {
            if (read.size()) {
                wprintw (add, "\b \b");
                wrefresh (add);
                read.pop_back();
            }
            continue;
        }
        read.push_back (c);
        wprintw (add, "%c", c);
        wrefresh (add);
    } while (1);
    curs_set (0);
}
//---------------------
void ToDo::readDate (int & day, int & mon, int & year) {
    mvwprintw (add, 2, 2, "enter date [dd mm yyyy]");
    wrefresh (add);
    std::string date = readString ();
    std::stringstream str (date);
    str >> day >> mon >> year;
}
//---------------------
void ToDo::clearAddRow (int row) {
    int i = row != 1 ? 1 : 8;
    for ( ; i < addWidth - 1; i++) mvwprintw (add, row, i, " ");
}
//---------------------
void ToDo::clearAdd () {
    for (int i = 1; i < height - 1; i++)
        clearAddRow (i);
}
//---------------------
void ToDo::refresh() {
    wrefresh (window);
    wrefresh (add);
}
//---------------------
void ToDo::printHeader () {
    for (int i = 1; i < width - 1; i++) mvwprintw (window, 2, i, "-");
    mvwprintw (window, 1,3 , "Tasks:");
    for (int i = 1; i < height - 1; i++) mvwprintw (window, i, width - dateWidth, "|");
    for (int i = 1; i < height - 1; i++) mvwprintw (window, i, width - dateWidth - themeWidth, "|");
    mvwprintw (window, 2, taskWidth, "+");
    mvwprintw (window, 2, taskWidth + themeWidth, "+");
    mvwprintw (window, 1, taskWidth + 3, "Themes:");
    mvwprintw (window, 1, taskWidth + themeWidth + 2, "DueDate:");
    wrefresh (window);
}
//---------------------
void ToDo::printHeaderBold () {
    wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "ToDo:");
    wattroff (window, A_REVERSE);
}
//---------------------
void ToDo::readToDo(){
    ///to add: exceptions
    std::ifstream file ("/home/daniel/Documents/git/todoList/todo2.txt");
    std::string line;
    std::string task, theme;
    int day, mon, year;
    char c;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.size() > 0 && line[0] == '#') continue;
            std::istringstream str (line);
            getline (str, theme, ',');
            getline (str, task, ',');
            str >> day >> c >> mon >> c >> year;
            list.emplace_back (Task {task, theme, day, mon, year} );
        }
    }
    file.close();
}
//----------------------------
void ToDo::writeToDo() {
    for (int i = 3; i < height - 1; i ++) {
        clearRow(i);
    }
    int i = 3;
    for (auto const & x : list) {
        if (highlight == i - 3) wattron (window, A_REVERSE);
        mvwprintw (window, i, 3 , "%d.%s", i-2, x.task.data());
        wattroff (window, A_REVERSE);
        mvwprintw (window, i, taskWidth+2, "%s", x.theme.data());
        if (x.day()) 
            mvwprintw (window, i, taskWidth + themeWidth + 2, "%02d.%02d.%02d", 
                   x.day(), x.mon(), x.year());
        else mvwprintw (window, i, taskWidth + themeWidth + 2, "--------");
        i++;
    }
    // wrefresh (window);
}
//----------------------------
void ToDo::writeToFile() {
    // std::ofstream file ("/home/daniel/Documents/git/todoList/todo.txt");
    // std::string line;
    // if (file.is_open()) {
    //     for (const auto & line : list)
    //         file << line << std::endl; 
    // }
    // file.close();
}