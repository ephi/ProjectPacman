#pragma once
#include "Levelwall.h"
#include "Pacman.h"
#include "Movable.h"
#include "GameState.h"
#include <vector>
#include <stack>
class GameLevel {
public:
	GameLevel(CDialogEx* dialog);
	~GameLevel();
	void draw(CDC* cdc);
	bool update();
	Pacman *getPacman();
	void restart(bool deleteOld = false);
	bool isGameOver();
	void finishGame(){forceGameOver = true;}
	void releaseUndosRedos();
	void redo();
	void undo();
	void save();
	void load();
	static void pause(HANDLE *gameThread,CDialogEx* dialog);
	static void resume(HANDLE *gameThread,CDialogEx* dialog);
	void clearLevel();
	friend class GameState;
private:
	//void restoreLevel(GameState* gameLvl);
	static stack<GameState*> undos;
	static stack<GameState*> redos;
	void clearStack(stack<GameState*> stack);
	vector<GameObject*> gameobjects;
	vector<Movable*> movableObjects;
	Pacman* pacman;
	CDialogEx* dialog;
	bool forceGameOver;
};