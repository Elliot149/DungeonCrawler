#pragma once

#include <vector>
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
        static void render(Camera& camera, const vector<vector<uint8_t>>& map_layer, const vector<Entity*>& entities);

    private:
        static vector<vector<uint8_t>> generate_entity_layer(const vector<Entity*>& entities, const int width, const int height);
};