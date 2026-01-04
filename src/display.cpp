#include "display.hpp"

vector<vector<uint8_t>> Display::previous_render = {{}};

// This is the main function and draws the map to the screen
void Display::render(Camera& camera, const vector<vector<uint8_t>>& map_layer, const vector<Entity*>& entities) {
    cout << "START - " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count() << endl;
    if ((int)previous_render.size() != camera.HEIGHT || (int)previous_render.front().size() != camera.WIDTH) {
        previous_render.assign( camera.HEIGHT, vector<uint8_t>(camera.WIDTH, EMPTY_PIXEL) );
    }
    vector<vector<uint8_t>> current_render( camera.HEIGHT, vector<uint8_t>(camera.WIDTH, EMPTY_PIXEL) );
    const vector<vector<uint8_t>>& entity_layer = generate_entity_layer(entities, map_layer.front().size(), map_layer.size());
    uint8_t current_colour = 0;

    for (int screen_y = 0; screen_y < camera.HEIGHT; screen_y++) {
        for (int screen_x = 0; screen_x < camera.WIDTH; screen_x++) {
            int world_x = camera.start_x + screen_x;
            int world_y = camera.start_y + screen_y;
            if (world_x < 0 || world_y < 0 || world_x >= (int)map_layer.front().size() || world_y >= (int)map_layer.size()) { continue; }

            uint8_t colour;
            if ( entity_layer[world_y][world_x] != EMPTY_PIXEL ) { colour = entity_layer[world_y][world_x]; }
            else { colour = map_layer[world_y][world_x]; }
            
            current_render[screen_y][screen_x] = colour;
            if (previous_render[screen_y][screen_x] != colour) {
                if (colour != current_colour) { attrset(COLOR_PAIR(colour+1)); current_colour = colour; }
                mvaddch(screen_y, screen_x, ' ');
            }
        }
    }
    wnoutrefresh(stdscr);
    doupdate();
    previous_render.swap(current_render);
    cout << "END -   " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count() << endl;
}


// This function generates the pixel map based on the state of all entities
vector<vector<uint8_t>> Display::generate_entity_layer(const vector<Entity*>& entities, const int width, const int height) {
    vector<vector<uint8_t>> entity_map;
    entity_map.resize(height);
    for (auto& row : entity_map) { row.resize(width, 232); }

    for (Entity* e : entities) {
        for (int y = 0; y < e->height; y++) {
            for (int x = 0; x < e->width; x++) {
                if (e->y+y >= 0 && e->y+y < height && e->x+x >= 0 && e->x+x < width) {
                    entity_map[e->y+y][e->x+x] = e->get_current_sprite()[y][x];
                }
            }
        }
    }
    return entity_map;
}