#include "stdafx.h"
#include "resource.h"
#include "Levelwall.h"
IMPLEMENT_SERIAL(Levelwall, CObject, 1)
Levelwall::Levelwall(int w,int h,int x,int y): GameObject(w,h,x,y){

}
void Levelwall::Serialize(CArchive& archive){
	GameObject::Serialize(archive);
}
void Levelwall::OnDraw(CDC *cdc){
	CBrush brush(RGB(39,58,161));
	cdc->FillRect(bindingRect,&brush);
}
GameObject* Levelwall::getInstance(){ return new Levelwall();}
Levelwall::~Levelwall(){
}