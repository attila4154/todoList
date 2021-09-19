#include <string>
#pragma once
#include <ctime>


struct Task {
    Task (const std::string & task, const std::string & theme, int day, int mon, int year, int hour);
    Task (const std::string & task, const std::string & theme, int day, int mon, int year);
    Task (const Task & other);
    Task operator = (const Task & other);
    std::string task;
    std::string theme;

    int day() const;
    int mon() const ;
    int year() const;
    tm date;
  private:
};