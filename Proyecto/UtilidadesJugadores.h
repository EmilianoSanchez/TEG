#ifndef UTILIDADES_JUGADORES_H
#define UTILIDADES_JUGADORES_H

//constantes para los componentes logicos:

#define MAXJUGADORES 6
#define MINJUGADORES 2

#define ATACANTE 0
#define DEFENSOR 1
#define EMPATE 2

#define AZUL 0
#define ROJO 1
#define AMARILLO 2
#define VERDE 3
#define CYAN 4
#define MAGENTA 5
#define NINGUNO 6

#define HUMANO 0
#define VIRTUAL 1
#define NADIE 2

//declaraciones y definiciones de tipos y clases:

typedef char TJugador;
typedef int TipoJugador;// {NADIE,HUMANO,VIRTUAL};
enum NivelDeInteligencia{NIVEL_0,NIVEL_1,NIVEL_2,NIVEL_3,NINGUN_NIVEL};

struct ResultBatalla{
	int ganador;// ATACANTE, DEFENSOR o EMPATE
	int perdidasAtacante;
	int perdidasDefensor;
};

class Jugador;
class JugadorVirtual;
class JugadorHumano;

#endif
