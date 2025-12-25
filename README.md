
# Terminal Todo List Manager

A lightweight, ncurses-based Terminal User Interface (TUI) application for managing tasks. Written in C++17, this project demonstrates the **Model-View-Controller (MVC)** architectural pattern applied to a console application.

It features persistent storage, hierarchical list management, and a modal-based input system.

## Features

* **Hierarchical Organization:** Create multiple Todo Lists to categorize tasks.
* **Persistent Storage:** Automatically saves and loads data from `~/.local/share/todo/` (XDG Base Directory compliant).
* **Modal Interface:** distinct windows for navigation, input, and alerts using `ncurses` panels.
* **Keyboard Driven:** Optimized for fast navigation without a mouse.
* **MVC Architecture:** Clean separation between data logic, rendering, and input handling.

## Dependencies

To build and run this application, you need a C++ compiler supporting C++17 and the ncurses library.

### Ubuntu/Debian
```bash
sudo apt install build-essential libncurses5-dev libncursesw5-dev

```

### Arch Linux

```bash
sudo pacman -S ncurses base-devel

```

### Fedora

```bash
sudo dnf install ncurses-devel

```

## Installation

The project includes an automated installation script.

1. **Clone the repository:**
```bash
git clone https://github.com/dengo07/tui-task-manager
cd tui-task-manager

```


2. **Run the install script:**
```bash
chmod +x install.sh
./install.sh

```
or

```bash
make install
```


*This will compile the source and move the binary to `/usr/local/bin/todo`.*
3. **Run the application:**
```bash
todo

```



### Manual Build

If you prefer to build locally without installing globally:

```bash
make
./todo

```

## Usage Controls

The application is controlled entirely via keyboard shortcuts.

| Key | Context | Action |
| --- | --- | --- |
| **↑ / ↓** | Global | Navigate up and down lists or tasks. |
| **Enter** | Main List | Open the selected Todo List. |
| **Enter** | Todo List | Toggle task completion status. |
| **c** | Global | **Create** a new List or a new Task (opens input modal). |
| **d** | Global | **Delete** the selected List or Task. |
| **q** | Global | Go back (if inside a list) or Quit the application. |
| **Esc** | Input Modal | Cancel input and close modal. |

## Technical Architecture

The project is structured around the MVC design pattern:

* **Models (`src/Models/`):** Handles data structures (`Todo`, `TodoList`, `ListOfLists`) and file I/O operations.
* **Views (`src/Views/`):** Manages the Ncurses windows and panels. Responsible for rendering the UI state provided by the controller.
* **Controllers (`src/Controllers/`):** Processes user input, updates the AppState, and mediates data flow between Models and Views.
* **State (`src/State/`):** Defines the application state machine (`AppState` enum) to manage navigation context (Main List, Todo List, Input Modal, etc.).

## File Structure

```
.
├── src/
│   ├── Controllers/   # Input handling and logic
│   ├── Models/        # Data structures and Persistence
│   ├── State/         # AppState definitions
│   ├── Views/         # Ncurses rendering logic
│   └── main.cpp       # Entry point
├── install.sh         # Installation script
├── uninstall.sh       # Uninstallation script
├── makefile           # Build configuration
└── README.md

```

## Uninstallation

To remove the application binary:

```bash
chmod +x uninstall.sh
./uninstall.sh
```
or

```bash
make uninstall
```

During uninstallation, the script will ask if you wish to remove your configuration and saved data located in `~/.local/share/todo`.


