#include <vector>
#include <string>
#include <curses.h>
#include <cstdint>
#include <iostream>

using namespace std;

struct Camera {
    int WIDTH;
    int HEIGHT;
    int start_x;
    int start_y;
};

class Display {

    public:
        static void draw_map(vector<vector<uint8_t>>& pixel_map, Camera& camera);

    private:

};