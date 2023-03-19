#include "entity.h"
#include "constant.h"

Entity::Entity(int address) {
	Entity::id = *(int*)(address + OFFSET::ID);
	//Entity::name = *(string*)(address + OFFSET::NAME);
	Entity::x_position = *(int*)(address + OFFSET::X_POSITION);
	Entity::y_position = *(int*)(address + OFFSET::Y_POSITION);
	Entity::z_position = *(int*)(address + OFFSET::Z_POSITION);
	Entity::health = *(int*)(address + OFFSET::HEALTH);
	Entity::can_be_attacked = *(bool*)(address + OFFSET::CAN_BE_ATTACKED);
}

void Entity::Update(int address) {
	Entity::id = *(int*)(address + OFFSET::ID);
	//Entity::name = *(string*)(address + OFFSET::NAME);
	Entity::x_position = *(int*)(address + OFFSET::X_POSITION);
	Entity::y_position = *(int*)(address + OFFSET::Y_POSITION);
	Entity::z_position = *(int*)(address + OFFSET::Z_POSITION);
	Entity::health = *(int*)(address + OFFSET::HEALTH);
	Entity::can_be_attacked = *(bool*)(address + OFFSET::CAN_BE_ATTACKED);
}

vector<int> Entity::DistanceTo(Entity entity) {
	vector<int> distance(2, NULL);
	if (z_position == entity.z_position) {
		//distance[0] = abs((int)x_position - (int)entity.x_position);
		//distance[1] = abs((int)y_position - (int)entity.y_position);
	}
	return distance;
}