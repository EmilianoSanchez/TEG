
#include "ControladorJuego.h"

extern ControladorJuego *controladorJuego;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	controladorJuego=new ControladorJuego();
	if(controladorJuego->IniciarNuevaPartida()){
		while(controladorJuego->EstadoJuego()!=FinPartida){
			controladorJuego->EjecutarTurnoSiguiente();
		}
		controladorJuego->TerminarPartida();
	}
	delete controladorJuego;
	return 0;
};
