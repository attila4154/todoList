#pragma once

#include <exception>

class exit_exc : public std::exception {

};

class date_change: public std::exception {
  public:
    date_change ();
    date_change (int day, int mon, int year);
    int day, mon, year;
};