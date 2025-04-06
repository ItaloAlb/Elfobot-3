#include "auto.h"
#include "constant.h"
#include "packet.h"
#include "enum.h"
#include "thread"

using milliseconds = std::chrono::milliseconds;

bool Auto::controller_targeting = false;

bool Auto::controller_fishing = false;

bool Auto::controller_loving = false;

bool Auto::controller_egg_loving = false;

int Auto::controller_fishing_rod_container = 0x40;

int Auto::controller_fishing_rod_id = 0x0;

bool Auto::controller_attacking = false;

bool Auto::controller_connecting = false;

bool Auto::is_wasd_move = false;

bool Auto::top_hunt = false;

int Auto::aoeCount[6] = { 2, 2, 2, 2, 2, 2 };

bool Auto::cooldownActive[6] = { false, false, false, false, false, false };
float Auto::cooldownRemaining[6] = { 0, 0, 0, 0, 0, 0 };

char Auto::buff[6][4] = { 0 };
char Auto::protect[6][4] = { 0 };
char Auto::aoe[6][4][4] = { 0 };
char Auto::cooldown[6][4] = { 0 };
int Auto::iCooldown[6] = { 0 };

int Auto::slot[6] = { 0 };

void Auto::Targeting(bool& controller) {
	while (controller) {
		auto entity_id_list = BattleList::GetEntityIdList(ONLY_ONE_WILD_POKEMON);
		if (!entity_id_list.empty()) {
			auto entity_id = entity_id_list.back();
			if ((*(int*)ADDRESS::RED_SQUARE == 0) || *(int*)ADDRESS::RED_SQUARE != entity_id) {
				*(int*)(ADDRESS::RED_SQUARE) = entity_id;
				SendPacket::Attack(entity_id);
			}
		}
		std::this_thread::sleep_for(milliseconds(COOLDOWN::TIME_TO_WAIT_FOR_TARGETING));
	}
}

void Auto::Fishing(bool& controller) {
	Map map = Map();
	while (controller) {
		map.Update();
		auto fishing_location = map.GetFishingLocation();
		if (fishing_location.IsValid()) {
			SendPacket::UseOn(Auto::controller_fishing_rod_container, Auto::controller_fishing_rod_id, fishing_location);
			std::this_thread::sleep_for(milliseconds(COOLDOWN::TIME_TO_WAIT_FOR_FISHING));
		}	
	}
}

void Auto::Attacking(bool& controller) {
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

void Auto::Loving(bool& controller) {
	while (controller) {
		SendPacket::Say(COMMANDS::LOVE, 0x1);
		Sleep(COOLDOWN::TIME_TO_WAIT_FOR_LOVING);
	};

}

void Auto::Egg_Loving(bool& controller) {
	while (controller) {
		SendPacket::Say(COMMANDS::EGG_LOVE, 0x1);
		Sleep(COOLDOWN::TIME_TO_WAIT_FOR_EGG_LOVING);
	};

}

void Auto::Callback(std::function<void(bool&)> call, bool& controller) {
	if (controller && *POINTER::CLIENT_STATE == 1) {
		std::thread thread_call(call, std::ref(controller));
		thread_call.detach();
	}
}

void Auto::Connecting(bool& controller) {
	while (controller) {
		if (*POINTER::CLIENT_STATE == 0) {
			SendPacket::Say(COMMANDS::CONNECT, 0x1);
		}
		Sleep(128);
	};

}
