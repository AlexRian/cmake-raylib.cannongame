#pragma once
#include <stdio.h>
#include <array>
#include "engine/settings.hpp"

struct StageEntityData
{
	StageEntityData(int x, int y, float angle, int width, int height) 
		: x(x), y(y), angle(angle), width(width), height(height) {}
	int x, y;
	float angle;
	int width, height;
};

std::array<std::array<StageEntityData, 6>, 1> stages = {
	{
		StageEntityData{Settings::screenWidth / 2 + 900, Settings::screenHeight / 2, 90, 200, 30},
		StageEntityData{Settings::screenWidth / 2 + 1100, Settings::screenHeight / 2, 90, 200, 30},
		StageEntityData{Settings::screenWidth / 2 + 1000, Settings::screenHeight / 2 - 200, 180, 300, 30},
		StageEntityData{Settings::screenWidth / 2 + 900, Settings::screenHeight / 2 - 500, 90, 200, 30},
		StageEntityData{Settings::screenWidth / 2 + 1100, Settings::screenHeight / 2 - 500, 90, 200, 30},
		StageEntityData{Settings::screenWidth / 2 + 1000, Settings::screenHeight / 2 - 700, 180, 300, 30},
	}
};