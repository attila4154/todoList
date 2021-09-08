#pragma once

#include "curses.h"
#include "exceptions.h"

class Interface {
  public:
    static int height;
    static int width;

    
    virtual void setUp() = 0;
    virtual void Run() = 0;
    virtual void reprint () = 0;
    virtual void reprintBold () = 0;
    void refresh();
    virtual ~Interface() {}
  
  protected:
    WINDOW * window;
};