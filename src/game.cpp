#include "game.hpp"

Game::Game() {
    const int CAMERA_WIDTH = 200;
    const int CAMERA_HEIGHT = 100;
    const pair<int,int> PLAYER_SPAWN = {49,49};

    map = Map();
    display = Display();
    player = make_unique<Player>(PLAYER_SPAWN);
    running = true;
    player_dx = 0;
    player_dy = 0;
    entity_list.push_back(player.get());
    camera = Camera({CAMERA_WIDTH, 
                     CAMERA_HEIGHT, 
                    (PLAYER_SPAWN.first+(player->width/2))-(CAMERA_WIDTH/2), 
                    (PLAYER_SPAWN.second+(player->height/2))-(CAMERA_HEIGHT/2)});
    
    srand(static_cast<unsigned>(time(nullptr)));
    init_curses();
}


Game::~Game() { 
    running = false;
    endwin();
}


void Game::run() {
    constexpr auto FRAME_TIME = chrono::milliseconds(100);
    while (running) {
        auto frame_start = std::chrono::steady_clock::now();

        int ch;
        while ((ch = getch()) != ERR) {
            switch (ch) {
                case 'q': running     = false; break;
                case 'w': input.up    = true;  break;
                case 'a': input.left  = true;  break;
                case 's': input.down  = true;  break;
                case 'd': input.right = true;  break;
            }
        }
        int dx = 0, dy = 0;
        if (input.up)    { dy -= 1; }
        if (input.down)  { dy += 1; }
        if (input.left)  { dx -= 1; }
        if (input.right) { dx += 1; }

        if ( dx || dy ) { 
            player->move({dx, dy}); 
            camera.start_x += dx;
            camera.start_y += dy;
        }
        input.up = input.down = input.left = input.right = false;
        display.render(camera, map.pixel_map, entity_list);

        auto elapsed = std::chrono::steady_clock::now() - frame_start;
        if (elapsed < FRAME_TIME) { this_thread::sleep_for(FRAME_TIME - elapsed); }
    }
}


void Game::init_curses() {
    initscr();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    resize_term(rows, cols - 1);

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    start_color();
    constexpr int MAX_COLORS = 256;
    for (int c = 0; c < MAX_COLORS; ++c) {
        init_pair(c + 1, COLOR_BLACK, c);
    }
}