#pragma once
#include "GameObject.h"
#include "GameLevel.h"
#include <vector>
using namespace std;
class GameLevel;
class GameState
{
private:
	vector<GameObject*> *gameobjects;
public:
	GameState(vector<GameObject*> *gameobjects);
	void restoreState(GameLevel* gameLvl);
	~GameState(void);
};

