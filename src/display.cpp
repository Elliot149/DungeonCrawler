#include "display.hpp"

// This is the main function and draws the map to the screen
void Display::draw_map(Camera& camera) {
    for (int screen_y = 0; screen_y < camera.HEIGHT; screen_y++) {
        for (int screen_x = 0; screen_x < camera.WIDTH; screen_x++) {
            int world_x = camera.start_x + screen_x;
            int world_y = camera.start_y + screen_y;

            if (world_x < 0 || world_y < 0 || world_x >= (int)map_layer.front().size() || world_y >= (int)map_layer.size()) {
                continue;
            }

            uint8_t colour;
            if ( sprite_layer[world_y][world_x] != EMPTY_PIXEL ) { colour = sprite_layer[world_y][world_x]; }
            else { colour = map_layer[world_y][world_x]; }
            attrset(COLOR_PAIR(colour+1));
            mvaddch(screen_y, screen_x, ' ');
        }
    }
}


// This function initialises the size of the sprite layer based on the size of the map layer, 
// therefore the map layer MUST be set first
void Display::initialise_sprite_layer() {
    sprite_layer.resize(map_layer.size() * Tile::HEIGHT);
    for (auto& row : sprite_layer) { row.resize(map_layer.front().size() * Tile::WIDTH, EMPTY_PIXEL); }
}


// This function adds a sprite to the sprite layer
void Display::add_sprite_to_layer(pair<int,int> pos, vector<vector<uint8_t>> &sprite) {
    for (int y = 0; y < (int)sprite.size(); y++) {
        for (int x = 0; x < (int)sprite.front().size(); x++) {
            sprite_layer[y + pos.second][x + pos.first] =  sprite[y][x];
        }
    }
}