#pragma once

#include <ncurses.h>
#include <iostream>

class exit_exc : public std::exception {
    
};

class CApplication {
  private:
    WINDOW * calendar;
    WINDOW * todo;
    WINDOW * done;
    WINDOW * hours;
    WINDOW * windows[3];
    int height, width, x, y;
    int highlight;

//------------------
    void runTodo();
    void runDone();
    void runCalendar();

    void setUp();
    void setUpCal();
    void setUpTodo();
    void setUpDone();
    
   public: 
    void start();
};