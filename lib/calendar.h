#pragma once

#include "interface.h"
#include <string>
#include <ctime>
#include <chrono>

class Calendar : public Interface {

  public:
    Calendar ();
    virtual ~Calendar();
    void setUp ()           override;
    void Run ()             override;
    void printHeader ()     override;
    void printHeaderBold () override;
    
  
  private:
    void printDays ();
    void printMonth();
    int  findFirstDay ();
    int highlightDay;
    int highlightMon;
    int highlightYear;
    int wday;
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string months [12] = {"January", "February", "March", "April", "May", "June",
                               "July", "August", "September", "October", "November", "December" 
                              };
};