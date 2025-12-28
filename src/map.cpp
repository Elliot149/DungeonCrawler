#include "map.hpp"
#include "display.hpp"


// Constructor function for the map class
Map::Map() {
    // This will change after I implement random generation
    pair<vector<vector<string>>, vector<vector<string>>> maps = generate_map();

    Display* display = new Display(); 

    // for (int y = 0; y < (int)maps.first.size() * display->TILE_HEIGHT; y++) { 
    //     Map::id_map.push_back({});
    //     Map::pixel_map.push_back({});
    //     int yInd = floor(y/display->TILE_HEIGHT);
    //     for (int x = 0; x < (int)maps.first.front().size() * display->TILE_WIDTH*2; x++) {
    //         int xInd = floor(x/(display->TILE_WIDTH*2));
    //         Map::id_map.at(y).push_back(maps.first.at(yInd).at(xInd));
    //         Map::pixel_map.at(y).push_back(display->get_pixel({x%16,y%16}, 
    //                                                           maps.first.at(yInd).at(xInd), 
    //                                                           get_neighbours(maps.first, {xInd, yInd})));
    //     }
    // }
}


// Destructor function for the map class
Map::~Map() {

}


// This is the master function for generating the map
pair<vector<vector<string>>, vector<vector<string>>> Map::generate_map() {
    vector<vector<string>> map_sample = {
        {"W", "W", "W", "W", "W", "W", "W", "W", "W", "W", "W", "W", "~", "~", "~", "~"},
        {"W", ".", ".", ".", "W", ".", ".", ".", ".", ".", ".", ".", "~", "~", "~", "~"},
        {"W", ".", ".", ".", "W", ".", ".", ".", ".", ".", ".", ".", ".", "~", "~", "~"},
        {"W", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "~", "~", "~"},
        {"W", ".", ".", ".", "W", "W", "W", "W", ".", ".", ".", ".", ".", "~", "~", "~"},
        {"W", ".", ".", ".", "W", "W", "W", "W", ".", ".", ".", ".", ".", ".", "~", "~"},
        {"W", ".", ".", ".", ".", ".", ".", "W", ".", ".", ".", ".", ".", ".", "~", "~"},
        {"W", ".", ".", ".", ".", ".", ".", "W", ".", ".", ".", ".", "~", "~", "~", "~"},
        {"W", "W", "W", "W", "W", "W", "W", "W", "w", "W", "W", "W", "W", "W", "W", "~"},
        {"W", "W", "W", "W", "W", "W", "W", "W", "w", "W", "W", "W", "W", "W", "W", "~"},
    };
    vector<vector<string>> map = replace_ground_tiles(map_sample);

    return {map, map};    //This is temp
}


// This function replaces all '.' in the map sample with ground tile types to avoid repetitive floors
vector<vector<string>> Map::replace_ground_tiles(vector<vector<string>> map_rep) {
    vector<string> tile_types = {GRASS, GRAVEL, DIRT, STONE};
    const int NUM_OF_SEEDS = 10;
    int randx, randy, randTile;

    // Place seeds
    for (int i = 0; i < NUM_OF_SEEDS; i++) {
        bool seed_placed = false;
        while (!seed_placed) {
            randx = rand() % map_rep.front().size();
            randy = rand() % map_rep.size();
            randTile = rand() % tile_types.size();
            if (map_rep.at(randy).at(randx) == ".") {
                map_rep.at(randy).at(randx) = tile_types.at(randTile);
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
        if (find(tile_types.begin(), tile_types.end(), neighbours.at(0)) != tile_types.end()) {
            map_rep.at(dot_coords.at(randDot).second).at(dot_coords.at(randDot).first) = neighbours.at(0);
            dot_coords.erase(dot_coords.begin()+randDot);
        } else if (neighbours.size() >= 1 && find(tile_types.begin(), tile_types.end(), neighbours.at(1)) != tile_types.end()) {
            map_rep.at(dot_coords.at(randDot).second).at(dot_coords.at(randDot).first) = neighbours.at(1);
            dot_coords.erase(dot_coords.begin()+randDot);
        } else if (neighbours.size() >= 2 && find(tile_types.begin(), tile_types.end(), neighbours.at(2)) != tile_types.end()) {
            map_rep.at(dot_coords.at(randDot).second).at(dot_coords.at(randDot).first) = neighbours.at(2);
            dot_coords.erase(dot_coords.begin()+randDot);
        } else if (neighbours.size() >= 3 && find(tile_types.begin(), tile_types.end(), neighbours.at(3)) != tile_types.end()) {
            map_rep.at(dot_coords.at(randDot).second).at(dot_coords.at(randDot).first) = neighbours.at(3);
            dot_coords.erase(dot_coords.begin()+randDot);
        }
        if (dot_coords.size() == 0) { dots_exist = false; }
    }

    return map_rep;
}


// This function returns a list of all ground positions that haven't been given a texture yet
vector<pair<int,int>> Map::get_dot_coords(vector<vector<string>> map_rep) {
    vector<pair<int,int>> coords;
    for (int y = 0; y < (int)map_rep.size(); y++) {
        for (int x = 0; x < (int)map_rep.front().size(); x++) {
            if (map_rep.at(y).at(x) == ".") { coords.push_back({x,y}); }
        }
    }
    return coords;
}


// This function returns the 4-term neighbours of a given coordinate
vector<string> Map::get_neighbours(vector<vector<string>> map_rep, pair<int,int> coordinate) {
    vector<string> neighbours;
    if ( coordinate.first > 0 ) { neighbours.push_back(map_rep.at(coordinate.second).at(coordinate.first-1)); }
    if ( coordinate.second > 0 ) { neighbours.push_back(map_rep.at(coordinate.second-1).at(coordinate.first)); }
    if ( coordinate.first < (int)map_rep.front().size() ) { neighbours.push_back(map_rep.at(coordinate.second).at(coordinate.first+1)); }
    if ( coordinate.second < (int)map_rep.size() ) { neighbours.push_back(map_rep.at(coordinate.second+1).at(coordinate.first)); }
    return neighbours;
}