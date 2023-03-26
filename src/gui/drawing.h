#ifndef DRAWING_H
#define DRAWING_H

#include <Windows.h>
#include "constant.h"
#include "imgui.h"

class Drawing
{
private:
	static LPCSTR lpWindowName;
	static ImVec2 vWindowSize;
	static ImGuiWindowFlags WindowFlags;
	static bool bDraw;
	static char* target_window;

public:
	static void Active();
	static bool isActive();
	static void Draw();
};

#endif
