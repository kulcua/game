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
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void Render(string name, float x, float y);
};

