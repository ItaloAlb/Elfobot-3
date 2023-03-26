#include "util.h"

Util::Vector3::Vector3(int x, int y, int z) {
	Util::Vector3::x = x;
	Util::Vector3::y = y;
	Util::Vector3::z = z;
	Util::Vector3::valid = true;
}

Util::Vector3::Vector3() {
	Util::Vector3::valid = false;
	//default constructor
}

bool Util::Vector3::IsValid() {
	return valid;
}