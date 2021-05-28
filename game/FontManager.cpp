#include "FontManager.h"
#include "Sprites.h"

FontManager* FontManager::__instance = NULL;

FontManager* FontManager::GetInstance()
{
	if (__instance == NULL) __instance = new FontManager();
	return __instance;
}

void FontManager::Render(string charName, float x, float y)
{
	CSprites::GetInstance()->Get(GetSpriteId(charName))->Draw(x, y, -1, -1);
}