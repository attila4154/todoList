#include "../lib/done.h"

Done::Done () {
    height = termHeight/2 - 5;
    width = 2*termWidth/3;
    window = newwin (height, width, height +10, termWidth/3);
    box (window, 0, 0);
    mvwprintw (window, 1,3 , "Done:");
}
//----------------------
Done::~Done () {
    
}
//----------------------
void Done::printHeader() {
    mvwprintw (window, 1,3 , "Done:");
    mvwprintw (window, 1, 10, "%02d.%02d.%02d", Interface::day, Interface::mon, Interface::year);
    auto pos = tasks.equal_range (Interface::date);
    int i = 2;

    if (pos.first != pos.second) {

    for ( ; pos.first != pos.second ; ++pos.first) {
        mvwprintw (window, i, 3, "%s %s", pos.first->second.task.data(), pos.first->second.theme.data());
        i++;
    }
    } else {
        for (int i = 2; i < height - 1; i++)
            clearRow(i);
    }
    
    mvwprintw (window, 1, width - 2, "%d", tasks.size());
    wrefresh (window);
}
//----------------------
void Done::printHeaderBold() {
    wattron (window, A_REVERSE);
    mvwprintw (window, 1,3 , "Done:");
    wattroff (window, A_REVERSE);
    auto pos = tasks.lower_bound (Interface::date);
    int i = 2;

    for ( ; pos != tasks.end(); pos++) {
        mvwprintw (window, i, 3, "%s", pos->second.task);
        i++;
    }
    mvwprintw (window, 1, width - 2, "%d", tasks.size());
}
//----------------------
void Done::Run() {
    char c;
    int i = 3;
    do {
        c = getch();
        // if (c == 'q' || c == 'Q') throw exit_exc();
        // mvwprintw (window, 2, i++, "%c", c);
        // wrefresh (window);
    } while (c != '\t');
}
//----------------------
void Done::addTask (const Task & task) {
    // mvwprintw (window, height - 2, 3, "%s %s", task.task, task.theme.date);
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    tm date;
    date.tm_mday = now->tm_mday;
    date.tm_mon = now->tm_mon+1;
    date.tm_year = now->tm_year + 1900;
    tasks.insert ({date, task});
}
//----------------------