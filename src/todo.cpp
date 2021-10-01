#include "../lib/todo.h"

ToDo::ToDo() {
    /*
        setting up dimensions of todoList
    */
    height = termHeight/2;
    width = 2 * termWidth/3;
    dateWidth = 16;
    themeWidth = (width - dateWidth)/2;
    taskWidth = width - themeWidth - dateWidth;
    /*
        setting up dimensions of addList
    */
    addHeight = 5;
    addWidth = width;

    window = newwin (height, width, 0, width/2);
    box (window,0,0);
    
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
        // wrefresh(window);
        c = getch();
        switch (c) {
            case 'q':
            case 'Q':
                throw exit_exc();
                break;
            case 'n':
            case 'N':
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
    box (window, 0, 0);
    writeToDo();
    printHeader();
    ///next interface is not "done" but "add" which is not a different class:
    addRun();
}
//---------------------
void ToDo::addRun() {
    wattron(add, COLOR_PAIR(BLUE_BLACK));
    box(add, 0, 0);
    wattroff(add,COLOR_PAIR(BLUE_BLACK));
    // wattron(add, A_REVERSE);
    // mvwprintw (add, 1, 2, "Add:");
    // wattroff(add, A_REVERSE);
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
            writeToDo();
            printHeader();
        } catch (exit_exc & e) {
            break;
        }
    } while (1);
    mvwprintw(add, 1, 2, "Add:");
    clearAddRow (1);
    clearAddRow (2);
    box (add, 0, 0);     
    wrefresh(add);
}
//---------------------
void ToDo::deleteTask () {
    if (list.size()) {
        char c;
        mvwprintw (window, height - 2, 3, "do you want to delete this task? %d", highlight);
        wrefresh (window);
        do {
            mvwprintw (add, 2, 3, "%s %s",
            (list.begin()+highlight)->task.data(), (list.begin()+highlight)->theme.data());
            wrefresh (add);
            c = getch();
            if (c == 'y' || c == 'Y') {
                list.erase (list.begin() + highlight);
                highlight--;
                if (highlight < 0) highlight = 0;
            }   
            if (c == 'n' || c == 'N') break;
        } while (!(c == 'y' || c == 'y' || c == 'n' || c == 'N'));
    }
    else {
        mvwprintw (window, height - 2, 3, "nothing to delete");
    }
        wrefresh (window);
}
//---------------------
void ToDo::deleteFromVector() {

    for (int i = highlight; i < list.size() - 1; i++) {
        // std::swap (list[i], list[i+1]);
        Task & temp = list[i+1];
        list[i+1] = list[i];
        list[i] = temp;
    }
    list.pop_back();
    // list[highlight].task = list[highlight].task + "deleted";
    // list[highlight] = Task ();
    // list[highlight].task = "";
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
                task_done done {list[highlight]};
                list.erase (list.begin() + highlight);
                highlight--;
                if (highlight < 0) highlight = 0;
                throw task_done (done);
            }
            if (c == 'n' || c == 'N') break;
        } while (!(c == 'y' || c == 'y' || c == 'n' || c == 'N'));
        // writeToDo();
    }
    else {
        mvwprintw (window, height - 2, 3, "no tasks");
    }
        wrefresh (window);
}
//---------------------
void ToDo::changeHighlight () {
    highlight++;
    if (highlight >= (int) list.size()) highlight = 0;
}
//---------------------
std::string ToDo::readString () {
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
    mvwprintw (window, 1, 3, "Tasks:");
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
    date_compare compare;
    for (int i = 1; i < height - 1; i ++) {
        clearRow(i);
    }
    int i = 0;
    for (auto const & x : list) {
        /**
            while printing highlihgted element, print it with A_REVERSE highlight
        */
        if (highlight == i) wattron (window, A_REVERSE);
        mvwprintw (window, i + 3, 3 , "%d.%s", i+1, x.task.data());
        wattroff (window, A_REVERSE);
        mvwprintw (window, i + 3, taskWidth+2, "%s", x.theme.data());
        if (x.day()) {
            if (compare(x.date, Interface::date)) wattron (window, COLOR_PAIR(COLOR_RED));
            mvwprintw (window, i + 3, taskWidth + themeWidth + 2, "%02d.%02d.%02d", 
                   x.day(), x.mon(), x.year());
            wattroff (window, COLOR_PAIR(COLOR_RED));
            wprintw (window, " (%d)", compare.difference(Interface::date, x.date));
        }
        else mvwprintw (window, i + 3, taskWidth + themeWidth + 2, "--------");
        i++;
    }

    // int h = 3;
    // for (int i = 0; i < list.size();i ++) {
    //     // h = i > heigth - 1 ? 
    //     if (highlight == i) wattron (window, A_REVERSE);
    //     mvwprintw (window, i + 3, 3 , "%d.%s", i+1, list[i].task.data());
    //     wattroff (window, A_REVERSE);
    //     mvwprintw (window, i + 3, taskWidth+2, "%s", list[i].theme.data());
    //     if (list[i].day()) {
    //         if (compare(list[i].date, Interface::date)) wattron (window, COLOR_PAIR(COLOR_RED));
    //         mvwprintw (window, i + 3, taskWidth + themeWidth + 2, "%02d.%02d.%02d", 
    //                list[i].day(), list[i].mon(), list[i].year());
    //         wattroff (window, COLOR_PAIR(COLOR_RED));
    //         wprintw (window, " (%d)", compare.difference(Interface::date, list[i].date));
    //     }
    //     else mvwprintw (window, i + 3, taskWidth + themeWidth + 2, "--------");
    // }
}
//----------------------------
void ToDo::writeToFile() {
    std::ofstream file ("/home/daniel/Documents/git/todoList/todo2.txt");
    if (file.is_open()) {
        for (const auto & element : list){
            file << element.theme << ',' << element.task << ','<< element.day()  << ',' << element.mon() <<
            ',';
            if (element.year()) file << element.year() + 2000;
            else file << 0;
            file << '\n';
        }
        file.close();
    }
}