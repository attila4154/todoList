#pragma once

#include "curses.h"
#include "exceptions.h"
#include "task.h"
#include "ctime"
#include <fstream>

#define RED_BLACK 1
#define BLUE_BLACK 2

struct date_compare : public std::binary_function<tm, Task, bool> {
  bool operator () (const tm & left, const tm & right) const {
    if (left.tm_year != right.tm_year) return left.tm_year < right.tm_year;
    if (left.tm_mon != right.tm_mon) return left.tm_mon < right.tm_mon;
    return left.tm_mday < right.tm_mday;
  }
  /**
    return difference between today's date (left) and other in days
  */
  int difference (const tm & left, const tm & right) const {
    int days1 = days (left);
    int days2 = days (right);
    if (days1 > days2) return 0;
    ///return incremented value because today is counted as a whole day
    return days2 - days1 + 1;
  }

  private:
    int days(const tm & date) const {
      int days = (date.tm_year - 2020) * 365;
      for (int i = 0; i < date.tm_mon - 1; i++) days += daysInMonths[i];
      days += date.tm_mday;
      return days;
    }
    static int daysInMonths[12];
};

class Interface {
  public:
    static int termHeight;
    static int termWidth;
    static int day, mon, year;
    static tm date;

    void redrawHighlightedBox();
    void redrawBox();
    
    virtual void addTask (const Task & task);
    virtual void Run() = 0;
    virtual void printHeader() = 0;
    virtual void printHeaderBold() = 0;
    virtual void refresh();
    virtual ~Interface() {}
  
  protected:
    void clearRow(int row);
    void clearScreen ();

    WINDOW * window;
    int height;
    int width;
};