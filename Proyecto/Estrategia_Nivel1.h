#ifndef ESTRATEGIA_NIVEL1_H_INCLUDED
#define ESTRATEGIA_NIVEL1_H_INCLUDED

#include "Estrategia.h"

class Estrategia_Nivel1: public Estrategia{
    protected:
        GrafoAciclico<Objetivo *,int> plan;

        virtual void PlanConquistar();
        virtual void PlanEliminar();
        virtual void ActualizarPlanConquistar();
        virtual void ActualizarPlanEliminar();

        virtual void ListaDeObjetivos(list<Objetivo *> &);
    public:
        Estrategia_Nivel1():Estrategia(){};
        virtual ~Estrategia_Nivel1(){};

        virtual void IniciarPlan(const Mision *mis);
        virtual void ActualizarPlan( Situacion sit);

        void DesplazarFichasPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant);
};




//implementaciones:

void Estrategia_Nivel1::PlanConquistar(){
    plan.limpiar();
    set<TPais> conjunto;
    for(TContinente c=ASIA;c<=OCEANIA;c++){
        if((mision->mision).paisesPorCont[c]!=0){
            Objetivo *intervenir,*completar;
            PaisesContinente(c,conjunto);
            intervenir=new Objetivo(INTERVENIR,conjunto);

            if((mision->mision).paisesPorCont[c]==PaisesContinentes[c])
                completar=new Objetivo(CONQUISTAR,conjunto);
            else
                completar=new Objetivo(EXPANDIR,conjunto,(mision->mision).paisesPorCont[c]);

            plan.agregarVertice(intervenir);
            plan.agregarVertice(completar);
            plan.agregarArco(intervenir,completar,CUMPLIDO);

            if(jugador->CantPaises(c)>0){
                Objetivo *defender=new Objetivo(DEFENDER,conjunto,(mision->mision).paisesPorCont[c]);
                plan.agregarVertice(defender);
                plan.agregarArco(defender,intervenir,PERDIDO);
                plan.agregarArco(defender,completar,CUMPLIDO);
                if((mision->mision).paisesPorCont[c]==PaisesContinentes[c])
                    plan.agregarArco(defender,completar,NOCUMPLIDO);
            }
        }
    }
};

void Estrategia_Nivel1::PlanEliminar(){
    plan.limpiar();
    Arreglo paisesEnem,paisesProp;
    PaisesJugador((mision->mision).enemigo,paisesEnem);
    PaisesJugador(jugador->Color(),paisesProp);

    int *distancias=new int[paisesEnem.cant];
    for(int i=0;i<paisesEnem.cant;i++)
        distancias[i]=CaminoMasCorto(paisesProp,paisesEnem[i]);

    list<pair<int,Objetivo*> > paises,paisesAux;
    set<TPais> aux;
    int d;
    for(;;){
        d=CANTPAISES;
        paises.clear();
        for(int i=0;i<paisesEnem.cant;i++)
            if(distancias[i]<d){
                paises.clear();
                d=distancias[i];
                i=-1;
            }else{
                if(distancias[i]==d){
                    aux.insert(paisesEnem[i]);
                    paises.push_back(make_pair(i,new Objetivo(INTERVENIR,aux)));
                    aux.clear();
                }
            }
        if(d==CANTPAISES)
            break;
        else{
            if(paisesAux.empty()){
                for(list<pair<int,Objetivo*> >::iterator it=paises.begin();it!=paises.end();it++){
                    distancias[it->first]=CANTPAISES+1;
                    plan.agregarVertice(it->second);
                }
            }else{
                for(list<pair<int,Objetivo*> >::iterator it=paises.begin();it!=paises.end();it++){
                    distancias[it->first]=CANTPAISES+1;
                    plan.agregarVertice(it->second);
                    for(list<pair<int,Objetivo*> >::iterator it2=paisesAux.begin();it2!=paisesAux.end();it2++){
                        plan.agregarArco(it2->second,it->second,NOCUMPLIDO);
                        plan.agregarArco(it2->second,it->second,CUMPLIDO);
                    }
                }
            }
            paisesAux=paises;
        }
    }

};

void Estrategia_Nivel1::ActualizarPlanConquistar(){
    PlanConquistar();
};

void Estrategia_Nivel1::ActualizarPlanEliminar(){
    PlanEliminar();
};

void Estrategia_Nivel1::IniciarPlan(const Mision *mis){
    Estrategia::IniciarPlan(mis);
    switch(mision->tipo){
        case CONQUISTA:
            PlanConquistar();
            break;
        case ELIMINACION:
            PlanEliminar();
    }
};

void Estrategia_Nivel1::ActualizarPlan(Situacion sit){
    if(sit==AgregandoFichas)
    switch(mision->tipo){
        case CONQUISTA:
            ActualizarPlanConquistar();
            break;
        case ELIMINACION:
            ActualizarPlanEliminar();
    }
};

void Estrategia_Nivel1::ListaDeObjetivos(list<Objetivo*> &objs){
    objs.clear();
    list<pair<Objetivo*,int> > aux;
    plan.devolverVertices(objs);

    list<Objetivo *>::iterator it=objs.begin();
    while(it!=objs.end()){

        int estado=(*it)->Estado();
        plan.devolverAdyacentes(*it,aux);

        for(list<pair<Objetivo *,int> >::iterator it2=aux.begin();it2!=aux.end();it2++){
            if(it2->second==estado)
                objs.push_back(it2->first);
        }
        if(estado==CUMPLIDO || estado==PERDIDO)
            it=objs.erase(it);
        else
            it++;
    }

   /* Interfaz::hge->System_Log("lista de objetivos: %i",jugador->Color());
    for(list<Objetivo*>::iterator it=objs.begin();it!=objs.end();it++)
        switch((*it)->Tipo()){
            case DEFENDER:
                Interfaz::hge->System_Log("defender %i",(*it)->Paises().size());
                break;
            case INTERVENIR:
                Interfaz::hge->System_Log("intervenir %i",(*(*it)->Paises().begin()));
                break;
            case EXPANDIR:
                Interfaz::hge->System_Log("expandir %i",(*it)->Paises().size());
                break;
            case CONQUISTAR:
                Interfaz::hge->System_Log("conquistar %i",(*it)->Paises().size());
        }*/

};


void Estrategia_Nivel1::DesplazarFichasPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant){
    if(jugador->desplazar)
        jugador->DesplazarFichas(_origen,_destino,MaxCant);
    else
        jugador->DesplazarFichas(_origen,_destino,1);
};


#endif // ESTRATEGIA_NIVEL1_H_INCLUDED
