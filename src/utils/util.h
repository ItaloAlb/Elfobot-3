#pragma once

namespace Util {
	struct Vector3
	{
		int x, y, z;

		bool valid;

		Vector3(int x, int y, int z);

		Vector3();

		bool IsValid();
	};
}