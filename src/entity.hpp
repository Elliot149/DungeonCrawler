#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

using namespace std;

class Entity {

    public:
        Entity();
        ~Entity();
        void move(pair<int,int> direction);
        virtual vector<vector<uint8_t>> &get_current_sprite() = 0;
        int x, y, width, height;
        bool hitbox;
};


class Player : public Entity {

    public:
        Player(const pair<int,int> &spawn_pos);
        ~Player();
        // void move(pair<int,int> direction) override;
        vector<vector<uint8_t>> &get_current_sprite() override;

        enum class State {
            IDLE_UP,    IDLE_DOWN,    IDLE_LEFT,    IDLE_RIGHT,
            RUNNING_UP, RUNNING_DOWN, RUNNING_LEFT, RUNNING_RIGHT,
            ATTACK_UP,  ATTACK_DOWN,  ATTACK_LEFT,  ATTACK_RIGHT
        };

    private:
        static void read_sprite_file(string sprite_name, vector<vector<uint8_t>> &data_struct);
        State current_state;

        vector<vector<uint8_t>> idle_down_sprite;
        vector<vector<uint8_t>> idle_up_sprite;
        vector<vector<uint8_t>> idle_right_sprite;
        vector<vector<uint8_t>> idle_left_sprite;
};