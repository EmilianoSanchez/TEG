#ifndef ALGORITMOSSOBRECONJUNTOSYARREGLOS_H_INCLUDED
#define ALGORITMOSSOBRECONJUNTOSYARREGLOS_H_INCLUDED


#include "Arreglo.h"


//cargadores de conjuntos y arreglos:
void PaisesJugador(TJugador j,set<TPais> &s);//
void PaisesContinente(TContinente c,set<TPais> &s);
void PaisesJugador(TJugador j,Arreglo &a);
void PaisesContinente(TContinente c,Arreglo &a);
void PaisesAdyacentesEnemigos(TPais p,Arreglo &a);

//operadores sobre conjuntos:
void Union(const set<TPais> &s1,const set<TPais> &s2,set<TPais> &r);
void Interseccion(const set<TPais> &s1,const set<TPais> &s2,set<TPais> &r);
void Complemento(const set<TPais> &s,set<TPais> &r);
void Diferencia(const set<TPais> &s1,const set<TPais> &s2,set<TPais> &r);

//Conversores:
void Conjunto_a_arreglo(const set<TPais> &conj,Arreglo &a);
void Arreglo_a_conjunto(const Arreglo &a,set<TPais> &conj);




//implementaciones:

void Conjunto_a_arreglo(const set<TPais> &conj,Arreglo &a){
    //a.Desalocar();
    a.cant=conj.size();
    //a.paises=new TPais[a.cant];
    int i=0;
    for(set<TPais>::iterator it=conj.begin();it!=conj.end();it++){
        a[i]=*it;
        i++;
    }
};
void Arreglo_a_conjunto(const Arreglo &a,set<TPais> &conj){
    conj.clear();
    for(int i=0;i<a.cant;i++)
        conj.insert(a[i]);
};


void Union(const set<TPais> &s1,const set<TPais> &s2,set<TPais> &r){
     r.clear();
    set<TPais>::iterator __first1=s1.begin(),__last1=s1.end(),__first2=s2.begin(),__last2=s2.end();
      while (__first1 != __last1 && __first2 != __last2) {
    if (*__first1 < *__first2) {
      r.insert(*__first1);
      ++__first1;
    }
    else if (*__first2 < *__first1) {
      r.insert(*__first2);
      ++__first2;
    }
    else {
      r.insert(*__first1);
      ++__first1;
      ++__first2;
    }
  }
  while(__first1 != __last1 ){
    r.insert(*__first1);
    ++__first1;
  }
  while(__first2 != __last2 ){
    r.insert(*__first2);
    ++__first2;
  }
};

void Interseccion(const set<TPais> &s1,const set<TPais> &s2,set<TPais> &r){
    r.clear();
    set<TPais>::iterator __first1=s1.begin(),__last1=s1.end(),__first2=s2.begin(),__last2=s2.end();
  while (__first1 != __last1 && __first2 != __last2)
    if (*__first1 < *__first2)
      ++__first1;
    else if (*__first2 < *__first1)
      ++__first2;
    else {
      r.insert(*__first1);
      ++__first1;
      ++__first2;
    }
};

void Diferencia(const set<TPais> &s1,const set<TPais> &s2,set<TPais> &r){
    r.clear();
    set<TPais>::iterator __first1=s1.begin(),__last1=s1.end(),__first2=s2.begin(),__last2=s2.end();
  while (__first1 != __last1 && __first2 != __last2){
    if (*__first1 < *__first2){
       r.insert(*__first1);
      ++__first1;
    }else if (*__first2 < *__first1)
      ++__first2;
    else {
      ++__first1;
      ++__first2;
    }
  }
  while (__first1 != __last1){
       r.insert(*__first1);
      ++__first1;
  }
};

void Complemento(const set<TPais> &s,set<TPais> &r){
    r.clear();
    set<TPais>::iterator first=s.begin(),last=s.end();
    TPais i=0;
    while(first!=last){
        while(i!=*first){
            r.insert(i);
            i++;
        }
        first++;
        i++;
    }
    while(i!=CANTPAISES){
        r.insert(i);
        i++;
    }
};

void PaisesJugador(TJugador j,set<TPais> &s){
    s.clear();
    for(TPais i=PRIMERPAIS;i<CANTPAISES;i++)
        if(TEG[i].Ocupante()==j)
            s.insert(i);
};
void PaisesJugador(TJugador j,Arreglo &a){
    a.cant=Jugadores[j]->CantPaises();
    //a.paises=new TPais[a.cant];
    int p=0;
    for(TPais i=PRIMERPAIS;i<CANTPAISES;i++)
        if(TEG[i].Ocupante()==j){
            a[p]=i;
            p++;
        }
};

void PaisesAdyacentesEnemigos(TPais p,Arreglo &a){
    int j=0;
    for(int i=0;i<TEG[p].CantAdy();i++)
        if(TEG[TEG[p].Ady(i)].Ocupante()!=TEG[p].Ocupante()){
            a.paises[j]=TEG[p].Ady(i);
            j++;
        }
    a.cant=j;
};
void PaisesContinente(TContinente c,Arreglo &a){
    int i=0;
    for(TPais p=0;p<CANTPAISES;p++)
        if(TEG[p].Continente()==c){
            a.paises[i]=p;
            i++;
        }
    a.cant=i;
};
void PaisesContinente(TContinente c,set<TPais> &s){
    s.clear();
    for(TPais i=PRIMERPAIS;i<CANTPAISES;i++)
        if(TEG[i].Continente()==c)
            s.insert(i);
};

#endif // ALGORITMOSSOBRECONJUNTOSYARREGLOS_H_INCLUDED
