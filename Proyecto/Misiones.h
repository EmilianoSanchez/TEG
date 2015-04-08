#ifndef MISIONES_H
#define MISIONES_H

#include "UtilidadesTablero.h"
#include "UtilidadesJugadores.h"

//macros y constantes globales:

#define CANTMISIONES 15
#define CANTMISIONES_DE_CONQUISTA 9
#define CANTPAISES_MISGLOBAL 30

//declaraciones:

enum TipoMision {CONQUISTA,ELIMINACION,CANTIDAD_PAISES};
class Mision;

//definicion de la clase Mision:

class Mision{
    public:
        int id;
        TipoMision tipo;
        union UObjetivo{
            int paisesPorCont[CANTCONTINENTES];
            TJugador enemigo;
            int cantPaises;
        } mision;
        const char *str;
};

//objetos globales:

const Mision Misiones[CANTMISIONES]={{0,CONQUISTA,{PAISES_ASIA,0,0,2,0,0},"Conquistar Asia y 2 paises de Sudamerica."},
									{1,CONQUISTA,{3,3,3,2,2,2},"Conquistar 3 paises de Asia, 3 de Norteamerica, 3 de Europa, 2 de Sudamerica, 2 de Africa y 2 de Oceania."},
									{2,CONQUISTA,{0,0,7,PAISES_SUDAMERICA,3,0},"Conquistar Sudamerica, 3 paises de Africa y 7 de Europa."},
									{3,CONQUISTA,{4,0,0,PAISES_SUDAMERICA,PAISES_AFRICA,0},"Conquistar Sudamerica, Africa y 4 paises de Asia."},
									{4,CONQUISTA,{0,5,4,0,PAISES_AFRICA,0},"Conquistar Africa, 4 paises de Europa y 5 de Norteamerica."},
									{5,CONQUISTA,{4,0,PAISES_EUROPA,2,0,0},"Conquistar Europa, 2 paises de Sudamerica y 4 de Asia."},
									{6,CONQUISTA,{0,5,0,0,PAISES_AFRICA,PAISES_OCEANIA},"Conquistar Africa, Oceania y 5 paises de Norteamerica."},
									{7,CONQUISTA,{4,PAISES_NORTEAMERICA,0,0,0,2},"Conquistar Norteamerica, 4 paises de Asia y 2 de Oceania."},
									{8,CONQUISTA,{0,PAISES_NORTEAMERICA,2,0,0,PAISES_OCEANIA},"Conquistar Oceania, Norteamerica y 2 paises de Europa."},
									{9,ELIMINACION,{AZUL},"Eliminar al jugador azul"},
									{10,ELIMINACION,{ROJO},"Eliminar al jugador rojo"},
									{11,ELIMINACION,{AMARILLO},"Eliminar al jugador amarillo"},
									{12,ELIMINACION,{VERDE},"Eliminar al jugador verde"},
									{13,ELIMINACION,{CYAN},"Eliminar al jugador cyan"},
									{14,ELIMINACION,{MAGENTA},"Eliminar al jugador magenta"}};

const Mision MisionGlobal={15,CANTIDAD_PAISES,{CANTPAISES_MISGLOBAL},"Mision global: Conquistar 30 paises."};

#endif

