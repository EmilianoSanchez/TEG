#ifndef TACTICANIVEL1_H_INCLUDED
#define TACTICANIVEL1_H_INCLUDED

#include "TacticaNivel0.h"

//ESTADOS DE ATAQUE:
#define OBLIGATORIO_DEFENSIVO 3
#define OBLIGATORIO_OFENSIVO 2
#define OPCIONAL_DEFENSIVO 1
#define OPCIONAL_OFENSIVO 0

class Tactica_Nivel1: public Tactica_Nivel0{
    private:
        void Agregar_Inteligentemente();
        void Agregar_Proporcionalmente(Arreglo &paises,float *pesos);

        void Agregar_Para_Defender(const set<TPais> & _paises,int cantADefender);
        void Agregar_A_Plan_Expandir(const set<TPais> & _paises,int cantAExpandir);
        void Agregar_A_Plan_Intervenir(const set<TPais> & _paises);
        void Agregar_A_Plan_Conquistar(const set<TPais> & _paises);

        void Expansion(const set<TPais> & _paises,set<TPais> & propios,int cantAExpandir,bool obligatorio);//provar

    protected:
        GrafoAciclico<TPais,int> planTactico;
    public:
        Tactica_Nivel1():Tactica_Nivel0(){};
        virtual ~Tactica_Nivel1(){};

        //agrega con inteligencia, considerando los objetivos:
        virtual void tacticaAgregar(list<Objetivo *> &);
};

void Tactica_Nivel1::tacticaAgregar(list<Objetivo *> &objs){
    planTactico.limpiar();
    if(!objs.empty()){
        list<Objetivo *>::iterator it=objs.begin();
        while(jug->FichasPorAgregar() && it!=objs.end()){
            switch((*it)->Tipo()){
                case DEFENDER:
                    Agregar_Para_Defender((*it)->Paises(),(*it)->CantPaises());
                    break;
                case EXPANDIR:
                    Agregar_A_Plan_Expandir((*it)->Paises(),(*it)->CantPaises());
                    break;
                case INTERVENIR:
                    Agregar_A_Plan_Intervenir((*it)->Paises());
                    break;
                case CONQUISTAR:
                    Agregar_A_Plan_Conquistar((*it)->Paises());
                    break;
            }
            it++;
        }
    }
    if(jug->FichasPorAgregar()){
        Agregar_Inteligentemente();
    }
};

void Tactica_Nivel1::Agregar_Para_Defender(const set<TPais> & _paises,int cantADefender){
    int cant=0;
    Arreglo padys;
    set<TPais>::const_iterator it=_paises.begin();
    while(it!=_paises.end() && cant<cantADefender){
        if(TEG[*it].Ocupante()==jug->Color()){

            if(TEG[*it].Fichas()==1){
                PaisesAdyacentesEnemigos(*it,padys);
                for(int j=0;j<padys.cant;j++){
                    if(TEG[padys[j]].Fichas()>=2){
                        if(TEG[padys[j]].Fichas()>=4)
                            if(jug->CantidadAgregar(*it)>=2){
                                jug->AgregarFichas(2,*it);
                                cant++;
                            }else{
                                jug->AgregarFichas(jug->CantidadAgregar(*it),*it);
                            }
                        else
                            if(jug->CantidadAgregar(*it)>=1){
                                jug->AgregarFichas(1,*it);
                                cant++;
                            }
                        break;
                    }
                }
            }else
                cant++;
        }
        it++;
    }
};
void Tactica_Nivel1::Agregar_A_Plan_Intervenir(const set<TPais> & _paises){

    Arreglo paises;
    Conjunto_a_arreglo(_paises,paises);

    list<TPais> camino;
    Arreglo aux;
    PaisesJugador(jug->Color(),aux);
    CaminoMasCorto(aux,paises,camino);
    int costo=CostoDeIntervension(camino);

    TPais primero=camino.front();
    planTactico.agregarVertice(primero);
    list<TPais>::iterator it=camino.begin();

    for(it++;it!=camino.end();it++){
        planTactico.agregarVertice(*it);
        it++;
        if(it==camino.end()){
            it--;
            planTactico.agregarArco(primero,*it,OBLIGATORIO_DEFENSIVO);
        }else{
            it--;
            planTactico.agregarArco(primero,*it,OBLIGATORIO_OFENSIVO);
        }
        primero=*it;
    }
    if(jug->CantidadAgregar(camino.front())>=costo)
        jug->AgregarFichas(costo,camino.front());
    else
        jug->AgregarFichas(jug->CantidadAgregar(camino.front()),camino.front());

};

void Tactica_Nivel1::Agregar_A_Plan_Expandir(const set<TPais> & _paises,int cantAExpandir){
    if( Limitrofes(_paises) ){
        set<TPais> propios,enemigos;
        for(set<TPais>::iterator it=_paises.begin();it!=_paises.end();it++)
            if(TEG[*it].Ocupante()==jug->Color())
                propios.insert(*it);
            else
                enemigos.insert(*it);

        if(enemigos.empty()){//_paises es propio
            set<TPais> zonaDeExpansion=propios;
            bool noExpandido=true;
            while(noExpandido){
                for(set<TPais>::iterator it=propios.begin();it!=propios.end();it++){
                    for(int j=0;j<TEG[*it].CantAdy();j++){
                        if(TEG[TEG[*it].Ady(j)].Ocupante()==jug->Color())
                            propios.insert(TEG[*it].Ady(j));
                        else{
                            if(zonaDeExpansion.find(TEG[*it].Ady(j))==zonaDeExpansion.end()){
                                zonaDeExpansion.insert(TEG[*it].Ady(j));
                                noExpandido=false;
                            }
                        }
                    }
                }
            }

            Expansion(zonaDeExpansion,propios,cantAExpandir,false);

        }else if(!propios.empty()){//_paises es mixto
            Expansion(_paises,propios,cantAExpandir,false);
        }
    }
};

//precondicion propios esta incluido en _paises:
void Tactica_Nivel1::Expansion(const set<TPais> & _paises,set<TPais> &propios,int cantAExpandir,bool obligatorio){
            int cant=propios.size();

            Arreglo adys;
            int adyacenciaEnem[CANTPAISES];//indica la cantidad de adyacentes de los paises enemigo con los propios
            bool matrizDeAdyacencia[CANTPAISES][CANTPAISES];//indica pares de adyacencia
            int adyacenciaProp[CANTPAISES];//indica la cantidad de adyacentes de los paises propios con los enemigos
            int fichasAAgregar[CANTPAISES];

            //inicializa los arreglos a 0
            for(int i=0;i<CANTPAISES;i++){
                adyacenciaEnem[i]=adyacenciaProp[i]=fichasAAgregar[i]=0;
                for(int j=0;j<CANTPAISES;j++)
                    matrizDeAdyacencia[i][j]=false;
            }
            //carga los arreglos con los datos correspondientes
            for(set<TPais>::iterator it=propios.begin();it!=propios.end();it++){
                PaisesAdyacentesEnemigos(*it,adys);
                for(int j=0;j<adys.cant;j++){
                    if(_paises.find(adys[j])!=_paises.end()){
                        adyacenciaEnem[adys[j]]++;
                        adyacenciaProp[*it]++;
                        matrizDeAdyacencia[*it][adys[j]]=true;
                    }
                }
            }

            bool hayMas=true;
            int mayorE,mayorP;
            TPais indiceME,indiceMP;
            while(hayMas && cant<cantAExpandir){
                mayorE=0;
                for(TPais j=0;j<CANTPAISES;j++)//busca el mayor adyacente enemigo
                    if(adyacenciaEnem[j]>mayorE){
                        mayorE=adyacenciaEnem[j];
                        indiceME=j;
                    }
                if(mayorE>0){
                    mayorP=0;
                    for(TPais i=0;i<CANTPAISES;i++){//busca el mayor adyacente propio
                        if(matrizDeAdyacencia[i][indiceME] && adyacenciaProp[i]>mayorP){
                            mayorP=adyacenciaProp[i];
                            indiceMP=i;
                        }
                    }

                    //agregar el ataque de indiceMP a indiceME al planTactico
                    planTactico.agregarVertice(indiceMP);
                    planTactico.agregarVertice(indiceME);
                    fichasAAgregar[indiceMP]++;
                    if(TEG[indiceME].Fichas()==1 || obligatorio){
                        planTactico.agregarArco(indiceMP,indiceME,OBLIGATORIO_DEFENSIVO);
                    }else{
                        planTactico.agregarArco(indiceMP,indiceME,OPCIONAL_DEFENSIVO);
                    }

                    //actualiza las matrices de adyacencia
                    cant++;
                    adyacenciaEnem[indiceME]=0;
                    PaisesAdyacentesEnemigos(indiceME,adys);
                    for(int k=0;k<adys.cant;k++)
                        if(adyacenciaEnem[adys[k]])
                            adyacenciaEnem[adys[k]]++;

                }else
                    hayMas=false;
            }

            //agregar las fichas correspondientes
            for(TPais i=0;i<CANTPAISES;i++)
                if(fichasAAgregar[i])
                    if(jug->CantidadAgregar(i)>=fichasAAgregar[i])
                        jug->AgregarFichas(fichasAAgregar[i],i);
                    else
                        jug->AgregarFichas(jug->CantidadAgregar(i),i);

};


void Tactica_Nivel1::Agregar_A_Plan_Conquistar(const set<TPais> &_paises){
    if( Limitrofes(_paises) ){
        set<TPais> propios;
        for(set<TPais>::iterator it=_paises.begin();it!=_paises.end();it++){
            if(TEG[*it].Ocupante()==jug->Color())
                propios.insert(*it);
        }
        Expansion(_paises,propios,_paises.size(),true);
    }
};

void Tactica_Nivel1::Agregar_Inteligentemente(){

    Arreglo paises;
    PaisesJugador(jug->Color(),paises);
    float fichasAdyEnemigas[paises.cant];
    FichasAdyacentesEnemigas(jug->Color(),paises,fichasAdyEnemigas);
    Agregar_Proporcionalmente(paises,fichasAdyEnemigas);

};
void Tactica_Nivel1::Agregar_Proporcionalmente(Arreglo &paises,float *pesos){
    float pesoTotal=0;
    for(int i=0;i<paises.cant;i++)
        pesoTotal+=pesos[i];
    float proporcion=pesoTotal/(float)jug->FichasPorAgregar();
    if(proporcion==0.0f)
        proporcion=1.0f;
    int max,indice;
    while(jug->FichasPorAgregar()){
        max=MENOS_INFINITO;
        for(int i=0;i<paises.cant;i++)
            if(max<pesos[i]){
                max=pesos[i];
                indice=i;
            }
        if(jug->CantidadAgregar(paises[indice]))
            jug->AgregarFichas(1,paises[indice]);
        pesos[indice]-=proporcion;
    }
};



#endif // TACTICANIVEL1_H_INCLUDED
