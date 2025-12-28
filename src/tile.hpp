#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Tile {
    public:
        Tile(const string& texture_name);
        string name;
        bool hitbox;
        static constexpr int WIDTH  = 16;
        static constexpr int HEIGHT = 16;
        uint8_t pixels[HEIGHT][WIDTH];
    
    private:
        Tile();
        static unordered_map<string, Tile> cache;
        static Tile load_texture(const string& texture_name);
};