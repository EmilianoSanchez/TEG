#ifndef HEURISTICAS_H_INCLUDED
#define HEURISTICAS_H_INCLUDED


//funciones heuristicas:

int CostoParaCumplirMision(const Mision *mision);
float ProbabilidadDeGanar(int fa,int fd);
int CostoDeIntervension(const list<TPais> &camino);


#define MENOS_INFINITO -10.0
float probBasicas[4][3]={{0.0f,0.0f,0.0f},{0.42f,0.25f,0.17f},{0.58f,0.42f,0.35f},{0.66f,0.54f,0.46f}};


//implementaciones:

int CostoDeIntervension(const list<TPais> &camino){
    int longitud=camino.size();
    list<TPais>::const_iterator it;
    switch(longitud){
        case 0:
            return 0;
        case 1:
            return 0;
        case 2:
            return TEG[camino.back()].Fichas()+1;
        default:
            it=camino.begin();
            it++;
            return TEG[*it].Fichas()+3;
    }
};

int CostoParaCumplirMision(const Mision *mision){
    TJugador jug=controladorJuego->Turno();
    int costo=0;
    switch(mision->tipo){
        case CONQUISTA:
            for(TContinente c=ASIA;c<CANTCONTINENTES;c++)
                if((mision->mision).paisesPorCont[c]>Jugadores[jug]->CantPaises(c))
                    costo+=(mision->mision).paisesPorCont[c]-Jugadores[jug]->CantPaises(c);
            break;
        case ELIMINACION:
            for(TContinente c=ASIA;c<CANTCONTINENTES;c++)
                if(Jugadores[(mision->mision).enemigo]->CantPaises(c)>Jugadores[jug]->CantPaises(c))
                    costo+=Jugadores[(mision->mision).enemigo]->CantPaises(c)-Jugadores[jug]->CantPaises(c);
            break;
        case CANTIDAD_PAISES:
            costo+=(mision->mision).cantPaises-Jugadores[jug]->CantPaises();
    }
    return costo;
};

float ProbabilidadDeGanar(int fa,int fd){
    if(fa<=1)
        return 0;
    else
        if(fd<=0)
            return 1;
        else
            if(fa<=4){
                if(fd<=3)
                    return probBasicas[fa-1][fd-1];
                else
                    return probBasicas[fa-1][2]*(2.0f/((float)fd-2));
            }else{
                if(fd<=3)
                    return probBasicas[3][fd-1]+(0.44f-1.0f/((float)fa-2));
                else{
                    float aux=0.35f*((float)fa/(float)fd);
                    if(aux>=1)
                        return 0.99f;
                    else
                        return aux;
                }
            }
};

#endif // HEURISTICAS_H_INCLUDED
