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
    start_threads();
}


Game::~Game() { 
    running = false;
    if (player_thread.joinable()) {
        player_thread.join();
    }
    endwin();
}


void Game::run() {
    while (running) {
        input.up = input.down = input.left = input.right = false;
        int ch = getch();
        switch (ch) {
            case 'q': running     = false; break;
            case 'w': input.up    = true;  break;
            case 'a': input.left  = true;  break;
            case 's': input.down  = true;  break;
            case 'd': input.right = true;  break;
            default: break;
        }
        display.render(camera, map.pixel_map, entity_list);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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


void Game::start_threads() {
    player_thread = thread(&Game::player_thread_func, this);
}


void Game::player_thread_func() {
    while (running) {
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
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}