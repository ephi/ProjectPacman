#include "StdAfx.h"
#include "CoinGenerator.h"
//void WINAPI OutputDebugString(
//  _In_opt_ LPCTSTR lpOutputString
//);
CoinGenerator::CoinGenerator(vector<GameObject*> *gameObjects,CDialogEx* dialog)
{
	coinWidth = 7;
	coinHeight = 7;
	coinsGenerated = 0;
	this->gameObjects = gameObjects;
	this->dialog = dialog;
}
bool CoinGenerator::canGenerate(Coin *c){
	for(vector<GameObject*>::size_type i=0;i< gameObjects->size(); ++i){	
		if((*gameObjects)[i]->areTouching(c))
			return false;
	}
	return true;
}
void CoinGenerator::generateCoins(int x,int y){
	if(x < 0 || y < 0)
		return;
	if(x > 721 || y > 452)
		return;
	int offset = 11;
	Coin *c = new Coin(coinWidth,coinHeight,x,y);
	c->setDialog(dialog);
	if(canGenerate(c))
	{
		//try generate right
		gameObjects->push_back(c);
		coinsGenerated++;
		TRACE("Coin x,y:(%d,%d)\n",x,y);
		generateCoins(x + coinWidth + offset,y);	
		//try generate up
		generateCoins(x ,y - coinHeight - offset);
		//try generate left	
		generateCoins(x - coinWidth - offset,y);	
		//try generate down
		generateCoins(x ,y + coinHeight + offset);
	}
	else{ 
		delete c;
	}

}
CoinGenerator::~CoinGenerator(void)
{
}