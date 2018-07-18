#include "stdafx.h"
#include "Pacman.h"
#include "Coin.h"
#include "resource.h"
#include "Powerup.h"
#include "Ghost.h"
#include "ThreadArgs.h"
#include <algorithm>
#include <vector>
#include <stack>
#define POWERUP_MUSIC L"Rocky_Theme_song.wav"
IMPLEMENT_SERIAL(Pacman, CObject, 1)
	Pacman::Pacman(int w,int h,int x,int y,MovmentVec vec,vector<GameObject*> *gameObjects,int totalCoins): Movable(w,h,x,y,vec,gameObjects),coinsEaten(0),totalCoins(totalCoins) {
		movable_res = IDB_PACMAN_D;
		isSuperPacman = false;
		isDead = false;
		activeGhostTimers = 0;
};
void Pacman::onClone(GameObject* clone){
	Movable::onClone(clone);
	Pacman * pacmanClone = (Pacman*)clone;
	pacmanClone->isDead = isDead;
	pacmanClone->isSuperPacman = isSuperPacman;
	pacmanClone->coinsEaten = coinsEaten;
	pacmanClone->totalCoins = totalCoins;
	pacmanClone->movableObjects = movableObjects;
	pacmanClone->activeGhostTimers = activeGhostTimers;
}
void Pacman::Serialize(CArchive& archive){
	Movable::Serialize(archive);
	if(archive.IsStoring())
		archive << isSuperPacman << isDead << coinsEaten << totalCoins;
	else
		archive >> isSuperPacman >> isDead >> coinsEaten >> totalCoins;
}
DWORD WINAPI SpawnGhostThread( LPVOID lpParam ) 
{

	Sleep(10000);
	ThreadArgs*     Data;
	int     count = 0;
	HANDLE  hStdout = NULL;
	// Get Handle To screen.
	// Else how will we print?
	if( (hStdout = 
		GetStdHandle(STD_OUTPUT_HANDLE)) 
		== INVALID_HANDLE_VALUE )  
		return 1;

	// Cast the parameter to the correct
	// data type passed by callee i.e main() in our case.
	Data = ((ThreadArgs*)lpParam);
	Data->movableObject->setToBeDeleted(false);
	Data->movableObject->reposition(350,170);
	//Ghost* ghost  = new Ghost(15,15,350,170,MovmentVec(8,MovmentVec::Left),Data->res_id,Data->gameObjects);
	Data->movableObject->getDialog()->InvalidateRect(Data->movableObject->getBindingRect());
	Data->gameObjects->push_back(Data->movableObject);
	Data->movableObjcts->push_back(Data->movableObject);
	Data->pacman->activeGhostTimers--;
	delete Data;
	return 0; 
} 


DWORD WINAPI PowerUpThread( LPVOID lpParam ) 
{

	Sleep(10000);
	Pacman*     Data;
	int     count = 0;
	HANDLE  hStdout = NULL;
	// Get Handle To screen.
	// Else how will we print?
	if( (hStdout = 
		GetStdHandle(STD_OUTPUT_HANDLE)) 
		== INVALID_HANDLE_VALUE )  
		return 1;

	// Cast the parameter to the correct
	// data type passed by callee i.e main() in our case.
	Data = ((Pacman*)lpParam); 
	Data->stopSuperPacman();

	return 0; 
} 

void Pacman::superPacmanModeConfig(bool isInSuperMode){
	int speed= this->movmentVec.getSpeed() - 3;
	if(isInSuperMode){
		PlaySound(NULL,NULL,0);
		PlaySound(POWERUP_MUSIC,NULL,SND_LOOP | SND_ASYNC);
		speed= this->movmentVec.getSpeed() + 3;
	}
	else
	{
		PlaySound(NULL,NULL,0);
		PlaySound(GAME_MUSIC,NULL,SND_LOOP | SND_ASYNC);
	}
	this->isSuperPacman = isInSuperMode;
	this->movmentVec.setSpeed(speed);
	for( vector<Movable*>::size_type i=0; i < movableObjects->size() ; ++i){
		if((*movableObjects)[i] == NULL)
			continue;
		Ghost* ghost = dynamic_cast<Ghost*> ((*movableObjects)[i]);
		if(ghost != NULL)
		{
			if(!isInSuperMode)
				ghost->setToBeDeleted(false);
			ghost->setEatableMode(isInSuperMode);
		}
	}

}
bool Pacman::allowUndosRedos(){
	return !IsDead() && activeGhostTimers == 0 && !IsSuperPacman();
}
void Pacman::stopSuperPacman(){
	/*int speed= this->movmentVec.getSpeed() - 3;
	this->isSuperPacman = false;
	this->movmentVec.setSpeed(speed);
	PlaySound(NULL,NULL,0);
	PlaySound(GAME_MUSIC,NULL,SND_LOOP | SND_ASYNC);*/
	superPacmanModeConfig(false);
}
void Pacman::startSuperPacman(){
	/*int speed= this->movmentVec.getSpeed() + 3;
	this->isSuperPacman = true;
	this->movmentVec.setSpeed(speed);
	PlaySound(NULL,NULL,0);
	PlaySound(POWERUP_MUSIC,NULL,SND_LOOP | SND_ASYNC);
	for( vector<GameObject*>::size_type i=0; i < gameObjects->size() ; ++i){
	Ghost* ghost = dynamic_cast<Ghost*> ((*gameObjects)[i]);
	if(ghost != NULL)
	ghost->setEatableMode(true);
	}*/
	superPacmanModeConfig(true);
}
void Pacman::onObjectTouching(GameObject* touched){

	Movable::onObjectTouching(touched);
	Pickable* pickable = dynamic_cast<Pickable*> (touched);

	if(pickable != NULL)//not null
	{
		//fix remove bug
		pickable->setToBeDeleted(true);
		dialog->InvalidateRect(pickable->getBindingRect());
		gameObjects->erase(std::remove( gameObjects->begin(),gameObjects->end(), pickable), gameObjects->end());
		Coin* coin = dynamic_cast<Coin*> (touched);
		if(coin != NULL)
		{
			coinsEaten++;
			wchar_t buff[100];
			swprintf(buff,L"ProjectPacmanCpp - Total Points: %d" , coinsEaten);
			dialog->SetWindowTextW(buff);

		}
		Powerup* powerup = dynamic_cast<Powerup*> (touched);
		if(powerup != NULL){
			startSuperPacman();
			CreateThread( NULL, 0, 
				PowerUpThread, this, 0, NULL);  
			//SetTimer(NULL, 1, 10000, superPacmanTimer); 
		}
		delete pickable;
		pickable= NULL;
		return;
	}

	Ghost* ghost = dynamic_cast<Ghost*> (touched);
	if(ghost != NULL){
		if(isSuperPacman){
			//eat Ghost
			ThreadArgs *args = new ThreadArgs();
			args->movableObject = ghost;
			ghost->setToBeDeleted(true);
			ghost->setEatableMode(false);
			dialog->InvalidateRect(ghost->getBindingRect());
			args->gameObjects = gameObjects;
			args->movableObjcts = movableObjects;
			args->pacman = this;
			gameObjects->erase(std::remove( gameObjects->begin(),gameObjects->end(), ghost), gameObjects->end());
			movableObjects->erase(std::remove( movableObjects->begin(),movableObjects->end(), ghost), movableObjects->end());
			activeGhostTimers++;
			CreateThread( NULL, 0, 
				SpawnGhostThread, args, 0, NULL);  
		}
		else
			isDead = true;
	}
}
void Pacman::onMoveLeft(){
	movable_res = IDB_PACMAN_L;
}
void Pacman::onMoveRight(){
	movable_res = IDB_PACMAN_R;

}
void Pacman::onMoveUp(){
	movable_res = IDB_PACMAN_U;
}
void Pacman::onMoveDown(){
	movable_res = IDB_PACMAN_D;
}