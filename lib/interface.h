#pragma once

#include "curses.h"
#include "exceptions.h"

class Interface {
  public:
    static int termHeight;
    static int termWidth;
    
    virtual void setUp() = 0;
    virtual void Run() = 0;
    virtual void reprint () = 0;
    virtual void reprintBold () = 0;
    void refresh();
    virtual ~Interface() {}
  
  protected:
    void clearRow(int row);

    WINDOW * window;
    int height;
    int width;
};