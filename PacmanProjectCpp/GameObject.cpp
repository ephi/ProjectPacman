#include "stdafx.h"
#include "GameObject.h"
GameObject::GameObject() {
	toBeDeleted = false;
	dialog = NULL;
} 
GameObject::GameObject(int w,int h,int x,int y) : bindingRect(x,y,x+w,y+h),dialog(NULL){
	toBeDeleted = false;
};
CRect GameObject::getBindingRect(){
	return this->bindingRect;
}
void GameObject::Draw(CDC *cdc) {
	if(!toBeDeleted)
		OnDraw(cdc);
	else{
		CBrush b(RGB(0,0,0));
		CBrush *oldB = cdc->SelectObject(&b);
		cdc->Rectangle(this->bindingRect);
		cdc->SelectObject(oldB);
	}
}
void GameObject::reposition(int x,int y){
	this->bindingRect.MoveToXY(x,y);
}
CDialogEx* GameObject::getDialog() const{
	return this->dialog;
}
void GameObject::setDialog(CDialogEx* dialog){
	this->dialog = dialog;
}

void GameObject::setToBeDeleted(bool toBeDeleted) {this->toBeDeleted = toBeDeleted;}
bool GameObject::getToBeDeleted() const {
	return toBeDeleted;
}
GameObject* GameObject::clone(){
	GameObject* clone = getInstance();
	clone->toBeDeleted = this->toBeDeleted;
	clone->bindingRect = CRect(this->bindingRect);
	clone->dialog = dialog;
	onClone(clone);
	return clone;
}

void GameObject::Serialize( CArchive& archive )
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );
    // now do the stuff for our specific class
    if(archive.IsStoring())
		archive << toBeDeleted << bindingRect;
    else
        archive >> toBeDeleted >> bindingRect;
}

bool GameObject::areTouching(GameObject* gameObject){
	if(gameObject == NULL)
		return false;
	if(this == gameObject)
		return false;
	CRect out;
	if(out.IntersectRect(this->bindingRect,gameObject->bindingRect))
	{
		onObjectTouching(gameObject);
		return true;
	}
	return false;
}
