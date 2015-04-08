#ifndef INTERFAZ_GUIBOTON_HGE_H
#define INTERFAZ_GUIBOTON_HGE_H

#include "ObjetosHGE.h"

class hgeGUIBoton : public hgeGUIObject
{
public:
	hgeGUIBoton(int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty);
	virtual			~hgeGUIBoton();

	void			SetMode(bool _bTrigger) { bTrigger=_bTrigger; }
	void			SetState(bool _bPressed) { bPressed=_bPressed; }
	bool			GetState() const { return bPressed; }

	virtual void	Render();
	virtual bool	MouseLButton(bool bDown);

private:
	bool			bTrigger;
	bool			bPressed;
	bool			bOldState;
	hgeSprite		*sprUp, *sprDown, *sprEnabled;
};

hgeGUIBoton::hgeGUIBoton(int _id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty)
{
	id=_id;
	bStatic=false;
	bVisible=true;
	bEnabled=true;
	rect.Set(x, y, x+w, y+h);

	bPressed=false;
	bTrigger=false;

	sprUp = new hgeSprite(tex, tx, ty, w, h);
	sprDown = new hgeSprite(tex, tx+w, ty, w, h);
	sprEnabled = new hgeSprite(tex,tx+w*2,ty,w,h);
}

hgeGUIBoton::~hgeGUIBoton()
{
	if(sprUp) delete sprUp;
	if(sprDown) delete sprDown;
	if(sprEnabled) delete sprEnabled;
}

void hgeGUIBoton::Render()
{
	if(!bEnabled) sprEnabled->Render(rect.x1,rect.y1);
	else 	if(bPressed) sprDown->Render(rect.x1, rect.y1);
		 	else sprUp->Render(rect.x1, rect.y1);
}

bool hgeGUIBoton::MouseLButton(bool bDown)
{
	if(bDown)
	{
		bOldState=bPressed; bPressed=true;
		return false;
	}
	else
	{
		if(bTrigger) bPressed=!bOldState;
		else bPressed=false;
		return true; 
	}
}

#endif
