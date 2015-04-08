#ifndef TACTICANIVEL3_H_INCLUDED
#define TACTICANIVEL3_H_INCLUDED

#include "TacticaNivel2.h"

class Tactica_Nivel3: public Tactica_Nivel2{
    private:
        void Reagrupar_Proporcionalmente(Arreglo &paises,float *pesos);
    public:
        Tactica_Nivel3():Tactica_Nivel2(){};
        virtual ~Tactica_Nivel3(){};

        //reagrupa con inteligencia, considerando los objetivos:
		virtual void tacticaReagrupar(list<Objetivo *> &);
};

void Tactica_Nivel3::tacticaReagrupar(list<Objetivo *> & objs){
    Arreglo paises;
    PaisesJugador(jug->Color(),paises);

    float fichasAdyEnemigas[paises.cant];

    FichasAdyacentesEnemigas(jug->Color(),paises,fichasAdyEnemigas);

    Reagrupar_Proporcionalmente(paises,fichasAdyEnemigas);

};


void Tactica_Nivel3::Reagrupar_Proporcionalmente(Arreglo &paises,float *pesos){

    for(int i=0;i<paises.cant;i++)
        if(pesos[i]==0.0){
            float pesoM=0.0;
            TPais p;
            for(int j=0;j<paises.cant;j++)
                if(pesos[j]>pesoM && TEG[paises[i]].EsAdy(paises[j])){
                    pesoM=pesos[j];
                    p=paises[j];
                }
            if(pesoM==0.0){
                for(int j=0;j<paises.cant;j++)
                    if(TEG[paises[i]].EsAdy(paises[j])){
                        p=paises[j];
                        break;
                    }
            }
            jug->DesplazarFichas(paises[i],p,jug->CantidadDesplazar(paises[i],p));
        }
};



#endif // TACTICANIVEL3_H_INCLUDED
