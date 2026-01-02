#include "tile.hpp"

unordered_map<string, Tile> Tile::cache;

// Public constructor used to create a tile by passing it a name
Tile::Tile(const string& texture_name) {
    auto it = cache.find(texture_name);
    if (it != cache.end()) {
        *this = it->second;
        return;
    }

    Tile loaded = load_texture(texture_name);
    cache.emplace(texture_name, loaded);
    *this = loaded;
}


// Private constructor used when loading a new texture for the first time
Tile::Tile() {
    hitbox = false;
}


// Function used to load textures from a .tile file
Tile Tile::load_texture(const string& texture_name) {

    Tile tile;
    tile.name = texture_name;

    ifstream file("static/tiles/tiles/"+texture_name+".tile");
    if (!file) { throw std::runtime_error("Failed to open tile file"); }

    // Currently can't handle when textures exceed 16x16
    int width, height;
    file >> width >> height;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int colour;
            file >> colour;
            tile.pixels[y][x] = static_cast<uint8_t>(colour);
        }
    }
    const string hitboxTiles[] = {"wall", "water"};
    for (string s : hitboxTiles) {
        if (texture_name.find(s) != string::npos) { tile.hitbox = true; }
    }
    return tile;
}


// // This function returns the pixel value at a given coord
// uint8_t Tile::get_pixel(pair<int,int> tileCoord) const {
//     return pixels[tileCoord.second][tileCoord.first];
// }