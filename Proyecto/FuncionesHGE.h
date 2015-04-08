#ifndef INTERFAZ_FUNSIONES_HGE_H
#define INTERFAZ_FUNSIONES_HGE_H


#include "ObjetosHGE.h"
#include "GUIsHGE.h"

//funciones privadas:

namespace Interfaz{

	bool Inicio_SetSistema();//
	bool Inicio_ConstruirObjetos();//
	bool Inicio_DestruirObjetos();//

	void GUIEJ_ConstruirObjetos();//
	void GUIEJ_DestruirObjetos();//
	bool GUIEJ_Frame();//
	bool GUIEJ_Render();//

	void Principal_ConstruirObjetos();//
	void Principal_DestruirObjetos();//

	//llamados por Dibujar_Elementos: el primero muestra el fondo y los textos, el segundo dibuja las GUIs
	void Render_Elementos();//
	void Render_GUIs();//

	bool Marcar_Frame();//
	bool MostrarMision_Frame();//
	bool Batalla_Frame();//
	bool DPBG_Frame();//
	//asignan valores distintos de cero a variables y punteros para que Dibujar_Elementos lo visualise:
	void MostrarMision_Inicio(TJugador _turno,const Mision *mision,bool ganador);//
	void Marcar_Inicio(TPais pais);//
	void Batalla_Inicio(TPais _a,TPais _d,int a1,int a2,int a3,int d1,int d2,int d3);//
	void DPBG_Inicio(TJugador _turno,TPais ori,TPais des,int max);//
	//coloca en cero los valores usados en las 3 funciones anteriores respectivamente:
	void MostrarMision_Fin();//
	void Marcar_Fin();//
	void Batalla_Fin();	//
	void DPBG_Fin();//

	void Inicio_Modo_Agregar(TJugador _turno);//
	bool Frame_Modo_Agregar();//
	void Fin_Modo_Agregar();//
	void Inicio_Modo_Atacar(TJugador _turno);//
	bool Frame_Modo_Atacar();//
	void Fin_Modo_Atacar();//
	void Inicio_Modo_Reagrupar(TJugador _turno);//
	bool Frame_Modo_Reagrupar();//
	void Fin_Modo_Reagrupar();//




	bool Abortar();//
};

//implementaciones:

bool Interfaz::Abortar(){
	if(GUIactivadas[GUI_EJ])
		GUIEJ_DestruirObjetos();
	TerminarInterfaz();
	exit(0);//abort();
};

bool Interfaz::Inicio_SetSistema(){
	if(hge){
	hge->System_SetState(HGE_LOGFILE, "Teg con HGE.log");
	hge->System_SetState(HGE_SHOWSPLASH,false);
	hge->System_SetState(HGE_TITLE, "TEG");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_HIDEMOUSE,false);
	hge->System_SetState(HGE_FPS,80);
	hge->System_SetState(HGE_EXITFUNC,Abortar);
	return true;
	}else return false;
};
bool Interfaz::Inicio_ConstruirObjetos(){
	//creacion de objetos globales:
	fnt=new hgeFont("font.fnt",true);
	fnt->SetColor(0xff000000);
	return true;
};
bool Interfaz::Inicio_DestruirObjetos(){
	//destruccion de objetos globales:
	delete fnt;
	return true;
};
void Interfaz::Principal_ConstruirObjetos(){
	fPRINCIPAL=new hgeSprite(hge->Texture_Load("fondoPRINCIPAL.png"),0,0,800,600);
	interrogacion=new hgeSprite(hge->Texture_Load("interrogacion.png"),0,0,132,100);
	dado=new hgeSprite(hge->Texture_Load("dados.png"),0,0,36,36);
	tpanel=hge->Texture_Load("panel.png");
	tficha=hge->Texture_Load("ficha.png");
	panel=new hgeSprite(tpanel,0,0,510,365);
	ConstruirGUI_MAPA();
	ConstruirGUI_ACCIONES();
	ConstruirGUI_MISIONES();

	ConstruirGUI_MOSTRARMISION();
	ConstruirGUI_DPBG();
	GUIactivadas[GUI_EJ]=false;
	GUIactivadas[GUI_MAPA]=true;
	GUIactivadas[GUI_ACCIONES]=false;
	GUIactivadas[GUI_MISIONES]=false;
	GUIactivadas[GUI_MOSTRARMISION]=false;
	GUIactivadas[GUI_DPBG]=false;
};
void Interfaz::Principal_DestruirObjetos(){
	for (int i=1;i<CANTGUIS;i++)
		delete GUIS[i];
	hge->Texture_Free(tguiej);
	hge->Texture_Free(tguip);

	hge->Texture_Free(fPRINCIPAL->GetTexture());
	delete fPRINCIPAL;
	hge->Texture_Free(interrogacion->GetTexture());
	delete interrogacion;
	hge->Texture_Free(dado->GetTexture());
	delete dado;
	hge->Texture_Free(tpanel);
	delete panel;
	hge->Texture_Free(tficha);
};
void Interfaz::GUIEJ_ConstruirObjetos(){
	//creacion objetos locales:
	fGUIEJ=new hgeSprite(hge->Texture_Load("fondoGUIEJ.PNG"),0,0,800,600);
	ConstruirGUI_EJ();
};
void Interfaz::GUIEJ_DestruirObjetos(){
	//destruccion objetos locales:
	delete GUIS[0];
	hge->Texture_Free(fGUIEJ->GetTexture());
	delete fGUIEJ;
};
bool Interfaz::GUIEJ_Frame(){
	float dt=hge->Timer_GetDelta();
	int id=GUIS[0]->Update(dt);
	int cant;
	switch(id){
		case DOS:
			for(int i=0;i<5;i++)
				auxb[i]->SetState(false);
			auxb[0]->SetState(true);
			for(int i=2;i<6;i++){
				auxt[i]->SetSelectedItem(2);
                tacts[i]->SetSelectedItem(0);
                estrs[i]->SetSelectedItem(0);
			}
			break;
		case TRES:
			for(int i=0;i<5;i++)
				auxb[i]->SetState(false);
			auxb[1]->SetState(true);
			for(int i=3;i<6;i++){
				auxt[i]->SetSelectedItem(2);
                tacts[i]->SetSelectedItem(0);
                estrs[i]->SetSelectedItem(0);
			}
			if(auxt[2]->GetSelectedItem()==2){
				auxt[2]->SetSelectedItem(1);
                tacts[2]->SetSelectedItem(1);
                estrs[2]->SetSelectedItem(1);
			}
			break;
		case CUATRO:
			for(int i=0;i<5;i++)
				auxb[i]->SetState(false);
			auxb[2]->SetState(true);
			for(int i=4;i<6;i++){
				auxt[i]->SetSelectedItem(2);
                tacts[i]->SetSelectedItem(0);
                estrs[i]->SetSelectedItem(0);
			}
			for(int i=2;i<4;i++)
				if(auxt[i]->GetSelectedItem()==2){
					auxt[i]->SetSelectedItem(1);
                    tacts[i]->SetSelectedItem(1);
                    estrs[i]->SetSelectedItem(1);
				}
			break;
		case CINCO:
			for(int i=0;i<5;i++)
				auxb[i]->SetState(false);
			auxb[3]->SetState(true);
			auxt[5]->SetSelectedItem(2);
            tacts[5]->SetSelectedItem(0);
            estrs[5]->SetSelectedItem(0);
			for(int i=2;i<5;i++)
				if(auxt[i]->GetSelectedItem()==2){
					auxt[i]->SetSelectedItem(1);
                    tacts[i]->SetSelectedItem(1);
                    estrs[i]->SetSelectedItem(1);
				}
			break;
		case SEIS:
			for(int i=0;i<5;i++)
				auxb[i]->SetState(false);
			auxb[4]->SetState(true);
			for(int i=2;i<6;i++)
				if(auxt[i]->GetSelectedItem()==2){
					auxt[i]->SetSelectedItem(1);
                    tacts[i]->SetSelectedItem(1);
                    estrs[i]->SetSelectedItem(1);
				}
			break;
		case TIPOAZUL:
            if(auxt[0]->GetSelectedItem()==0){
                tacts[0]->SetSelectedItem(0);
                estrs[0]->SetSelectedItem(0);
            }else{
                tacts[0]->SetSelectedItem(1);
                estrs[0]->SetSelectedItem(1);
            }
			break;
		case TIPOROJO:
            if(auxt[1]->GetSelectedItem()==0){
                tacts[1]->SetSelectedItem(0);
                estrs[1]->SetSelectedItem(0);
            }else{
                tacts[1]->SetSelectedItem(1);
                estrs[1]->SetSelectedItem(1);
            }
			break;
		case TIPOAMARILLO:
			for(int i=0;i<5;i++)
				if(auxb[i]->GetState()){
					cant=i+2;
					break;
				}
            if(cant>=3){
                switch(auxt[2]->GetSelectedItem()){
                    case 0:
                        tacts[2]->SetSelectedItem(0);
                        estrs[2]->SetSelectedItem(0);
                        break;
                    case 1:
                        tacts[2]->SetSelectedItem(1);
                        estrs[2]->SetSelectedItem(1);
                        break;
                    case 2:
                        auxt[2]->SetSelectedItem(1);
                        tacts[2]->SetSelectedItem(1);
                        estrs[2]->SetSelectedItem(1);
                }
            }else{
                auxt[2]->SetSelectedItem(2);
            }
			break;
		case TIPOVERDE:
			for(int i=0;i<5;i++)
				if(auxb[i]->GetState()){
					cant=i+2;
					break;
				}
            if(cant>=4){
                switch(auxt[3]->GetSelectedItem()){
                    case 0:
                        tacts[3]->SetSelectedItem(0);
                        estrs[3]->SetSelectedItem(0);
                        break;
                    case 1:
                        tacts[3]->SetSelectedItem(1);
                        estrs[3]->SetSelectedItem(1);
                        break;
                    case 2:
                        auxt[3]->SetSelectedItem(1);
                        tacts[3]->SetSelectedItem(1);
                        estrs[3]->SetSelectedItem(1);
                }
            }else{
                auxt[3]->SetSelectedItem(2);
            }
			break;
		case TIPOCYAN:
			for(int i=0;i<5;i++)
				if(auxb[i]->GetState()){
					cant=i+2;
					break;
				}
            if(cant>=5){
                switch(auxt[4]->GetSelectedItem()){
                    case 0:
                        tacts[4]->SetSelectedItem(0);
                        estrs[4]->SetSelectedItem(0);
                        break;
                    case 1:
                        tacts[4]->SetSelectedItem(1);
                        estrs[4]->SetSelectedItem(1);
                        break;
                    case 2:
                        auxt[4]->SetSelectedItem(1);
                        tacts[4]->SetSelectedItem(1);
                        estrs[4]->SetSelectedItem(1);
                }
            }else{
                auxt[4]->SetSelectedItem(2);
            }
			break;
		case TIPOMAGENTA:
			for(int i=0;i<5;i++)
				if(auxb[i]->GetState()){
					cant=i+2;
					break;
				}
            if(cant>=6){
                switch(auxt[5]->GetSelectedItem()){
                    case 0:
                        tacts[5]->SetSelectedItem(0);
                        estrs[5]->SetSelectedItem(0);
                        break;
                    case 1:
                        tacts[5]->SetSelectedItem(1);
                        estrs[5]->SetSelectedItem(1);
                        break;
                    case 2:
                        auxt[5]->SetSelectedItem(1);
                        tacts[5]->SetSelectedItem(1);
                        estrs[5]->SetSelectedItem(1);
                }
            }else{
                auxt[5]->SetSelectedItem(2);
            }
			break;

        case TACTICAAZUL:
            if(auxt[0]->GetSelectedItem()==0)
                tacts[0]->SetSelectedItem(0);
            else
                if(tacts[0]->GetSelectedItem()==0)
                    tacts[0]->SetSelectedItem(1);
            break;
        case TACTICAROJO:
            if(auxt[1]->GetSelectedItem()==0)
                tacts[1]->SetSelectedItem(0);
            else
                if(tacts[1]->GetSelectedItem()==0)
                    tacts[1]->SetSelectedItem(1);
            break;
        case TACTICAAMARILLO:
            if(auxt[2]->GetSelectedItem()==0 || auxt[2]->GetSelectedItem()==2)
                tacts[2]->SetSelectedItem(0);
            else
                if(tacts[2]->GetSelectedItem()==0)
                    tacts[2]->SetSelectedItem(1);
            break;
        case TACTICAVERDE:
            if(auxt[3]->GetSelectedItem()==0 || auxt[2]->GetSelectedItem()==2)
                tacts[3]->SetSelectedItem(0);
            else
                if(tacts[3]->GetSelectedItem()==0)
                    tacts[3]->SetSelectedItem(1);
            break;
        case TACTICACYAN:
            if(auxt[4]->GetSelectedItem()==0 || auxt[2]->GetSelectedItem()==2)
                tacts[4]->SetSelectedItem(0);
            else
                if(tacts[4]->GetSelectedItem()==0)
                    tacts[4]->SetSelectedItem(1);
            break;
        case TACTICAMAGENTA:
            if(auxt[5]->GetSelectedItem()==0 || auxt[2]->GetSelectedItem()==2)
                tacts[5]->SetSelectedItem(0);
            else
                if(tacts[5]->GetSelectedItem()==0)
                    tacts[5]->SetSelectedItem(1);
            break;
        case ESTRATEGIAAZUL:
            if(auxt[0]->GetSelectedItem()==0)
                estrs[0]->SetSelectedItem(0);
            else
                if(estrs[0]->GetSelectedItem()==0)
                    estrs[0]->SetSelectedItem(1);
            break;
        case ESTRATEGIAROJO:
            if(auxt[1]->GetSelectedItem()==0)
                estrs[1]->SetSelectedItem(0);
            else
                if(estrs[1]->GetSelectedItem()==0)
                    estrs[1]->SetSelectedItem(1);
            break;
        case ESTRATEGIAAMARILLO:
            if(auxt[2]->GetSelectedItem()==0 || auxt[2]->GetSelectedItem()==2)
                estrs[2]->SetSelectedItem(0);
            else
                if(estrs[2]->GetSelectedItem()==0)
                    estrs[2]->SetSelectedItem(1);
            break;
        case ESTRATEGIAVERDE:
            if(auxt[3]->GetSelectedItem()==0 || auxt[2]->GetSelectedItem()==2)
                estrs[3]->SetSelectedItem(0);
            else
                if(estrs[3]->GetSelectedItem()==0)
                    estrs[3]->SetSelectedItem(1);
            break;
        case ESTRATEGIACYAN:
            if(auxt[4]->GetSelectedItem()==0 || auxt[2]->GetSelectedItem()==2)
                estrs[4]->SetSelectedItem(0);
            else
                if(estrs[4]->GetSelectedItem()==0)
                    estrs[4]->SetSelectedItem(1);
            break;
        case ESTRATEGIAMAGENTA:
            if(auxt[5]->GetSelectedItem()==0 || auxt[2]->GetSelectedItem()==2)
                estrs[5]->SetSelectedItem(0);
            else
                if(estrs[5]->GetSelectedItem()==0)
                    estrs[5]->SetSelectedItem(1);
            break;
		case ACEPTAR:
			for(int i=0;i<5;i++)
				if(auxb[i]->GetState()){
					CantJugadores=i+2;
					break;
				}
			for(int i=0;i<MAXJUGADORES;i++){
				Tipos[i]=auxt[i]->GetSelectedItem();
				switch(tacts[i]->GetSelectedItem()){
				    case 0:
                        Tacticas[i]=NINGUN_NIVEL;
                        break;
				    case 1:
                        Tacticas[i]=NIVEL_0;
                        break;
				    case 2:
                        Tacticas[i]=NIVEL_1;
                        break;
                    case 3:
                        Tacticas[i]=NIVEL_2;
                        break;
                    case 4:
                        Tacticas[i]=NIVEL_3;
				}
				switch(estrs[i]->GetSelectedItem()){
				    case 0:
                        Estrategias[i]=NINGUN_NIVEL;
                        break;
				    case 1:
                        Estrategias[i]=NIVEL_0;
                        break;
				    case 2:
                        Estrategias[i]=NIVEL_1;
                        break;
                    case 3:
                        Estrategias[i]=NIVEL_2;
				}
				/*if(Tipos[i]==VIRTUAL)
					Tacticas[i]=Estrategias[i]=NIVEL_0;
				else
					Tacticas[i]=Estrategias[i]=NINGUN_NIVEL;*/
			}

			return true;
	}
	return false;
};
bool Interfaz::GUIEJ_Render(){
	hge->Gfx_BeginScene();
	fGUIEJ->Render(0,0);
	GUIS[0]->Render();
	fnt->SetColor(0xff000000);
	fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
	hge->Gfx_EndScene();
	return false;
};


void Interfaz::Render_Elementos(){

	fPRINCIPAL->Render(0,0);
	fnt->SetColor(0xff000000);
	fnt->printf(4, 8, HGETEXT_LEFT, "Turno: %s", StrJugadores[controladorJuego->Turno()]);
	fnt->printf(204, 8, HGETEXT_LEFT, "Primero de la ronda: %s", StrJugadores[controladorJuego->Primero()]);
	fnt->printf(404, 8, HGETEXT_LEFT, "%s", StrEstados[controladorJuego->EstadoJuego()]);
	fnt->printf(604, 8, HGETEXT_LEFT, "Accion: %s", StrSituacion[TEG.GetSituacionActual()]);

	for(int i=0;i<MAXJUGADORES;i++){
		fnt->printf(644,i*86+85, HGETEXT_LEFT, "%s", StrTipoJugador[Tipos[i]]);
		if(Jugadores[i]){
			fnt->printf(656,i*86+109, HGETEXT_LEFT, "%s", StrNivelInteligencia[Tacticas[i]]);
			fnt->printf(755,i*86+109, HGETEXT_LEFT, "%s", StrNivelInteligencia[Estrategias[i]]);
			fnt->printf(673,i*86+133, HGETEXT_LEFT, "%i",Jugadores[i]->CantFichas());
			fnt->printf(763,i*86+133, HGETEXT_LEFT, "%i",Jugadores[i]->CantPaises());
		}else{
			for(;i<MAXJUGADORES;i++)
				fnt->printf(644,i*86+85, HGETEXT_LEFT, "%s", StrTipoJugador[Tipos[i]]);
			break;
		}
	};
	if(TEG.GetSituacionActual()==AgregandoFichas){
		int y=455;
		fnt->printf(350,y, HGETEXT_LEFT, "Asia: %i", Jugadores[controladorJuego->Turno()]->FichasPorAgregar(ASIA));
		y+=16;
		fnt->printf(350,y, HGETEXT_LEFT, "Norteamerica: %i", Jugadores[controladorJuego->Turno()]->FichasPorAgregar(NORTEAMERICA));
		y+=16;
		fnt->printf(350,y, HGETEXT_LEFT, "Europa: %i", Jugadores[controladorJuego->Turno()]->FichasPorAgregar(EUROPA));
		y+=16;
		fnt->printf(350,y, HGETEXT_LEFT, "Sudamerica: %i", Jugadores[controladorJuego->Turno()]->FichasPorAgregar(SUDAMERICA));
		y+=16;
		fnt->printf(350,y, HGETEXT_LEFT, "Africa: %i", Jugadores[controladorJuego->Turno()]->FichasPorAgregar(AFRICA));
		y+=16;
		fnt->printf(350,y, HGETEXT_LEFT, "Oceania: %i", Jugadores[controladorJuego->Turno()]->FichasPorAgregar(OCEANIA));
		y+=32;
		fnt->printf(350,y, HGETEXT_LEFT, "Libres: %i", Jugadores[controladorJuego->Turno()]->FichasPorAgregar(LIBRES));
	}

	if(psel!=0){
		int y=464;
		fnt->printf(16,y, HGETEXT_LEFT,"Pais: %s",TEG[psel-1].Nombre());
		y+=24;
		fnt->printf(16,y, HGETEXT_LEFT,"Continente: %s",StrContinentes[TEG[psel-1].Continente()]);
		y+=24;
		fnt->printf(16,y, HGETEXT_LEFT,"Ocupante: %s",StrJugadores[TEG[psel-1].Ocupante()]);
		y+=24;
		fnt->printf(16,y, HGETEXT_LEFT,"Fichas: %i",TEG[psel-1].Fichas());
		y+=24;
		fnt->printf(16,y, HGETEXT_LEFT,"Fichas movibles: %i",TEG[psel-1].FichasMovibles());
	}

	if(controladorJuego->Turno()!=NINGUNO && Jugadores[controladorJuego->Turno()]->GetMision())
		fnt->printfb(190,465,132,100,HGETEXT_CENTER,"%s",Jugadores[controladorJuego->Turno()]->GetMision()->str);
	else
		interrogacion->Render(190,465);


	if(Batalla){
		fnt->printf(483,451,HGETEXT_LEFT,"Atacante-Defensor");
		if(bdados[0][0]){
			dado->SetTextureRect(dados[0][0]*36,0,36,36,false);
			dado->Render(490,467);
			if(bdados[0][1]){
				dado->SetTextureRect(dados[0][1]*36,0,36,36,false);
				dado->Render(490,505);
				if(bdados[0][2]){
					dado->SetTextureRect(dados[0][2]*36,0,36,36,false);
					dado->Render(490,543);
					if(bdados[1][0]){
						dado->SetTextureRect(dados[1][0]*36,0,36,36,false);
						dado->Render(528,467);
						if(bdados[1][1]){
							dado->SetTextureRect(dados[1][1]*36,0,36,36,false);
							dado->Render(528,505);
							if(bdados[1][2]){
								dado->SetTextureRect(dados[1][2]*36,0,36,36,false);
								dado->Render(528,543);
							}}}}}}
	}
};

void Interfaz::Render_GUIs(){
	for(int i=0;i<4;i++)
		if(GUIactivadas[i])
			GUIS[i]->Render();
	for(int i=4;i<CANTGUIS;i++)
		if(GUIactivadas[i]){
			panel->Render(150,110);
			GUIS[i]->Render();
			break;
		}
};
bool Interfaz::Marcar_Frame(){
	auxdt+=hge->Timer_GetDelta();
	int id=GUIS[GUI_MAPA]->Update(dt);
	if(id){
		if(psel){
			MAPA[psel-1]->SetState(false);
			if(psel==id){
				psel=0;
			}else{
				psel=id;
				MAPA[psel-1]->SetState(true);
			}
		}else{
			psel=id;
			MAPA[psel-1]->SetState(true);
		}
	}
	if(auxdt>DELAY /*&& hge->Input_GetKeyState(HGEK_ENTER)*/)
		return true;
	else
		return false;
};


void Interfaz::Marcar_Inicio(TPais pais){
	auxdt=0.0f;
	pfoc=pais+1;
	MAPA[pfoc-1]->SetMarcado(true);
};
void Interfaz::Marcar_Fin(){
	MAPA[pfoc-1]->SetMarcado(false);
};

bool Interfaz::Batalla_Frame(){
	auxdt+=hge->Timer_GetDelta();
	int id=GUIS[GUI_MAPA]->Update(dt);
	if(id){
		if(psel){
			MAPA[psel-1]->SetState(false);
			if(psel==id){
				psel=0;
			}else{
				psel=id;
				MAPA[psel-1]->SetState(true);
			}
		}else{
			psel=id;
			MAPA[psel-1]->SetState(true);
		}
	}
	if(bdados[0][0]==false)
		if(auxdt>0.4f){
			bdados[0][0]=true;
			return false;
		}else
			return false;
	else if(bdados[0][1]==false)
			if(auxdt>0.8f){
				bdados[0][1]=true;
				return false;
			}else
				return false;
		else if(bdados[0][2]==false)
				if(auxdt>1.2f){
					bdados[0][2]=true;
					return false;
				}else
					return false;
			else if(bdados[1][0]==false)
					if(auxdt>1.6f){
						bdados[1][0]=true;
						return false;
					}else
						return false;
				else if(bdados[1][1]==false)
						if(auxdt>2.0f){
							bdados[1][1]=true;
							return false;
						}else
							return false;
					else if(bdados[1][2]==false)
							if(auxdt>2.4f){
								bdados[1][2]=true;
								return false;
							}else
								return false;
						else if	(auxdt>2.8f /*&& hge->Input_GetKeyState(HGEK_ENTER)*/)
								return true;
							else
								return false;
};

void Interfaz::Batalla_Inicio(TPais _a,TPais _d,int a1,int a2,int a3,int d1,int d2,int d3){
	Atacante=_a;
	Defensor=_d;
	Batalla=true;
	bdados[0][0]=bdados[0][1]=bdados[0][2]=bdados[1][0]=bdados[1][1]=bdados[1][2]=false;
	dados[0][0]=a1;
	dados[0][1]=a2;
	dados[0][2]=a3;
	dados[1][0]=d1;
	dados[1][1]=d2;
	dados[1][2]=d3;
	auxdt=0.0f;
	MAPA[Atacante]->SetMarcado(true);
	MAPA[Defensor]->SetMarcado(true);
};

void Interfaz::Batalla_Fin(){
	Batalla=false;
	BOTONES_ACCION[BOTON_ATACAR]->SetState(false);
	psel=0;
	MAPA[Atacante]->SetState(false);
	MAPA[Atacante]->SetMarcado(false);
	MAPA[Defensor]->SetState(false);
	MAPA[Defensor]->SetMarcado(false);
};


void Interfaz::MostrarMision_Inicio(TJugador _turno,const Mision *mision,bool ganador){

	GUIactivadas[GUI_MOSTRARMISION]=true;
	if(ganador)
		if(Jugadores[_turno]->CantPaises()>=CANTPAISES_MISGLOBAL){
			GUIPanel_Texto->printf("Felicitaciones jugador %s, ha cumplido la mision global: ",StrJugadores[_turno]);
			GUIPanel_Mision->SetText(MisionGlobal.str);
		}else{
			GUIPanel_Texto->printf("Felicitaciones jugador %s, ha cumplido su mision: ",StrJugadores[_turno]);
			GUIPanel_Mision->SetText(mision->str);
	}else{
		GUIPanel_Texto->printf("Jugador humano %s, su mision es: ",StrJugadores[_turno]);
		GUIPanel_Mision->SetText(mision->str);
	}
};

bool Interfaz::MostrarMision_Frame(){
	int id=GUIS[GUI_MOSTRARMISION]->Update(hge->Timer_GetDelta());
	if(id==BOTON_SALIR)
		return true;
	else
		return false;
};

void Interfaz::MostrarMision_Fin(){
	GUIactivadas[GUI_MOSTRARMISION]=false;
};


void Interfaz::Inicio_Modo_Agregar(TJugador _turno){
	turno=_turno;
	GUIactivadas[GUI_ACCIONES]=true;
	for(int i=1;i<=CANTBOTONESACCION;i++)
		BOTONES_ACCION[i]->bEnabled=false;
	BOTONES_ACCION[BOTON_AGREGAR]->bEnabled=true;
	BOTONES_ACCION[BOTON_VERMISIONES]->bEnabled=true;
	BOTONES_ACCION[BOTON_FINAGREGAR]->bEnabled=true;
	psel=0;
};
bool Interfaz::Frame_Modo_Agregar(){
	dt=hge->Timer_GetDelta();
	int id;
	if(GUIactivadas[GUI_MISIONES]){
		id=GUIS[GUI_MISIONES]->Update(dt);
		if(id)
			GUIactivadas[GUI_MISIONES]=false;
		return false;
	}else{
		id=GUIS[GUI_MAPA]->Update(dt);
		if(id){
			if(psel)
				MAPA[psel-1]->SetState(false);
			psel=id;
			MAPA[psel-1]->SetState(true);
			return false;
		}else{
			id=GUIS[GUI_ACCIONES]->Update(dt);
			switch(id){
				case BOTON_AGREGAR:
					if(psel){
						Jugadores[turno]->AgregarFichas(1,psel-1);
					}
					return false;
				case BOTON_FINAGREGAR:
					if(psel)
						MAPA[psel-1]->SetState(false);
					psel=0;
					return true;
				case BOTON_VERMISIONES:
					GUIactivadas[GUI_MISIONES]=true;
					return false;
				default:
					return false;
			}
		}
	}
};
void Interfaz::Fin_Modo_Agregar(){
	GUIactivadas[GUI_ACCIONES]=false;
	GUIactivadas[GUI_MISIONES]=false;
};

void Interfaz::Inicio_Modo_Atacar(TJugador _turno){
	turno=_turno;
	GUIactivadas[GUI_ACCIONES]=true;
	for(int i=1;i<=CANTBOTONESACCION;i++)
		BOTONES_ACCION[i]->bEnabled=false;
	BOTONES_ACCION[BOTON_ATACAR]->bEnabled=true;
	BOTONES_ACCION[BOTON_VERMISIONES]->bEnabled=true;
	BOTONES_ACCION[BOTON_FINATACAR]->bEnabled=true;
	ataq=false;
	if(psel)
		MAPA[psel-1]->SetState(false);
	psel=0;
};

bool Interfaz::Frame_Modo_Atacar(){
	dt=hge->Timer_GetDelta();
	int id;
	if(GUIactivadas[GUI_MISIONES]){
		id=GUIS[GUI_MISIONES]->Update(dt);
		if(id)
			GUIactivadas[GUI_MISIONES]=false;
		return false;
	}else{
		id=GUIS[GUI_MAPA]->Update(dt);
		if(id){
			if(psel)
				if(psel==id){
					MAPA[psel-1]->SetState(false);
					psel=0;
					BOTONES_ACCION[BOTON_ATACAR]->SetState(false);
					ataq=false;
					return false;
				}else
					if(ataq)
						if(Jugadores[turno]->PosibleBatalla(psel-1,id-1)){
							Batalla=true;
							Atacante=psel-1;
							Defensor=id-1;
							return true;
						}else{
							MAPA[id-1]->SetState(false);
							return false;
						}
					else{
						MAPA[psel-1]->SetState(false);
						psel=id;
						MAPA[psel-1]->SetState(true);
						return false;
					}
			else{
				psel=id;
				MAPA[psel-1]->SetState(true);
				return false;
			}
		}else{
			id=GUIS[GUI_ACCIONES]->Update(dt);
			switch(id){
				case BOTON_ATACAR:
					if(psel)
						ataq=true;
					return false;
				case BOTON_FINATACAR:
					return true;
				case BOTON_VERMISIONES:
					GUIactivadas[GUI_MISIONES]=true;
					return false;
				default:
					return false;
			}
		}
	}
};

void Interfaz::Fin_Modo_Atacar(){
	GUIactivadas[GUI_ACCIONES]=false;
	GUIactivadas[GUI_MISIONES]=false;
};

void Interfaz::Inicio_Modo_Reagrupar(TJugador _turno){
	turno=_turno;
	GUIactivadas[GUI_ACCIONES]=true;
	for(int i=1;i<=CANTBOTONESACCION;i++)
		BOTONES_ACCION[i]->bEnabled=false;
	BOTONES_ACCION[BOTON_DESPLAZAR]->bEnabled=true;
	BOTONES_ACCION[BOTON_VERMISIONES]->bEnabled=true;
	BOTONES_ACCION[BOTON_FINREAGRUPAR]->bEnabled=true;
	desp=false;
	if(psel)
		MAPA[psel-1]->SetState(false);
	psel=0;
};
bool Interfaz::Frame_Modo_Reagrupar(){
	dt=hge->Timer_GetDelta();
	int id;
	if(GUIactivadas[GUI_MISIONES]){
		id=GUIS[GUI_MISIONES]->Update(dt);
		if(id)
			GUIactivadas[GUI_MISIONES]=false;
		return false;
	}else{
		id=GUIS[GUI_MAPA]->Update(dt);
		if(id){
			if(psel)
				if(psel==id){
					MAPA[psel-1]->SetState(false);
					psel=0;
					BOTONES_ACCION[BOTON_DESPLAZAR]->SetState(false);
					desp=false;
					return false;
				}else
					if(desp)
						if(Jugadores[turno]->CantidadDesplazar(psel-1,id-1)){
							Jugadores[turno]->DesplazarFichas(psel-1,id-1,1);
							//desp=false;
							MAPA[id-1]->SetState(false);
							return false;
						}else{
							MAPA[id-1]->SetState(false);
							return false;
					}else{
						MAPA[psel-1]->SetState(false);
						psel=id;
						MAPA[psel-1]->SetState(true);
						return false;
					}
			else{
				psel=id;
				MAPA[psel-1]->SetState(true);
				return false;
			}
		}else{
			id=GUIS[GUI_ACCIONES]->Update(dt);
			switch(id){
				case BOTON_DESPLAZAR:
					if(psel)
						desp=true;
					return false;
				case BOTON_FINREAGRUPAR:
					return true;
				case BOTON_VERMISIONES:
					GUIactivadas[GUI_MISIONES]=true;
					return false;
				default:
					return false;
			}
		}
	}

};

void Interfaz::Fin_Modo_Reagrupar(){
	GUIactivadas[GUI_ACCIONES]=false;
	GUIactivadas[GUI_MISIONES]=false;
};
void Interfaz::DPBG_Inicio(TJugador _turno,TPais ori,TPais des,int max){
	Origen=ori;
	Destino=des;
	GUIactivadas[GUI_DPBG]=true;
	GUIDPBG_Texto->printf("El jugador %s\ndesplaza fichas por\nbatalla ganada entre:\n%s y %s:",StrJugadores[_turno],TEG[ori].Nombre(),TEG[des].Nombre());
	GUIDPBG_Texto->SetColor(0xff000000);
	if(max==1){
		GUIDPBG_Botones[1]->bEnabled=false;
		GUIDPBG_Botones[2]->bEnabled=false;
	}else if(max==2)
			GUIDPBG_Botones[2]->bEnabled=false;
};
bool Interfaz::DPBG_Frame(){
	dt=hge->Timer_GetDelta();
	cant=GUIS[GUI_DPBG]->Update(dt);
	if(cant)
		return true;
	else
		return false;
};
void Interfaz::DPBG_Fin(){
	GUIactivadas[GUI_DPBG]=false;
	GUIDPBG_Botones[1]->bEnabled=true;
	GUIDPBG_Botones[2]->bEnabled=true;
	MAPA[Origen]->SetMarcado(false);
	MAPA[Destino]->SetMarcado(false);
};

#endif
