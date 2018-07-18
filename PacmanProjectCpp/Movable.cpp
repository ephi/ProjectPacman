#include "stdafx.h"
#include "Movable.h"
Movable::Movable(int w,int h,int x,int y,MovmentVec movementVec,vector<GameObject*> *gameObjects): GameObject(w,h,x,y),movmentVec(movementVec),gameObjects(gameObjects)
	,isAllowedToMove(true),lastX(-1),lastY(-1){};
void Movable::onClone(GameObject* clone){
	Movable* movableClone = (Movable*)clone;
	movableClone->gameObjects = this->gameObjects;
	movableClone->lastX = lastX;
	movableClone->lastY = lastY;
	movableClone->movable_res = movable_res;
	movableClone->movmentVec = MovmentVec(this->movmentVec);
}
void Movable::changeDirection(DIRECTION direction){
	isAllowedToMove = true;
	this->movmentVec.setDirection(direction);
}
void Movable::onObjectTouching(GameObject* touched){
	if(!touched->isMovementBlocking())
		return ;
	reposition(lastX,lastY);
	isAllowedToMove = false;

}
void Movable::OnDraw(CDC *cdc){
	CBitmap bitmap;
	bitmap.LoadBitmap(movable_res);
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(cdc);
    dcMemory.SelectObject(&bitmap);
	cdc->BitBlt(this->bindingRect.TopLeft().x, this->bindingRect.TopLeft().y,
		this->bindingRect.Width(),this->bindingRect.Height() , &dcMemory, 0, 0, SRCCOPY);
}
void Movable::Serialize(CArchive& archive){
	GameObject::Serialize(archive);
     /*
	 	bool isAllowedToMove;
	int movable_res;
	int lastX,lastY;
	vector<GameObject*> *gameObjects;
	MovmentVec movmentVec;
	 
	 */
	  if(archive.IsStoring())
		  archive << isAllowedToMove << movable_res << lastX << lastY << movmentVec.getSpeed() << static_cast<unsigned>(movmentVec.getDirection());
    else{
		int speed;
		unsigned direciton;
        archive >> isAllowedToMove >> movable_res >> lastX >> lastY >> speed >> direciton;
		movmentVec.setDirection(static_cast<DIRECTION>(direciton));
		movmentVec.setSpeed(speed);
	}
}

void Movable::move(){
	if(!isAllowedToMove)
	{
		OnMoveHalt();
		return;
	}
	if(dialog != 0)
		dialog->InvalidateRect(this->bindingRect);
	int newX,newY;
	lastX = newX = this->bindingRect.TopLeft().x;
	lastY = newY = this->bindingRect.TopLeft().y;
	//GameObject::bindingRect.topLeft();
	switch(movmentVec.getDirection()){
	case DIRECTION::Left:
		newX -= movmentVec.getSpeed();
		onMoveLeft();
		break;
	case DIRECTION::Right:
		newX += movmentVec.getSpeed();
		onMoveRight();
		break;
	case DIRECTION::Up:
		newY -= movmentVec.getSpeed();
		onMoveUp();
		break;
	case DIRECTION::Down:
		newY += movmentVec.getSpeed();
		onMoveDown();
		break;
	}
	if(newX > 720)
		newX = 0;
	if(newX < 0)
		newX = 719;
	reposition(newX,newY);
	if(dialog != 0)
		dialog->InvalidateRect(this->bindingRect);
}
int Movable::getLastX(){
	return lastX;
}
int Movable::getLastY(){
	return lastY;
}
Movable::~Movable(){}

