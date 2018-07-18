#include "stdafx.h"
#include "GameLevel.h"
#include "Coin.h"
#include "CoinGenerator.h"
#include "Powerup.h"
#include "Pacman.h"
#include "Ghost.h"
#include "resource.h"
#include <stack>
stack<GameState*> GameLevel::redos;
stack<GameState*> GameLevel::undos;
GameLevel::GameLevel(CDialogEx* dialog) : dialog(dialog){
	//The Maze
	gameobjects.push_back(new Levelwall(720,22,0,0));
	gameobjects.push_back(new Levelwall(10,190,0,0));
	gameobjects.push_back(new Levelwall(77,58,0,146));
	gameobjects.push_back(new Levelwall(77,55,0,225));
	gameobjects.push_back(new Levelwall(10,173,0,279));
	gameobjects.push_back(new Levelwall(38,14,0,349));
	gameobjects.push_back(new Levelwall(720,22,0,432));
	gameobjects.push_back(new Levelwall(11,225,710,256));
	gameobjects.push_back(new Levelwall(36,12,685,351));
	gameobjects.push_back(new Levelwall(77,53,644,225));
	gameobjects.push_back(new Levelwall(77,58,644,146));//change
	gameobjects.push_back(new Levelwall(10,179,710,0));
	gameobjects.push_back(new Levelwall(14,71,518,0));
	gameobjects.push_back(new Levelwall(14,71,354,0));
	gameobjects.push_back(new Levelwall(14,71,188,0));
	gameobjects.push_back(new Levelwall(42,31,37,46));
	gameobjects.push_back(new Levelwall(54,30,107,46));
	gameobjects.push_back(new Levelwall(96,30,230,45));
	gameobjects.push_back(new Levelwall(96,30,396,46));
	gameobjects.push_back(new Levelwall(55,29,560,46));
	gameobjects.push_back(new Levelwall(42,26,642,48));
	gameobjects.push_back(new Levelwall(38,13,40,103));
	gameobjects.push_back(new Levelwall(11,97,108,102));
	gameobjects.push_back(new Levelwall(96,13,148,102));
	gameobjects.push_back(new Levelwall(15,50,188,102));
	gameobjects.push_back(new Levelwall(14,94,271,102));
	gameobjects.push_back(new Levelwall(94,11,232,144));
	gameobjects.push_back(new Levelwall(93,15,315,102));
	gameobjects.push_back(new Levelwall(14,57,356,102));
	gameobjects.push_back(new Levelwall(14,94,438,102));
	gameobjects.push_back(new Levelwall(94,11,398,144));
	gameobjects.push_back(new Levelwall(93,15,480,102));
	gameobjects.push_back(new Levelwall(14,57,520,102));
	gameobjects.push_back(new Levelwall(12,52,560,144));
	gameobjects.push_back(new Levelwall(14,96,601,102));
	gameobjects.push_back(new Levelwall(41,15,644,104));
	gameobjects.push_back(new Levelwall(13,54,149,145));
	gameobjects.push_back(new Levelwall(55,16,191,187));
	gameobjects.push_back(new Levelwall(13,55,191,187));
	gameobjects.push_back(new Levelwall(52,13,150,230));
	gameobjects.push_back(new Levelwall(96,56,313,185));
	gameobjects.push_back(new Levelwall(55,16,478,187));
	gameobjects.push_back(new Levelwall(13,55,520,187));
	gameobjects.push_back(new Levelwall(52,13,520,230));
	//lower half
	gameobjects.push_back(new Levelwall(13,53,108,227));
	gameobjects.push_back(new Levelwall(53,14,231,227));
	gameobjects.push_back(new Levelwall(13,53,272,227));
	//--
	gameobjects.push_back(new Levelwall(53,14,439,227));
	gameobjects.push_back(new Levelwall(13,53,439,227));
	//--
	gameobjects.push_back(new Levelwall(13,53,601,227));
	///--
	gameobjects.push_back(new Levelwall(94,15,149,267));
	gameobjects.push_back(new Levelwall(14,55,189,267));
	//---
	gameobjects.push_back(new Levelwall(94,15,315,267));
	gameobjects.push_back(new Levelwall(14,55,356,267));
	///---
	gameobjects.push_back(new Levelwall(94,15,480,267));
	gameobjects.push_back(new Levelwall(14,55,519,267));
	//--lower Rish
	gameobjects.push_back(new Levelwall(39,15,40,309));
	gameobjects.push_back(new Levelwall(12,55,67,309));
	//--
	gameobjects.push_back(new Levelwall(51,13,110,309));
	//---
	gameobjects.push_back(new Levelwall(93,14,232,309));
	//---
	gameobjects.push_back(new Levelwall(93,14,397,309));
	//---
	gameobjects.push_back(new Levelwall(51,13,563,309));
	//---
	gameobjects.push_back(new Levelwall(39,15,644,309));
	gameobjects.push_back(new Levelwall(12,55,644,309));
	//---
	gameobjects.push_back(new Levelwall(14,55,107,351));
	gameobjects.push_back(new Levelwall(123,15,40,392));
	//---
	gameobjects.push_back(new Levelwall(94,15,149,351));
	gameobjects.push_back(new Levelwall(14,55,189,351));
	//--
	gameobjects.push_back(new Levelwall(13,53,272,351));
	gameobjects.push_back(new Levelwall(95,16,231,392));
	//---
	gameobjects.push_back(new Levelwall(94,15,316,351));
	gameobjects.push_back(new Levelwall(14,55,355,351));
	//---
	gameobjects.push_back(new Levelwall(13,53,438,351));
	gameobjects.push_back(new Levelwall(95,16,396,392));
	//--
	gameobjects.push_back(new Levelwall(94,15,480,351));
	gameobjects.push_back(new Levelwall(14,55,521,351));
	//--
	gameobjects.push_back(new Levelwall(14,55,603,351));
	gameobjects.push_back(new Levelwall(123,15,563,392));
	forceGameOver = false;
	restart();
}
Pacman* GameLevel::getPacman(){
	return pacman;
}
void GameLevel::draw(CDC* cdc){
	for (vector<GameObject*>::size_type i=0; i < gameobjects.size() ; ++i){
		gameobjects[i]->Draw(cdc);
	}
}
void GameLevel::clearLevel() {
	for (vector<Movable*>::size_type i=0; i < movableObjects.size() ; ++i){
		movableObjects.erase(movableObjects.begin() + i);
		i--;
	}
	for( vector<GameObject*>::size_type i=0; i < gameobjects.size() ; ++i){
		if(gameobjects[i] == NULL)
			continue;
		Levelwall* lvlWall = dynamic_cast<Levelwall*> (gameobjects[i]);
		if(lvlWall == NULL)
		{
			delete gameobjects[i];
			gameobjects[i] = NULL;
			gameobjects.erase(gameobjects.begin() + i);
			i--;
		}
	}
	this->pacman = NULL;
}
void GameLevel::restart(bool deleteOld){
	if(deleteOld)
	{
		clearLevel();
	}
	//powerUps
	gameobjects.push_back(new Powerup(13,14,18,53));
	gameobjects.push_back(new Powerup(13,14,690,53));
	gameobjects.push_back(new Powerup(13,14,16,330));
	gameobjects.push_back(new Powerup(13,14,690,326));
	//Coins..
	CoinGenerator cg(&gameobjects,dialog);
	cg.generateCoins(90,208);
	gameobjects.push_back(new Coin(7,7,90,208));
	//Pacman
	pacman = new Pacman(14,14,87,190,MovmentVec(8,DIRECTION::Down),&gameobjects,cg.getTotalCoins());
	movableObjects.push_back(pacman);
	gameobjects.push_back(pacman);
	//ghosts
	Ghost *ghost_a = new Ghost(15,15,350,170,MovmentVec(8,DIRECTION::Left),IDB_GHOST_A,&gameobjects);
	movableObjects.push_back(ghost_a);
	gameobjects.push_back(ghost_a);
	Ghost *ghost_b = new Ghost(15,15,350,170,MovmentVec(8,DIRECTION::Right),IDB_GHOST_B,&gameobjects);
	movableObjects.push_back(ghost_b);
	gameobjects.push_back(ghost_b);
	Ghost *ghost_c = new Ghost(15,15,350,170,MovmentVec(8,DIRECTION::Up),IDB_GHOST_C,&gameobjects);
	movableObjects.push_back(ghost_c);
	gameobjects.push_back(ghost_c);
	Ghost *ghost_d = new Ghost(15,15,350,170,MovmentVec(8,DIRECTION::Up),IDB_GHOST_D,&gameobjects);
	movableObjects.push_back(ghost_d);
	gameobjects.push_back(ghost_d);


	//extra setting
	pacman->setMovableObjects(&movableObjects);
	for (vector<GameObject*>::size_type i=0; i < gameobjects.size() ; ++i){
		if(gameobjects[i]->getDialog() == 0)
			gameobjects[i]->setDialog(dialog);
	}
	if(deleteOld)
	{
		dialog->Invalidate();

	}	
	PlaySound(GAME_MUSIC,NULL,SND_LOOP | SND_ASYNC);
	redos.push(new GameState(&gameobjects));

}
void GameLevel::redo(){
	if(isGameOver())
		return;
	if(!pacman->allowUndosRedos())
		return;
	if(undos.empty())
		return;
	GameState  *gamstate= undos.top();
	redos.push(gamstate);
	gamstate->restoreState(this);
	undos.pop();
}
void GameLevel::undo(){
	if(isGameOver())
		return;
	if(!pacman->allowUndosRedos())
		return;
	if(redos.empty())
		return;
	GameState * gamstate= redos.top();
	undos.push(gamstate);
	gamstate->restoreState(this);
	redos.pop();
}

bool GameLevel::isGameOver(){
	TRACE("PACMAN WON: %d, PACMAN DEAD: %d\n",this->pacman->hasWon(),this->pacman->IsDead());
	return this->pacman->IsDead() || this->pacman->hasWon() || forceGameOver;
}

bool GameLevel::update(){
	for (vector<Movable*>::size_type i=0; i < movableObjects.size() ; ++i){
		movableObjects[i]->move();
		for (vector<GameObject*>::size_type j=0; j < gameobjects.size() ; ++j){
			Coin* coin = dynamic_cast<Coin*> (gameobjects[j]);
			if(movableObjects[i]->areTouching(gameobjects[j]))
			{

				Pacman* pacman = dynamic_cast<Pacman*> (movableObjects[i]);

				//if pacman touched  coin add to redo's and it was the 10th coin
				if(pacman != NULL && coin != NULL && pacman->getCoinsEaten() % 10 == 0 && pacman->allowUndosRedos()){
					redos.push(new GameState(&gameobjects));

				}
			}
		}
	}
	if(isGameOver()){
		PlaySound(NULL,NULL,0);
	}
	return !isGameOver();
}

void GameLevel::save(){
	CFile file(L"PACMAM_DATA.$$", CFile::modeWrite | CFile::modeCreate);
	CArchive ar(&file, CArchive::store);
	/*vector<GameObject*> gameobjects;
	vector<Movable*> movableObjects;
	Pacman* pacman;*/
	ar << gameobjects.size() - 78; //78 is the number of walls in the game
	for (size_t i = 0; i < gameobjects.size(); ++i)
	{
		Levelwall* lvlWall = dynamic_cast<Levelwall*> (gameobjects[i]);
		if(lvlWall == NULL)
		{
			ar << gameobjects[i];
		}
	}
}
void GameLevel::load(){
	CFile file(L"PACMAM_DATA.$$", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	clearLevel();
	size_t size;
	ar >> size;
	for (size_t i = 0; i < size; ++i)
	{
		CObject *o;
		ar >> o;
		((GameObject*)o)->setDialog(dialog);
		gameobjects.push_back((GameObject*)o);
	}
	for (size_t i = 0; i < gameobjects.size(); ++i)
	{
		Movable* movable = dynamic_cast<Movable*> (gameobjects[i]);
		if(movable != NULL){
			movable->setGameObjects(&gameobjects);
			movableObjects.push_back(movable);
			Pacman* pacman = dynamic_cast<Pacman*> (movable);
			if(pacman != NULL){
			
				this->pacman = pacman;
			}
		}
	}
	this->pacman->setMovableObjects(&movableObjects);
	dialog->Invalidate();
}
void GameLevel::clearStack(stack<GameState*> stack){
	while(!stack.empty())
	{
		//GameState *state = stack.top();
		//delete state;
		//GameLevel * lvl = stack.top();
		//if(lvl != this)
		//delete lvl;
		stack.pop();
	}
}
void GameLevel::releaseUndosRedos(){
	//clean redos undos
	clearStack(undos);
	clearStack(redos);
}
GameLevel::~GameLevel(){
	releaseUndosRedos();
	for( vector<GameObject*>::size_type i=0; i < gameobjects.size() ; ++i){
		delete gameobjects[i];
	}
}
void GameLevel::pause(HANDLE *gameThread,CDialogEx* dialog){
	SuspendThread(*gameThread);
	PlaySound(NULL,NULL,0);
	dialog->ShowWindow(SW_SHOW);
}
void GameLevel::resume(HANDLE *gameThread,CDialogEx* dialog){
	ResumeThread(*gameThread);
	PlaySound(GAME_MUSIC,NULL,SND_LOOP | SND_ASYNC);
	dialog->ShowWindow(SW_HIDE);
}