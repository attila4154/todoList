#include "../lib/todo.h"

ToDo::ToDo() {
    setUp();
}
//---------------------
ToDo::~ToDo() {
    writeToFile();
}
//---------------------
void ToDo::Run () {
    char c;
    // int i = 3;
    highlight = 0;
    do {
        writeToDo();
        printHeader();
        wrefresh(window);
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
        else if (c == 'n') {
            highlight++;
            if (highlight >= (int) list.size()) highlight = 0;
        }
        else if (c == '-') {
            //change 8th row to half or sth
            mvwprintw (window, height - 2, 3, "do you want to delete thing?");
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
            // if (ifadd) list.push_back(toAdd);
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
        3.due date(optionally)

    */
    char c;
    do {
        std::string name;
        std::string theme;
        try {
            mvwprintw (add, 1, 8, "enter task name:");
            wrefresh(add);
            name = readString ();
            // for (int i = 8; i < addWidth - 1; i ++) mvwprintw (add,1,i," ");
            clearAddRow (1);
            clearAddRow (2);
            mvwprintw (add, 1, 8, "enter theme name:");
            wrefresh(add);
            theme = readString ();
        } catch (exit_exc & e) {
            break;
        }
        list.emplace_back (Task {name, theme, 0, 0, 0});

        c = getch();
    } while (c != '\t');
    mvwprintw(add, 1, 2, "Add:");
    // for (int i = 8; i < addWidth - 1; i ++) mvwprintw (add,1,i," ");
    clearAddRow (1);
    clearAddRow (2);
    wrefresh(add);
}
//---------------------
std::string ToDo::readString () {
    for (int i = 1; i < addWidth; i++) mvwprintw (add, 2, i, " ");
    char c;
    std::string read;
    do {
        c = getch();
        if (c == '\n') return read;
        if (c == 27 || c == '\t') throw exit_exc();
        if (c == 127) {
            if (read.size()) {
                mvwprintw (add, 2, read.size()+1, " ");
                read.pop_back();
                wrefresh(add);
            }
            continue;
        }
        read.push_back(c);
        mvwprintw (add, 2, read.size () + 1, "%c", c);
        // mvwprintw (add, 3, read.size () + 1, "%d", c);
        wrefresh(add);
    } while (1);
}
//---------------------
void ToDo::clearAddRow (int row) {
    int i = row != 1 ? 1 : 8;
    for ( ; i < addWidth - 1; i++) mvwprintw (add, row, i, " ");
}
//---------------------
void ToDo::refresh() {
    wrefresh(window);
    wrefresh(add);
}
//---------------------
void ToDo::setUp () {
    height = termHeight/2;
    width = 2 * termWidth/3;
    dateWidth = 12;
    themeWidth = (width - dateWidth)/2;
    taskWidth = width - themeWidth - dateWidth;

    addHeight = 5;
    addWidth = width;
    add = newwin (addHeight, addWidth, height, width/2);
    box (add, 0,0);
    mvwprintw (add, 1, 2, "Add:");


    window = newwin (height, width, 0, width/2);
    box (window,0,0);
    mvwprintw(window, 1,3 , "ToDo:");
    readToDo();
    writeToDo();
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
    // werase (todo);
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