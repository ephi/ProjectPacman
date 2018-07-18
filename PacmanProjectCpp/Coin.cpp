#include "stdafx.h"
#include "Coin.h"
#include "resource.h"
IMPLEMENT_SERIAL(Coin, CObject, 1)
void Coin::OnDraw(CDC *cdc) {
	CBrush b(RGB(228,228,228));
	CBrush *oldB = cdc->SelectObject(&b);
	cdc->Ellipse(bindingRect);
	cdc->SelectObject(oldB);
}