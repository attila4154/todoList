#pragma once

#include "interface.h"

class Done : public Interface {
  public:
    Done ();
    ~Done();
    void setUp () override;
    void Run () override;
    void printHeader() override;
    void printHeaderBold() override;
  private:
};