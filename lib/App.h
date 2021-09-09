#pragma once

#include "interface.h"
#include "calendar.h"
#include "done.h"
#include "todo.h"

#include "exceptions.h"

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// #define LUI long unsigned int

class CApplication {
  private:
    std::vector<Interface*> interfaces;
    std::vector<std::string> list;
    // WINDOW * calendar;
    // WINDOW * todo;
    // WINDOW * done;
    // WINDOW * hours;
    // WINDOW * windows[3];
    // int height, width, x, y;
    int highlight;
    // int highlightTodo = -1;

//------------------
    // void runTodo();
    // void runDone();
    // void runCalendar();

    void setUp();
    // void setUpCal();
    // void setUpTodo();
    // void setUpDone();

    // void readToDo();
    // void writeToDo();
    
   public: 
    void start();
    ~CApplication ();
};