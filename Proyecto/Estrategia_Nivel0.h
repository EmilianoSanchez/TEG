#ifndef ESTRATEGIA_NIVEL0_H_INCLUDED
#define ESTRATEGIA_NIVEL0_H_INCLUDED

#include "Estrategia.h"

class Estrategia_Nivel0: public Estrategia{
    protected:
        virtual void ListaDeObjetivos(list<Objetivo *> &);

    public:
        Estrategia_Nivel0():Estrategia(){};
        ~Estrategia_Nivel0(){};

        void ActualizarPlan( Situacion sit){};
        void Agregar();
        void DesplazarFichasPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant);
};




//implementaciones:

void Estrategia_Nivel0::ListaDeObjetivos(list<Objetivo*> &objs){
};

void Estrategia_Nivel0::DesplazarFichasPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant){
    jugador->DesplazarFichas(_origen,_destino,1);
};


#endif // ESTRATEGIA_NIVEL0_H_INCLUDED
