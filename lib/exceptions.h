#pragma once

#include <exception>
// #include <ctime>
#include "task.h"

class exit_exc : public std::exception {

};

class date_change: public std::exception {
  public:
    date_change ();
    date_change (int day, int mon, int year);
    int day, mon, year;
};

class task_done : public std::exception {
  public:
    task_done () = delete;
    // task_done operator = (const Task & task) = delete;
    task_done (const Task & task);
    Task task;
};