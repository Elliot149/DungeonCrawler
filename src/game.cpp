#include "game.hpp"

Game::Game() : 
    map(),
    display(78, 52, 0, 0),
    player(make_unique<Player>(PLAYER_SPAWN)),
    camera({display.get_width(), display.get_height(), 0, 0}),
    running(true),
    player_dx(0),
    player_dy(0)
{
    camera.start_x = (PLAYER_SPAWN.first+(player->width/2))-(camera.WIDTH/2);
    camera.start_y = (PLAYER_SPAWN.second+(player->height/2))-(camera.HEIGHT/2);
    entity_list.push_back(player.get());
    srand(time(0)); // Consider changing this line to add custom seeds
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
            if (ch == 'q') { running = false; break; }
            if (ch == 'w') { input.up    = true; }
            if (ch == 'a') { input.left  = true; }
            if (ch == 's') { input.down  = true; }
            if (ch == 'd') { input.right = true; }
        }
        handle_movement();
        input.up = input.down = input.left = input.right = false;
        display.render(camera, map.pixel_map, entity_list);

        auto elapsed = std::chrono::steady_clock::now() - frame_start;
        if (elapsed < FRAME_TIME) { this_thread::sleep_for(FRAME_TIME - elapsed); }
    }
}


// This function handles player movement
void Game::handle_movement() {        
    float dx = 0.0f, dy = 0.0f;
    if (input.up)    { dy -= 1.0f; }
    if (input.down)  { dy += 1.0f; }
    if (input.left)  { dx -= 1.0f; }
    if (input.right) { dx += 1.0f; }
    float length = std::sqrt(dx*dx + dy*dy);
    if (length > 0.0f) {
        dx /= length;
        dy /= length;
    }
    dx = round(dx * player.get()->movement_speed);
    dy = round(dy * player.get()->movement_speed * 0.7);

    if ( dx || dy ) {
        if ( !map.check_for_collision(player.get()->x+dx+3, player.get()->y+dy+(player.get()->height*0.8), 
                                      10, (player.get()->height*0.2)) ) {
            player->move({dx, dy}); 
            camera.start_x += dx;
            camera.start_y += dy;
        }
    }
}