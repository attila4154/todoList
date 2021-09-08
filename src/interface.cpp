#include "../lib/interface.h"

int Interface::height = 40;
int Interface::width = 70;

void Interface::refresh() {
    wrefresh(window);
}