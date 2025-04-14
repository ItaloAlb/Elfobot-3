#include "map.h"

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
	bool validID = (*id == 4809) || (*id == 4810) || (*id == 4811) ||
		(*id == 4812) || (*id == 4813) || (*id == 4814) ||
		(*id == 4600) || (*id == 4601) || (*id == 4602) ||
		(*id == 5526) || (*id == 5527) || (*id == 5528);

	return validID &&
		std::abs(x_position - *POINTER::LOCAL_PLAYER_X_POSITION) <= 7 &&
		std::abs(y_position - *POINTER::LOCAL_PLAYER_Y_POSITION) <= 5;
}

//bool Tile::IsValidFishingLocation() {
//	int tileId = *id;
//
//	// Conjunto com os IDs adicionais de fishing tiles.
//	static const std::unordered_set<int> fishingTileIds = {
//		0x00001596,
//		0x00001597,
//		0x00001598,
//		0x02689A84,
//		0x02689B2C,
//		0x02689BD4,
//		0x02689C7C,
//		0x02689D24,
//		0x02689DCC,
//		0x02689E74,
//		0x02689F1C,
//		0x02689FC4,
//		0x0268A06C,
//		0x0268A114,
//		0x0268A1BC,
//		0x0268A264,
//		0x0268A30C
//	};
//
//	// Verifica se o tileId é válido:
//	// Se o tileId não estiver no intervalo padrão e também não estiver no conjunto adicional, retorna false.
//	if (fishingTileIds.find(tileId) == fishingTileIds.end()) {
//		return false;
//	}
//
//	// Verifica se a posição da tile está dentro da área de alcance do jogador.
//	return std::abs(x_position - *POINTER::LOCAL_PLAYER_X_POSITION) <= 7 &&
//		std::abs(y_position - *POINTER::LOCAL_PLAYER_Y_POSITION) <= 5;
//}

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
			std::cout << "[" << *current_tile.id << "] ";
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