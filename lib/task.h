#include <string>
#include <ctime>


struct Task {
    Task (const std::string & task, const std::string & theme, int day, int mon, int year, int hour);
    Task (const std::string & task, const std::string & theme, int day, int mon, int year);
    std::string task;
    std::string theme;

    int day() const;
    int mon() const ;
    int year() const;
  private:
    tm date;
};