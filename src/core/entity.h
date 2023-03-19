#pragma once
#include "string"
#include "vector"

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

		vector<int> DistanceTo(Entity entity);
};