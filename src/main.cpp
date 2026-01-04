#include "game.hpp"

void init_curses() {
    initscr();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    resize_term(rows, cols - 1);

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    idlok(stdscr, FALSE);
    idlok(stdscr, FALSE);
    scrollok(stdscr, FALSE);

    start_color();
    constexpr int MAX_COLORS = 256;
    for (int c = 0; c < MAX_COLORS; ++c) {
        init_pair(c + 1, COLOR_BLACK, c);
    }
}

int main() {
    init_curses();
    Game game = Game();
    game.run();
    return 0;
}