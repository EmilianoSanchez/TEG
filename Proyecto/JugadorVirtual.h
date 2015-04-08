#ifndef CLASE_JUGADOR_VIRTUAL_H
#define CLASE_JUGADOR_VIRTUAL_H

#include "Jugador.h"

#include "InteligenciaArtificial.h"

//Definicion de la clase JugadorVirtual:
class JugadorVirtual:public Jugador{
	public:
		//Estrategia:
		Estrategia *estrategia;
        int desplazar;

        //Tactica:
        Tactica *tactica;

		JugadorVirtual(TJugador _color,Estrategia *est,Tactica *tac);
		~JugadorVirtual();

		const Mision *GetMision();
		void TomarMision(const Mision *_mision);
		void Agregar();
		void Atacar();
		void Reagrupar();
		void DesplazarPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant);
};

#include "ComponentesIA.h"


//implementaciones:

JugadorVirtual::JugadorVirtual(TJugador _color,Estrategia *est,Tactica *tac):Jugador(_color){

    estrategia=est;
    estrategia->SetJugador(this);
	tactica=tac;
	tactica->SetJugador(this);
};

JugadorVirtual::~JugadorVirtual(){
    delete estrategia;
	mision=0;
};

const Mision *JugadorVirtual::GetMision(){
	return NULL;
};

void JugadorVirtual::TomarMision(const Mision *_mision){

	mision=_mision;
	estrategia->IniciarPlan(mision);
};

void JugadorVirtual::Agregar(){

    estrategia->ActualizarPlan(TEG.GetSituacionActual());
    estrategia->Agregar();
};

void JugadorVirtual::Atacar(){

    estrategia->ActualizarPlan(TEG.GetSituacionActual());
    estrategia->Atacar();
};

void JugadorVirtual::Reagrupar(){

    estrategia->ActualizarPlan(TEG.GetSituacionActual());
    estrategia->Reagrupar();
};

void JugadorVirtual::DesplazarPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant){

	estrategia->DesplazarFichasPorBatallaGanada(_origen,_destino,MaxCant);
};

#endif
