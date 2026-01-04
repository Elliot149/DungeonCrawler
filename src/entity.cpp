#include "entity.hpp"
#include "display.hpp"
#include "map.hpp"


// ==========-----========== ENTITY FUNCTIONS ==========-----========== //

Entity::Entity() {

}

Entity::~Entity() {}


// This function handles player movement
void Entity::move(pair<float,float> direction) {
    x += direction.first;
    y += direction.second; 
}


// ==========-----========== PLAYER FUNCTIONS ==========-----========== //

// This is the constructor function for the player class
Player::Player(const pair<int,int> &spawn_pos) {
    read_sprite_file("idle_sprite_forward", idle_down_sprite);
    x = spawn_pos.first;
    y = spawn_pos.second;
    width = 16;
    height = 16;
    current_state = State::IDLE_DOWN;
    movement_speed = 3.0;
}


// This is the destructor function for the player class
Player::~Player() {}



// This function is used by the constructor function to read all of the sprites
void Player::read_sprite_file(string sprite_name, vector<vector<uint8_t>> &data_struct) {
    ifstream file("static/sprites/tiles/"+sprite_name+".tile");
    if (!file) { throw std::runtime_error("Failed to open tile file"); }

    int width, height;
    file >> width >> height;

    data_struct.resize(height);
    for (auto& row : data_struct) { row.resize(width); }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int colour;
            file >> colour;
            if (colour != 15) { data_struct[y][x] = static_cast<uint8_t>(colour); }
            else { data_struct[y][x] = 232; }   // Update here if I change EMPTY_PIXEL
        }
    }
}


// This function returns the current sprite of the player based on the state
vector<vector<uint8_t>> &Player::get_current_sprite() {
    switch(current_state) {
        case State::IDLE_DOWN: return idle_down_sprite;
        default:               return idle_down_sprite;
    }
}