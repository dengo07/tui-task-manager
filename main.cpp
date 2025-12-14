#include <ncurses.h>
#include <panel.h>
#include <vector>
#include <string>
#include "./Controllers/TodoController.hpp"
#include "./Views/ViewController.hpp"
#include "./Models/models.hpp"


void initialize(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

}

int main(){
    initialize();
    std::vector<TodoList> lists = {

    {
        "Gunluk",
        {
            {"Su iç", true},
            {"Kod yaz", false},
            {"Yürüyüş yap", false}
        }
    },

    {
        "Okul",
        {
            {"Veri Yapilari ödevini bitir", false},
            {"OS notlarini oku", true},
            {"Lineer cebir tekrar", false}
        }
    },

    {
        "Projeler",
        {
            {"ncurses TUI tasarla", true},
            {"MVC mimarisini oturt", false},
            {"State machine refactor", false}
        }
    }
};


    ViewController* view  = new ViewController();
    TodoController* todoControl = new TodoController(&lists,view);
 

    todoControl->run();

    return 0;

}