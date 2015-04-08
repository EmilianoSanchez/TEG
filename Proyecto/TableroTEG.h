#ifndef CLASE_TABLERO_TEG_H
#define CLASE_TABLERO_TEG_H

#include "UtilidadesTablero.h"
#include "UtilidadesJugadores.h"

//definicion de la clase TableroTEG:

class TableroTEG{
	private:
		TPais cantPaises;
		Pais **casilleros;
		Situacion SituacionActual;
        pair<int,TPais> **caminosEntrePaises;
        void CargarCaminos();
	public:
	//constructor-destructor:
		TableroTEG();
		~TableroTEG();

		int CantPaises();
		Situacion GetSituacionActual();
		void SetSituacionActual(Situacion sit);
		Pais &operator[](TPais indice);

    //algoritmos de grafos:
        void CaminoMasCorto(TPais ori,TPais des,list<TPais> &l);
        int CaminoMasCorto(TPais ori,TPais des);

    //iteradores:
		class Iterador;
		class IBFS;
		class IDFS;
        class IBestFS;

};

#include "Pais.h"

TableroTEG TEG;

#include "Iteradores.h"


//implementaciones:

void TableroTEG::CaminoMasCorto(TPais ori,TPais des,list<TPais> &l){
    TPais aux=ori;
    while(aux!=des){
        aux=caminosEntrePaises[aux][des].second;
        l.push_back(aux);
    }
};
int TableroTEG::CaminoMasCorto(TPais ori,TPais des){
    return caminosEntrePaises[ori][des].first;
};
void TableroTEG::CargarCaminos(){
    caminosEntrePaises=new pair<int,TPais> *[cantPaises];
	for(TPais i=0;i<cantPaises;i++){
        caminosEntrePaises[i]=new pair<int,TPais>[cantPaises];
        for(TPais j=0;j<cantPaises;j++)
            if(casilleros[i]->EsAdy(j)){
                caminosEntrePaises[i][j].first=1;
                caminosEntrePaises[i][j].second=j;
            }else{
                caminosEntrePaises[i][j].first=CANTPAISES;
                caminosEntrePaises[i][j].second=NOPAIS;
            }
	}
	for(TPais i=0;i<cantPaises;i++){
        caminosEntrePaises[i][i].first=0;
        caminosEntrePaises[i][i].second=i;
	}
	for(TPais k=0;k<cantPaises;k++)
        for(TPais i=0;i<cantPaises;i++)
            for(TPais j=0;j<cantPaises;j++)
                if(caminosEntrePaises[i][j].first > caminosEntrePaises[i][k].first + caminosEntrePaises[k][j].first){
                    caminosEntrePaises[i][j].first = caminosEntrePaises[i][k].first + caminosEntrePaises[k][j].first;
                    caminosEntrePaises[i][j].second= caminosEntrePaises[i][k].second;
                }

};

TableroTEG::TableroTEG(){

	cantPaises=CANTPAISES;
	casilleros=new Pais*[cantPaises];
	SituacionActual=Ninguna;

	TPais *aux=new TPais[2];
	aux[0]=1;
	aux[1]=2;
	casilleros[0]=new Pais(0,"Arabia",ASIA,2,aux,this);
	aux=new TPais[3];
	aux[0]=0;
	aux[1]=2;
	aux[2]=41;
	casilleros[1]=new Pais(1,"Israel",ASIA,3,aux,this);
	aux=new TPais[6];
	aux[0]=0;
	aux[1]=1;
	aux[2]=41;
	aux[3]=31;
	aux[4]=32;
	aux[5]=3;
	casilleros[2]=new Pais(2,"Turquia",ASIA,6,aux,this);
	aux=new TPais[7];
	aux[0]=2;
	aux[1]=32;
	aux[2]=9;
	aux[3]=8;
	aux[4]=7;
	aux[5]=6;
	aux[6]=4;
	casilleros[3]=new Pais(3,"Iran",ASIA,7,aux,this);
	aux=new TPais[4];
	aux[0]=3;
	aux[1]=6;
	aux[2]=5;
	aux[3]=46;
	casilleros[4]=new Pais(4,"India",ASIA,4,aux,this);
	aux=new TPais[3];
	aux[0]=4;
	aux[1]=6;
	aux[2]=47;
	casilleros[5]=new Pais(5,"Malasia",ASIA,3,aux,this);
	aux=new TPais[8];
	aux[0]=3;
	aux[1]=7;
	aux[2]=8;
	aux[3]=12;
	aux[4]=13;
	aux[5]=14;
	aux[6]=5;
	aux[7]=4;
	casilleros[6]=new Pais(6,"China",ASIA,8,aux,this);
	aux=new TPais[3];
	aux[0]=3;
	aux[1]=8;
	aux[2]=6;
	casilleros[7]=new Pais(7,"Gobi",ASIA,3,aux,this);
	aux=new TPais[5];
	aux[0]=3;
	aux[1]=9;
	aux[2]=12;
	aux[3]=6;
	aux[4]=7;
	casilleros[8]=new Pais(8,"Mongolia",ASIA,5,aux,this);
	aux=new TPais[5];
	aux[0]=3;
	aux[1]=32;
	aux[2]=10;
	aux[3]=12;
	aux[4]=8;
	casilleros[9]=new Pais(9,"Aral",ASIA,5,aux,this);
	aux=new TPais[3];
	aux[0]=9;
	aux[1]=11;
	aux[2]=12;
	casilleros[10]=new Pais(10,"Tartaria",ASIA,3,aux,this);
	aux=new TPais[2];
	aux[0]=10;
	aux[1]=12;
	casilleros[11]=new Pais(11,"Taimir",ASIA,2,aux,this);
	aux=new TPais[6];
	aux[0]=6;
	aux[1]=8;
	aux[2]=9;
	aux[3]=10;
	aux[4]=11;
	aux[5]=13;
	casilleros[12]=new Pais(12,"Siberia",ASIA,6,aux,this);
	aux=new TPais[4];
	aux[0]=6;
	aux[1]=12;
	aux[2]=15;
	aux[3]=14;
	casilleros[13]=new Pais(13,"Kamchatka",ASIA,4,aux,this);
	aux=new TPais[2];
	aux[0]=6;
	aux[1]=13;
	casilleros[14]=new Pais(14,"Japon",ASIA,2,aux,this);

	aux=new TPais[3];
	aux[0]=13;
	aux[1]=19;
	aux[2]=16;
	casilleros[15]=new Pais(15,"Alaska",NORTEAMERICA,3,aux,this);
	aux=new TPais[5];
	aux[0]=15;
	aux[1]=19;
	aux[2]=20;
	aux[3]=21;
	aux[4]=17;
	casilleros[16]=new Pais(16,"Oregon",NORTEAMERICA,5,aux,this);
	aux=new TPais[3];
	aux[0]=16;
	aux[1]=21;
	aux[2]=18;
	casilleros[17]=new Pais(17,"California",NORTEAMERICA,3,aux,this);
	aux=new TPais[2];
	aux[0]=17;
	aux[1]=34;
	casilleros[18]=new Pais(18,"Mejico",NORTEAMERICA,2,aux,this);
	aux=new TPais[3];
	aux[0]=15;
	aux[1]=20;
	aux[2]=16;
	casilleros[19]=new Pais(19,"Yukon",NORTEAMERICA,3,aux,this);
	aux=new TPais[4];
	aux[0]=16;
	aux[1]=19;
	aux[2]=22;
	aux[3]=21;
	casilleros[20]=new Pais(20,"Canada",NORTEAMERICA,4,aux,this);
	aux=new TPais[5];
	aux[0]=16;
	aux[1]=20;
	aux[2]=22;
	aux[3]=24;
	aux[4]=17;
	casilleros[21]=new Pais(21,"Nueva York",NORTEAMERICA,5,aux,this);
	aux=new TPais[3];
	aux[0]=20;
	aux[1]=23;
	aux[2]=21;
	casilleros[22]=new Pais(22,"Terranova",NORTEAMERICA,3,aux,this);
	aux=new TPais[2];
	aux[0]=22;
	aux[1]=24;
	casilleros[23]=new Pais(23,"Labrador",NORTEAMERICA,2,aux,this);
	aux=new TPais[3];
	aux[0]=21;
	aux[1]=23;
	aux[2]=25;
	casilleros[24]=new Pais(24,"Greonlandia",NORTEAMERICA,3,aux,this);

	aux=new TPais[3];
	aux[0]=24;
	aux[1]=33;
	aux[2]=26;
	casilleros[25]=new Pais(25,"Islandia",EUROPA,3,aux,this);
	aux=new TPais[3];
	aux[0]=25;
	aux[1]=30;
	aux[2]=27;
	casilleros[26]=new Pais(26,"Gran Bretaña",EUROPA,3,aux,this);
	aux=new TPais[3];
	aux[0]=26;
	aux[1]=28;
	aux[2]=40;
	casilleros[27]=new Pais(27,"España",EUROPA,3,aux,this);
	aux=new TPais[3];
	aux[0]=27;
	aux[1]=30;
	aux[2]=29;
	casilleros[28]=new Pais(28,"Francia",EUROPA,3,aux,this);
	aux=new TPais[2];
	aux[0]=28;
	aux[1]=30;
	casilleros[29]=new Pais(29,"Italia",EUROPA,2,aux,this);
	aux=new TPais[4];
	aux[0]=26;
	aux[1]=31;
	aux[2]=29;
	aux[3]=28;
	casilleros[30]=new Pais(30,"Alemania",EUROPA,4,aux,this);
	aux=new TPais[4];
	aux[0]=2;
	aux[1]=41;
	aux[2]=30;
	aux[3]=32;
	casilleros[31]=new Pais(31,"Polonia",EUROPA,4,aux,this);
	aux=new TPais[5];
	aux[0]=2;
	aux[1]=31;
	aux[2]=33;
	aux[3]=9;
	aux[4]=3;
	casilleros[32]=new Pais(32,"Rusia",EUROPA,5,aux,this);
	aux=new TPais[2];
	aux[0]=25;
	aux[1]=32;
	casilleros[33]=new Pais(33,"Suecia",EUROPA,2,aux,this);

	aux=new TPais[3];
	aux[0]=18;
	aux[1]=39;
	aux[2]=35;
	casilleros[34]=new Pais(34,"Colombia",SUDAMERICA,3,aux,this);
	aux=new TPais[4];
	aux[0]=34;
	aux[1]=39;
	aux[2]=37;
	aux[3]=36;
	casilleros[35]=new Pais(35,"Peru",SUDAMERICA,4,aux,this);
	aux=new TPais[3];
	aux[0]=35;
	aux[1]=37;
	aux[2]=49;
	casilleros[36]=new Pais(36,"Chile",SUDAMERICA,3,aux,this);
	aux=new TPais[4];
	aux[0]=35;
	aux[1]=39;
	aux[2]=38;
	aux[3]=36;
	casilleros[37]=new Pais(37,"Argentina",SUDAMERICA,4,aux,this);
	aux=new TPais[2];
	aux[0]=37;
	aux[1]=39;
	casilleros[38]=new Pais(38,"Uruguay",SUDAMERICA,2,aux,this);
	aux=new TPais[5];
	aux[0]=34;
	aux[1]=40;
	aux[2]=38;
	aux[3]=37;
	aux[4]=35;
	casilleros[39]=new Pais(39,"Brasil",SUDAMERICA,5,aux,this);

	aux=new TPais[5];
	aux[0]=27;
	aux[1]=41;
	aux[2]=44;
	aux[3]=43;
	aux[4]=39;
	casilleros[40]=new Pais(40,"Sahara",AFRICA,5,aux,this);
	aux=new TPais[6];
	aux[0]=1;
	aux[1]=42;
	aux[2]=44;
	aux[3]=40;
	aux[4]=31;
	aux[5]=2;
	casilleros[41]=new Pais(41,"Egipto",AFRICA,6,aux,this);
	aux=new TPais[2];
	aux[0]=41;
	aux[1]=43;
	casilleros[42]=new Pais(42,"Madagascar",AFRICA,2,aux,this);
	aux=new TPais[4];
	aux[0]=40;
	aux[1]=44;
	aux[2]=45;
	aux[3]=42;
	casilleros[43]=new Pais(43,"Zaire",AFRICA,4,aux,this);
	aux=new TPais[4];
	aux[0]=40;
	aux[1]=41;
	aux[2]=45;
	aux[3]=43;
	casilleros[44]=new Pais(44,"Etiopia",AFRICA,4,aux,this);
	aux=new TPais[2];
	aux[0]=43;
	aux[1]=44;
	casilleros[45]=new Pais(45,"Sudafrica",AFRICA,2,aux,this);

	aux=new TPais[2];
	aux[0]=4;
	aux[1]=49;
	casilleros[46]=new Pais(46,"Sumatra",OCEANIA,2,aux,this);
	aux=new TPais[2];
	aux[0]=5;
	aux[1]=49;
	casilleros[47]=new Pais(47,"Borneo",OCEANIA,2,aux,this);
	aux=new TPais[1];
	aux[0]=49;
	casilleros[48]=new Pais(48,"Java",OCEANIA,1,aux,this);
	aux=new TPais[4];
	aux[0]=36;
	aux[1]=46;
	aux[2]=47;
	aux[3]=48;
	casilleros[49]=new Pais(49,"Australia",OCEANIA,4,aux,this);

	CargarCaminos();

};

TableroTEG::~TableroTEG(){
	for(TPais i=0;i<cantPaises;i++){
		delete casilleros[i];
        delete[] caminosEntrePaises[i];
	}
	delete[] casilleros;
	delete[] caminosEntrePaises;
	cantPaises=0;
	casilleros=0;
};

int TableroTEG::CantPaises(){
	return cantPaises;
};
Pais &TableroTEG::operator[](TPais indice){
	return *(casilleros[indice]);
};
Situacion TableroTEG::GetSituacionActual(){
	return SituacionActual;
};
void TableroTEG::SetSituacionActual(Situacion sit){
	SituacionActual=sit;
};



#endif

