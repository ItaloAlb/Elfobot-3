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

bool Entity::IsValidWildPokemon() {
	return	can_be_attacked == 1 &&
			id >= BATTLELIST::MIN_WILD_POKEMON_ID_VALUE &&
			id <= BATTLELIST::MAX_WILD_POKEMON_ID_VALUE &&
			health > 0 &&
			z_position == *POINTER::LOCAL_PLAYER_Z_POSITION &&
			std::abs(x_position - *POINTER::LOCAL_PLAYER_X_POSITION) <= 7 &&
			std::abs(y_position - *POINTER::LOCAL_PLAYER_Y_POSITION) <= 5;
}

int Entity::GetId() {
	return id;
}

Util::Vector3 Entity::Get_Location() {
	return Util::Vector3(x_position, y_position, z_position);
}