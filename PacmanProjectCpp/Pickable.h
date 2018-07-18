#pragma once
#include "GameObject.h"
class Pickable : public GameObject {
public:
	Pickable(){};
	Pickable(int w,int h,int x,int y): GameObject(w,h,x,y){};
};