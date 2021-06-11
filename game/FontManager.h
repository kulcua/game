#pragma once
#include "Utils.h"
#include <unordered_map>
class FontManager
{
	static FontManager* __instance;

	float x, y;
public:
	static FontManager* GetInstance();

	// name - spriteId
	unordered_map<string, int> characters;

	int GetSpriteId(string charName) { return characters[charName]; }
	void Render(string name, float x, float y);
};

