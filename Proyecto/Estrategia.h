#ifndef ESTRATEGIA_H_INCLUDED
#define ESTRATEGIA_H_INCLUDED

#include "Objetivo.h"

#include "GrafoAciclico.h"

#include "Tacticas.h"

class Estrategia{
    protected:
        const Mision *mision;
        JugadorVirtual *jugador;
        virtual void ListaDeObjetivos(list<Objetivo *> &)=0;
    public:
        Estrategia(){};
        virtual ~Estrategia(){};
        void SetJugador(JugadorVirtual *jug){jugador=jug;};

        virtual void IniciarPlan(const Mision *mis){mision=mis;};
        virtual void ActualizarPlan(Situacion sit)=0;

        virtual void DesplazarFichasPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant)=0;

        //false: si terminaron de hacer los agregamientos, ataques, etc
        void Agregar();
        void Atacar();
        void Reagrupar();
};

void Estrategia::Agregar(){
    list<Objetivo *> objs;
    ListaDeObjetivos(objs);
    jugador->tactica->tacticaAgregar(objs);
};

void Estrategia::Atacar(){
    list<Objetivo *> objs;
    ListaDeObjetivos(objs);
    jugador->tactica->tacticaAtacar(objs);
};
void Estrategia::Reagrupar(){
    list<Objetivo *> objs;
    ListaDeObjetivos(objs);
    jugador->tactica->tacticaReagrupar(objs);
};

#endif // ESTRATEGIA_H_INCLUDED
