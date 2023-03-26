#pragma once
#include "enum.h"
#include "util.h"

class Tile {
	public:
		// item_count: a pointer to tile item count value (i.e. how many items a tile has)
		int* item_count;
		// id: a pointer to tile id value 
		int* id;

		int x_position;
		int y_position;
		int z_position;

		Tile();

		Tile(int* adress, int x, int y, int z);

		bool IsValidFishingLocation();
};

class Map {
	private:
		bool state;

		int init_x, init_y;
		int last_dx, last_dy;
		int dx, dy;
	public:
		Tile tile[8][14][18];

		Map();

		void Initialize();

		void Update();

		Util::Vector3 GetFishingLocation();


};
