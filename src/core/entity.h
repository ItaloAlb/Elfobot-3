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
		bool can_be_attacked;

		Entity(int address);

		void Update(int address);

		Util::Vector3 Get_Location();
		
		int GetId();

		int GetHealth();

		bool GetCanBeAttacked();

		bool IsValidWildPokemon();
};