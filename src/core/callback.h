#pragma once
#include "map.h"

namespace Callback{
	void Call(void(*callback)(bool&), bool& v);

	void Call(void(*callback)(Map&, bool&), Map& map, bool& v);
}
