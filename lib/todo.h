#pragma once

#include "interface.h"
#include "task.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


class ToDo : public Interface {
  public:
    ToDo ();
    void setUp () override;
    void Run () override;
    void printHeader() override;
    void printHeaderBold() override;
    void refresh() override;
    ~ToDo();
  private:
    void readToDo();
    void writeToDo();
    void writeToFile();

    int taskWidth, themeWidth, dateWidth;
    int highlight;

    std::vector<Task> list;

    WINDOW * add;
    int addHeight, addWidth;
};