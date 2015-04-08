#ifndef CLASE_JUGADOR_HUMANO_H
#define CLASE_JUGADOR_HUMANO_H

#include "Interfaz.h"
#include "Jugador.h"

//Definicion de la clase JugadorHumano:
class JugadorHumano:public Jugador{
	public:
		JugadorHumano(TJugador _color);
		~JugadorHumano();

		const Mision *GetMision();
		void Agregar();
		void Atacar();
		void Reagrupar();
		void DesplazarPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant);
};


//implementaciones:

JugadorHumano::JugadorHumano(TJugador _color):Jugador(_color){
};

JugadorHumano::~JugadorHumano(){
	mision=0;
};

const Mision *JugadorHumano::GetMision(){
	return mision;
};

void JugadorHumano::Agregar(){
	Interfaz::ModoJuego_AgregarFichas(Color());
};

void JugadorHumano::Atacar(){
	Interfaz::ModoJuego_Atacar(Color());
};

void JugadorHumano::Reagrupar(){
	Interfaz::ModoJuego_Reagrupar(Color());
};

void JugadorHumano::DesplazarPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant){
	int cant=Interfaz::GUI_DesplazarPorBatallaGanada(Color(),_origen,_destino,MaxCant);
	DesplazarFichas(_origen,_destino,cant);
};

#endif
