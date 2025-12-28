#include <vector>
#include <string>
#include <curses.h>
#include "tile.hpp"

using namespace std;

class Display {

    public:
        Display();
        ~Display();
        static string get_pixel(pair<int,int> tileCoord, string symbol, vector<string> neighbours);

    private:

};