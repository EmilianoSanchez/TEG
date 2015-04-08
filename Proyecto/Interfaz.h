#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "include\hge.h"
//componentes publicos de la interfaz:


namespace Interfaz{
//variables:
float DELAY=0.05f;

//funciones basicas:
bool IniciarInterfaz();
bool TerminarInterfaz();
void Alerta(const char *mensaje);
void Log(const char *mensaje);
int Random(int min,int max);

//funciones de GUI:
bool GUI_EdicionJugadores();
bool GUI_MostrarMision(TJugador _turno,const Mision *mision,bool ganador=false);
bool GUI_Alerta(const char *mensaje);
int GUI_DesplazarPorBatallaGanada(TJugador _turno,TPais ori,TPais des,int max);

//funciones de renderizado:
bool Dibujar_Elementos();

//funciones "loop":
bool Modo_MarcarPais(TPais pais);
bool Modo_Batalla(TPais _a,TPais _d,int a1,int a2,int a3,int d1,int d2,int d3);

bool Modo_FinPartida(TJugador ganador,const Mision *mision);

//funciones invocadas por la clase JugadorHumano:
bool ModoJuego_AgregarFichas(TJugador _turno);
bool ModoJuego_Atacar(TJugador _turno);
bool ModoJuego_Reagrupar(TJugador _turno);
};

#endif
