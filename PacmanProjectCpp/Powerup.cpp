#include "stdafx.h"
#include "Powerup.h"
IMPLEMENT_SERIAL(Powerup, CObject, 1)
void Powerup::OnDraw(CDC *cdc) {
	CBrush b(RGB(237,28,36));
	CBrush *oldB = cdc->SelectObject(&b);
	cdc->Ellipse(bindingRect);
	cdc->SelectObject(oldB);
}
