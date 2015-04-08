#ifndef UTILIDADES_TABLERO_H
#define UTILIDADES_TABLERO_H

#include <utility>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
using namespace std;


//constantes del tablero de juego:

#define PRIMERPAIS 0
#define ULTIMOPAIS 49
#define NOPAIS -1
#define CANTPAISES 50
#define CANTCONTINENTES 6

#define PAISES_ASIA 15
#define PAISES_NORTEAMERICA 10
#define PAISES_EUROPA 9
#define PAISES_SUDAMERICA 6
#define PAISES_AFRICA 6
#define PAISES_OCEANIA 4

const int PaisesContinentes[CANTCONTINENTES]={15,10,9,6,6,4};

#define BONUS_ASIA 7
#define BONUS_NORTEAMERICA 5
#define BONUS_EUROPA 5
#define BONUS_SUDAMERICA 3
#define BONUS_AFRICA 3
#define BONUS_OCEANIA 2

const int BonusContinentes[CANTCONTINENTES]={7,5,5,3,3,2};

#define PRIMER_PAIS_ASIA 0
#define PRIMER_PAIS_NORTEAMERICA 15
#define PRIMER_PAIS_EUROPA 25
#define PRIMER_PAIS_SUDAMERICA 34
#define PRIMER_PAIS_AFRICA 40
#define PRIMER_PAIS_OCEANIA 46

const int PrimerPaisContinentes[CANTCONTINENTES+1]={0,15,25,34,40,46,50};

#define ASIA 0
#define NORTEAMERICA 1
#define EUROPA 2
#define SUDAMERICA 3
#define AFRICA 4
#define OCEANIA 5
#define LIBRES 6


//declaraciones de tipos y clases:

typedef short int TPais;
typedef char TContinente;
enum Situacion{RepartoInicial,AgregandoFichas,Atacando,Reagrupando,Ninguna};

/*
    TableroTEG es un contenedor de Pais, clase que representa los casilleros del tablero.
    TableroTEG se modela como un grafo no dirigido plano.
*/
class TableroTEG;
/*
    Las instancias de Pais son los casilleros de TableroTEG.
    Guarda informacion constante como el nombre, el continente al que pertenece, etc
    informacion variable como el ocupante y la cantidad de fichas,
    e informacion de historial.
*/
class Pais;

#endif
