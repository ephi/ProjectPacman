#pragma once
#include "Pickable.h"
class Powerup : public Pickable {
protected:
	GameObject* getInstance() { return new Powerup(); }
public:
	DECLARE_SERIAL(Powerup)
	Powerup(){};
	Powerup(int w,int h,int x,int y) : Pickable(w,h,x,y){};
	~Powerup(){};
	void OnDraw(CDC *cdc);
};