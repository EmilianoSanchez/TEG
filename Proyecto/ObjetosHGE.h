#ifndef INTERFAZ_OBJETOS_HGE_H
#define INTERFAZ_OBJETOS_HGE_H

#include "include\hge.h"
#include "include\hgesprite.h"
#include "include\hgefont.h"
#include "include\hgegui.h"
#include "include\hgeguictrls.h"

#define CANTGUIS 			6
#define GUI_EJ 				0
#define GUI_MAPA 			1
#define GUI_ACCIONES		2
#define GUI_DPBG			3
#define GUI_MISIONES		4
#define GUI_MOSTRARMISION	5


#define NORMAL 			6
#define MARCADO			7
#define SELECCIONADO	8

namespace Interfaz{
	//strings:
	const char *StrJugadores[MAXJUGADORES+1]={"Azul","Rojo","Amarillo","Verde","Cyan","Magenta","Ninguno"};
	const char *StrEstados[]={"NoJuego","InicioNuevaPartida","RondaInicial1","RondaInicial2","RondaDefensiva","RondaOfensiva","FinPartida"};
	const char *StrSituacion[]={"RepartoInicial","AgregandoFichas","Atacando","Reagrupando","Ninguna"};
	const char *StrTipoJugador[]={"HUMANO","VIRTUAL","NINGUNO"};
	const char *StrNivelInteligencia[]={"Nivel 0","Nivel 1","Nivel 2","Nivel 3","Ninguna"};
	const char *StrContinentes[]={"Asia","Norteamerica","Europa","Sudamerica","Africa","Oceania"};
	const DWORD ClrJug[MAXJUGADORES+1]={0xff0000e0,0xffe00000,0xffb0b000,0xff00e000,0xff00b0b0,0xffb000b0,0xffa0a0a0};

	//objetos globales:
	HGE *hge=0;
	hgeFont *fnt;
	float dt=0.001f;
	float auxdt=0;

	//guis:
	hgeGUI *GUIS[CANTGUIS];
	bool GUIactivadas[CANTGUIS];

	//objetos para modos de juego
	TJugador turno;

	bool ataq=false;
	bool desp=false;
	int cant;
	TPais psel=0;//pais seleccionado
	TPais psel2=0;
	TPais pfoc=0;//pais en el que se agrega, saca o ataca

	//sprites y fondos:
	hgeSprite *fGUIEJ;

	hgeSprite *fPRINCIPAL;
	hgeSprite *interrogacion;

	HTEXTURE tficha;
	HTEXTURE tpanel;
	hgeSprite *panel;
	//del DPBG:
	TPais Origen,Destino;
	//de la batalla:
	hgeSprite *dado;
	TPais Atacante;
	TPais Defensor;
	bool Batalla=false;
	bool bdados[2][3];
	int dados[2][3];

};

#endif
