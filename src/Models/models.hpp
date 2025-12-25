#ifndef MODELS_HPP
#define MODELS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdlib>

struct Todo {
    std::string title;
    bool done = false;
};

struct TodoList {
    std::string title;
    std::vector<Todo> todos;

    void toggle(int index) {
        if (index >= 0 && index < (int)todos.size()) {
            todos[index].done = !todos[index].done;
        }
    }

    void add(const std::string& t) {
        todos.push_back({t, false});
    }
};

struct ListOfLists {
    std::vector<TodoList> lists;

    static std::string dataPath() {
        const char* xdg = std::getenv("XDG_DATA_HOME");
        std::string base;

        if (xdg)
            base = xdg;
        else
            base = std::string(std::getenv("HOME")) + "/.local/share";

        std::filesystem::path dir = base + "/todo";
        std::filesystem::create_directories(dir);

        return (dir / "todos.txt").string();
    }

    void getFromFile() {
        std::ifstream file(dataPath());
        if (!file.is_open()) return;

        lists.clear();
        std::string line;
        TodoList currentList;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            std::string type;
            iss >> type;

            if (type == "LIST") {
                currentList = TodoList{};
                std::getline(iss, currentList.title);
                if (!currentList.title.empty() && currentList.title[0] == ' ')
                    currentList.title.erase(0, 1);
            }
            else if (type == "TODO") {
                Todo todo;
                iss >> todo.done;
                std::getline(iss, todo.title);
                if (!todo.title.empty() && todo.title[0] == ' ')
                    todo.title.erase(0, 1);

                currentList.todos.push_back(todo);
            }
            else if (type == "ENDLIST") {
                lists.push_back(currentList);
            }
        }
    }

    void saveToFile() {
        std::ofstream file(dataPath());
        if (!file.is_open()) return;

        for (const auto& list : lists) {
            file << "LIST " << list.title << "\n";

            for (const auto& todo : list.todos) {
                file << "TODO "
                     << todo.done << " "
                     << todo.title << "\n";
            }

            file << "ENDLIST\n\n";
        }
    }
};

#endif // MODELS_HPP
