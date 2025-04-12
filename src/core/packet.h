#pragma once
#include "util.h"
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace SendPacket {
	//Step at one direction
	void Step(int direction);

	//Look an item from container and container slot
	void LookItem(int container, int container_slot, int container_item);

	//Use an item from container and container slot
	void UseItem(int container, int container_slot, int container_item);

	//Move an item from container and container slot to another container and container slot
	void MoveItem(int from_container, int from_container_slot, int from_container_item, int to_container, int to_container_slot);

	//Use item from container id and container slot on x, y, z positions
	void UseOn(int container, int container_slot, int x_position, int y_position, int z_position);

	void UseOn(int container, int container_slot, Util::Vector3 location);

	//Target-follow a creature id
	void Follow(int creature);

	//Target-attack a creature id
	void Attack(int creature);

	//Change fight mode: fighting style, stand mode and attack unmarked
	void FightMode(int fighting_mode, int stand_mode, int attack_unmarked);

	//Say a text in a chat channel. Can be use to cast pokemon's moves.
	void Say(const char text[], int channel);

	void Test();

	void EnqueueStep(int direction);

	void EnqueueLookItemPacket(int container, int container_slot, int container_item);

	void EnqueueUseItemPacket(int container, int container_slot, int container_item);

	void EnqueueMoveItemPacket(int from_container, int from_container_slot, int from_container_item, int to_container, int to_container_slot);

	//void EnqueueUseOnPacket(int container, int container_slot, int x_position, int y_position, int z_position);

	void EnqueueUseOn(int container, int container_slot, Util::Vector3 location);

	void EnqueueFollow(int creature);

	void EnqueueAttack(int creature);

	void EnqueueFightMode(int fighting_mode, int stand_mode, int attack_unmarked);

	void EnqueueSay(const char* text, int channel);

}

struct PacketTask {
	std::function<void()> task;
};

class PacketQueue {
public:
	void push(const PacketTask& task);
	PacketTask pop();
	void shutdown();
private:
	std::queue<PacketTask> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_condVar;
	bool m_shutdown = false;

};

extern PacketQueue packetQueue;
