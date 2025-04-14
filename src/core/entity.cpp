#include "entity.h"
#include "constant.h"

Entity::Entity(int address) {
    if (address == -1) {
        // Configura uma entidade com valores inválidos ou um estado de erro
        Entity::id = -1;
        // Se for uma string, considere atribuir uma string vazia ou "invalido"
        Entity::x_position = -1;
        Entity::y_position = -1;
        Entity::z_position = -1;
        Entity::health = -1;
        Entity::can_be_attacked = false; // melhor representado como false, pois bool
        Entity::sprite_id = -1;
        Entity::is_local_player_pokemon = false;
        return;  // Interrompe a construção da entidade
    }
    else {
        Entity::id = *reinterpret_cast<int*>(address + OFFSET::ID);
        // Entity::name = *reinterpret_cast<string*>(address + OFFSET::NAME);
        Entity::x_position = *reinterpret_cast<int*>(address + OFFSET::X_POSITION);
        Entity::y_position = *reinterpret_cast<int*>(address + OFFSET::Y_POSITION);
        Entity::z_position = *reinterpret_cast<int*>(address + OFFSET::Z_POSITION);
        Entity::health = *reinterpret_cast<int*>(address + OFFSET::HEALTH);
        Entity::can_be_attacked = *reinterpret_cast<bool*>(address + OFFSET::CAN_BE_ATTACKED);
        Entity::sprite_id = *reinterpret_cast<int*>(address + OFFSET::SPRITE_ID);
        Entity::is_local_player_pokemon = *reinterpret_cast<bool*>(address + OFFSET::IS_LOCAL_PLAYER_POKEMON);
    }
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
	return	GetCanBeAttacked() &&
			id >= BATTLELIST::MIN_WILD_POKEMON_ID_VALUE &&
			id <= BATTLELIST::MAX_WILD_POKEMON_ID_VALUE &&
			health > 0 &&
			z_position == *POINTER::LOCAL_PLAYER_Z_POSITION &&
			std::abs(x_position - *POINTER::LOCAL_PLAYER_X_POSITION) <= 7 &&
			std::abs(y_position - *POINTER::LOCAL_PLAYER_Y_POSITION) <= 5 &&
			!IsShiny();
}

int Entity::GetId() {
	return id;
}

bool Entity::GetCanBeAttacked() {
    return can_be_attacked;
}

int Entity::GetPercentualHealth() {
	return health;
}

Util::Vector3 Entity::GetLocation() {
	return Util::Vector3(x_position, y_position, z_position);
}

bool Entity::IsShiny() {
	return (sprite_id > 2000 && sprite_id <= 2700);
}

bool Entity::IsLocalPlayerPokemon() {
	return is_local_player_pokemon && id >= BATTLELIST::MIN_WILD_POKEMON_ID_VALUE && id <= BATTLELIST::MAX_WILD_POKEMON_ID_VALUE && !GetCanBeAttacked();
}