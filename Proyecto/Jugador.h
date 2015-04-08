#ifndef CLASE_JUGADOR_H
#define CLASE_JUGADOR_H

#include "UtilidadesJugadores.h"
#include "UtilidadesTablero.h"
#include "Misiones.h"
#include "Interfaz.h"

//Definicion de la clase Jugador:
class Jugador{
	friend class ControladorJuego;
	private:
		TJugador color;
		int cantFichas;
		int cantPaises;
		int cantPaisesPorCont[CANTCONTINENTES];

		int fichasPorAgregar[CANTCONTINENTES+1];

	//accion elemental privada:
		/*Llamado por:	Batalla(TPais,TPais)
		  Poscondicion: SacarFichas(x,y)==true si las x fichas fueron sacadas de y
		*/
		bool SacarFichas(int _fichas,TPais _pais);

	protected:
		const Mision *mision;

	public:
	//constructor-destructor:
		Jugador(TJugador _color);
		virtual ~Jugador();

	//observadores. Utiles para la IA y la interfaz:
		TJugador Color();
		int CantFichas();
		int CantPaises();
		int CantPaises(TContinente _continente);

    //observadores que complementan a las acciones elementales. Utiles para la IA:
        int FichasPorAgregar(TContinente _continente);
        int FichasPorAgregar();
        int CantidadAgregar(TPais _pais);
		int CantidadDesplazar(TPais _origen,TPais _destino);
		bool PosibleBatalla(TPais _atacante,TPais _defensor);
		bool MisionCumplida();//utilizada por ControladorJuego para ver si algun jugador cumple su objetivo

	//acciones elementales: funciones concretas que modifican los atributos privados y son llamadas por las acciones generales para facilitar su implementacion:

		/*Llamado por: 	Agregar() y por controladorJuego en el reparto inicial de paises.
		  Poscondicion: AgregarFichas(x,y)==true si las x fichas fueron agregadas en y
		*/
		bool AgregarFichas(int _fichas,TPais _pais);

		/*Llamado por: Reagrupar()
		  Precondicion: _cantFichas<=CantidadDesplazar(_origen,_destino)
		  Poscondicion: DesplazarFichas(x,y,z)==true si las fichas fueron desplazadas
		*/
		bool DesplazarFichas(TPais _origen,TPais _destino,int _cantFichas);

		/*Llamado por: Atacar()
		  Precondicion: PosibleBatalla(_atacante,_defensor)==true
		*/
		ResultBatalla Batalla(TPais _atacante,TPais _defensor);

	//acciones generales: llamadas por controladorJuego segun el estado del juego. Representan las acciones mas abstractas de los jugadores, por eso son virtuales:
		//virtuales:
		virtual void TomarMision(const Mision *_mision);

		//virtuales puras, acciones correspondientes a los turnos de los jugadores:
		virtual const Mision *GetMision()=0;
		virtual void Agregar() =0;
		virtual void Atacar()=0;
		virtual void Reagrupar()=0;
		//llamado por la funcion miembro Batalla dependiendo del resultado de la misma:
		virtual void DesplazarPorBatallaGanada(TPais _origen,TPais _destino,int MaxCant)=0;
};



//implementaciones:

Jugador::Jugador(TJugador _color){
	color=_color;
	mision=0;
	cantFichas=0;
	cantPaises=0;
	for(TContinente i=ASIA;i<=OCEANIA;i++){
		cantPaisesPorCont[i]=0;
		fichasPorAgregar[i]=0;
	}
	fichasPorAgregar[LIBRES]=0;
};
Jugador::~Jugador(){
	mision=0;
};
TJugador Jugador::Color() {
	return color;
};
int Jugador::CantFichas() {
	return cantFichas;
};
int Jugador::CantPaises() {
	return cantPaises;
};
int Jugador::CantPaises(TContinente _continente) {
	return cantPaisesPorCont[_continente];
};
int Jugador::FichasPorAgregar(TContinente _continente){
	return fichasPorAgregar[_continente];
};
int Jugador::FichasPorAgregar(){
    int aux=0;
    for(TContinente i=ASIA;i<=LIBRES;i++)
        aux+=fichasPorAgregar[i];
    return aux;
};
void Jugador::TomarMision(const Mision *_mision){
	mision=_mision;
};
bool Jugador::MisionCumplida(){
	if(cantPaises>=MisionGlobal.mision.cantPaises)
		return true;
	else
		switch (mision->tipo){
			case CONQUISTA:
				for(TContinente i=ASIA;i<NINGUNO;i++)
					if(mision->mision.paisesPorCont[i]>cantPaisesPorCont[i])
						return false;
				return true;
			case ELIMINACION:
				if(Jugadores[mision->mision.enemigo]->CantPaises()==0)
					return true;
				else
					return false;
			case CANTIDAD_PAISES:
				if(cantPaises>=mision->mision.cantPaises)
					return true;
				else
					return false;
		}
};

int Jugador::CantidadAgregar(TPais _pais){
    if(TEG.GetSituacionActual()==AgregandoFichas && TEG[_pais].Ocupante()==color)
        return fichasPorAgregar[TEG[_pais].Continente()]+fichasPorAgregar[LIBRES];
    else
        return 0;
};

bool Jugador::AgregarFichas(int _fichas,TPais _pais){
    if(_fichas==0)
        return true;
	switch(TEG.GetSituacionActual()){
		case RepartoInicial:
			if(TEG[_pais].AgregarFichas(_fichas,color)){
				cantFichas+=_fichas;
				cantPaises++;
				cantPaisesPorCont[TEG[_pais].Continente()]++;
				Interfaz::Modo_MarcarPais(_pais);//marcado
				return true;
			}else{
				Interfaz::GUI_Alerta("PAIS OCUPADO");
				return false;
			}
		case AgregandoFichas:
			if( fichasPorAgregar[TEG[_pais].Continente()]+fichasPorAgregar[LIBRES]<_fichas){
				Interfaz::GUI_Alerta("NO HAY FICHAS DISPONIBLES");
				return false;
			}else
				if(TEG[_pais].AgregarFichas(_fichas,color)){
					cantFichas+=_fichas;

					if(fichasPorAgregar[TEG[_pais].Continente()]>=_fichas)
						fichasPorAgregar[TEG[_pais].Continente()]-=_fichas;
					else{
						_fichas-=fichasPorAgregar[TEG[_pais].Continente()];
						fichasPorAgregar[TEG[_pais].Continente()]=0;
						fichasPorAgregar[LIBRES]-=_fichas;
					}
					Interfaz::Modo_MarcarPais(_pais);//marcado
					return true;
				}else{
					Interfaz::GUI_Alerta("PAIS ENEMIGO");
					return false;
					}
		default://mientras se ataque o reagrupen fichas se debe llamar a DesplazarFichas()
			Interfaz::GUI_Alerta("No se puede agregar fichas");
			return false;
	}
};
bool Jugador::SacarFichas(int _fichas,TPais _pais){
	switch (TEG.GetSituacionActual()){
		case Atacando:
			if(TEG[_pais].SacarFichas(_fichas)){
				cantFichas-=_fichas;
				if(TEG[_pais].Ocupante()==NINGUNO){
					cantPaises--;
					cantPaisesPorCont[TEG[_pais].Continente()]--;
				}
				Interfaz::Modo_MarcarPais(_pais);//marcado
				return true;
			}else
				return false;
		default:
			return false;
	}
};

int Jugador::CantidadDesplazar(TPais _origen,TPais _destino){
	switch(TEG.GetSituacionActual()){
		case Atacando:
			if(TEG[_destino].Ocupante()==NINGUNO && TEG[_origen].Ocupante()==color && TEG[_origen].EsAdy(_destino))
				return TEG[_origen].FichasMovibles();
			else
				return 0;
		case Reagrupando:
			if(TEG[_destino].Ocupante()==color && TEG[_origen].Ocupante()==color && TEG[_origen].EsAdy(_destino))
				return TEG[_origen].FichasMovibles();
			else
				return 0;
		default:
			return 0;
	}
};

bool Jugador::DesplazarFichas(TPais _origen,TPais _destino,int _cantFichas){
	switch(TEG.GetSituacionActual()){
		case Atacando:
			if(CantidadDesplazar(_origen,_destino)&& TEG[_origen].SacarFichas(_cantFichas,color)){//TEG[_destino].Ocupante()==NINGUNO && TEG[_origen].Ocupante()==color && TEG[_origen].EsAdy(_destino)&& TEG[_origen].SacarFichas(_cantFichas,color)){
				TEG[_destino].AgregarFichas(_cantFichas,color);
				cantPaises++;
				cantPaisesPorCont[TEG[_destino].Continente()]++;
				Interfaz::Modo_MarcarPais(_origen);
				Interfaz::Modo_MarcarPais(_destino);
				return true;
			}else
				return false;
		case Reagrupando:
			if(CantidadDesplazar(_origen,_destino) && TEG[_origen].SacarFichas(_cantFichas)){//TEG[_destino].Ocupante()==color && TEG[_origen].Ocupante()==color && TEG[_origen].EsAdy(_destino) &&TEG[_origen].SacarFichas(_cantFichas)){
				TEG[_destino].AgregarFichas(_cantFichas);
				Interfaz::Modo_MarcarPais(_origen);
				Interfaz::Modo_MarcarPais(_destino);
				return true;
			}else
				return false;
		default:
			return false;
	}
};

bool Jugador::PosibleBatalla(TPais _atacante,TPais _defensor){
	if(TEG[_atacante].Ocupante()==color && TEG[_atacante].Fichas()>1 &&TEG [_defensor].Ocupante()!=color &&TEG[_defensor].Fichas()>0 && TEG[_atacante].EsAdy(_defensor))
		return true;
	else
		return false;
};
ResultBatalla Jugador::Batalla(TPais _atacante,TPais _defensor){
	ResultBatalla r={0,0,0};

	int dados[2][4]={{0,0,0,0},{0,0,0,0}};
	dados[ATACANTE][0]=TEG[_atacante].Fichas();
	dados[DEFENSOR][0]=TEG[_defensor].Fichas();

	//carga los resultados de los dados de ambos jugadores:
    dados[0][1]=Interfaz::Random(1,6);
    dados[1][1]=Interfaz::Random(1,6);
    switch(dados[0][0]){
        case 2:
            break;
        case 3:
            dados[0][2]=Interfaz::Random(1,6);
            break;
        default:
            dados[0][2]=Interfaz::Random(1,6);
            dados[0][3]=Interfaz::Random(1,6);
    }
    switch(dados[1][0]){
        case 1:
            break;
        case 2:
            dados[1][2]=Interfaz::Random(1,6);
            break;
        default:
            dados[1][2]=Interfaz::Random(1,6);
            dados[1][3]=Interfaz::Random(1,6);
    }

	//ordena el resultado de los dados para enfrentarlos:
	int aux;
	for(int i=ATACANTE;i<EMPATE;i++){
		if(dados[i][2]>dados[i][1]){
			aux=dados[i][1];
			dados[i][1]=dados[i][2];
			dados[i][2]=aux;
		}
		if(dados[i][3]>dados[i][2]){
			aux=dados[0][2];
			dados[i][2]=dados[i][3];
			dados[i][3]=aux;
		}
		if(dados[i][2]>dados[i][1]){
			aux=dados[i][1];
			dados[i][1]=dados[i][2];
			dados[i][2]=aux;
		}
	}

	//enfrenta el resultado de los dados de los jugadores:
	if(dados[ATACANTE][1]>dados[DEFENSOR][1])
		r.perdidasDefensor++;
	else
		r.perdidasAtacante++;
	if(dados[ATACANTE][2]!=0 && dados[DEFENSOR][2]){
		if(dados[ATACANTE][2]>dados[DEFENSOR][2])
			r.perdidasDefensor++;
		else
			r.perdidasAtacante++;
		if(dados[ATACANTE][3]!=0 && dados[DEFENSOR][3]!=0)
			if(dados[ATACANTE][3]>dados[DEFENSOR][3])
				r.perdidasDefensor++;
			else
				r.perdidasAtacante++;
	}

	//saca las fichas perdidas en batalla y revisa si alguno gano la batalla. En todo caso llama a la correspondiente funcion DesplazarPorBatallaGanada:
	Interfaz::Modo_Batalla(_atacante,_defensor,dados[ATACANTE][1],dados[ATACANTE][2],dados[ATACANTE][3],dados[DEFENSOR][1],dados[DEFENSOR][2],dados[DEFENSOR][3]);
	SacarFichas(r.perdidasAtacante,_atacante);
	Jugadores[TEG[_defensor].Ocupante()]->SacarFichas(r.perdidasDefensor,_defensor);

    if(TEG[_defensor].Ocupante()==NINGUNO){//gana el atacante
        DesplazarPorBatallaGanada(_atacante,_defensor,TEG[_atacante].FichasMovibles());
        r.ganador=ATACANTE;
        return r;
    }else{//empate
        r.ganador=EMPATE;
        return r;
    }
};
#endif
