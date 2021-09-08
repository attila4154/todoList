#pragma once

#include "interface.h"

class Done : public Interface {
  public:
    Done ();
    ~Done();
    void setUp () override;
    void Run () override;
    void reprint () override;
    void reprintBold () override;
  private:
};