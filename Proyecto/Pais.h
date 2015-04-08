#ifndef CLASE_PAIS_H
#define CLASE_PAIS_H

#include "UtilidadesTablero.h"
#include "UtilidadesJugadores.h"
#include "TableroTEG.h"

class Pais{
	private:
	//atributos constantes:
		TPais id;
		char *nombre;
		TContinente continente;
		int cantAdy;
		TPais *ady;
		TableroTEG *tab;
	//atributos variables:
		TJugador ocupante;
		int fichas;
		int fichasMovibles;
	//atributos de historial:
        TJugador ocupInicial;
        TJugador ocupAnterior;
		int historial[MAXJUGADORES];

	public:
	//constructor-destructor:
		Pais(TPais _id,char *_nombre,TContinente _continente,int _cantAdy,TPais *_ady,TableroTEG *_tab);
		~Pais();

	//observadores:
		TPais Id();
		const char *Nombre();
		TContinente Continente();
		int CantAdy();
		int CantAdy(TJugador jug);
		TPais Ady(TPais indice);
		bool EsAdy(TPais _id);
		TableroTEG *Tablero();

		TJugador Ocupante();
		int Fichas();
		int FichasMovibles();

        TJugador OcupanteInicial();
        int Historial();
		int Historial(TJugador _jugador);
		TJugador OcupanteAnterior();

	//Modificadores.Retornan true si la accion se realiza correctamente
		bool AgregarFichas(int _fichas,TJugador _ocupante=NINGUNO);
		bool SacarFichas(int _fichas,TJugador _ocupante=NINGUNO);
};




//implementaciones:


Pais::Pais(TPais _id,char *_nombre,TContinente _continente,int _cantAdy,TPais *_ady,TableroTEG *_tab)
{
	tab=_tab;
	id=_id;
	int i;
	for(i=0;_nombre[i]!='\0';i++);
    nombre=new char[i+1];
	for(int j=0;j<=i;j++)
		nombre[j]=_nombre[j];
	continente=_continente;
	cantAdy=_cantAdy;
	ady=new TPais[cantAdy];
	for(int i=0;i<cantAdy;i++)
		ady[i]=_ady[i];
	ocupAnterior=NINGUNO;
	ocupInicial=NINGUNO;
	ocupante=NINGUNO;
	fichas=0;
	fichasMovibles=0;
	for(TJugador i=AZUL;i<MAXJUGADORES;i++)
		historial[i]=0;
};
Pais::~Pais(){
	delete[] nombre;
	nombre=0;
	delete[] ady;
	ady=0;
	tab=0;
};

bool Pais::EsAdy(TPais _id){
	for(int i=0;i<cantAdy;i++)
		if(ady[i]==_id)
			return true;
	return false;
};
TableroTEG *Pais::Tablero(){
	return tab;
};
TPais Pais::Id(){
	return id;
};
const char *Pais::Nombre(){
	return nombre;
};
TContinente Pais::Continente(){
	return continente;
};
int Pais::CantAdy(){
	return cantAdy;
};
int Pais::CantAdy(TJugador jug){
    int cant=0;
    for(int i=0;i<cantAdy;i++)
        if((*tab)[ady[i]].Ocupante()==jug)
            cant++;
    return cant;
};
TPais Pais::Ady(TPais indice){
	return ady[indice];
};
int Pais::Historial(){
    int aux=0;
    for(TJugador j=AZUL;j<MAXJUGADORES;j++)
        aux+=historial[j];
    return aux;
};
int Pais::Historial(TJugador _jugador){
	return historial[_jugador];
};
int Pais::Fichas(){
	return fichas;
};
TJugador Pais::Ocupante(){
	return ocupante;
};
TJugador Pais::OcupanteAnterior(){
	return ocupAnterior;
};
TJugador Pais::OcupanteInicial(){
	return ocupInicial;
};
int Pais::FichasMovibles(){
	switch(tab->GetSituacionActual()){
		case Atacando:
			if(fichas>1)
				if(fichas>3)
					return 3;
				else
					return fichas-1;
			else
				return 0;
		case Reagrupando:
			return fichasMovibles;
		default:
			return 0;
	}
};

bool Pais::AgregarFichas(int _fichas,TJugador _ocupante){
	switch(tab->GetSituacionActual()){
		case RepartoInicial:
			if(_ocupante!=NINGUNO && _fichas>0){
				fichas=_fichas;
				ocupante=_ocupante;
				ocupInicial=_ocupante;
				historial[ocupante]+=_fichas;
				return true;
			}else
				return false;
		case Atacando:
			if(fichas==0 && _fichas<=3 && _fichas>0 && _ocupante!=NINGUNO && _ocupante!=ocupante){
				fichas=_fichas;
				fichasMovibles=fichas-1;
				ocupante=_ocupante;
				historial[ocupante]+=_fichas;
				return true;
			}else
				return false;

		case AgregandoFichas:
			if((_ocupante==NINGUNO || _ocupante==ocupante) && _fichas>=0){
				fichas+=_fichas;
				historial[ocupante]+=_fichas;
				fichasMovibles=fichas-1;
				return true;
			}else
				return false;
		case Reagrupando:
			if((_ocupante==NINGUNO || _ocupante==ocupante) && _fichas>=0){
				fichas+=_fichas;
				historial[ocupante]+=_fichas;
				return true;
			}else
				return false;
		default:
			return false;
	}
};

bool Pais::SacarFichas(int _fichas,TJugador _ocupante){
  if(_fichas>=0 && fichas>=_fichas && (_ocupante==NINGUNO||_ocupante==ocupante))
	switch(tab->GetSituacionActual()){
		case Atacando:
			if(_ocupante==NINGUNO){
				if(_fichas>3)
					return false;
			}else
				if(_fichas>=fichas || _fichas>3)
					return false;
			fichas-=_fichas;
			fichasMovibles-=_fichas;
			if(fichas==0){
				ocupAnterior=ocupante;
				ocupante=NINGUNO;
				fichasMovibles=0;
			}
			return true;
		case Reagrupando:
			if(_fichas<=fichasMovibles){
				fichas-=_fichas;
				fichasMovibles-=_fichas;
				return true;
			}else
				return false;
		default:
			return false;
  }
  else
  	return false;
};


#endif
