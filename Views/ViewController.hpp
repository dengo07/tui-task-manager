#ifndef VIEW_CONTROLLER_HPP
#define VIEW_CONTROLLER_HPP


#include "ncurses.h"
#include "panel.h"
#include "../State/AppState.hpp"
#include "../Models/models.hpp"
#include <string>
#include <vector>


class ViewController{
    private:
        //std::vector<TodoList> lists;

        //Design the windows Here
        WINDOW* MainListWindow = newwin(50,50,0,0);
        WINDOW* TodoListWindow= newwin(50,50,0,0);
        WINDOW* InputModalWindow= newwin(50,50,0,0);
        WINDOW* ExitPromptWindow= newwin(50,50,0,0);


        //Create Panels to manage
        PANEL* MainListPanel = new_panel(MainListWindow);
        PANEL* TodoListPanel = new_panel(TodoListWindow);
        PANEL* InputModalPanel = new_panel(InputModalWindow);
        PANEL* ExitPromptPanel = new_panel(ExitPromptWindow);
        

        
        void renderTitle(){
            mvwprintw(stdscr,0,0,"#TODO-LIST APP# -- [UP][DOWN] for navigating -- [ENTER] to open list or toggle -- ['q'] for back\n -- ['c'] for new list or task -- ['d'] for delete");
        }

    void renderMainList(int highlight, ListOfLists* lists, int maxy, int maxx)
    {
        curs_set(0);

        werase(MainListWindow);

        int win_h = maxy / 2;
        int win_w = maxx / 2;

        wresize(MainListWindow, win_h, win_w);
        move_panel(MainListPanel, maxy / 4, maxx / 4);

        box(MainListWindow, '|', '-');
        mvwprintw(MainListWindow, 0, 2, " Todo Lists ");

        int visible_rows = win_h - 3; // header + border
        int total = lists->lists.size();

        int start_index = 0;

        if (highlight >= visible_rows) {
            start_index = highlight - visible_rows + 1;
        }

        if (start_index < 0) start_index = 0;
        if (start_index > total - visible_rows)
            start_index = std::max(0, total - visible_rows);

        for (int i = 0; i < visible_rows; i++) {
            int idx = start_index + i;
            if (idx >= total) break;

            if (idx == highlight)
                wattron(MainListWindow, A_REVERSE);

            mvwprintw(MainListWindow, i + 2, 1,
                    "%s", lists->lists[idx].title.c_str());

            if (idx == highlight)
                wattroff(MainListWindow, A_REVERSE);
        }

        top_panel(MainListPanel);
        hide_panel(TodoListPanel);
        hide_panel(InputModalPanel);
        hide_panel(ExitPromptPanel);
    }


    void renderTodoList(int highlight, TodoList* selectedList, int maxy, int maxx)
    {
        curs_set(0);
        werase(TodoListWindow);

        int win_h = maxy / 2;
        int win_w = maxx / 2;

        wresize(TodoListWindow, win_h, win_w);
        move_panel(TodoListPanel, maxy / 4, maxx / 4);

        box(TodoListWindow, '|', '-');
        mvwprintw(TodoListWindow, 0, 2, " %s ", selectedList->title.c_str());

        int total = selectedList->todos.size();
        int visible_rows = win_h - 3; // header + border

        int start_index = 0;

        if (highlight >= visible_rows)
            start_index = highlight - visible_rows + 1;

        if (start_index < 0) start_index = 0;
        if (start_index > total - visible_rows)
            start_index = std::max(0, total - visible_rows);

        //RENDER VISIBLE PART
        for (int i = 0; i < visible_rows; i++) {
            int idx = start_index + i;
            if (idx >= total) break;

            if (idx == highlight)
                wattron(TodoListWindow, A_REVERSE);

            mvwprintw(
                TodoListWindow,
                i + 2,
                1,
                "%s [%s]",
                selectedList->todos[idx].title.c_str(),
                selectedList->todos[idx].done ? "x" : " "
            );

            if (idx == highlight)
                wattroff(TodoListWindow, A_REVERSE);
        }

        top_panel(TodoListPanel);
        hide_panel(MainListPanel);
        hide_panel(InputModalPanel);
        hide_panel(ExitPromptPanel);
    }


        void renderInputModal(int maxy , int maxx,std::string buffer){
            curs_set(1);
            werase(InputModalWindow);
            wresize(InputModalWindow,maxy/2,maxx/2);
            move_panel(InputModalPanel,maxy/4,maxx/4);
            box(InputModalWindow,'|','-');
            mvwprintw(InputModalWindow,0,0,"Enter title for new...");
            mvwprintw(InputModalWindow,2,1,buffer.c_str());

            show_panel(InputModalPanel);
            top_panel(InputModalPanel);
        }

        void renderExitModal(int maxx , int maxy){
            curs_set(0);
            show_panel(ExitPromptPanel);
            top_panel(ExitPromptPanel);
        }   

    public:
        ViewController(){
            //Bordering the windows
        }


        void render(AppState s,int highlight,TodoList* selectedList,ListOfLists* lists,int maxy, int maxx,std::string buffer){
            clear();
            renderTitle();
            switch (s)
            {
            case AppState::MAIN_LIST:
                renderMainList(highlight,lists,maxy, maxx);
                break;
            
            case AppState::TODO_LIST:
                renderTodoList(highlight,selectedList,maxy,maxx);
                break;
            
            case AppState::MAIN_INPUT_MODAL:
                renderInputModal(maxy,maxx,buffer);
                break;
            case  AppState::TODOLIST_INPUT_MODAL:
                renderInputModal(maxy,maxx,buffer);
                break;      
            
            case AppState::EXIT_PROMPT:
                renderExitModal(maxy,maxx);
                break;
            }
            refresh();
            update_panels();
            doupdate();

        }
};

#endif