#pragma once

#include <atomic>
#include <thread>
#include <chrono>
#include "map.hpp"
#include "display.hpp"
#include "entity.hpp"

using namespace std;

class Game {
    public:
        Game();
        ~Game();
        void run();

    private:
        Map map;
        Display display;
        Camera camera;
        unique_ptr<Player> player;
        vector<Entity*> entity_list;

        atomic<bool> running;
        atomic<int> player_dx;
        atomic<int> player_dy;
        thread player_thread;

        void init_curses();

        struct InputState {
            atomic<bool> up{false};
            atomic<bool> down{false};
            atomic<bool> left{false};
            atomic<bool> right{false};
        };
        InputState input;
};