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
    ListOfLists lists;



    ViewController* view  = new ViewController();
    TodoController* todoControl = new TodoController(&lists,view);
 

    todoControl->run();
    
    return 0;

}