#pragma once
#include "iostream"
#include "windows.h"
#include <cstdint>

namespace ADDRESS {
	const uintptr_t MODULE_HANDLE = reinterpret_cast<uintptr_t>(GetModuleHandle(L"Client.exe"));
	const uintptr_t PBB_DLL_HANDLE = reinterpret_cast<uintptr_t>(GetModuleHandle(L"pbb.dll"));

	const uintptr_t PACKET_START = MODULE_HANDLE + 0x000F3680;
	const uintptr_t PACKET_END = MODULE_HANDLE + 0x000F4230;
	const uintptr_t PACKET_DATA = MODULE_HANDLE + 0x000F3AF0;
	const uintptr_t PACKET_INFO = MODULE_HANDLE + 0x000F3950;

	const uintptr_t PACKET_TARGET = MODULE_HANDLE + 0x000F3C90;
	const uintptr_t PACKET_SAY = MODULE_HANDLE + 0x000F3E30;

	const uintptr_t RED_SQUARE = MODULE_HANDLE + 0x00235EDC;

	const uintptr_t BATTLE_LIST_START_SEARCH = MODULE_HANDLE + 0x00235F70;

	const uintptr_t LOCAL_PLAYER_ID = MODULE_HANDLE + 0x00235F10;

	const uintptr_t LOCAL_PLAYER_X_POSITION = MODULE_HANDLE + 0x00245538;
	const uintptr_t LOCAL_PLAYER_Y_POSITION = MODULE_HANDLE + 0x00245534;
	const uintptr_t LOCAL_PLAYER_Z_POSITION = MODULE_HANDLE + 0x00245530;

	const uintptr_t CLIENT_STATE = PBB_DLL_HANDLE + 0x0013E140;

	const uintptr_t pMAP_START = MODULE_HANDLE + 0x0024A048;

	const uintptr_t CONTAINER_STATE = MODULE_HANDLE + 0x00242C40;
	const uintptr_t CONTAINER_ID = MODULE_HANDLE + 0x00242C44;

	const uintptr_t FISHING_ROD_CONTAINER_STATE = MODULE_HANDLE + 0x00242E2C;

	const uintptr_t POKEMON_SLOT = PBB_DLL_HANDLE + 0x0013E404;

	const uintptr_t FIGHTING_MODE = MODULE_HANDLE + 0x0038FC1C;

	const uintptr_t EXHAUSTED = MODULE_HANDLE + 0x002455A0;
}

namespace POINTER {
	int* const CLIENT_STATE = (int*)ADDRESS::CLIENT_STATE;

	int* const LOCAL_PLAYER_ID = (int*)ADDRESS::LOCAL_PLAYER_ID;

	int* const LOCAL_PLAYER_X_POSITION = (int*)ADDRESS::LOCAL_PLAYER_X_POSITION;
	int* const LOCAL_PLAYER_Y_POSITION = (int*)ADDRESS::LOCAL_PLAYER_Y_POSITION;
	int* const LOCAL_PLAYER_Z_POSITION = (int*)ADDRESS::LOCAL_PLAYER_Z_POSITION;

	int* const pMAP_START = (int*)ADDRESS::pMAP_START;

	// usage: * MAP_START = value // MAP_START = address
	int* const MAP_START = (int*)(*pMAP_START);

	int* const CONTAINER_STATE = (int*)ADDRESS::CONTAINER_STATE;
	int* const CONTAINER_ID = (int*)ADDRESS::CONTAINER_ID;

	int* const FISHING_ROD_CONTAINER_STATE = (int*)ADDRESS::FISHING_ROD_CONTAINER_STATE;

	uintptr_t* const POKEMON_SLOT = (uintptr_t*)ADDRESS::POKEMON_SLOT;

	uintptr_t* const FIGHTING_MODE = (uintptr_t*)ADDRESS::FIGHTING_MODE;
}

namespace PACKET {
	//const int START = 0x00000000;
	const int DATA = 0x0000FFFF;
	const int INFO = 0x00000000;
	const int END = 0x00000001;

	const int STEP = 0x00000066;
	const int LOOK_ITEM = 0x0000008C;
	const int USE_ITEM = 0x00000082;
	const int MOVE_ITEM = 0x00000078;
	const int USE_ON = 0x00000083;
	const int FOLLOW = 0x000000A2;
	const int ATTACK = 0x000000A1;
	const int FIGHT_MODE = 0x000000A0;
	const int SAY = 0x00000096;
}

namespace OFFSET {
	// offset next entity
	const int ENTITY = 0x000000A8;
	// entity id
	const int ID = 0x00000000;
	// entity name
	const int NAME = 0x00000004;
	// entity x position
	const int X_POSITION = 0x00000024;
	// entity y position
	const int Y_POSITION = 0x00000028;
	// entity z position
	const int Z_POSITION = 0x0000002C;
	// entity percentual health
	const int HEALTH = 0x00000088;
	// entity sprite id; is shiny? yes if 2000 < id <= 2700 else no
	const int SPRITE_ID = 0x00000060;
	// entity is local player pokemon? yes : no
	const int IS_LOCAL_PLAYER_POKEMON = 0x00000090;
	// entity can be attacked? yes : no
	const int CAN_BE_ATTACKED = 0x000000A4;
	//
	

	// offset next item
	const int ITEM = 0x0000000C;
	// item id
	const int ITEM_ID = 0x00000000;
	// item count
	const int ITEM_COUNT = 0x00000004;

	// offset next container
	const int CONTAINER = 0x00000000;
	// container state ? on : off
	const int CONTAINER_STATE = 0x00000000;
	// container id
	const int CONTAINER_ID = 0x00000000;
	// container name
	const int CONTAINER_NAME = 0x00000000;
	// how many slot a container have
	const int CONTAINER_SLOT_COUNT = 0x00000000;
	// how many items ocupy a container
	const int CONTAINER_ITEM_COUNT = 0x00000000;

	// all values gathered from the game above this section should be divided by 4 because idk

	const int TILE = 0x000002A;
	const int TILE_ITEM_COUNT = 0x00000000;
	const int TILE_ID = 0x00000001;

	const int POKEMON_SLOT[6][3] = {
		{0x8, 0x1D0, 0x24},  // Slot 1
		{0x8, 0x1D0, 0x50},  // Slot 2
		{0x8, 0x1D0, 0x7C},  // Slot 3
		{0x8, 0x1D0, 0xA8},  // Slot 4
		{0x8, 0x1D0, 0xD4},  // Slot 5
		{0x8, 0x1D0, 0x100}  // Slot 6
	};
}

namespace STEP {
	const int UP = 0x00000065;
	const int RIGHT = 0x00000066;
	const int LEFT = 0x00000068;
	const int DOWN = 0x00000067;
}

namespace BATTLELIST {
	const int MAX_SEARCH = 2048;
	const int MIN_WILD_POKEMON_ID_VALUE = 1070000000;
	const int MAX_WILD_POKEMON_ID_VALUE = 1080000000;
}

namespace COOLDOWN {
	const int TIME_TO_WAIT_FOR_TARGETING = 0x00000200;
	const int TIME_TO_WAIT_FOR_ATTACKING = 0x00000300;
	const int TIME_TO_WAIT_FOR_FISHING = 0x0001000;
	const int TIME_TO_WAIT_FOR_LOVING = 0x00016378;
	const int TIME_TO_WAIT_FOR_EGG_LOVING = 0x0002C308;
	const int SEND_PACKET = 0x0000100;
}

namespace FISHING {
	const int WILD_POKEMON_THRESHOLD = 3;
	const int MIN_COOLDOWN = 3000;
}

namespace AUTO {
	const int FISHING_ROD_CONTAINER_ID = 0x00000041;
	const int FISHING_ROD_ID = 0x00000000;
	const int MAX_FISHING_TILE_ID_VALUE = 0x00001598;
	const int MIN_FISHING_TILE_ID_VALUE = 0x00001596;
}

namespace GUI {
	const LPCSTR NAME = "Elfobot 3";
	const int WIDTH = 600;
	const int HEIGHT = 200;
	static char TARGET_WINDOW[] = "PokeBRO";
}

namespace COMMANDS {
	static const char CONNECT[] = "\x01\/init 0";

	static const char ADD_EGG_ENERGY[] = "\x01\/daycare addenergy";

	static const char LOVE[] = "\x01\/love";

	static const char HAPPINESS[] = "\x01\/happiness";

	static const char EGG_LOVE[] = "\x01\/daycare love";

	static const char THROW[] = "\x01\/throw";
}