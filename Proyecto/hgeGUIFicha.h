#ifndef INTERFAZ_GUIFICHA_HGE_H
#define INTERFAZ_GUIFICHA_HGE_H

#include "ObjetosHGE.h"




class hgeGUIFicha : public hgeGUIObject
{
public:
	hgeGUIFicha(int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty,hgeFont *_fnt);
	virtual			~hgeGUIFicha();

	void			SetState(bool _bSelected) { bSelected=_bSelected; }
	bool			GetState() const { return bSelected; }
	void			SetMarcado(bool _bMarcado) { bMarcado=_bMarcado; }
	bool			GetMarcado() const { return bMarcado; }

	virtual void	Render();
	virtual bool	MouseLButton(bool bDown);

private:
	bool			bSelected;
	bool			bMarcado;
	bool			bOldState;
	hgeFont *fnt;
	hgeSprite		*sprNoSel, *sprSel,*sprMarcado;
	TJugador 		jug;
};

hgeGUIFicha::hgeGUIFicha(int _id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty,hgeFont *_fnt)
{
	id=_id;
	bStatic=false;
	bVisible=true;
	bEnabled=true;
	rect.Set(x, y, x+w, y+h);

	bSelected=false;
	bMarcado=false;

	fnt=_fnt;
	jug=TEG[id-1].Ocupante();

	sprNoSel = new hgeSprite(tex, tx, ty, w, h);
	sprSel = new hgeSprite(tex, tx+w, ty, w, h);
	sprMarcado = new hgeSprite(tex, tx+w*2, ty, w, h);

	sprNoSel->SetBlendMode(BLEND_COLORADD|BLEND_ALPHABLEND  );
	sprSel->SetBlendMode(BLEND_COLORADD|BLEND_ALPHABLEND  );
	sprMarcado->SetBlendMode(BLEND_COLORADD|BLEND_ALPHABLEND  );
	sprNoSel->SetColor(Interfaz::ClrJug[jug]);
	sprSel->SetColor(Interfaz::ClrJug[jug]);
	sprMarcado->SetColor(Interfaz::ClrJug[jug]);
}

hgeGUIFicha::~hgeGUIFicha()
{
	if(sprNoSel) delete sprNoSel;
	if(sprSel) delete sprSel;
	if(sprMarcado) delete sprSel;
}

void hgeGUIFicha::Render()
{
	if(jug!=TEG[id-1].Ocupante()){
		jug=TEG[id-1].Ocupante();
		sprNoSel->SetColor(Interfaz::ClrJug[jug]);
		sprSel->SetColor(Interfaz::ClrJug[jug]);
		sprMarcado->SetColor(Interfaz::ClrJug[jug]);
	}
	if(bMarcado)  sprMarcado->Render(rect.x1, rect.y1);
	else if(bSelected) sprSel->Render(rect.x1, rect.y1);
		 	else sprNoSel->Render(rect.x1, rect.y1);

	fnt->printfb(rect.x1+9,rect.y1+10,15.0f,13.0f,HGETEXT_CENTER,"%i",TEG[id-1].Fichas());
}

bool hgeGUIFicha::MouseLButton(bool bDown)
{
	if(bDown)
	{
		bOldState=bSelected; bSelected=true;
		return false;
	}
	else
	{
		bSelected=!bOldState;
		return true;
	}
}


#endif
