#pragma once

class Item {
	public:
		// a pointer to item id value
		int* id;
		// a pointer to item count value
		int* count;

		Item(int* address);

		Item();
};

class Container
{
	public:
		int* state; //0x0000

		int* id; //0x0004

		//char* name[24]; //0x0010

		int* slot_count; //0x0030
		int* item_count; //0x0038

		Item items[32];

		Container(int* address);

		Container();
}; //Size: 0x01B8
