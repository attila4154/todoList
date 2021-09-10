#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>




struct Task {
    Task (const std::string & task, const std::string & theme, int day, int mon, int year, int hour);
    Task (const std::string & task, const std::string & theme, int day, int mon, int year);
    std::string task;
    std::string theme;
  private:
    tm date;
};

Task::Task (const std::string & task, const std::string & theme, int day, int mon, int year, int hour) : 
            task(task), theme(theme) {
    date.tm_year = year;
    date.tm_mon  = mon;
    date.tm_mday = day;
    date.tm_hour = hour;
}
//-----------------------
Task::Task (const std::string & task, const std::string & theme, int day, int mon, int year) :
            task(task), theme(theme) {
    date.tm_year = year;
    date.tm_mon  = mon;
    date.tm_mday = day;
}
//-----------------------


int main () {
    // std::ifstream file ("/home/daniel/Documents/git/todoList/todo2.txt");
    // std::string line;
    // std::string task, theme;
    // int day, mon, year;
    // char c;
    // if (file.is_open()) {
    //     while (getline(file, line)) {
    //         if (line.size() > 0 && line[0] == '#') continue;
    //         std::istringstream str (line); 
    //         getline (str, theme, ',');
    //         getline (str, task, ',');
    //         str >> day >> c >> mon >> c >> year;
    //         std::cout << line << std::endl;
    //         std::cout << task << ' ' << theme << day << ' ' << mon << ' ' << year << std::endl;
    //         // list.emplace_back (Task {theme, task, day, mon, year} );
    //     }
    // }
    // file.close();
    char c = getchar();
    // std::cin >> c;
    std::cout << (int)c;
}