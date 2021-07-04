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

		vector<string> tokens = split(line);
		if (tokens.size() < 4) return;

		int level = atoi(tokens[0].c_str());
		int point = atoi(tokens[1].c_str());
		int money = atoi(tokens[2].c_str());
		int life = atoi(tokens[3].c_str());

		CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetLevel(level);
		CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetPoint(point);
		CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetMoney(money);
		CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetLife(life);

		//DebugOut(L"%d %d %d %d\n", level, point, money, life);
	}

	f.close();
}

void DataManager::SavePlayerData() {
	ofstream MyFile("map/state.txt");

	int level = CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetLevel();
	int point = CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetPoint();
	int money = CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetMoney();
	int life = CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetLife();

	// Write to the file
	MyFile << "#level - point - money - life" << endl;

	MyFile << level << "\t" << point << "\t" << money << "\t" << life;

	// Close the file
	MyFile.close();
}