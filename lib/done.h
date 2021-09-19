#pragma once

#include "interface.h"
#include <map>

struct date_compare : public std::binary_function<tm, Task, bool> {
  bool operator () (const tm & left, const tm & right) const {
    if (left.tm_year != right.tm_year) return left.tm_year < right.tm_year;
    if (left.tm_mon != right.tm_mon) return left.tm_mon < right.tm_mon;
    return left.tm_mday < right.tm_mday;
  }
};

class Done : public Interface {
  public:
    Done ();
    ~Done();
    void Run () override;
    void printHeader() override;
    void printHeaderBold() override;
    void addTask (const Task & task) override;
  private:
    std::multimap <tm, Task, date_compare> tasks;
};
