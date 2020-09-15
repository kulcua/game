#pragma once
#include "Scene.h"

#define TILE_SIZE 64

class CMaps
{
	static CMaps* __instance;
	int max_map_x;
	int max_map_y;
	int num_tile_x;
	int num_tile_y;
	int tile[50][50];
public:
	void Add(int id, LPCWSTR path_img, int width, int height,
	int num_tile_x, int num_tile_y,	LPCWSTR path_txt, D3DCOLOR transparentColor);
	void Render();

	static CMaps* GetInstance();
};

