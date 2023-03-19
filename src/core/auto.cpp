#include "constant.h"
#include "auto.h"
#include "packet.h"
#include "enum.h"
#include "iostream"

void Auto::Targeting(std::atomic<bool>& controller) {
	controller = true;
	while (controller) {
		uint32_t entity_id = BattleList::GetEntityIdList(ONLY_ONE_WILD_POKEMON).back();
		if ((*(int*)ADDRESS::RED_SQUARE == 0) || *(int*)ADDRESS::RED_SQUARE != entity_id) {
			*(int*)(ADDRESS::RED_SQUARE) = entity_id;
			SendPacket::Attack(entity_id);
		}
	}
}

void Auto::Fishing(std::atomic<bool>& controller, Map& map) {
	controller = true;
	while (controller) {
		Sleep(COOLDOWN::TIME_TO_WAIT_FOR_FISHING);
		Vector3* fishing_location = new Vector3(map.GetFishingTileLocation());
		SendPacket::UseOn(AUTO::FISHING_ROD_CONTAINER_ID, AUTO::FISHING_ROD_ID, fishing_location->x, fishing_location->y, fishing_location->z);
		delete fishing_location;
	}
}

//need improvement
void Auto::Attacking(std::atomic<bool>& controller) {
	controller = true;
	while (controller) {
		const char* moves[] = { "m1", "m2", "m3", "m4", "m5", "m6", "m7", "m8", "m9", "m10", "m11", "m12" };
		for (int i = 0; i < 12; i++) {
			if (*(int*)ADDRESS::RED_SQUARE == 0) {
				break;
			}
			Sleep(COOLDOWN::TIME_TO_WAIT_FOR_ATTACKING);
			SendPacket::Say((char*)moves[i], 0x1);
		}
	}
	
}