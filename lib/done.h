#pragma once

#include "interface.h"
#include <map>
#include <string>
#include <sstream>

class Done : public Interface {
  public:
    Done ();
    ~Done();
    void Run () override;
    void printHeader() override;
    void printHeaderBold() override;
    void addTask (const Task & task) override;
  private:
    void writeDone();
    void readDone();

    std::multimap <tm, Task, date_compare> tasks;
};
