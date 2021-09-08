#pragma once

#include "interface.h"

class Calendar : public Interface {
  public:
    Calendar ();
    virtual ~Calendar();
    void setUp () override;
    void Run () override;
    void reprint () override;
    void reprintBold () override;
};