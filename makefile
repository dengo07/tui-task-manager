CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LIBS = -lpanel -lncurses

TARGET = todo

SRC = \
	src/main.cpp \
	src/Models/models.cpp \
	src/Controllers/TodoController.cpp \
	src/Views/ViewController.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)

install:
	./install.sh

uninstall:
	./uninstall.sh
