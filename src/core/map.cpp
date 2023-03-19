#include "map.h"
#include "constant.h"

Tile::Tile(int* address, int x, int y, int z) {
	Tile::item_count = address + OFFSET::TILE_ITEM_COUNT;
	Tile::id = address + OFFSET::TILE_ID;

	Tile::x_position = x;
	Tile::y_position = y;
	Tile::z_position = z;

}

Tile::Tile() {
	// default constructor
}

Map::Map() {
	Update();
	return;
}

void Map::Update() {
	if (*POINTER::CLIENT_STATE == 0) {
		return;
	}
	int i = 0;
	for (int z = 0; z < 8; z++) {
		for (int y = 0; y < 14; y++) {
			for (int x = 0; x < 18; x++) {
				Map::tile[z][y][x] = Tile((int*)(POINTER::MAP_START + OFFSET::TILE * i), *POINTER::LOCAL_PLAYER_X_POSITION + x - 8, *POINTER::LOCAL_PLAYER_Y_POSITION + y - 6, z);
				i++;
			}
		}
	}
	return;
}

void Map::Debug() {
	for (int y = 0; y < 14; y++) {
		for (int x = 0; x < 18; x++) {
			std::cout<< * tile[0][y][x].id << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Vector3 Map::GetFishingTileLocation() {
	Vector3 location;
	for (int y = 0; y < 14; y++) {
		for (int x = 0; x < 18; x++) {
			if ((*tile[*POINTER::LOCAL_PLAYER_Z_POSITION - 7][y][x].id >= AUTO::MIN_FISHING_TILE_ID_VALUE) && 
				(*tile[*POINTER::LOCAL_PLAYER_Z_POSITION - 7][y][x].id <= AUTO::MAX_FISHING_TILE_ID_VALUE) &&
				(abs(tile[*POINTER::LOCAL_PLAYER_Z_POSITION - 7][y][x].x_position - *POINTER::LOCAL_PLAYER_X_POSITION) <= 7) &&
				(abs(tile[*POINTER::LOCAL_PLAYER_Z_POSITION - 7][y][x].y_position - *POINTER::LOCAL_PLAYER_Y_POSITION) <= 5)) {
				location = Vector3(
					tile[*POINTER::LOCAL_PLAYER_Z_POSITION - 7][y][x].x_position, 
					tile[*POINTER::LOCAL_PLAYER_Z_POSITION - 7][y][x].y_position, 
					*POINTER::LOCAL_PLAYER_Z_POSITION);
			}
		}
	}

	return location;
}