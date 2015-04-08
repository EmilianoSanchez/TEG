#ifndef TACTICANIVEL2_H_INCLUDED
#define TACTICANIVEL2_H_INCLUDED

#include "TacticaNivel1.h"

class Tactica_Nivel2: public Tactica_Nivel1{
    private:
        void Atacar_Recursivamente(TPais p);
        void Atacar_Inteligentemente();

    public:
        Tactica_Nivel2():Tactica_Nivel1(){};
        virtual ~Tactica_Nivel2(){};

        //ataca con inteligencia, considerando la lista de objetivos
		virtual void tacticaAtacar(list<Objetivo *> &);
};

void Tactica_Nivel2::tacticaAtacar(list<Objetivo *> &){
    if(planTactico.estaVacio())
        Atacar_Inteligentemente();
    else{
        list<TPais> origen;
        planTactico.devolverVertices(origen);
        for(list<TPais>::iterator it=origen.begin();it!=origen.end();it++){
            Atacar_Recursivamente(*it);
        }
        Atacar_Inteligentemente();
    }
};


void Tactica_Nivel2::Atacar_Recursivamente(TPais p){

    list<pair<TPais,int> > adys;
    planTactico.devolverAdyacentes(p,adys);

    for(list<pair<TPais,int> >::iterator it=adys.begin();it!=adys.end();it++)
        switch(it->second){
            case OBLIGATORIO_DEFENSIVO:
                jug->desplazar=false;
                while(jug->PosibleBatalla(p,it->first))
                    jug->Batalla(p,it->first);
                break;
            case OBLIGATORIO_OFENSIVO:
                jug->desplazar=true;
                while(jug->PosibleBatalla(p,it->first)){
                    if((jug->Batalla(p,it->first)).ganador==ATACANTE){
                        Atacar_Recursivamente(it->first);
                        break;
                    }
                }
                break;
            case OPCIONAL_DEFENSIVO:
                jug->desplazar=false;
                while(jug->PosibleBatalla(p,it->first) && ProbabilidadDeGanar(TEG[p].Fichas(),TEG[it->first].Fichas())>0.5)
                    jug->Batalla(p,it->first);
                break;
            case OPCIONAL_OFENSIVO:
                jug->desplazar=true;
                while(jug->PosibleBatalla(p,it->first) && ProbabilidadDeGanar(TEG[p].Fichas(),TEG[it->first].Fichas())>0.5){
                    if((jug->Batalla(p,it->first)).ganador==ATACANTE){
                        Atacar_Recursivamente(it->first);
                        break;
                    }
                }
        }
};

void Tactica_Nivel2::Atacar_Inteligentemente(){

    Arreglo paises;
	PaisesJugador(jug->Color(),paises);

	for(int i=0;i<paises.cant;i++)
        if(TEG[paises[i]].Fichas()>1)
            for(int j=0;j<TEG[paises[i]].CantAdy();j++)
                while(jug->PosibleBatalla(paises[i],TEG[paises[i]].Ady(j)) && ProbabilidadDeGanar(TEG[paises[i]].Fichas(),TEG[TEG[paises[i]].Ady(j)].Fichas())>0.5)
                    jug->Batalla(paises[i],TEG[paises[i]].Ady(j));

};

#endif // TACTICANIVEL2_H_INCLUDED
