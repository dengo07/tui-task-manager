

compile: src/main.cpp
	g++  -lpanel -lncurses Models/models.cpp  Controllers/TodoController.cpp Views/ViewController.cpp main.cpp   -o  Main

