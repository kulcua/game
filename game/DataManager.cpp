#include "DataManager.h"
#include "Mario.h"
#include "Game.h"

DataManager* DataManager::__instance = NULL;

DataManager* DataManager::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new DataManager();
	}
	return __instance;
}

void DataManager::ReadPlayerData()
{
	DebugOut(L"ReadPlayerData\n");
	ifstream f;
	f.open("map/state.txt");

	char str[100];
	while (f.getline(str, 100))
	{
		string line(str);

		if (line[0] == '#') continue;
		DebugOut(L"ReadPlayerData 2\n");

		vector<string> tokens = split(line);
		DebugOut(L"ReadPlayerData 3\n");

		if (tokens.size() < 4) return;

		DebugOut(L"ReadPlayerData\n");
		int level = atoi(tokens[0].c_str());
		int point = atoi(tokens[1].c_str());
		int money = atoi(tokens[2].c_str());
		int life = atoi(tokens[3].c_str());

		CGame::GetInstance()->GetPlayer()->SetLevel(level);
		CGame::GetInstance()->GetPlayer()->SetPoint(point);
		CGame::GetInstance()->GetPlayer()->SetMoney(money);
		CGame::GetInstance()->GetPlayer()->SetLife(life);

		DebugOut(L"%d %d %d %d\n", level, point, money, life);
	}

	f.close();
}

void DataManager::SavePlayerData() {
	ofstream MyFile("map/state.txt");

	int level = CGame::GetInstance()->GetPlayer()->GetLevel();
	int point = CGame::GetInstance()->GetPlayer()->GetPoint();
	int money = CGame::GetInstance()->GetPlayer()->GetMoney();
	int life = CGame::GetInstance()->GetPlayer()->GetLife();

	// Write to the file
	MyFile << "#level - point - money - life" << endl;

	MyFile << level << " " << point << " " << money << " " << life;

	// Close the file
	MyFile.close();
}