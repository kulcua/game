#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#define ID_TEX_BBOX -100

using namespace std;

class CSprite
{
	int id;
	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int nx, int ny, int alpha = 255);
};

typedef CSprite* LPSPRITE;

//Manage sprite database
class CSprites {
	static CSprites* __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	void Clear();

	static CSprites* GetInstance();
};

