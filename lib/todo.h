#pragma once

#include "interface.h"
#include "task.h"
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
    void writeToFile();

    int highlight;
    std::vector<Task> list;
};