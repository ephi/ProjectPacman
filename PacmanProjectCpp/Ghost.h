#pragma once
#include "Movable.h"
#include "MovmentVec.h"
class Ghost : public Movable {
private:
	void fillterDirections(vector<DIRECTION> *directionsToGo,DIRECTION direction);
	int original_res;
protected:
	void OnMoveHalt();
	GameObject* getInstance(){ return new Ghost();}
	int getOriginalRes() const { return original_res; }
	void setOriginalRes(int original_res) { this->original_res = original_res; }
public:
	DECLARE_SERIAL(Ghost)
	Ghost(){}
	Ghost(int w,int h,int x,int y,MovmentVec vec,int ghost_res,vector<GameObject*> *gameObjects);
	void Serialize(CArchive& archive);
	void setEatableMode(bool isEatable);
	~Ghost();
};