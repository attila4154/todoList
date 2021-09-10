#pragma once

#include "interface.h"

class Spent : public Interface{
  public:
    Spent();
    ~Spent();

    void setUp() override;
    void Run() override;
    void printHeader() override;
    void printHeaderBold() override;
    
  private:

};