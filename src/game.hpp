#pragma once

#include <atomic>
#include <thread>
#include <chrono>
#include <Xinput.h>
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
        const pair<int,int> PLAYER_SPAWN = {49,49};

        Map map;
        Display display;
        unique_ptr<Player> player;
        Camera camera;
        vector<Entity*> entity_list;

        atomic<bool> running;
        atomic<int> player_dx;
        atomic<int> player_dy;

        struct InputState {
            atomic<bool> up{false};
            atomic<bool> down{false};
            atomic<bool> left{false};
            atomic<bool> right{false};
        };
        InputState input;

        void handle_movement();
};