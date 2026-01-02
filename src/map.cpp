#include "map.hpp"
#include "display.hpp"

// UNUSED TILES : STONE_BRICK
const vector<string> Map::ground_tiles = {GRASS, GRAVEL, DIRT};
const vector<string> Map::wall_tiles = {STONE_WALL};
const vector<string> Map::fully_directional_tiles = {GRASS, DIRT};
const vector<string> Map::horizontally_directional_tiles = {STONE_WALL};
const vector<pair<string,int>> Map::tiles_with_random_textures = {{GRAVEL,3}, {WATER, 1}};

vector<vector<uint8_t>> Map::pixel_map{};
vector<vector<string>>  Map::id_map{};

// Constructor function for the map class
Map::Map() {
    // This will change after I implement random generation
    vector<vector<Tile>> map = generate_map();
    pixel_map.resize(map.size() * Tile::HEIGHT);
    id_map.resize(map.size() * Tile::HEIGHT);
    for (auto& row : pixel_map) { row.resize(map.front().size() * Tile::WIDTH); }
    for (auto& row : id_map)    { row.resize(map.front().size() * Tile::WIDTH); }

    for (int map_y = 0; map_y < (int)map.size(); map_y++) {
        for (int map_x = 0; map_x < (int)map[map_y].size(); map_x++) {
            const Tile& t = map[map_y][map_x];
            int base_y = map_y * Tile::HEIGHT;
            int base_x = map_x * Tile::WIDTH;
            for (int tile_y = 0; tile_y < Tile::HEIGHT; tile_y++) {
                for (int tile_x = 0; tile_x < Tile::WIDTH; tile_x++) {
                    pixel_map[base_y + tile_y][base_x + tile_x] = t.pixels[tile_y][tile_x];
                    id_map[base_y + tile_y][base_x + tile_x] = t.name;
                }
            }
        }
    }
    cout << "Generated Map" << endl;
}


// Destructor function for the map class
Map::~Map() {

}


// This is the master function for generating the map
vector<vector<Tile>> Map::generate_map() {
    vector<vector<string>> map_sample = {
        {STONE_WALL, STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  WATER, WATER, WATER, WATER, WATER},
        {STONE_WALL, FLOOR, FLOOR, FLOOR, STONE_WALL,  FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, WATER, WATER, WATER, WATER, WATER},
        {STONE_WALL, FLOOR, FLOOR, FLOOR, STONE_WALL,  FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, WATER, WATER, WATER, WATER},
        {STONE_WALL, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, WATER, WATER, WATER, WATER},
        {STONE_WALL, FLOOR, FLOOR, FLOOR, STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, WATER, WATER, WATER, WATER},
        {STONE_WALL, FLOOR, FLOOR, FLOOR, STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, WATER, WATER, WATER},
        {STONE_WALL, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, STONE_WALL,  FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, WATER, WATER, WATER},
        {STONE_WALL, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, STONE_WALL,  FLOOR, FLOOR, FLOOR, FLOOR, WATER, WATER, WATER, WATER, WATER},
        {STONE_WALL, STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  WATER, WATER},
        {STONE_WALL, STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  STONE_WALL,  WATER, WATER},
    };
    replace_ground_tiles(map_sample);
    handle_directional_tiles(map_sample);
    handle_random_textures(map_sample);
    handle_walls(map_sample);

    vector<vector<Tile>> map = build_tile_map(map_sample);
    return map;
}


// This function takes the map of texture names and generates all of the Tile entites to populate it
vector<vector<Tile>> Map::build_tile_map(vector<vector<string>> map_rep) {
    vector<vector<Tile>> tile_map;
    for (int y = 0; y < (int)map_rep.size(); y++) {
        tile_map.push_back({});
        for (int x = 0; x < (int)map_rep.front().size(); x++) {
            string current_tile = map_rep.at(y).at(x);
            // cout << current_tile << " (" << x << "," << y << ")" << endl;
            tile_map.back().push_back(Tile(current_tile));
        }
    }
    cout << "Built tile map" << endl;
    return tile_map;
}


// This function handles updating the texture name for walls
void Map::handle_walls(vector<vector<string>>& map_rep) {
    vector<vector<string>> return_map;
    for (int y = 0; y < (int)map_rep.size(); y++) {
        return_map.push_back({});
        for (int x = 0; x < (int)map_rep.front().size(); x++) {
            string t = map_rep.at(y).at(x);
            for (string wall_tile : wall_tiles) {
                if (wall_tile+"_tile_left" == t || wall_tile+"_tile_right" == t || 
                    wall_tile+"_tile_center" == t || wall_tile+"_tile_alone" == t) {
                    vector<string> n = get_neighbours(map_rep, {x,y});
                    // cout << n[3] << " " << t << endl;
                    if (n[3].find(wall_tile) == string::npos) { return_map.back().push_back({t + "_1"}); }
                    else if (y < (int)map_rep.size()-1) {
                        vector<string> lower_n = get_neighbours(map_rep, {x,y+1});
                        if (lower_n[3] != wall_tile+"_tile_left"   && lower_n[3] != wall_tile+"_tile_right" &&
                            lower_n[3] != wall_tile+"_tile_center" && lower_n[3] != wall_tile+"_tile_alone") { 
                            return_map.back().push_back({t + "_2"}); 
                        }
                        else { return_map.back().push_back({t + "_top"}); }
                    }
                    else { cout << "Error at (" << x << "," << y << ")" << endl; }
                } else { return_map.back().push_back({t}); }
            }
        }
    }
    map_rep = return_map;
}


// This function assignes random textures to those that require it
void Map::handle_random_textures(vector<vector<string>>& map_rep) {
    for (int y = 0; y < (int)map_rep.size(); y++) {
        for (int x = 0; x < (int)map_rep.front().size(); x++) {
            for (pair<string,int> t : tiles_with_random_textures) {
                if (map_rep.at(y).at(x) == t.first+"_tile") { 
                    map_rep.at(y).at(x) += ("_" + to_string((rand() % t.second) + 1)); 
                }
            }
        }
    }
}


// This function replaces each tile that varies with direction and replaces them with the tile name
// This function only handles tiles in the fully_directional and horizontally_directional vectors
void Map::handle_directional_tiles(vector<vector<string>>& map_rep) {
    vector<vector<string>> return_map;
    for (int y = 0; y < (int)map_rep.size(); y++) {
        return_map.push_back({});
        for (int x = 0; x < (int)map_rep.front().size(); x++) {
            string t = map_rep.at(y).at(x);
            if (find(fully_directional_tiles.begin(), fully_directional_tiles.end(), t) != fully_directional_tiles.end()) {
                vector<string> n = get_neighbours(map_rep, {x,y});
                if      (n[0] == t && n[1] == t && n[2] == t && n[3] == t) { return_map.back().push_back({t + "_tile_center"}); }
                else if (n[0] == t && n[1] == t && n[2] == t && n[3] != t) { return_map.back().push_back({t + "_tile_bottom"}); }
                else if (n[0] == t && n[1] == t && n[2] != t && n[3] == t) { return_map.back().push_back({t + "_tile_right"}); }
                else if (n[0] == t && n[1] != t && n[2] == t && n[3] == t) { return_map.back().push_back({t + "_tile_top"}); }
                else if (n[0] != t && n[1] == t && n[2] == t && n[3] == t) { return_map.back().push_back({t + "_tile_left"}); }
                else if (n[0] == t && n[1] == t && n[2] != t && n[3] != t) { return_map.back().push_back({t + "_tile_bottom_right"}); }
                else if (n[0] == t && n[1] != t && n[2] == t && n[3] != t) { return_map.back().push_back({t + "_tile_horizontal"}); }
                else if (n[0] != t && n[1] == t && n[2] == t && n[3] != t) { return_map.back().push_back({t + "_tile_bottom_left"}); }
                else if (n[0] == t && n[1] != t && n[2] != t && n[3] == t) { return_map.back().push_back({t + "_tile_top_right"}); }
                else if (n[0] != t && n[1] == t && n[2] != t && n[3] == t) { return_map.back().push_back({t + "_tile_vertical"}); }
                else if (n[0] != t && n[1] != t && n[2] == t && n[3] == t) { return_map.back().push_back({t + "_tile_top_left"}); }
                else if (n[0] == t && n[1] != t && n[2] != t && n[3] != t) { return_map.back().push_back({t + "_tile_left_open"}); }
                else if (n[0] != t && n[1] == t && n[2] != t && n[3] != t) { return_map.back().push_back({t + "_tile_top_open"}); }
                else if (n[0] != t && n[1] != t && n[2] == t && n[3] != t) { return_map.back().push_back({t + "_tile_right_open"}); }
                else if (n[0] != t && n[1] != t && n[2] != t && n[3] == t) { return_map.back().push_back({t + "_tile_bottom_open"}); }
                else if (n[0] != t && n[1] != t && n[2] != t && n[3] != t) { return_map.back().push_back({t + "_tile_surrounded"}); }
            }
            else if (find(horizontally_directional_tiles.begin(), horizontally_directional_tiles.end(), t) != horizontally_directional_tiles.end()) {
                vector<string> n = get_neighbours(map_rep, {x,y});
                if      (n[0] == t && n[2] == t) { return_map.back().push_back({t + "_tile_center"}); }
                else if (n[0] == t && n[2] != t) { return_map.back().push_back({t + "_tile_right"}); }
                else if (n[0] != t && n[2] == t) { return_map.back().push_back({t + "_tile_left"}); }
                else if (n[0] != t && n[2] != t) { return_map.back().push_back({t + "_tile_alone"}); }
            }
            // Could allow for vertically directional tiles here
            else { return_map.back().push_back({t + "_tile"}); }
        }
    }
    map_rep = return_map;
}


// This function replaces all '.' in the map sample with ground tile types to avoid repetitive floors
void Map::replace_ground_tiles(vector<vector<string>>& map_rep) {
    
    const int NUM_OF_SEEDS = 10;
    int randx, randy, randTile;

    // Place seeds
    for (int i = 0; i < NUM_OF_SEEDS; i++) {
        bool seed_placed = false;
        while (!seed_placed) {
            randx = rand() % map_rep.front().size();
            randy = rand() % map_rep.size();
            randTile = rand() % ground_tiles.size();
            if (map_rep.at(randy).at(randx) == FLOOR) {
                map_rep.at(randy).at(randx) = ground_tiles.at(randTile);
                seed_placed = true;
            }
        }
    }
    // Spread seeds
    vector<pair<int,int>> dot_coords = get_dot_coords(map_rep);
    bool dots_exist = true;
    int randDot;
    while (dots_exist) {
        randDot = rand() % dot_coords.size();
        vector<string> neighbours = get_neighbours(map_rep, dot_coords.at(randDot));
        if (find(ground_tiles.begin(), ground_tiles.end(), neighbours.at(0)) != ground_tiles.end()) {
            map_rep.at(dot_coords.at(randDot).second).at(dot_coords.at(randDot).first) = neighbours.at(0);
            dot_coords.erase(dot_coords.begin()+randDot);
        } else if (find(ground_tiles.begin(), ground_tiles.end(), neighbours.at(1)) != ground_tiles.end()) {
            map_rep.at(dot_coords.at(randDot).second).at(dot_coords.at(randDot).first) = neighbours.at(1);
            dot_coords.erase(dot_coords.begin()+randDot);
        } else if (find(ground_tiles.begin(), ground_tiles.end(), neighbours.at(2)) != ground_tiles.end()) {
            map_rep.at(dot_coords.at(randDot).second).at(dot_coords.at(randDot).first) = neighbours.at(2);
            dot_coords.erase(dot_coords.begin()+randDot);
        } else if (find(ground_tiles.begin(), ground_tiles.end(), neighbours.at(3)) != ground_tiles.end()) {
            map_rep.at(dot_coords.at(randDot).second).at(dot_coords.at(randDot).first) = neighbours.at(3);
            dot_coords.erase(dot_coords.begin()+randDot);
        }
        if (dot_coords.size() == 0) { dots_exist = false; }
    }
}


// This function returns a list of all ground positions that haven't been given a texture yet
vector<pair<int,int>> Map::get_dot_coords(vector<vector<string>> map_rep) {
    vector<pair<int,int>> coords;
    for (int y = 0; y < (int)map_rep.size(); y++) {
        for (int x = 0; x < (int)map_rep.front().size(); x++) {
            if (map_rep.at(y).at(x) == FLOOR) { coords.push_back({x,y}); }
        }
    }
    return coords;
}


// This function returns the 4-term neighbours of a given coordinate
// [left, up, right, down]
vector<string> Map::get_neighbours(vector<vector<string>> map_rep, pair<int,int> coordinate) {
    vector<string> neighbours = {"", "", "", ""};
    if ( coordinate.first > 0 ) { neighbours[0] = map_rep.at(coordinate.second).at(coordinate.first-1); }
    if ( coordinate.second > 0 ) { neighbours[1] = map_rep.at(coordinate.second-1).at(coordinate.first); }
    if ( coordinate.first < (int)map_rep.front().size()-1 ) { neighbours[2] = map_rep.at(coordinate.second).at(coordinate.first+1); }
    if ( coordinate.second < (int)map_rep.size()-1 ) { neighbours[3] = map_rep.at(coordinate.second+1).at(coordinate.first); }
    return neighbours;
}