#pragma once
#include "Movable.h"
#include <vector>
using namespace std;
class Pacman : public Movable {
protected:
	void onObjectTouching(GameObject* touched);
	void onMoveLeft();
	void onMoveRight();
	void onMoveUp();
	void onMoveDown();
	GameObject* getInstance(){ return new Pacman();}
	void onClone(GameObject* clone);
private:
	int totalCoins;
	int coinsEaten;
	int activeGhostTimers;
	bool isSuperPacman;
	bool isDead;
	void superPacmanModeConfig(bool isInSuperMode);
	vector<Movable*> *movableObjects;
public:
	DECLARE_SERIAL(Pacman)
	Pacman(){};
	Pacman(int w,int h,int x,int y,MovmentVec vec,vector<GameObject*> *gameObjects,int totalCoins);
	~Pacman(){};
	void startSuperPacman();
	void stopSuperPacman();
	void Serialize(CArchive& archive);
	int getCoinsEaten() { return coinsEaten; }
	bool IsSuperPacman() { return isSuperPacman; }
	bool allowUndosRedos();
	vector<Movable*> *getMovableObjects() { return movableObjects;}
	void setMovableObjects(vector<Movable*> *movableObjects){this->movableObjects = movableObjects;}
	bool IsDead() { return isDead; }
	bool hasWon() { 	
		return totalCoins == coinsEaten; }
	friend DWORD WINAPI SpawnGhostThread( LPVOID lpParam );
};