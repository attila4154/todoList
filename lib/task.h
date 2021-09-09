#include <string>
#include <ctime>


struct Task {
    Task (const std::string & task, const std::string & theme, int day, int mon, int hour);
    Task (const std::string & task, const std::string & theme, int day, int mon);
  private:
    std::string task;
    std::string theme;
    tm date;
};