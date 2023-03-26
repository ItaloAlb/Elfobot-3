#include "callback.h"
#include <thread>

void Callback::Call(void(*callback)(bool&), bool& v) {
	if (&v) {
		std::thread thread_callback(callback, std::ref(v));
		thread_callback.detach();
	}
}

void Callback::Call(void(*callback)(Map&, bool&), Map& map, bool& v) {
	if (&v) {
		std::thread thread_callback(callback, std::ref(map), std::ref(v));
		thread_callback.detach();
	}
}