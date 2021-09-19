#pragma once

#include "curses.h"
#include "exceptions.h"
#include "task.h"
#include "ctime"


class Interface {
  public:
    static int termHeight;
    static int termWidth;
    static int day, mon, year;
    static tm date;
    
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