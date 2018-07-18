#include "stdafx.h"
#include "Ghost.h"
#include "resource.h"
#include <random>
#include <algorithm>
IMPLEMENT_SERIAL(Ghost, CObject, 1)
	Ghost::Ghost(int w,int h,int x,int y,MovmentVec vec,int ghost_res,vector<GameObject*> *gameObjects): Movable(w,h,x,y,vec,gameObjects){
		movable_res  = ghost_res;
		original_res = movable_res;
		srand ((unsigned int)time(NULL));
};
void Ghost::Serialize(CArchive& archive){
	Movable::Serialize(archive);
	if(archive.IsStoring())
		archive << original_res;
	else
		archive >> original_res;	
}
void Ghost::setEatableMode(bool isEatable){
	movable_res = original_res;
	if(isEatable)
		movable_res = IDB_GHOST_EATABLE;
}
void Ghost::fillterDirections(vector<DIRECTION> *directionsToGo,DIRECTION direction){
	this->movmentVec.setDirection(direction);
	auto it = std::find(directionsToGo->begin(), directionsToGo->end(), direction);
	for(vector<GameObject*>::size_type i=0;i< gameObjects->size(); ++i){	
		if((*gameObjects)[i]->areTouching(this) && (*gameObjects)[i]->isMovementBlocking())
		{	
			directionsToGo->erase(it);
			break;
		}	
	}

}

void Ghost::OnMoveHalt(){

	vector<DIRECTION> directionsToGo;
	directionsToGo.push_back(DIRECTION::Right);
	directionsToGo.push_back(DIRECTION::Left);
	directionsToGo.push_back(DIRECTION::Up);
	directionsToGo.push_back(DIRECTION::Down);
	fillterDirections(&directionsToGo,DIRECTION::Right);
	fillterDirections(&directionsToGo,DIRECTION::Left);
	fillterDirections(&directionsToGo,DIRECTION::Up);
	fillterDirections(&directionsToGo,DIRECTION::Down);
	int select = rand() % directionsToGo.size();
	this->movmentVec.setDirection(directionsToGo[select]);
	this->isAllowedToMove = true;
}
Ghost::~Ghost(){

}