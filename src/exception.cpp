#include "../lib/exceptions.h"
#include "../lib/interface.h"

date_change::date_change () {
    
}

date_change::date_change (int day, int mon, int year) : day (day), mon(mon), year(year) {

}

task_done::task_done (const Task & task) : task (task) {}