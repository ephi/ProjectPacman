#pragma once
#include "GameObject.h"
#include <vector>
#include "Pacman.h"
using namespace std;
class ThreadArgs
{
public:
	Pacman *pacman;
	Movable *movableObject;
	vector<GameObject*> *gameObjects;
	vector<Movable*> *movableObjcts;
	ThreadArgs(void);
	~ThreadArgs(void);
};

