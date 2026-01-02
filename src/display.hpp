#include <vector>
#include <string>
#include <curses.h>
#include <cstdint>
#include <iostream>
#include "tile.hpp"

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
        void draw_map(Camera& camera);
        void initialise_sprite_layer();   // This must be called after the map_layer has been set
        void add_sprite_to_layer(pair<int,int> pos, vector<vector<uint8_t>> &sprite);

        vector<vector<uint8_t>> sprite_layer;
        vector<vector<uint8_t>> map_layer;

    private:

};