#include "../lib/task.h"

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
int Task::day() const{
    return date.tm_mday;
}
int Task::mon() const {
    return date.tm_mon;
}
int Task::year() const {
    return (date.tm_year - 2000) % 100;
}
//-----------------------