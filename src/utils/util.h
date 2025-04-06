#pragma once
#include <cstdint>
#include <windows.h>

namespace Util {
	struct Vector3
	{
		int x, y, z;

		bool valid;

		Vector3(int x, int y, int z);

		Vector3();

		bool IsValid();
	};
	
	template <size_t N>
    int GetValueFromOffsetChain(const int baseAddress, const int(&offsets)[N]) {
        if (N == 0) return 0;

        // Check the base pointer before dereferencing.
        if (IsBadReadPtr(reinterpret_cast<void*>(baseAddress), sizeof(uintptr_t))) {
            return 0;
        }

        uintptr_t current = *reinterpret_cast<uintptr_t*>(baseAddress);
        if (!current || IsBadReadPtr(reinterpret_cast<void*>(current), sizeof(uintptr_t))) {
            return 0;
        }

        // Walk the offset chain, checking pointers at each step.
        for (size_t i = 0; i < N - 1; ++i) {
            uintptr_t addr = current + offsets[i];
            if (!addr || IsBadReadPtr(reinterpret_cast<void*>(addr), sizeof(uintptr_t))) {
                return 0;
            }

            current = *reinterpret_cast<uintptr_t*>(addr);
            if (!current || IsBadReadPtr(reinterpret_cast<void*>(current), sizeof(uintptr_t))) {
                return 0;
            }
        }

        // Final offset addition.
        current += offsets[N - 1];
        if (!current || IsBadReadPtr(reinterpret_cast<void*>(current), sizeof(int))) {
            return 0;
        }

        return *reinterpret_cast<int*>(current);
    }
}