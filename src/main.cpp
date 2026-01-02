#include <curses.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "map.hpp"
#include "display.hpp"
#include "player.hpp"

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

    start_color();
    constexpr int MAX_COLORS = 256;
    for (int c = 0; c < MAX_COLORS; ++c) {
        init_pair(c+1, COLOR_BLACK, c);
    }

    srand(time(0));         // Consider changing this to use generated seeds

    // printw("Hello from PDCurses!\n");
    // printw("Press 'q' to quit.");
    // for (int j = 0; j < 5; j++) {
    //     for (int i = 0; i < 9; i++) { printw("+------------------------------+"); } printw("\n");
    //     for (int k = 0; k < 14; k++) { for (int i = 0; i < 9; i++) { printw("|                              |"); } printw("\n"); }
    //     for (int i = 0; i < 9; i++) { printw("+------------------------------+"); } printw("\n");
    // }

    Map map = Map();
    vector<vector<string>>  id_map    = map.id_map;
    Display display = Display();
    Player  player  = Player({17,17});
    Camera  camera    { 200, 100, 0, 0 };

    // for (auto& row : id_map) {
    //     for (string s : row) { cout << s << " "; }
    //     cout << endl;
    // }

    display.map_layer = map.pixel_map;
    display.initialise_sprite_layer();
    display.add_sprite_to_layer(player.get_coordinates(), player.get_current_sprite());
    display.draw_map(camera);

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