#ifndef TACTICAS_H_INCLUDED
#define TACTICAS_H_INCLUDED

#include "Objetivo.h"

#include "GrafoAciclico.h"

#include "AlgoritmosDeBajoNivel.h"

class Tactica{
    protected:
        JugadorVirtual *jug;
    public:
        Tactica(){};
        virtual ~Tactica(){};
        void SetJugador(JugadorVirtual *j){jug=j;};

        //algoritmos tacticos:
        virtual void tacticaAgregar(list<Objetivo *> &)=0;
		virtual void tacticaAtacar(list<Objetivo *> &)=0;
		virtual void tacticaReagrupar(list<Objetivo *> &)=0;
};


#include "TacticaNivel0.h"
#include "TacticaNivel1.h"
#include "TacticaNivel2.h"
#include "TacticaNivel3.h"

#endif // TACTICAS_H_INCLUDED
