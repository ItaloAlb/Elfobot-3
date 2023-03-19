#pragma once
#include "iostream"

namespace SendPacket {
	//
	void Step(int direction);

	//Look an item from container and container slot
	void LookItem(int container, int container_slot, int container_item);

	//Use an item from container and container slot
	void UseItem(int container, int container_slot, int container_item);

	//Move an item from container and container slot to another container and container slot
	void MoveItem(int from_container, int from_container_slot, int from_container_item, int to_container, int to_container_slot);

	//Use item from container id and container slot on x, y, z positions
	void UseOn(int container, int container_slot, int x_position, int y_position, int z_position);

	//Target-follow a creature id
	void Follow(int creature);

	//Target-attack a creature id
	void Attack(int creature);

	//
	void FightMode(int fighting_mode, int stand_mode, int attack_unmarked);

	//
	void Say(char text[], int channel);


}
