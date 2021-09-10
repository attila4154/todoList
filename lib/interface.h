#pragma once

#include "curses.h"
#include "exceptions.h"

class Interface {
  public:
    static int termHeight;
    static int termWidth;
    static int day, mon, year;
    
    virtual void setUp() = 0;
    virtual void Run() = 0;
    // virtual void reprint () = 0;
    // virtual void reprintBold () = 0;
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