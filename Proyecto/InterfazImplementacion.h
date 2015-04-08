#ifndef INTERFAZ_IMPLEMENTACION_H
#define INTERFAZ_IMPLEMENTACION_H

#include "Interfaz.h"

#include "ObjetosHGE.h"

#include "FuncionesHGE.h"

bool Interfaz::IniciarInterfaz(){
	hge = hgeCreate(HGE_VERSION);
	Inicio_SetSistema();
	if(hge->System_Initiate()){
		Inicio_ConstruirObjetos();
		return true;
	}else
		return false;
};
bool Interfaz::TerminarInterfaz(){
	Principal_DestruirObjetos();
	Inicio_DestruirObjetos();
	hge->System_Shutdown();
	hge->Release();
	hge=0;
	return true;
};
void Interfaz::Alerta(const char *mensaje){
	MessageBox(NULL, mensaje, "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
};
void Interfaz::Log(const char *mensaje){
    hge->System_Log("%s",mensaje);
};
int Interfaz::Random(int min,int max){
	return hge->Random_Int(min,max);
};



bool Interfaz::GUI_EdicionJugadores(){
	GUIEJ_ConstruirObjetos();
	hge->System_SetState(HGE_FRAMEFUNC, GUIEJ_Frame);
	hge->System_SetState(HGE_RENDERFUNC, GUIEJ_Render);
	GUIS[GUI_EJ]->Enter();
	hge->System_Start();
	GUIEJ_DestruirObjetos();

	Principal_ConstruirObjetos();
	hge->System_SetState(HGE_FRAMEFUNC, 0);
	hge->System_SetState(HGE_RENDERFUNC, Dibujar_Elementos);
	return true;
};

bool Interfaz::GUI_MostrarMision(TJugador _turno,const Mision *mision,bool ganador){
	MostrarMision_Inicio(_turno,mision,ganador);
	hge->System_SetState(HGE_FRAMEFUNC, MostrarMision_Frame);
	hge->System_Start();
	MostrarMision_Fin();
	hge->System_SetState(HGE_FRAMEFUNC, 0);
	return true;
};
bool Interfaz::GUI_Alerta(const char *mensaje){
	MessageBox(NULL, mensaje, "Advertencia:", MB_OK | MB_SYSTEMMODAL);
	return true;
};

int Interfaz::GUI_DesplazarPorBatallaGanada(TJugador _turno,TPais ori,TPais des,int maxCant){
	DPBG_Inicio(_turno,ori,des,maxCant);
	hge->System_SetState(HGE_FRAMEFUNC, DPBG_Frame);
	hge->System_Start();
	DPBG_Fin();
	hge->System_SetState(HGE_FRAMEFUNC, 0);
	return cant;
};


bool Interfaz::Dibujar_Elementos(){

	hge->Gfx_BeginScene();

	Render_Elementos();
	Render_GUIs();
	hge->Gfx_EndScene();

	return false;
};
bool Interfaz::Modo_MarcarPais(TPais pais){
	if(hge->System_GetState(HGE_FRAMEFUNC)==0){
		Marcar_Inicio(pais);
		hge->System_SetState(HGE_FRAMEFUNC, Marcar_Frame);
		hge->System_Start();
		Marcar_Fin();
		hge->System_SetState(HGE_FRAMEFUNC, 0);
		return true;
	}else
		return false;
};

bool Interfaz::Modo_Batalla(TPais _a,TPais _d,int a1,int a2,int a3,int d1,int d2,int d3){
	Batalla_Inicio(_a,_d,a1,a2,a3,d1,d2,d3);
	hge->System_SetState(HGE_FRAMEFUNC, Batalla_Frame);
	hge->System_Start();
	Batalla_Fin();
	hge->System_SetState(HGE_FRAMEFUNC, 0);

	return true;

};

bool Interfaz::Modo_FinPartida(TJugador ganador,const Mision *mision){
	GUI_MostrarMision(ganador,mision,true);
	return true;
};

bool Interfaz::ModoJuego_AgregarFichas(TJugador _turno){
	Inicio_Modo_Agregar(_turno);
	hge->System_SetState(HGE_FRAMEFUNC, Frame_Modo_Agregar);
	hge->System_Start();
	Fin_Modo_Agregar();
	hge->System_SetState(HGE_FRAMEFUNC, 0);
	return true;
};

bool Interfaz::ModoJuego_Atacar(TJugador _turno){

	Inicio_Modo_Atacar(_turno);

	for(;;){
		hge->System_SetState(HGE_FRAMEFUNC, Frame_Modo_Atacar);
		Batalla=false;
		hge->System_Start();
		if(Batalla)
			Jugadores[_turno]->Batalla(Atacante,Defensor);
		else
			break;
	}
	Fin_Modo_Atacar();
	hge->System_SetState(HGE_FRAMEFUNC, 0);
	return true;
};

bool Interfaz::ModoJuego_Reagrupar(TJugador _turno){
	Inicio_Modo_Reagrupar(_turno);
	hge->System_SetState(HGE_FRAMEFUNC, Frame_Modo_Reagrupar);
	hge->System_Start();
	Fin_Modo_Reagrupar();
	hge->System_SetState(HGE_FRAMEFUNC, 0);
	return true;
};



#endif
