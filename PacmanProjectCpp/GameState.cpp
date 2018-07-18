#include "StdAfx.h"
#include "GameState.h"
#include "Levelwall.h"
GameState::GameState(vector<GameObject*> *gameobjects)
{
	this->gameobjects = new vector<GameObject*>();
	for(size_t i = 0; i < gameobjects->size() ; ++i){
		GameObject * gameObj = (*gameobjects)[i];
		if(gameObj == NULL)
			continue;
		Levelwall* lvlWall = dynamic_cast<Levelwall*> (gameObj);
		if(lvlWall == NULL)//not a wall
		{
			this->gameobjects->push_back(gameObj->clone());
		}
	}
}

void GameState::restoreState(GameLevel* gameLvl){
	gameLvl->clearLevel();
	for (vector<GameObject*>::size_type i=0; i < gameobjects->size() ; ++i){
		if((*gameobjects)[i] == NULL)
			continue;
		GameObject * gameObj = (*gameobjects)[i]->clone();
		gameLvl->gameobjects.push_back(gameObj);
		Movable* movable = dynamic_cast<Movable*> (gameObj);
		if(movable != NULL){
			gameLvl->movableObjects.push_back(movable);
			Pacman* pacman = dynamic_cast<Pacman*> (movable);
			if(pacman != NULL)
				gameLvl->pacman = pacman;
		}
	}
	gameLvl->dialog->Invalidate();
}
GameState::~GameState(void)
{
	if(gameobjects == NULL)
		return;
	for(size_t i = 0; i < gameobjects->size() ; ++i){
		if((*gameobjects)[i]  == NULL)
			continue;
		delete (*gameobjects)[i];
		(*gameobjects)[i] = NULL;
	}
	delete gameobjects;
	gameobjects = NULL;
}
