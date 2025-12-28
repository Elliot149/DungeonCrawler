#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;
using tileID = int;

#define GRASS "G"
#define GRAVEL "g"
#define DIRT "d"
#define STONE "S"

class Map {
    public:

        Map();                                     // Constructor function
        ~Map();                                    // Destructor function
        static vector<vector<string>> pixel_map;   // Stores the ascii codes of each pixel on the map
        static vector<vector<string>> id_map;      // Stores what each pixel on the map actually is
        int width, height;

    private:

        static pair<vector<vector<string>>, vector<vector<string>>> generate_map();
        static vector<vector<string>> replace_ground_tiles(vector<vector<string>> map_rep);
        static vector<pair<int,int>> get_dot_coords(vector<vector<string>> map_rep);
        static vector<string> get_neighbours(vector<vector<string>> map_rep, pair<int,int> coordinate);
};