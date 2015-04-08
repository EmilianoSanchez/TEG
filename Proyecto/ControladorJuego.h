#ifndef CONTROLADOR_DEL_JUEGO_H
#define CONTROLADOR_DEL_JUEGO_H


#define FICHAS_POR_PAIS_EN_REPARTO_INICIAL 1
#define PAISES_POR_FICHA_DE_INGRESO 2
#define INGRESO_MINIMO 3
#define FICHAS_PRIMER_RONDA 5
#define FICHAS_SEGUNDA_RONDA 3


//estados del juego:
enum Estado {NoJuego,InicioNuevaPartida,RondaInicial1,RondaInicial2,RondaDefensiva,RondaOfensiva,FinPartida};

class ControladorJuego;


#include "ComponentesConcretos.h"
#include "UtilidadesJugadores.h"
#include "Interfaz.h"


//definicion de ControladorJuego:
class ControladorJuego{
	private:
		Estado estadoJuego;
		TJugador turno;
		TJugador primero;
        int ronda;

		void CrearJugadores();
		void RepartirPaises();
		void RepartirMisiones();
	public:
		//constructor-destructor:
		ControladorJuego();
		~ControladorJuego();

		//Observadores:
		Estado EstadoJuego();
		TJugador Turno();
		TJugador Primero();
        int NroRonda();

		//Ejecutor de estado inicial:
		bool IniciarNuevaPartida();

		//Ejecutor de estados de juego:
		void EjecutarTurnoSiguiente();

		//Ejecutor de estado final:
		void TerminarPartida();
};

//objeto global:
ControladorJuego *controladorJuego;

#include "ComponentesLogicos.h"
#include "InterfazImplementacion.h"


//implementacion de ControladorJuego:

ControladorJuego::ControladorJuego(){
	estadoJuego=NoJuego;
	turno=NINGUNO;
	primero=NINGUNO;
	ronda=0;
};

ControladorJuego::~ControladorJuego(){
};

bool ControladorJuego::IniciarNuevaPartida(){
	if(!Interfaz::IniciarInterfaz()){
		Interfaz::Alerta("No se pudo iniciar la interfaz");
		return false;
	}

	TEG.SetSituacionActual(Ninguna);
	estadoJuego=InicioNuevaPartida;

	if(!Interfaz::GUI_EdicionJugadores())
        return false;
	CrearJugadores();

	TEG.SetSituacionActual(RepartoInicial);
	RepartirPaises();
	Interfaz::Dibujar_Elementos();
	RepartirMisiones();

	TEG.SetSituacionActual(AgregandoFichas);
	estadoJuego=RondaInicial1;
	turno=AZUL;
	primero=AZUL;
	ronda=1;
	return true;
};

void ControladorJuego::CrearJugadores(){
    Estrategia *aux;
    Tactica *aux2;
    for(TJugador i=0;i<CantJugadores;i++)
        if(Tipos[i]==VIRTUAL){
            switch(Estrategias[i]){
                case NIVEL_0:
                    aux=new Estrategia_Nivel0();
                    break;
                case NIVEL_1:
                    aux=new Estrategia_Nivel1();
                    break;
                case NIVEL_2:
                    aux=new Estrategia_Nivel2();
            }
            switch(Tacticas[i]){
                case NIVEL_0:
                    aux2=new Tactica_Nivel0();
                    break;
                case NIVEL_1:
                    aux2=new Tactica_Nivel1();
                    break;
                case NIVEL_2:
                    aux2=new Tactica_Nivel2();
                    break;
                case NIVEL_3:
                    aux2=new Tactica_Nivel3();
            }
            Jugadores[i]=new JugadorVirtual(i,aux,aux2);
        }else
            Jugadores[i]=new JugadorHumano(i);
};

void ControladorJuego::RepartirPaises(){
	turno=NINGUNO;
    TPais Paises[CANTPAISES];
	for(TPais i=PRIMERPAIS;i<CANTPAISES;i++)
		Paises[i]=i;
	TPais aux,random;
	for(TPais i=PRIMERPAIS;i<CANTPAISES;i++){
		random=Interfaz::Random(i,CANTPAISES-1);
		aux=Paises[i];
		Paises[i]=Paises[random];
		Paises[random]=aux;
	}
	int it=0;
	for(TJugador i=AZUL;i<CantJugadores;i++)
		for(int j=0;j<CANTPAISES/CantJugadores;j++)
		{
			Jugadores[i]->AgregarFichas(1,Paises[it]);
			it++;
		}
	for(TPais i=0;i<CANTPAISES%CantJugadores;i++)
	{
		Jugadores[i]->AgregarFichas(1,Paises[it]);
		it++;
	}
	Interfaz::DELAY=0.9f;
};

void ControladorJuego::RepartirMisiones(){
	int cantm=CANTMISIONES-(6-CantJugadores);
	bool Obj[cantm];
	for(int i=0;i<cantm;i++)
		Obj[i]=false;

	turno=AZUL;
	for(int i=0;i<CantJugadores;i++){
		int i;
		do{
			i=Interfaz::Random(0,cantm-1);
		}while(Obj[i]==true);
		if(Misiones[i].tipo==ELIMINACION && Misiones[i].mision.enemigo==Jugadores[turno]->Color()){
			i++;
			if(i==cantm)
				i=CANTMISIONES_DE_CONQUISTA;
		}
		Jugadores[turno]->TomarMision(&Misiones[i]);
		if(Tipos[turno]==HUMANO)
			Interfaz::GUI_MostrarMision(turno,&Misiones[i]);
		turno++;
		Obj[i]=true;
	}
};
Estado ControladorJuego::EstadoJuego(){
	return estadoJuego;
};
TJugador ControladorJuego::Turno(){
	return turno;
};
TJugador ControladorJuego::Primero(){
	return primero;
};
int ControladorJuego::NroRonda(){
    return ronda;
};
void ControladorJuego::EjecutarTurnoSiguiente(){
	switch (estadoJuego){
		case RondaInicial1:
			Jugadores[turno]->fichasPorAgregar[LIBRES]=FICHAS_PRIMER_RONDA;
			Jugadores[turno]->Agregar();
			turno++;
			if(turno==CantJugadores){
				estadoJuego=RondaInicial2;
				turno=AZUL;
			}
			break;
		case RondaInicial2:
			Jugadores[turno]->fichasPorAgregar[LIBRES]=FICHAS_SEGUNDA_RONDA;
			Jugadores[turno]->Agregar();
			turno++;
			if(turno==CantJugadores){
				estadoJuego=RondaOfensiva;
				turno=AZUL;
			}
			break;
		case RondaOfensiva:
				TEG.SetSituacionActual(Atacando);

				if(Jugadores[turno]->CantPaises()>0){
				 	Jugadores[turno]->Atacar();
					if(Jugadores[turno]->MisionCumplida()){
						TEG.SetSituacionActual(Ninguna);
						estadoJuego=FinPartida;
						break;
					}
					else{
						TEG.SetSituacionActual(Reagrupando);
						if(Jugadores[turno]->CantPaises()>0)
							Jugadores[turno]->Reagrupar();
						}
				}

				turno++;
				if(turno==CantJugadores)
					turno=AZUL;
				if(turno==primero){
					turno++;
					if(turno==CantJugadores)
						turno=AZUL;
					primero++;
					if(primero==CantJugadores)
						primero=AZUL;
					estadoJuego=RondaDefensiva;
				}
				ronda++;
				break;
		case RondaDefensiva:
			TEG.SetSituacionActual(AgregandoFichas);
			if(Jugadores[turno]->CantPaises()>0){
				for(TContinente i=ASIA;i!=NINGUNO;i++)
					if(Jugadores[turno]->CantPaises(i)==PaisesContinentes[i])
						Jugadores[turno]->fichasPorAgregar[i]=BonusContinentes[i];
				if(Jugadores[turno]->CantPaises()/PAISES_POR_FICHA_DE_INGRESO<INGRESO_MINIMO)
					Jugadores[turno]->fichasPorAgregar[LIBRES]=INGRESO_MINIMO;
				else
					Jugadores[turno]->fichasPorAgregar[LIBRES]=(Jugadores[turno]->CantPaises()/PAISES_POR_FICHA_DE_INGRESO);
				Jugadores[turno]->Agregar();
			}
			turno++;
			if(turno==CantJugadores)
				turno=AZUL;
			if(turno==primero)
				estadoJuego=RondaOfensiva;
			break;
		default:;
	}
};
void ControladorJuego::TerminarPartida(){
	if(turno!=NINGUNO)
		Interfaz::Modo_FinPartida(turno,Jugadores[turno]->mision);

	Interfaz::TerminarInterfaz();

	for(TJugador i=AZUL;i<CantJugadores;i++)
		if(Jugadores[i])
		{
			delete Jugadores[i];
			Jugadores[i]=0;
		}
};


#endif
