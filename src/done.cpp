#include "../lib/done.h"

Done::Done () {
    height = termHeight/2 - 5;
    width = 2*termWidth/3;
    window = newwin (height, width, height +10, termWidth/3);
    box (window, 0, 0);
    mvwprintw (window, 1,3 , "Done:");

    readDone();
}
//----------------------
Done::~Done () {
    writeDone();
}
//----------------------
void Done::printHeader() {
    for (int i = 2; i < height - 1; i++)
            clearRow(i);
    mvwprintw (window, 1,3 , "Done:");
    mvwprintw (window, 1, 10, "%02d.%02d.%02d", Interface::day, Interface::mon, Interface::year);
    auto pos = tasks.equal_range (Interface::date);
    int i = 3;

    if (pos.first != pos.second) {

    for ( ; pos.first != pos.second ; ++pos.first) {
        mvwprintw (window, i, 3, "* %s %s", pos.first->second.task.data(), pos.first->second.theme.data());
        i++;
    }
    } 
    else {
        mvwprintw (window, 2, 3, "Nothing done this day");
    }

    wrefresh (window);
}
//----------------------
void Done::printHeaderBold() {
    wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "Done:");
    wattroff (window, A_REVERSE);
    auto pos = tasks.equal_range (Interface::date);
    int i = 3;

    if (pos.first != pos.second) {

        for ( ; pos.first != pos.second ; ++pos.first) {
            mvwprintw (window, i, 3, "* %s %s", pos.first->second.task.data(), pos.first->second.theme.data());
            i++;
        }
    } 
    else {
        mvwprintw (window, 2, 3, "Nothing done yet");
    }

    wrefresh (window);
}
//----------------------
void Done::Run() {
    char c;
    do {
        c = getch();
        if (c == 'q' || c == 'Q') throw exit_exc();
    } while (c != '\t');
}
//----------------------
void Done::addTask (const Task & task) {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    tm date;
    date.tm_mday = now->tm_mday;
    date.tm_mon = now->tm_mon+1;
    date.tm_year = now->tm_year + 1900;
    tasks.insert ({date, task});
}
//----------------------
void Done::readDone() {
    std::ifstream file ("/home/daniel/Documents/git/todoList/done.csv");
    std::string line, name, theme;
    int day, mon, year;
    char c;
    tm date;
    if (file.is_open() ){
        while (getline(file, line)) {
            if (line.size() > 0 && line[0] == '#') continue;
            std::istringstream str (line);
            str >> date.tm_mday >> c >> date.tm_mon >> c >> date.tm_year >> c;
            getline (str, theme, ',');
            getline (str, name, ',');
            str >> day >> c >> mon >> c >> year;
            tasks.insert ({date, Task {theme, name, day, mon, year}});
        }

        file.close();
    }
}
//----------------------
void Done::writeDone() {
    std::ofstream file ("/home/daniel/Documents/git/todoList/done.csv");
    if (file.is_open()) {
        for (auto const & task : tasks) {
            auto const & t = task.second;
            file << task.first.tm_mday << ',' << task.first.tm_mon << ',' << task.first.tm_year << ',';
            file << t.theme << ',' << t.task << ',' << t.day() << ',' <<
            t.mon() << ',' << t.year() << '\n';
        }
        file.close();
    }
}
//----------------------