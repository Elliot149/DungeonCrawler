#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "tile.hpp"

using namespace std;

#define GRASS "grass"
#define GRAVEL "gravel"
#define DIRT "dirt"
#define STONE_BRICK "stone_brick"
#define WATER "water"
#define STONE_WALL "stone_wall"
#define FLOOR "."

class Map {
    public:

        Map();                                      // Constructor function
        ~Map();                                     // Destructor function
        static bool check_for_collision(int x, int y, int width, int height);
        static vector<vector<uint8_t>> pixel_map;   // Stores the ascii codes of each pixel on the map
        static vector<vector<Tile>>    id_map;      // Stores what each pixel on the map actually is
        static int width, height;

    private:
        static const vector<string> ground_tiles;
        static const vector<pair<string,int>> tiles_with_random_textures;
        static const vector<string> fully_directional_tiles;
        static const vector<string> horizontally_directional_tiles;
        static const vector<string> wall_tiles;

        static vector<vector<Tile>> generate_map();
        static vector<pair<int,int>> get_dot_coords(vector<vector<string>> map_rep);
        static vector<string> get_neighbours(vector<vector<string>> map_rep, pair<int,int> coordinate);
        static void replace_ground_tiles(vector<vector<string>>& map_rep);
        static void handle_directional_tiles(vector<vector<string>>& map_rep);
        static void handle_random_textures(vector<vector<string>>& map_rep);
        static void handle_walls(vector<vector<string>>& map_rep);
        static vector<vector<Tile>> build_tile_map(vector<vector<string>> map_rep);
};