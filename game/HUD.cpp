#include "HUD.h"
#include "Sprites.h"

HUD* HUD::__instance = NULL;

HUD* HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}

RECT* HUD::GetRectHUD()
{
	RECT rect;

	rect.left = x;
	rect.top = y;
	rect.right = x + SCREEN_WIDTH;
	rect.bottom = y + HUD_HEIGHT;

	DebugOut(L"%d %d %d %d\n", rect.left, rect.right, rect.top, rect.bottom);

	return &rect;
}

void HUD::Render()
{
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y, NULL);
}