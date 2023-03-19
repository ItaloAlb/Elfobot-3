#pragma once
#include "enum.h"
#include "util.h"

using namespace std;
using namespace Struct;

struct Tile {
	// item_count: a pointer to tile item count value
	int* item_count;
	// id: a pointer to tile id value
	int* id;

	int x_position;
	int y_position;
	int z_position;

	Tile();

	Tile(int* adress, int x, int y, int z);
};

class Map {
	private:
		bool state;
	public:
		Tile tile[8][14][18];

		Map();

		void Update();

		Vector3 GetFishingTileLocation();

		void Debug();
};
