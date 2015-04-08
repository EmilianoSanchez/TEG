#ifndef OBJETIVO_H_INCLUDED
#define OBJETIVO_H_INCLUDED


//estado:
#define CUMPLIDO 2
#define PSEUDOCUMPLIDO 1
#define NOCUMPLIDO 0
#define PERDIDO -1

//importancia
#define OBLIGATORIO 10
#define OPCIONAL 0

//tipos:
//#define CONQUISTAR 1  //conquistar todos los paises:atacar masivamente
//#define INTERVENIR  2    // conquistar 1 o mas paises: eliminar poseciones enemigas
//#define EXPANDIR 3  //atacar unificando territorios. hay distintos niveles de unificacion:
                    //mantener posiciones unidas
                    //mantener posiciones unidas en cuellos de botella
//#define DEFENDER 4

//otra alternativa es definir INTERVENIR y ELIMINAR como tipos y un nivel de agresion

//comparar:
#define MENOR -1
#define MAYOR 1
#define IGUAL 0


enum TObjetivo{NADA,DEFENDER,EXPANDIR,INTERVENIR,CONQUISTAR};

//definicion de la clase Objetivo:
class Objetivo{
    private:

        TJugador jugador;
        TObjetivo tipo;
        set<TPais> paises;
        int cantPaises;
        int importancia;

        int rondaInicial;
        int fichasGastadas;

    public:

        Objetivo(TObjetivo _tipo,const set<TPais> &_paises,int _cantPaises=0,int _importancia=OBLIGATORIO);
        ~Objetivo();

        //observadores:
        TObjetivo Tipo(){ return tipo;};
        set<TPais> &Paises(){ return paises;};
        int CantPaises();
        int Importancia(){return importancia;};
        int Estado();
        int RondasPasadas(){return controladorJuego->NroRonda()-rondaInicial;};
        int &FichasGastadas(){return fichasGastadas;};
};




//implementaciones:

Objetivo::Objetivo(TObjetivo _tipo,const set<TPais> &_paises,int _cantPaises,int _importancia){
    tipo=_tipo;
    paises=_paises;
    jugador=controladorJuego->Turno();
    rondaInicial=controladorJuego->NroRonda();
    fichasGastadas=0;
    importancia=_importancia;
    cantPaises=_cantPaises;
    switch(tipo){
        case EXPANDIR:
            if(cantPaises==0)
                cantPaises=CANTPAISES;
            break;
        case DEFENDER:
            if(cantPaises==0){
                for(set<TPais>::iterator it=paises.begin();it!=paises.end();it++)
                    if(TEG[(*it)].Ocupante()==jugador)
                        cantPaises++;
            }
    }
};

int Objetivo::CantPaises(){
    int p;
    switch(tipo){
        case DEFENDER:
            p=0;
            for(set<TPais>::iterator it=paises.begin();it!=paises.end();it++)
                if(TEG[*it].Ocupante()==jugador)
                    p++;
            if(cantPaises>p)
                return p;
            else
                return cantPaises;
        default:
            return cantPaises;
    }
};

int Objetivo::Estado(){
    int p,d;
    set<TPais> paisesProp,aux;
    switch(tipo){
        case DEFENDER:
            p=CantPaises();
            d=0;
            for(set<TPais>::iterator it=paises.begin();it!=paises.end();it++)
                if(TEG[*it].Ocupante()==jugador){
                    d++;
                    if(TEG[*it].Fichas()>=2){
                        continue;
                    }else{
                        Arreglo aux;
                        PaisesAdyacentesEnemigos(*it,aux);
                        for(int i=0;i<aux.cant;i++)
                            if(TEG[aux[i]].Fichas()>1){
                                d--;
                                break;
                            }
                    }
                }
            if(p==0)
                return PERDIDO;
            else if(d>=p)
                    return CUMPLIDO;
                else
                    return NOCUMPLIDO;
        case EXPANDIR:
            for(set<TPais>::iterator it=paises.begin();it!=paises.end();it++)
                if(TEG[*it].Ocupante()==jugador)
                    paisesProp.insert(*it);
            if(paisesProp.empty())
                return PERDIDO;
            else{
                PaisesJugador(jugador,aux);
                TableroTEG::IBFS it(paisesProp,aux);
                p=paisesProp.size();
                while(!it.EsFin()){
                    it.Siguiente();
                    p++;
                }
                if(p>=CantPaises())
                    return CUMPLIDO;
                else
                    return NOCUMPLIDO;
            }
        case INTERVENIR:
            for(set<TPais>::iterator it=paises.begin();it!=paises.end();it++)
                if(TEG[*it].Ocupante()==jugador)
                    return CUMPLIDO;
            return NOCUMPLIDO;
        case CONQUISTAR:
            for(set<TPais>::iterator it=paises.begin();it!=paises.end();it++)
                if(TEG[*it].Ocupante()!=jugador)
                    return NOCUMPLIDO;
            return CUMPLIDO;

        default:
            return PERDIDO;
    }
};

#endif // OBJETIVO_H_INCLUDED
