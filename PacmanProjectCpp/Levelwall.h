#pragma once
#include "GameObject.h"
#include <string>
using namespace std;
class Levelwall : public GameObject{
protected:
	GameObject* getInstance();
public: 
	virtual bool isMovementBlocking() { return true; }
	void OnDraw(CDC *cdc);
	DECLARE_SERIAL(Levelwall)
	Levelwall(){};
	void Serialize(CArchive& archive);
	Levelwall(int w,int h,int x,int y);
	~Levelwall();
};