#include "packet.h"
#include "constant.h"

void SendPacket::Step(int direction) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(direction);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}

void SendPacket::LookItem(int container, int container_slot, int container_item) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(PACKET::LOOK_ITEM);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::DATA);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(container);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(container_slot);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(container_item);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(PACKET::INFO);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}

void SendPacket::UseItem(int container, int container_slot, int container_item) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(PACKET::USE_ITEM);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::DATA);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(container);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(container_slot);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(container_item);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(container_slot);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(PACKET::INFO);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}

void SendPacket::MoveItem(int from_container, int from_container_slot, int from_container_item, int to_container, int to_container_slot) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(PACKET::MOVE_ITEM);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::DATA);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(from_container);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(from_container_slot);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(from_container_item);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(PACKET::INFO);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::DATA);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(to_container);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(to_container_slot);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(PACKET::INFO);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}

void SendPacket::UseOn(int container, int container_slot, int x_position, int y_position, int z_position) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(PACKET::USE_ON);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::DATA);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(container);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(container_slot);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::INFO);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(PACKET::INFO);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(x_position);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(y_position);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(z_position);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::INFO);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(PACKET::INFO);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}

void SendPacket::UseOn(int container, int container_slot, Util::Vector3 location) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(PACKET::USE_ON);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::DATA);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(container);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(container_slot);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::INFO);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(PACKET::INFO);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(location.x);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(location.y);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(location.z);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_DATA)(PACKET::INFO);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(PACKET::INFO);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}

void SendPacket::Follow(int creature) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(PACKET::FOLLOW);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_TARGET)(creature);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}

void SendPacket::Attack(int creature) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(PACKET::ATTACK);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_TARGET)(creature);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}

void SendPacket::FightMode(int fighting_mode, int stand_mode, int attack_unmarked) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(PACKET::FIGHT_MODE);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(fighting_mode);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(stand_mode);
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(attack_unmarked);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}

void SendPacket::Say(char text[], int channel) {
	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_START)(PACKET::SAY);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_INFO)(channel);
	reinterpret_cast<void(__cdecl*)(char*)>(ADDRESS::PACKET_SAY)(text);

	reinterpret_cast<void(__cdecl*)(int)>(ADDRESS::PACKET_END)(PACKET::END);

	Sleep(COOLDOWN::SEND_PACKET);
}