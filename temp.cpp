#include <iostream>
#include <fstream>
#include <string>
#include <vector>



int main() {
    std::vector<std::string> list;
    std::ifstream file ("/home/daniel/Documents/git/todoList/todo.txt");
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            list.push_back(line);
        }
    }

    file.close();
    for (auto const & x : list) {
        std::cout << x << std::endl;
    }
}