#pragma once
#include <vector>
#include "GameObject.h"
#include "MovmentVec.h"
using namespace std;
class Movable : public GameObject {
protected:
	bool isAllowedToMove;
	int movable_res;
	int lastX,lastY;
	vector<GameObject*> *gameObjects;
	MovmentVec movmentVec;
    void onObjectTouching(GameObject* touched);
	virtual void OnMoveHalt(){};
	virtual void onMoveLeft(){};
	virtual void onMoveRight(){};
	virtual void onMoveUp(){};
	virtual void onMoveDown(){};
	void OnDraw(CDC *cdc);
	void onClone(GameObject* clone);
public:
	//DECLARE_SERIAL(Movable)
	Movable():movmentVec(0,DIRECTION::Down){};
	Movable(int w,int h,int x,int y,MovmentVec movementVec,	vector<GameObject*> *gameObjects);
	virtual void move();
	void changeDirection(DIRECTION direction);
	void Serialize(CArchive& archive);
	int getLastX();
	int getLastY();
	int getResource() { return movable_res;}
	void setGameObjects(vector<GameObject*> *gameObjects) {this->gameObjects = gameObjects;} 
	~Movable();
};

//CArchive& operator>>(CArchive& in, Movable& movable)
//{
//	movable.Serialize(in);
//	return in;
//}
//
//CArchive& operator<<(CArchive& out, Movable& movable)
//{
//	movable.Serialize(out);
//	return out;
//}