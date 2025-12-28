#include <curses.h>
#include <chrono>
#include <thread>
#include "map.hpp"

int main() {

    initscr();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    resize_term(rows, cols-1);

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    // printw("Hello from PDCurses!\n");
    // printw("Press 'q' to quit.");
    // for (int j = 0; j < 5; j++) {
    //     for (int i = 0; i < 9; i++) { printw("+------------------------------+"); } printw("\n");
    //     for (int k = 0; k < 14; k++) { for (int i = 0; i < 9; i++) { printw("|                              |"); } printw("\n"); }
    //     for (int i = 0; i < 9; i++) { printw("+------------------------------+"); } printw("\n");
    // }
    Map* map = new Map();
    vector<vector<string>> id_map = map->id_map;

    for (vector<string> line : id_map) {
        for (string s : line) {
            printw("%s", s.c_str());
        }
        printw("\n");
    }

    refresh();

    bool running = true;
    while (running) {
        int ch = getch();
        if (ch == 'q') { running = false; }

        // Example of independent updates
        // static int counter = 0;
        // mvprintw(5, 10, "Counter: %d", counter++);
        // refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    endwin();
    return 0;
}