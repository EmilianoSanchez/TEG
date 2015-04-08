#ifndef COMPONENTES_LOGICOS_H
#define COMPONENTES_LOGICOS_H

#include "ComponentesConcretos.h"

#include "UtilidadesJugadores.h"

TipoJugador Tipos[MAXJUGADORES]={HUMANO,VIRTUAL,NADIE,NADIE,NADIE,NADIE};
NivelDeInteligencia Tacticas[MAXJUGADORES]={NIVEL_0,NIVEL_0,NIVEL_0,NIVEL_0,NIVEL_0,NIVEL_0};
NivelDeInteligencia Estrategias[MAXJUGADORES]={NIVEL_0,NIVEL_0,NIVEL_0,NIVEL_0,NIVEL_0,NIVEL_0};
int CantJugadores=MINJUGADORES;

Jugador *Jugadores[MAXJUGADORES];

#include "Jugador.h"
#include "JugadorVirtual.h"
#include "JugadorHumano.h"
#include "InteligenciaArtificial.h"



#endif
