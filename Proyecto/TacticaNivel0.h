#ifndef TACTICANIVEL0_H_INCLUDED
#define TACTICANIVEL0_H_INCLUDED

#include "Tacticas.h"

class Tactica_Nivel0: public Tactica{

    public:
        Tactica_Nivel0():Tactica(){};
        virtual ~Tactica_Nivel0(){};

        virtual void tacticaAgregar(list<Objetivo *> &);
		virtual void tacticaAtacar(list<Objetivo *> &);
		virtual void tacticaReagrupar(list<Objetivo *> &);
};

//agrega al azar
void Tactica_Nivel0::tacticaAgregar(list<Objetivo *> &){

    Arreglo paises;
	for(TContinente c=ASIA;c<=OCEANIA;c++)
		if(jug->FichasPorAgregar(c)){
		    PaisesContinente(c,paises);
			while(jug->FichasPorAgregar(c))
				jug->AgregarFichas(1,paises[Interfaz::Random(0,paises.cant)]);
		}

    PaisesJugador(jug->Color(),paises);
	while(jug->FichasPorAgregar(LIBRES))
		jug->AgregarFichas(1,paises[Interfaz::Random(0,paises.cant)]);
};

//ataca agresivamente
void Tactica_Nivel0::tacticaAtacar(list<Objetivo *> &){
    Arreglo paises;
	PaisesJugador(jug->Color(),paises);

	for(int i=0;i<paises.cant;i++)
        if(TEG[paises[i]].Fichas()>1)
            for(int j=0;j<TEG[paises[i]].CantAdy();j++)
                while(jug->PosibleBatalla(paises[i],TEG[paises[i]].Ady(j)))
                    jug->Batalla(paises[i],TEG[paises[i]].Ady(j));
};

//no realiza desplazamientos de fichas
void Tactica_Nivel0::tacticaReagrupar(list<Objetivo *> &){

};

#endif // TACTICANIVEL0_H_INCLUDED
