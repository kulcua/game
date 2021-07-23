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
	int section = 0;
	DebugOut(L"ReadPlayerData\n");
	ifstream f;
	f.open("map/state.txt");

	char str[100];
	while (f.getline(str, 100))
	{
		string line(str);

		if (line[0] == '#') continue;
		if (line == "[MARIO]") { section = 1; continue; }
		if (line == "[CARD]") { section = 2; continue; }
		switch (section)
		{
			case 1: LoadMario(line); break;
			case 2: LoadCard(line); break;
		}
	}

	f.close();
}

void DataManager::LoadMario(string line)
{
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

void DataManager::LoadCard(string line)
{
	vector<string> tokens = split(line);

	int numCard = atoi(tokens[0].c_str());

	for (int i = 0; i < numCard; i++)
	{
		TextCard* card = new TextCard();
		card->SetContent(tokens[i + 1].c_str());
		card->blink = false;
		CGame::GetInstance()->GetCurrentScene()->GetHUD()->cards.push_back(card);
	}
}

void DataManager::SavePlayerData() {
	ofstream MyFile("map/state.txt");

	int level = CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetLevel();
	int point = CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetPoint();
	int money = CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetMoney();
	int life = CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetLife();

	vector<TextCard*> cardList = CGame::GetInstance()->GetCurrentScene()->GetHUD()->cards;

	// Write to the file
	MyFile << "[MARIO]" << endl;
	MyFile << "#level - point - money - life" << endl;

	MyFile << level << "\t" << point << "\t" << money << "\t" << life << endl;

	MyFile << "[CARD]" << endl;
	MyFile << "#number-card" << endl;
	MyFile << cardList.size();

	for (size_t i = 0; i < cardList.size(); i++)
	{
		MyFile << "\t" << cardList[i]->GetContent();
	}
	cardList.clear();
	// Close the file
	MyFile.close();
}