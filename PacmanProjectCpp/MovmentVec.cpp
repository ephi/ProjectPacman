#include "StdAfx.h"
#include "MovmentVec.h"
//IMPLEMENT_SERIAL(MovmentVec, CObject, 1)
MovmentVec::MovmentVec(): speed(0),direction(DIRECTION::Down){
}
MovmentVec::MovmentVec(int speed,DIRECTION direction): speed(speed),direction(direction)
{
}
int MovmentVec::getSpeed() const{
	return speed;
}
DIRECTION MovmentVec::getDirection() const{
	return direction;
}
void MovmentVec::setSpeed(int speed){
	this->speed = speed;
}
void MovmentVec::setDirection(DIRECTION direction){
	this->direction = direction;
}
void MovmentVec::Serialize(CArchive& archive){
	//CObject::Serialize( archive );
	// now do the stuff for our specific class
	if(archive.IsStoring())
		archive << speed;
	else
		archive >> speed;

}
MovmentVec::~MovmentVec(void)
{
}
