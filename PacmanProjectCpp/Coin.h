#pragma once
#include "Pickable.h"
class Coin : public Pickable {
protected:
	GameObject* getInstance(){ return new Coin();}
public:
	DECLARE_SERIAL(Coin)
	Coin(){};
	Coin(int w,int h,int x,int y) : Pickable(w,h,x,y){};
	~Coin(){};
	void OnDraw(CDC *cdc);
};