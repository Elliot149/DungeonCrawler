#pragma once

#include <vector>
#include <chrono>
#include <string>
#include <curses.h>
#include <cstdint>
#include <iostream>
#include "tile.hpp"
#include "entity.hpp"

using namespace std;

#define EMPTY_PIXEL 232     // This is a very dark gray, will likely never use but will cause issues if I do

struct Camera {
    int WIDTH;
    int HEIGHT;
    int start_x;
    int start_y;
};

class Display {

    public:
        Display(int width, int height, int x, int y);
        ~Display();
        void render(Camera& camera, const vector<vector<uint8_t>>& map_layer, const vector<Entity*>& entities);
        int get_width();
        int get_height();

    private:
        int DISPLAY_WIDTH;
        int DISPLAY_HEIGHT;
        vector<vector<uint8_t>> generate_entity_layer(const vector<Entity*>& entities, const int width, const int height);
        vector<vector<uint8_t>> previous_render;
        WINDOW* gamewin = nullptr;
};