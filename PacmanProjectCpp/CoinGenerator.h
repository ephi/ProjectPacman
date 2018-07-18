#pragma once
#include "Coin.h"
#include "GameLevel.h"
using namespace std;
class CoinGenerator
{
public:
	CoinGenerator(vector<GameObject*> *gameObjects,CDialogEx* dialog);
	~CoinGenerator(void);
	void generateCoins(int x,int y);
	int getTotalCoins() { return coinsGenerated;}

private:
	CDialogEx* dialog;
	bool canGenerate(Coin *c);
	int coinWidth,coinHeight,coinsGenerated;
	vector<GameObject*> *gameObjects;
};

