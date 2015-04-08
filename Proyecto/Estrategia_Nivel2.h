#ifndef ESTRATEGIA_NIVEL2_H_INCLUDED
#define ESTRATEGIA_NIVEL2_H_INCLUDED

#include "Estrategia.h"



class Estrategia_Nivel2: public Estrategia_Nivel1{
    protected:
        virtual void PlanCantidadPaises();
        virtual void ActualizarPlanCantidadPaises();
        const Mision *misionAlternativa;
    public:
        Estrategia_Nivel2():Estrategia_Nivel1(){};
        virtual ~Estrategia_Nivel2(){};

        virtual void IniciarPlan(const Mision *mis);
        virtual void ActualizarPlan( Situacion sit);

};




//implementaciones:

void Estrategia_Nivel2::PlanCantidadPaises(){
    plan.limpiar();
    float aux=0.0f;
    TContinente cont;
    set<TPais> conj;
    for(TContinente c=ASIA;c<CANTCONTINENTES;c++)
        if(jugador->CantPaises(c)==PaisesContinentes[c]){
            PaisesContinente(c,conj);
            plan.agregarVertice(new Objetivo(DEFENDER,conj));
        }else{
            if((float)jugador->CantPaises(c)/(float)PaisesContinentes[c]>aux){
                aux=(float)jugador->CantPaises(c)/(float)PaisesContinentes[c];
                cont=c;
            }
        }

    PaisesContinente(cont,conj);

    Objetivo *intervenir,*expandir,*defender;
    intervenir=new Objetivo(INTERVENIR,conj);
    expandir=new Objetivo(EXPANDIR,conj);
    defender=new Objetivo(DEFENDER,conj);

    plan.agregarVertice(defender);
    plan.agregarVertice(intervenir);
    plan.agregarVertice(expandir);
    plan.agregarArco(defender,expandir,CUMPLIDO);
    plan.agregarArco(defender,expandir,NOCUMPLIDO);
    plan.agregarArco(intervenir,expandir,CUMPLIDO);
    plan.agregarArco(defender,intervenir,PERDIDO);

    list<Arreglo> grupos;
    Arreglo paises;
    PaisesJugador(jugador->Color(),paises);
    GruposLimitrofes(paises,grupos);

    list<Arreglo>::iterator laux;
    int max=0;
    for(list<Arreglo>::iterator it=grupos.begin();it!=grupos.end();it++)
        if((*it).cant>max){
            laux=it;
            max=(*it).cant;
        }
    Arreglo_a_conjunto((*laux),conj);
    plan.agregarVertice(new Objetivo(EXPANDIR,conj));

};

void Estrategia_Nivel2::ActualizarPlanCantidadPaises(){
    PlanCantidadPaises();
};

void Estrategia_Nivel2::IniciarPlan(const Mision *mis){
    mision=mis;
    misionAlternativa=&MisionGlobal;
    if( CostoParaCumplirMision(misionAlternativa)<CostoParaCumplirMision(mision) ){
        const Mision *aux=mision;
        mision=misionAlternativa;
        misionAlternativa=aux;
    }
    if(mision->tipo==CANTIDAD_PAISES)
        PlanCantidadPaises();
    else
        Estrategia_Nivel1::IniciarPlan(mision);
};

void Estrategia_Nivel2::ActualizarPlan(Situacion sit){
    if(sit==AgregandoFichas){
        if( CostoParaCumplirMision(misionAlternativa)<CostoParaCumplirMision(mision) ){
            const Mision *aux=mision;
            mision=misionAlternativa;
            misionAlternativa=aux;
            if(mision->tipo==CANTIDAD_PAISES)
                PlanCantidadPaises();
            else
                Estrategia_Nivel1::IniciarPlan(mision);
        }else{
            if(mision->tipo==CANTIDAD_PAISES)
                ActualizarPlanCantidadPaises();
            else
                Estrategia_Nivel1::ActualizarPlan(sit);
        }
    }
};


#endif // ESTRATEGIA_NIVEL2_H_INCLUDED
