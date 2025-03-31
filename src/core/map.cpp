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

bool Tile::IsValidFishingLocation() {
	return	*id >= AUTO::MIN_FISHING_TILE_ID_VALUE &&
			*id <= AUTO::MAX_FISHING_TILE_ID_VALUE &&
			std::abs(x_position - *POINTER::LOCAL_PLAYER_X_POSITION) <= 7 &&
			std::abs(y_position - *POINTER::LOCAL_PLAYER_Y_POSITION) <= 5;
}

Map::Map() {
	Map::state = false;
	Initialize();
	return;
}

void Map::Initialize() {
	if (*POINTER::CLIENT_STATE == 0) {
		return;
	}

	init_x = *POINTER::LOCAL_PLAYER_X_POSITION;
	init_y = *POINTER::LOCAL_PLAYER_Y_POSITION;

	last_dx = 0;
	last_dy = 0;

	int i = 0;
	for (int z = 0; z < 8; z++) {
		for (int y = 0; y < 14; y++) {
			for (int x = 0; x < 18; x++) {
				Map::tile[z][y][x] = Tile((int*)(POINTER::MAP_START + OFFSET::TILE * i), *POINTER::LOCAL_PLAYER_X_POSITION + x - 8, *POINTER::LOCAL_PLAYER_Y_POSITION + y - 6, z);
				i++;
			}
		}
	}
	state = true;
	return;
}

void Map::Update() {
	if (*POINTER::CLIENT_STATE == 0) {
		return;
	}

	// Se o player mudou de posição, reinicializa o mapa
	if (*POINTER::LOCAL_PLAYER_X_POSITION != init_x || *POINTER::LOCAL_PLAYER_Y_POSITION != init_y) {
		Initialize();
	}
}

void Map::PrintMap()
{
	std::cout << "==== MAP DATA ====" << std::endl;
	for (int y = 0; y < 14; y++) {
		for (int x = 0; x < 18; x++) {
			auto& current_tile = tile[*POINTER::LOCAL_PLAYER_Z_POSITION - 7][y][x];
			std::cout << "[" << current_tile.id << "] ";
		}
		std::cout << std::endl;
	}
	std::cout << "==================" << std::endl;
}

Util::Vector3 Map::GetFishingLocation() {
	for (int y = 0; y < 14; y++) {
		for (int x = 0; x < 18; x++) {
			auto& current_tile = tile[*POINTER::LOCAL_PLAYER_Z_POSITION - 7][y][x];
			if(current_tile.IsValidFishingLocation()) {
				return { current_tile.x_position, current_tile.y_position, *POINTER::LOCAL_PLAYER_Z_POSITION };
			}
		}
	}
	return { };
}