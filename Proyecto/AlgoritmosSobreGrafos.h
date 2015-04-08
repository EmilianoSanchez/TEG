#ifndef ALGORITMOSSOBREGRAFOS_H_INCLUDED
#define ALGORITMOSSOBREGRAFOS_H_INCLUDED




//algoritmos para paises limitrofes:

bool Limitrofes(const set<TPais> &s);
void GruposLimitrofes(const Arreglo &paises,list<Arreglo> &grupos);

//algoritmos para calcular caminos mas cortos:

void CaminoMasCorto(const Arreglo &origen,TPais destino,list<TPais> &camino);
int CaminoMasCorto(const Arreglo &origen,TPais destino);
void CaminoMasCorto(const Arreglo &origen,const Arreglo &destino,list<TPais> &camino);
int CaminoMasCorto(const Arreglo &origen,const Arreglo &destino);

//auxiliares:

void FichasAdyacentesEnemigas(TJugador jug,Arreglo &paises,float *fichasAdyEnemigas);//listo y correcto



//implementaciones:

void GruposLimitrofes(const Arreglo &paises,list<Arreglo> &grupos){
    Arreglo aux=paises;
    grupos.clear();
    if(paises.cant!=0){
        set<TPais> p;
        Arreglo_a_conjunto(aux,p);

        while(aux.cant>0){
            TableroTEG::IBFS it(aux[0],p);
            Arreglo aux2;
            aux.Borrar(it.posicion);
            aux2.Agregar(it.posicion);
            while(!it.EsFin()){
                it.Siguiente();
                aux.Borrar(it.posicion);
                aux2.Agregar(it.posicion);
            }
            grupos.push_back(aux2);
        }
    }
};

bool Limitrofes(const set<TPais> &s){
    TableroTEG::IBFS it(*(s.begin()),s);
    int cant=0;
    while(!it.EsFin()){
        cant++;
        it.Siguiente();
    }
    if(cant==s.size()-1)
        return true;
    else
        return false;
};

void FichasAdyacentesEnemigas(TJugador jug,Arreglo &paises,float *fichasAdyEnemigas){
    for(int i=0;i<paises.cant;i++){
        fichasAdyEnemigas[i]=0.0;
        for(int j=0;j<TEG[paises[i]].CantAdy();j++)
            if(TEG[TEG[paises[i]].Ady(j)].Ocupante()!=jug)
                fichasAdyEnemigas[i]+=(float)TEG[TEG[paises[i]].Ady(j)].Fichas();
    }
};

int CaminoMasCorto(const Arreglo &origen,TPais destino){
    int min=CANTPAISES;
    for(int i=0;i<origen.cant;i++){
        if(TEG.CaminoMasCorto(origen[i],destino)<min)
            min=TEG.CaminoMasCorto(origen[i],destino);
    }
    return min;
};

void CaminoMasCorto(const Arreglo &origen,TPais destino,list<TPais> &camino){
    int menor=CANTPAISES,iaux;
    for(int i=0;i<origen.cant;i++){
        if(TEG.CaminoMasCorto(origen[i],destino)<menor){
            menor=TEG.CaminoMasCorto(origen[i],destino);
            iaux=i;
        }
    }
    TEG.CaminoMasCorto(origen[iaux],destino,camino);
    camino.push_front(origen[iaux]);
};

void CaminoMasCorto(const Arreglo &origen,const Arreglo &destino,list<TPais> &camino){
    int menor=CANTPAISES,iaux,jaux;
    for(int i=0;i<origen.cant;i++){
        for(int j=0;j<destino.cant;j++){
            if(TEG.CaminoMasCorto(origen[i],destino[j])<menor){
                menor=TEG.CaminoMasCorto(origen[i],destino[j]);
                iaux=i;
                jaux=j;
            }
            if(menor==0)
                break;
        }
        if(menor==0)
            break;
    }
    TEG.CaminoMasCorto(origen[iaux],destino[jaux],camino);
    camino.push_front(origen[iaux]);
};


#endif // ALGORITMOSSOBREGRAFOS_H_INCLUDED
