#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

using namespace std;

class Player {

    public:
        Player(const pair<int,int> &spawn_pos);
        ~Player();
        void move(pair<int,int> direction, vector<vector<uint8_t>>& pixel_map, vector<vector<string>>& id_map);
        pair<int,int> get_coordinates();
        vector<vector<uint8_t>> &get_current_sprite();

        enum class State {
            IDLE_UP,    IDLE_DOWN,    IDLE_LEFT,    IDLE_RIGHT,
            RUNNING_UP, RUNNING_DOWN, RUNNING_LEFT, RUNNING_RIGHT,
            ATTACK_UP,  ATTACK_DOWN,  ATTACK_LEFT,  ATTACK_RIGHT
        };

    private:
        static constexpr int WIDTH  = 16;
        static constexpr int HEIGHT = 16;
        int x, y;
        State current_state;

        vector<vector<uint8_t>> idle_down_sprite;
        vector<vector<uint8_t>> idle_up_sprite;
        vector<vector<uint8_t>> idle_right_sprite;
        vector<vector<uint8_t>> idle_left_sprite;

        static void read_sprite_file(string sprite_name, vector<vector<uint8_t>> &data_struct);
};