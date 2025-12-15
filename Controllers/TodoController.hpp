#ifndef TODO_CONTROLLER_HPP
#define TODO_CONTROLLER_HPP


#include "../State/AppState.hpp"
#include "../Models/models.hpp"
#include "../Views/ViewController.hpp"
#include <vector>
#include <string>

class TodoController
{

private:
    AppState currentState =  AppState::MAIN_LIST;
    ListOfLists* lists;
    TodoList* selectedList;
    std::string buffer = "";
    ViewController* viewController;
    int highlight = 0;
    bool running = true;
    void processInput(int ch){
        switch (currentState)
        {
        case AppState::MAIN_LIST:
            handleMainListInput(ch);
            break;
        
        case AppState::TODO_LIST:
            handleTodoListInput(ch);
            break;

        case AppState::MAIN_INPUT_MODAL:
            handleInputModalInput(ch);
            break;

        case AppState::TODOLIST_INPUT_MODAL:
            handleInputModalInput(ch);
            break;        

        case AppState::EXIT_PROMPT:
            handleExitPromptInput(ch);
            break;
        }
    }

    void handleMainListInput(int ch){
        switch (ch)
        {
        case KEY_UP:
            if(highlight>0){
                highlight--;
            }
            break;
        case KEY_DOWN:
            if(highlight < lists->lists.size()-1){
                highlight++;
            }
            break;
        case 'c':
            setState(AppState::MAIN_INPUT_MODAL);
            break;
        case 'd':
            if(lists->lists.size()>0){
                lists->lists.erase(lists->lists.begin() + highlight);
            }
            highlight =0;
            break;
        case 'q':
            clear();
            running = false;
            break;
        case '\n':
            selectedList = &(lists->lists[highlight]);
            setState(AppState::TODO_LIST);
            highlight =0;
            break;
        default:
            break;
        }
    }
    void handleTodoListInput(int ch){
        switch (ch)
        {
        case KEY_UP:
            if(highlight>0){
                highlight--;
            }
            break;
        case KEY_DOWN:
            if(highlight < selectedList->todos.size()-1){
                highlight++;
            }
            break;
        case 'c':
            setState(AppState::TODOLIST_INPUT_MODAL);
            break;
        case 'q':
            setState(AppState::MAIN_LIST);
            highlight =0;
            break;
        case 'd':
            if(selectedList->todos.size()>0){
                selectedList->todos.erase(selectedList->todos.begin()+highlight);
            }
            highlight = 0;
            break;
        case '\n':
            (*selectedList).toggle(highlight);
            break;
        default:
            break;
        }

    }

    void handleInputModalInput(int ch){

        switch (currentState)
        {
        case AppState::MAIN_INPUT_MODAL:
            if(ch == '\n'){
                if(buffer.size() >0){
                    TodoList newList;
                    newList.title = buffer;
                    lists->lists.push_back(newList);
                    buffer = "";
                } 
                setState(AppState::MAIN_LIST);

            }
            else if(ch == KEY_BACKSPACE){
                if(buffer.size() > 0){
                    buffer.pop_back();
                }
            }
            else if(ch == 27){
                setState(AppState::MAIN_LIST);
            }
            else{
                buffer.push_back(ch);
            }
            break;
        case AppState::TODOLIST_INPUT_MODAL:
            if(ch == '\n'){
                if(buffer.size() >0){
                    Todo newTodo;
                    newTodo.title = buffer;
                    selectedList->add(buffer);
                    buffer = "";
                } 
                setState(AppState::TODO_LIST);

            }
            else if(ch == KEY_BACKSPACE){
                if(buffer.size() > 0){
                    buffer.pop_back();
                }
            }
            else if(ch == 27){
                setState(AppState::TODO_LIST);
            }
            else{
                buffer.push_back(ch);
            }
            break;
        default:
            break;
        }

    }

    void handleExitPromptInput(int ch){

    }

public:

   TodoController(ListOfLists* l,ViewController* view){
        lists = l;
        viewController = view;
   }

    void setState(AppState s){
        currentState = s;
    }
    AppState getState(){
        return currentState;
    }

    void run(){
        lists->getFromFile();
        int x,y;
        getmaxyx(stdscr,y,x);
        viewController->render(currentState,highlight,selectedList,lists,y,x,buffer);
        while(running){
            int c = getch();
            processInput(c);
            getmaxyx(stdscr,y,x);
            viewController->render(currentState,highlight,selectedList,lists,y,x,buffer);
        }
        lists->saveToFile();
        endwin();
    }
};

#endif