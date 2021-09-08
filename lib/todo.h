#pragma once

#include "interface.h"
#include <string>
#include <fstream>
#include <vector>


class ToDo : public Interface {
  public:
    ToDo ();
    void setUp () override;
    void Run () override;
    void reprint () override;
    void reprintBold () override;
    ~ToDo();
  private:
    void readToDo();
    void writeToDo();

    int highlight;
    std::vector<std::string> list;
};