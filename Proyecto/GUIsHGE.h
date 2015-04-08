#ifndef INTERFAZ_GUIS_HGE_H
#define INTERFAZ_GUIS_HGE_H

#include "ObjetosHGE.h"

#include "hgeGUIBoton.h"
#include "hgeGUIFicha.h"

#define DOS 2
#define TRES 3
#define CUATRO 4
#define CINCO 5
#define SEIS 6
#define ACEPTAR 7
#define TIPOAZUL 8
#define TIPOROJO 9
#define TIPOAMARILLO 10
#define TIPOVERDE 11
#define TIPOCYAN 12
#define TIPOMAGENTA 13
#define TACTICAAZUL 14
#define TACTICAROJO 15
#define TACTICAAMARILLO 16
#define TACTICAVERDE 17
#define TACTICACYAN 18
#define TACTICAMAGENTA 19
#define ESTRATEGIAAZUL 20
#define ESTRATEGIAROJO 21
#define ESTRATEGIAAMARILLO 22
#define ESTRATEGIAVERDE 23
#define ESTRATEGIACYAN 24
#define ESTRATEGIAMAGENTA 25

#define BOTON_SALIR 16
#define CANTBOTONESACCION 7
#define BOTON_AGREGAR 		1
#define BOTON_ATACAR		2
#define BOTON_DESPLAZAR		3
#define BOTON_FINAGREGAR	4
#define BOTON_FINATACAR		5
#define BOTON_FINREAGRUPAR	6
#define BOTON_VERMISIONES 	7

#define ID_BOTON_DESP_1		1
#define ID_BOTON_DESP_2		2
#define ID_BOTON_DESP_3		3

#define XMAPA				5
#define YMAPA				61
namespace Interfaz{
	//objetos:
	hgeGUIButton *auxb[5];//
	hgeGUIListbox *auxt[6];//
    hgeGUIListbox *tacts[6];
    hgeGUIListbox *estrs[6];

	HTEXTURE tguiej;
	HTEXTURE tguip;

	hgeGUIText *GUIMisiones_Texto[CANTMISIONES+1];
	hgeGUIText *GUIPanel_Texto;
	hgeGUIText *GUIPanel_Mision;
	hgeGUIBoton *BOTONES_ACCION[CANTBOTONESACCION+1];
	hgeGUIText *GUIDPBG_Texto;
	hgeGUIBoton *GUIDPBG_Botones[3];

	hgeGUIFicha *MAPA[CANTPAISES];

	//constructores de GUIs:
	void ConstruirGUI_ACCIONES(); //
	void ConstruirGUI_MISIONES(); //
	void ConstruirGUI_MOSTRARMISION();	//
	void ConstruirGUI_EJ();//
	void ConstruirGUI_DPBG();//

	void ConstruirGUI_MAPA();
};

//terminar!!!!:

void Interfaz::ConstruirGUI_MAPA(){
	MAPA[0]=new hgeGUIFicha(1,458+XMAPA,169+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[1]=new hgeGUIFicha(2,424+XMAPA,169+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[2]=new hgeGUIFicha(3,431+XMAPA,136+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[3]=new hgeGUIFicha(4,434+XMAPA,99+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[4]=new hgeGUIFicha(5,503+XMAPA,158+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[5]=new hgeGUIFicha(6,542+XMAPA,143+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[6]=new hgeGUIFicha(7,515+XMAPA,90+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[7]=new hgeGUIFicha(8,468+XMAPA,94+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[8]=new hgeGUIFicha(9,454+XMAPA,60+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[9]=new hgeGUIFicha(10,414+XMAPA,41+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[10]=new hgeGUIFicha(11,431+XMAPA,15+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[11]=new hgeGUIFicha(12,465+XMAPA,11+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[12]=new hgeGUIFicha(13,481+XMAPA,35+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[13]=new hgeGUIFicha(14,512+XMAPA,6+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[14]=new hgeGUIFicha(15,551+XMAPA,27+YMAPA,33,33,tficha,0,0,fnt);

	MAPA[15]=new hgeGUIFicha(16,18+XMAPA,92+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[16]=new hgeGUIFicha(17,45+XMAPA,129+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[17]=new hgeGUIFicha(18,74+XMAPA,162+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[18]=new hgeGUIFicha(19,125+XMAPA,175+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[19]=new hgeGUIFicha(20,57+XMAPA,70+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[20]=new hgeGUIFicha(21,95+XMAPA,34+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[21]=new hgeGUIFicha(22,114+XMAPA,113+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[22]=new hgeGUIFicha(23,165+XMAPA,108+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[23]=new hgeGUIFicha(24,166+XMAPA,68+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[24]=new hgeGUIFicha(25,226+XMAPA,22+YMAPA,33,33,tficha,0,0,fnt);

	MAPA[25]=new hgeGUIFicha(26,288+XMAPA,50+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[26]=new hgeGUIFicha(27,290+XMAPA,110+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[27]=new hgeGUIFicha(28,298+XMAPA,165+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[28]=new hgeGUIFicha(29,334+XMAPA,146+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[29]=new hgeGUIFicha(30,362+XMAPA,177+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[30]=new hgeGUIFicha(31,359+XMAPA,130+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[31]=new hgeGUIFicha(32,393+XMAPA,130+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[32]=new hgeGUIFicha(33,392+XMAPA,83+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[33]=new hgeGUIFicha(34,349+XMAPA,41+YMAPA,33,33,tficha,0,0,fnt);

	MAPA[34]=new hgeGUIFicha(35,161+XMAPA,214+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[35]=new hgeGUIFicha(36,162+XMAPA,253+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[36]=new hgeGUIFicha(37,163+XMAPA,288+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[37]=new hgeGUIFicha(38,182+XMAPA,307+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[38]=new hgeGUIFicha(39,208+XMAPA,275+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[39]=new hgeGUIFicha(40,212+XMAPA,233+YMAPA,33,33,tficha,0,0,fnt);

	MAPA[40]=new hgeGUIFicha(41,318+XMAPA,256+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[41]=new hgeGUIFicha(42,401+XMAPA,243+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[42]=new hgeGUIFicha(43,441+XMAPA,307+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[43]=new hgeGUIFicha(44,356+XMAPA,290+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[44]=new hgeGUIFicha(45,391+XMAPA,272+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[45]=new hgeGUIFicha(46,398+XMAPA,306+YMAPA,33,33,tficha,0,0,fnt);

	MAPA[46]=new hgeGUIFicha(47,478+XMAPA,243+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[47]=new hgeGUIFicha(48,521+XMAPA,221+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[48]=new hgeGUIFicha(49,561+XMAPA,225+YMAPA,33,33,tficha,0,0,fnt);
	MAPA[49]=new hgeGUIFicha(50,526+XMAPA,287+YMAPA,33,33,tficha,0,0,fnt);

	GUIS[GUI_MAPA]=new hgeGUI();
	for(int i=0;i<CANTPAISES;i++)
		GUIS[GUI_MAPA]->AddCtrl(MAPA[i]);
};

void Interfaz::ConstruirGUI_MOSTRARMISION(){
	GUIPanel_Texto=new hgeGUIText(1,200,150,400,50,fnt);
	GUIPanel_Mision=new hgeGUIText(2,200,250,400,50,fnt);

	GUIS[GUI_MOSTRARMISION]=new hgeGUI();
	GUIS[GUI_MOSTRARMISION]->AddCtrl(GUIPanel_Texto);
	GUIS[GUI_MOSTRARMISION]->AddCtrl(GUIPanel_Mision);
	GUIS[GUI_MOSTRARMISION]->AddCtrl(new hgeGUIBoton(BOTON_SALIR,350,400,104,41,tpanel,0,366));
};

void Interfaz::ConstruirGUI_MISIONES(){

	for(int i=0;i<CANTMISIONES;i++){
		GUIMisiones_Texto[i]=new hgeGUIText(i,160,i*20+120,400,20,fnt);
		GUIMisiones_Texto[i]->SetText(Misiones[i].str);
	}
	GUIMisiones_Texto[CANTMISIONES]=new hgeGUIText(CANTMISIONES,160,CANTMISIONES*20+120,400,20,fnt);
	GUIMisiones_Texto[CANTMISIONES]->SetText(MisionGlobal.str);
	GUIS[GUI_MISIONES]=new hgeGUI();
	for(int i=0;i<CANTMISIONES+1;i++)
		GUIS[GUI_MISIONES]->AddCtrl(GUIMisiones_Texto[i]);
	GUIS[GUI_MISIONES]->AddCtrl(new hgeGUIBoton(BOTON_SALIR,350,400,104,41,tpanel,0,366));
};

void Interfaz::ConstruirGUI_DPBG(){
	GUIS[GUI_DPBG]=new hgeGUI();
	GUIDPBG_Texto=new hgeGUIText(4,473,422,118,65,fnt);
	GUIDPBG_Texto->SetMode(HGETEXT_CENTER);
	GUIDPBG_Botones[0]=new hgeGUIBoton(1,487,504,89,25,tpanel,0,407);
	GUIDPBG_Botones[1]=new hgeGUIBoton(2,487,529,89,25,tpanel,0,432);
	GUIDPBG_Botones[2]=new hgeGUIBoton(3,487,554,89,25,tpanel,0,457);

	GUIS[GUI_DPBG]->AddCtrl(GUIDPBG_Texto);
	GUIS[GUI_DPBG]->AddCtrl(GUIDPBG_Botones[0]);
	GUIS[GUI_DPBG]->AddCtrl(GUIDPBG_Botones[1]);
	GUIS[GUI_DPBG]->AddCtrl(GUIDPBG_Botones[2]);
};

void Interfaz::ConstruirGUI_ACCIONES(){
	GUIS[GUI_ACCIONES]=new hgeGUI();
	tguip=hge->Texture_Load("GUIP.PNG");
	BOTONES_ACCION[0]=0;
	BOTONES_ACCION[1]=new hgeGUIBoton(BOTON_AGREGAR,8,28,81,25,tguip,0,0);
	BOTONES_ACCION[2]=new hgeGUIBoton(BOTON_ATACAR,96,28,73,25,tguip,0,25);
	BOTONES_ACCION[2]->SetMode(true);
	BOTONES_ACCION[3]=new hgeGUIBoton(BOTON_DESPLAZAR,176,28,89,25,tguip,0,50);
	BOTONES_ACCION[3]->SetMode(true);
	BOTONES_ACCION[4]=new hgeGUIBoton(BOTON_FINAGREGAR,304,28,73,25,tguip,0,75);
	BOTONES_ACCION[5]=new hgeGUIBoton(BOTON_FINATACAR,384,28,81,25,tguip,0,100);
	BOTONES_ACCION[6]=new hgeGUIBoton(BOTON_FINREAGRUPAR,472,28,81,25,tguip,0,125);
	BOTONES_ACCION[7]=new hgeGUIBoton(BOTON_VERMISIONES,560,28,89,25,tguip,0,150);

	for(int i=1;i<=CANTBOTONESACCION;i++){
		BOTONES_ACCION[i]->bEnabled=false;	////
		GUIS[GUI_ACCIONES]->AddCtrl(BOTONES_ACCION[i]);
	}
}

void Interfaz::ConstruirGUI_EJ(){
	GUIS[GUI_EJ]=new hgeGUI();
	tguiej=hge->Texture_Load("GUIEJ.PNG");


	auxb[0]=new hgeGUIButton(DOS,232,24,41,41,tguiej,0,0);
	auxb[0]->SetMode(true);
	auxb[0]->SetState(true);
	GUIS[GUI_EJ]->AddCtrl(auxb[0]);
	auxb[1]=new hgeGUIButton(TRES,280,24,41,41,tguiej,0,41);
	auxb[1]->SetMode(true);
	GUIS[GUI_EJ]->AddCtrl(auxb[1]);
	auxb[2]=new hgeGUIButton(CUATRO,328,24,41,41,tguiej,0,82);
	auxb[2]->SetMode(true);
	GUIS[GUI_EJ]->AddCtrl(auxb[2]);
	auxb[3]=new hgeGUIButton(CINCO,376,24,41,41,tguiej,0,123);
	auxb[3]->SetMode(true);
	GUIS[GUI_EJ]->AddCtrl(auxb[3]);
	auxb[4]=new hgeGUIButton(SEIS,424,24,41,41,tguiej,0,164);
	auxb[4]->SetMode(true);
	GUIS[GUI_EJ]->AddCtrl(auxb[4]);
	//GUIS[GUI_EJ]->AddCtrl(new hgeGUIButton(CANCELAR,624,24,73,41,tguiej,82,0));
	GUIS[GUI_EJ]->AddCtrl(new hgeGUIButton(ACEPTAR,704,24,73,41,tguiej,0,246));

	auxt[0]=new hgeGUIListbox(TIPOAZUL,146,98,91,47,fnt,0xff000000,0xffffffff,0xff0000ff);
	auxt[0]->AddItem("HUMANO");
	auxt[0]->AddItem("VIRTUAL");
	//auxt[0]->AddItem("NINGUNO");
	GUIS[GUI_EJ]->AddCtrl(auxt[0]);
	auxt[1]=new hgeGUIListbox(TIPOROJO,410,98,91,47,fnt,0xff000000,0xffffffff,0xffff0000);
	auxt[1]->AddItem("HUMANO");
	auxt[1]->AddItem("VIRTUAL");
	auxt[1]->SetSelectedItem(1);
	//auxt[1]->AddItem("NINGUNO");
	GUIS[GUI_EJ]->AddCtrl(auxt[1]);
	auxt[2]=new hgeGUIListbox(TIPOAMARILLO,674,98,91,47,fnt,0xff000000,0xffffffff,0xffdddd00);
	auxt[2]->AddItem("HUMANO");
	auxt[2]->AddItem("VIRTUAL");
	auxt[2]->AddItem("NINGUNO");
	auxt[2]->SetSelectedItem(2);
	GUIS[GUI_EJ]->AddCtrl(auxt[2]);
	auxt[3]=new hgeGUIListbox(TIPOVERDE,146,355,91,47,fnt,0xff000000,0xffffffff,0xff00ff00);
	auxt[3]->AddItem("HUMANO");
	auxt[3]->AddItem("VIRTUAL");
	auxt[3]->AddItem("NINGUNO");
	auxt[3]->SetSelectedItem(2);
	GUIS[GUI_EJ]->AddCtrl(auxt[3]);
	auxt[4]=new hgeGUIListbox(TIPOCYAN,410,355,91,47,fnt,0xff000000,0xffffffff,0xff00dddd);
	auxt[4]->AddItem("HUMANO");
	auxt[4]->AddItem("VIRTUAL");
	auxt[4]->AddItem("NINGUNO");
	auxt[4]->SetSelectedItem(2);
	GUIS[GUI_EJ]->AddCtrl(auxt[4]);
	auxt[5]=new hgeGUIListbox(TIPOMAGENTA,674,355,91,47,fnt,0xff000000,0xffffffff,0xffdd00dd);
	auxt[5]->AddItem("HUMANO");
	auxt[5]->AddItem("VIRTUAL");
	auxt[5]->AddItem("NINGUNO");
	auxt[5]->SetSelectedItem(2);
	GUIS[GUI_EJ]->AddCtrl(auxt[5]);


    tacts[0]=new hgeGUIListbox(TACTICAAZUL,27,179,91,91,fnt,0xff000000,0xffffffff,0xff0000ff);
    tacts[0]->AddItem("NINGUN NIVEL");
    tacts[0]->AddItem("NIVEL 0");
    tacts[0]->AddItem("NIVEL 1");
    tacts[0]->AddItem("NIVEL 2");
    tacts[0]->AddItem("NIVEL 3");
    tacts[0]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(tacts[0]);
    tacts[1]=new hgeGUIListbox(TACTICAROJO,291,179,91,91,fnt,0xff000000,0xffffffff,0xffff0000);
    tacts[1]->AddItem("NINGUN NIVEL");
    tacts[1]->AddItem("NIVEL 0");
    tacts[1]->AddItem("NIVEL 1");
    tacts[1]->AddItem("NIVEL 2");
    tacts[1]->AddItem("NIVEL 3");
    tacts[1]->SetSelectedItem(1);
    GUIS[GUI_EJ]->AddCtrl(tacts[1]);
    tacts[2]=new hgeGUIListbox(TACTICAAMARILLO,555,179,91,91,fnt,0xff000000,0xffffffff,0xffdddd00);
    tacts[2]->AddItem("NINGUN NIVEL");
    tacts[2]->AddItem("NIVEL 0");
    tacts[2]->AddItem("NIVEL 1");
    tacts[2]->AddItem("NIVEL 2");
    tacts[2]->AddItem("NIVEL 3");
    tacts[2]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(tacts[2]);
    tacts[3]=new hgeGUIListbox(TACTICAVERDE,27,435,91,91,fnt,0xff000000,0xffffffff,0xff00ff00);
    tacts[3]->AddItem("NINGUN NIVEL");
    tacts[3]->AddItem("NIVEL 0");
    tacts[3]->AddItem("NIVEL 1");
    tacts[3]->AddItem("NIVEL 2");
    tacts[3]->AddItem("NIVEL 3");
    tacts[3]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(tacts[3]);
    tacts[4]=new hgeGUIListbox(TACTICACYAN,291,435,91,91,fnt,0xff000000,0xffffffff,0xff00dddd);
    tacts[4]->AddItem("NINGUN NIVEL");
    tacts[4]->AddItem("NIVEL 0");
    tacts[4]->AddItem("NIVEL 1");
    tacts[4]->AddItem("NIVEL 2");
    tacts[4]->AddItem("NIVEL 3");
    tacts[4]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(tacts[4]);
    tacts[5]=new hgeGUIListbox(TACTICAMAGENTA,555,435,91,91,fnt,0xff000000,0xffffffff,0xffdd00dd);
    tacts[5]->AddItem("NINGUN NIVEL");
    tacts[5]->AddItem("NIVEL 0");
    tacts[5]->AddItem("NIVEL 1");
    tacts[5]->AddItem("NIVEL 2");
    tacts[5]->AddItem("NIVEL 3");
    tacts[5]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(tacts[5]);

    estrs[0]=new hgeGUIListbox(ESTRATEGIAAZUL,147,179,91,91,fnt,0xff000000,0xffffffff,0xff0000ff);
    estrs[0]->AddItem("NINGUN NIVEL");
    estrs[0]->AddItem("NIVEL 0");
    estrs[0]->AddItem("NIVEL 1");
    estrs[0]->AddItem("NIVEL 2");
    estrs[0]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(estrs[0]);
    estrs[1]=new hgeGUIListbox(ESTRATEGIAROJO,411,179,91,91,fnt,0xff000000,0xffffffff,0xffff0000);
    estrs[1]->AddItem("NINGUN NIVEL");
    estrs[1]->AddItem("NIVEL 0");
    estrs[1]->AddItem("NIVEL 1");
    estrs[1]->AddItem("NIVEL 2");
    estrs[1]->SetSelectedItem(1);
    GUIS[GUI_EJ]->AddCtrl(estrs[1]);
    estrs[2]=new hgeGUIListbox(ESTRATEGIAAMARILLO,675,179,91,91,fnt,0xff000000,0xffffffff,0xffdddd00);
    estrs[2]->AddItem("NINGUN NIVEL");
    estrs[2]->AddItem("NIVEL 0");
    estrs[2]->AddItem("NIVEL 1");
    estrs[2]->AddItem("NIVEL 2");
    estrs[2]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(estrs[2]);
    estrs[3]=new hgeGUIListbox(ESTRATEGIAVERDE,147,435,91,91,fnt,0xff000000,0xffffffff,0xff00ff00);
    estrs[3]->AddItem("NINGUN NIVEL");
    estrs[3]->AddItem("NIVEL 0");
    estrs[3]->AddItem("NIVEL 1");
    estrs[3]->AddItem("NIVEL 2");
    estrs[3]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(estrs[3]);
    estrs[4]=new hgeGUIListbox(ESTRATEGIACYAN,411,435,91,91,fnt,0xff000000,0xffffffff,0xff00dddd);
    estrs[4]->AddItem("NINGUN NIVEL");
    estrs[4]->AddItem("NIVEL 0");
    estrs[4]->AddItem("NIVEL 1");
    estrs[4]->AddItem("NIVEL 2");
    estrs[4]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(estrs[4]);
    estrs[5]=new hgeGUIListbox(ESTRATEGIAMAGENTA,675,435,91,91,fnt,0xff000000,0xffffffff,0xffdd00dd);
    estrs[5]->AddItem("NINGUN NIVEL");
    estrs[5]->AddItem("NIVEL 0");
    estrs[5]->AddItem("NIVEL 1");
    estrs[5]->AddItem("NIVEL 2");
    estrs[5]->SetSelectedItem(0);
    GUIS[GUI_EJ]->AddCtrl(estrs[5]);

	GUIS[GUI_EJ]->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	//GUIS[GUI_EJ]->SetCursor(cursor);
	GUIS[GUI_EJ]->SetFocus(1);
};

#endif
