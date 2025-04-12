#pragma once
#include "string"
#include "vector"
#include "util.h"

using namespace std;

class Entity {
	public:
		int id;

		int x_position;
		int y_position;
		int z_position;
		int health;
		int sprite_id;
		bool is_local_player_pokemon;
		bool can_be_attacked;

		Entity(int address);

		void Update(int address);

		Util::Vector3 GetLocation();
		
		int GetId();

		int GetPercentualHealth();

		bool GetCanBeAttacked();

		bool IsValidWildPokemon();

		bool IsShiny();

		bool IsLocalPlayerPokemon();
};