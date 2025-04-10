#ifndef DRAWING_H
#define DRAWING_H

#include <Windows.h>
#include "constant.h"
#include "imgui.h"
#include "auto.h"
#include "packet.h"
#include "map.h"
#include "util.h"
#include "config.h"
#include "ui.h"
#include "ability.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

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
