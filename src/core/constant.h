#pragma once
#include "iostream"
#include "windows.h"

namespace ADDRESS {
	const int MODULE_HANDLE = (int)GetModuleHandle(L"Client.exe");
	const int PBB_DLL_HANDLE = (int)GetModuleHandle(L"pbb.dll");

	const int PACKET_START = MODULE_HANDLE + 0x000F3680;
	const int PACKET_END = MODULE_HANDLE + 0x000F4230;
	const int PACKET_DATA = MODULE_HANDLE + 0x000F3AF0;
	const int PACKET_INFO = MODULE_HANDLE + 0x000F3950;

	const int PACKET_TARGET = MODULE_HANDLE + 0x000F3C90;
	const int PACKET_SAY = MODULE_HANDLE + 0x000F3E30;

	const int RED_SQUARE = MODULE_HANDLE + 0x00235EDC;

	const int BATTLE_LIST_START_SEARCH = MODULE_HANDLE + 0x00235F70;

	const int LOCAL_PLAYER_ID = MODULE_HANDLE + 0x00235F10;

	const int LOCAL_PLAYER_X_POSITION = MODULE_HANDLE + 0x00245538;
	const int LOCAL_PLAYER_Y_POSITION = MODULE_HANDLE + 0x00245534;
	const int LOCAL_PLAYER_Z_POSITION = MODULE_HANDLE + 0x00245530;

	const int CLIENT_STATE = PBB_DLL_HANDLE + 0x0013E140;

	const int pMAP_START = MODULE_HANDLE + 0x0024A048;

	const int CONTAINER_STATE = MODULE_HANDLE + 0x00242C40;
	const int CONTAINER_ID = MODULE_HANDLE + 0x00242C44;

	const int FISHING_ROD_CONTAINER_STATE = MODULE_HANDLE + 0x00243018;
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

}

namespace PACKET {
	//const int START = 0x00000000;
	const int DATA = 0x0000FFFF;
	const int INFO = 0x00000000;
	const int END = 0x00000001;

	const int LOOK_ITEM = 0x0000008C;
	const int USE_ITEM = 0x00000082;
	const int MOVE_ITEM = 0x00000078;
	const int USE_ON = 0x00000083;
	const int FOLLOW = 0x000000A2;
	const int ATTACK = 0x000000A1;
	const int FIGHT_MODE = 0x000000A1;
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
	// entity can be attacked? yes : no
	const int CAN_BE_ATTACKED = 0x000000A4;

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
}

namespace BATTLELIST {
	const int MAX_SEARCH = 2048;
	const int MIN_WILD_POKEMON_ID_VALUE = 1070000000;
	const int MAX_WILD_POKEMON_ID_VALUE = 1080000000;
}

namespace COOLDOWN {
	const int TIME_TO_WAIT_FOR_TARGETING = 0x00000200;
	const int TIME_TO_WAIT_FOR_ATTACKING = 0x00000200;
	const int TIME_TO_WAIT_FOR_FISHING = 0x0001000;
	const int SEND_PACKET = 0x00000032;
}

namespace AUTO {
	const int FISHING_ROD_CONTAINER_ID = 0x00000041;
	const int FISHING_ROD_ID = 0x00000000;
	const int MAX_FISHING_TILE_ID_VALUE = 0x00001598;
	const int MIN_FISHING_TILE_ID_VALUE = 0x00001596;
}

namespace GUI {
	const LPCSTR NAME = "Elfobot 3";
	const int WIDTH = 250;
	const int HEIGHT = 350;
	static char TARGET_WINDOW[] = "PokeBRO";
}