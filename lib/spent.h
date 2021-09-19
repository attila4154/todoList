#pragma once

#include "interface.h"
#include "activity.h"

class Spent : public Interface{
  public:
    Spent();
    ~Spent();

    void Run() override;
    void printHeader() override;
    void printHeaderBold() override;
    
  private:

    // void readActivities ();
    // void writeActivities ();
    /// map of spent hours for each day
    /// with activity as a key
    // std::map <Activity, short> activities;
};