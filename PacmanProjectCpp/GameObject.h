#pragma once
#include <mmsystem.h>
#define GAME_MUSIC L"Pac-Man_Fever.wav"
class GameObject : public CObject {
public: 
	//DECLARE_SERIAL(GameObject)
	GameObject();
	GameObject(int w,int h,int x,int y);
	virtual ~GameObject(){};
	virtual void Draw(CDC *cdc);
	virtual void OnDraw(CDC *cdc) = 0;
	bool areTouching(GameObject* gameObject);
	virtual bool isMovementBlocking() { return false; }
	virtual void onObjectTouching(GameObject* touched){}
	void reposition(int x,int y);
	CRect getBindingRect();
	CDialogEx* getDialog() const;
	void setDialog(CDialogEx* dialog);
	void setToBeDeleted(bool toBeDeleted);
	bool getToBeDeleted() const;
	virtual GameObject* clone();
	void Serialize(CArchive& archive);
protected:
	virtual GameObject* getInstance() = 0;
	virtual void onClone(GameObject* clone){ }
	bool toBeDeleted;
	CDialogEx* dialog;
	CRect bindingRect;
};