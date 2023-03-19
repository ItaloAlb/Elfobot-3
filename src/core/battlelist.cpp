#pragma once
#include "battlelist.h"
#include "constant.h"

BattleList::BattleList() {
	BattleList::last_search_index = 0;
}

list<int> BattleList::GetEntityIdList(Flag flag, int last_search_index) {
	list<int> entity_id_list(1, 0);

	if (flag == ALL) {
		for (int i = last_search_index; i < last_search_index + BATTLELIST::MAX_SEARCH; i++) {
			Entity entity(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
			if (entity.id == 0) {
				break;
			}
			entity_id_list.push_back(entity.id);
		}
	}

	if (flag == ONLY_WILD_POKEMON || flag == ONLY_ONE_WILD_POKEMON) {
		for (int i = last_search_index; i < last_search_index + BATTLELIST::MAX_SEARCH; i++) {
			Entity entity(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
			if (entity.id == 0) {
				break;
			}
			if ((entity.id > BATTLELIST::MIN_WILD_POKEMON_ID_VALUE) &&
				(entity.id < BATTLELIST::MAX_WILD_POKEMON_ID_VALUE) &&
				(entity.health > 0) &&
				(entity.can_be_attacked) &&
				(entity.z_position == * POINTER::LOCAL_PLAYER_Z_POSITION) &&
				(abs(entity.x_position - * POINTER::LOCAL_PLAYER_X_POSITION) <= 7) &&
				(abs(entity.y_position - * POINTER::LOCAL_PLAYER_Y_POSITION) <= 5)) {
				entity_id_list.push_back(entity.id);
				if (flag == ONLY_ONE_WILD_POKEMON) {
					return entity_id_list;
				}

			}
		}
	}
	return entity_id_list;
}

int BattleList::GetLocalPlayerAddress() {
	for (int i = 0; i < BATTLELIST::MAX_SEARCH; i++) {
		int entity_id = *(int*)(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
		if (entity_id == 0) {
			break;
		}
		if (entity_id == * POINTER::LOCAL_PLAYER_ID) {
			return (ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
		}
	}
}
