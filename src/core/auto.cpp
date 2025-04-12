#include "auto.h"


using milliseconds = std::chrono::milliseconds;

bool Auto::controller_targeting = false;

bool Auto::controller_fishing = false;

bool Auto::controller_loving = false;

bool Auto::controller_egg_loving = false;

int Auto::controller_fishing_cooldown = 3;

int Auto::controller_fishing_rod_container = 0x41;

int Auto::controller_fishing_rod_id = 0x0;

bool Auto::controller_attacking = false;

bool Auto::controller_connecting = false;

int Auto::controller_fishing_wild_pokemon_threshold = 3;

bool Auto::is_wasd_move = false;

bool Auto::top_hunt = false;

int Auto::aoeCount[6] = { 2, 2, 2, 2, 2, 2 };

std::vector<Ability> Auto::moveset;

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
		if (!entity_id_list.empty() && *POINTER::CLIENT_STATE == 1) {
			auto entity_id = entity_id_list.back();
			if ((*(int*)ADDRESS::RED_SQUARE == 0) || *(int*)ADDRESS::RED_SQUARE != entity_id) {
				*(int*)(ADDRESS::RED_SQUARE) = entity_id;
				SendPacket::EnqueueAttack(entity_id);
				//SendPacket::Attack(entity_id);
			}
		}
		std::this_thread::sleep_for(milliseconds(COOLDOWN::TIME_TO_WAIT_FOR_TARGETING));
	}
}

void Auto::Fishing(bool& controller) {
	Map map = Map();
	while (controller) {
		map.Update();
		Entity entity(BattleList::GetLocalPlayerPokemonAddress());

		std::cout << entity.GetPercentualHealth() << std::endl;
		std::cout << entity.GetId() << std::endl;
		
		//Entity entity(BattleList::GetLocalPlayerPokemonAddress());
		//std::cout << entity.GetPercentualHealth() << std::endl;
		auto fishing_location = map.GetFishingLocation();
		if (fishing_location.IsValid() && 
			*POINTER::CLIENT_STATE == 1 && 
			BattleList::GetEntityCount(ONLY_WILD_POKEMON) <= controller_fishing_wild_pokemon_threshold &&
			entity.GetPercentualHealth() >= 30) {
			SendPacket::EnqueueUseOn(Auto::controller_fishing_rod_container, Auto::controller_fishing_rod_id, fishing_location);
			Sleep(controller_fishing_cooldown * 1000);
		}
	}
}

//void Auto::Attacking(bool& controller) {
//	while (controller) {
//		const char* moves[] = { "m12", "m11", "m10", "m9", "m8", "m7", "m6", "m5", "m4", "m3", "m2", "m1" };
//		for (int i = 0; i < 12; i++) {
//			if (*(int*)ADDRESS::RED_SQUARE == 0 || *POINTER::CLIENT_STATE == 0) {
//				break;
//			}
//			Sleep(COOLDOWN::TIME_TO_WAIT_FOR_ATTACKING);
//			SendPacket::Say((char*)moves[i], 0x1);
//		}
//	}
//	
//}

void Auto::Attacking(bool& controller) {
	while (controller) {
		if (*POINTER::CLIENT_STATE == 0) {
			continue;
		}

		// Coleta a situação de combate, levando em conta a ausência de inimigos também
		int situation = BattleList::GetCombatSituation();

		// Checa se não há inimigo visível (ex: red square == 0)
		if (*(int*)ADDRESS::RED_SQUARE == 0) {
			situation = CombatSituation::NO_ENEMY;
		}

		// Decide o que fazer com base na situação
		Ability* bestAbility = SelectBestAbility(moveset, situation);

		if (bestAbility) {
			// Executa a sequência de ataque
			*POINTER::FIGHTING_MODE = 1;
			SendPacket::EnqueueFightMode(1, 0, 0);
			SendPacket::EnqueueSay(bestAbility->name.c_str(), 0x1);
			*POINTER::FIGHTING_MODE = 3;
			SendPacket::EnqueueFightMode(3, 0, 0);

			bestAbility->cooldownRemaining = bestAbility->cooldown;
		}
		Sleep(COOLDOWN::TIME_TO_WAIT_FOR_ATTACKING);
	}
}

void Auto::Loving(bool& controller) {
	while (controller) {
		if (*POINTER::CLIENT_STATE == 1) {
			SendPacket::EnqueueSay(COMMANDS::LOVE, 1);
			//SendPacket::Say(COMMANDS::LOVE, 0x1);
			Sleep(COOLDOWN::TIME_TO_WAIT_FOR_LOVING);
		}
	};

}

void Auto::Egg_Loving(bool& controller) {
	while (controller) {
		if (*POINTER::CLIENT_STATE == 1) {
			SendPacket::EnqueueSay(COMMANDS::EGG_LOVE, 1);
			//SendPacket::Say(COMMANDS::EGG_LOVE, 0x1);
			Sleep(COOLDOWN::TIME_TO_WAIT_FOR_EGG_LOVING);
		}
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

int Auto::CalculateAbilityScore(const Ability& ability, int situation) {
	int score = 0;

	// If no enemy around, only heal abilities count.
	if (situation == CombatSituation::NO_ENEMY) {
		if (std::find(ability.tags.begin(), ability.tags.end(), "heal") != ability.tags.end())
			score += 1000;
		if (std::find(ability.tags.begin(), ability.tags.end(), "single target") != ability.tags.end())
			score -= 10000;
		if (std::find(ability.tags.begin(), ability.tags.end(), "offensive buff") != ability.tags.end())
			score -= 10000;
		if (std::find(ability.tags.begin(), ability.tags.end(), "deffensive buff") != ability.tags.end())
			score -= 10000;
		if (std::find(ability.tags.begin(), ability.tags.end(), "AoE") != ability.tags.end())
			score -= 10000;
	}
	// Single enemy scenario.
	else if (situation == CombatSituation::SINGLE_ENEMY) {
		// Favor single target abilities.
		if (std::find(ability.tags.begin(), ability.tags.end(), "single target") != ability.tags.end())
			score += 200;
		// Also favor abilities with healing effects.
		if (std::find(ability.tags.begin(), ability.tags.end(), "heal") != ability.tags.end())
			score += 50;
		 //Defensive buffs might be secondary.
		if (std::find(ability.tags.begin(), ability.tags.end(), "offensive buff") != ability.tags.end())
			score += 200;
		if (std::find(ability.tags.begin(), ability.tags.end(), "deffensive buff") != ability.tags.end())
			score += 100;
	}
	// Multiple enemies scenario.
	else if (situation == CombatSituation::MULTIPLE_ENEMIES) {
		// Favor buffing first.
		if (std::find(ability.tags.begin(), ability.tags.end(), "offensive buff") != ability.tags.end())
			score += 200;
		if (std::find(ability.tags.begin(), ability.tags.end(), "deffensive buff") != ability.tags.end())
			score += 200;
		if (std::find(ability.tags.begin(), ability.tags.end(), "AoE") != ability.tags.end())
			score += 180;
		if (std::find(ability.tags.begin(), ability.tags.end(), "single target") != ability.tags.end())
			score += 100;
		if (std::find(ability.tags.begin(), ability.tags.end(), "heal") != ability.tags.end())
			score += 50;
	}
	// Adjust score further based on cooldown if needed (e.g., lower cooldown might be more favorable)
	// For example, you can subtract the cooldown from the score.
	score += - ability.cooldownRemaining * 1000;

	return score;
}

Ability* Auto::SelectBestAbility(const std::vector<Ability>& moveset, int situation) {
	int bestScore = 0; // Start with a very low score.
	Ability* bestAbility = nullptr;

	// Iterate through moveset.
	for (const auto& ability : moveset) {
		int score = CalculateAbilityScore(ability, situation);
		if (score > bestScore) {
			bestScore = score;
			bestAbility = const_cast<Ability*>(&ability);
		}
	}

	return bestAbility;
}

void Auto::UpdateCooldowns(float deltaTime) {
	for (auto& ability : moveset) {
		if (ability.cooldownRemaining > 0) {
			ability.cooldownRemaining -= deltaTime;
			if (ability.cooldownRemaining < 0)
				ability.cooldownRemaining = 0;
		}
	}
}