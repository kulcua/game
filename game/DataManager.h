#pragma once
#include "Utils.h"
#include <iostream>
#include <fstream>

class DataManager
{
	static DataManager* __instance;
public:
	static DataManager* GetInstance();
	void ReadPlayerData();
	void SavePlayerData();
	void LoadMario(string line);
	void LoadCard(string line);
};

