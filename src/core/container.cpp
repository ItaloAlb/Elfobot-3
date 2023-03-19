#include "container.h"
#include "constant.h"

Item::Item(int* address) {
	Item::id = address + OFFSET::ITEM_ID;
	Item::count = address + OFFSET::ITEM_COUNT;
}

Item::Item() {
	//default constructor
}

Container::Container(int* address) {
	Container::state = address + OFFSET::CONTAINER_STATE;
	Container::id = address + OFFSET::CONTAINER_ID;
	//Container::name = address + OFFSET::CONTAINER_NAME;

	Container::slot_count = address + OFFSET::CONTAINER_SLOT_COUNT;
	Container::item_count = address + OFFSET::CONTAINER_ITEM_COUNT;

}

Container::Container() {
	//default constructor
}