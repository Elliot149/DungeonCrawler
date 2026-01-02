#include "display.hpp"

void Display::draw_map(vector<vector<uint8_t>>& pixel_map, Camera& camera) {
    for (int screen_y = 0; screen_y < camera.HEIGHT; screen_y++) {
        for (int screen_x = 0; screen_x < camera.WIDTH; screen_x++) {
            int world_x = camera.start_x + screen_x;
            int world_y = camera.start_y + screen_y;

            if (world_x < 0 || world_y < 0 || world_x >= (int)pixel_map.front().size() || world_y >= (int)pixel_map.size()) {
                continue;
            }
            uint8_t colour = pixel_map.at(world_y).at(world_x);
            attron(COLOR_PAIR(colour));
            mvaddch(screen_y, screen_x, ' ');
        }
    }
}