#ifndef MODELS_HPP
#define MODELS_HPP

#include<string>
#include<vector>



struct Todo
{
    std::string title = "";
    bool done = false;



};


struct TodoList
{
    std::string title = "";
    std::vector<Todo> todos={};
    void toggle(int index) {
        if (index >= 0 && index < todos.size()) {
            todos[index].done = !todos[index].done;
        }
    }

    void add(const std::string& t) {
        todos.push_back({t, false});
    }
    void getFromFile(){

    }
    void saveToFile(){

    }
};

#endif