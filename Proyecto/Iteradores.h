#ifndef ITERADORES_H_INCLUDED
#define ITERADORES_H_INCLUDED



class TableroTEG::Iterador{
	public:
		TPais posicion;
		virtual void Siguiente()=0;
		virtual bool EsFin()=0;
};

class TableroTEG::IBFS:public Iterador{
    private:
        const set<TPais> *conj;
        bool visitados[CANTPAISES];
        queue<TPais> q;

        void Inicializar(TPais ini){
            posicion=ini;
            for(TPais i=0;i<CANTPAISES;i++)
                visitados[i]=false;
            visitados[posicion]=true;
        };
        void Inicializar(const set<TPais> &ini){
            for(TPais i=0;i<CANTPAISES;i++)
                visitados[i]=false;
            for(set<TPais>::iterator it=ini.begin();it!=ini.end();it++)
                visitados[*it]=true;
        };
    public:
        IBFS(TPais ini){
            Inicializar(ini);
            conj=0;
            for(TPais i=0;i<TEG[ini].CantAdy();i++){
                q.push(TEG[ini].Ady(i));
                visitados[TEG[ini].Ady(i)]=true;
            }
        };
        IBFS(TPais ini,const set<TPais> &s){
            Inicializar(ini);
            conj=&s;
            for(int i=0;i<TEG[ini].CantAdy();i++)
                if(conj->find(TEG[ini].Ady(i))!=conj->end()){//ini pertenece a s
                    q.push(TEG[ini].Ady(i));
                    visitados[TEG[ini].Ady(i)]=true;
                }
        };
        IBFS(const set<TPais> &ini,const set<TPais> &s){
            Inicializar(ini);
            conj=&s;
            for(set<TPais>::iterator it=ini.begin();it!=ini.end();it++)
                for(int i=0;i<TEG[*it].CantAdy();i++)
                    if(visitados[TEG[*it].Ady(i)]==false && conj->find(TEG[*it].Ady(i))!=conj->end()){//ini pertenece a s
                        q.push(TEG[*it].Ady(i));
                        visitados[TEG[*it].Ady(i)]=true;
                    }
        };

		void Siguiente(){
		    posicion=q.front();
		    q.pop();
            for(int i=0;i<TEG[posicion].CantAdy();i++)
                if(visitados[TEG[posicion].Ady(i)]==false && (conj==0 || conj->find(TEG[posicion].Ady(i))!=conj->end())){//ini pertenece a s
                    q.push(TEG[posicion].Ady(i));
                    visitados[TEG[posicion].Ady(i)]=true;
                }
        };
		bool EsFin(){
            if(q.empty())
                return true;
            else
                return false;
        };
};

class TableroTEG::IDFS:public Iterador{
    private:
        const set<TPais> *conj;
        bool visitados[CANTPAISES];
        stack<TPais> p;

        void Inicializar(TPais ini){
            posicion=ini;
            for(TPais i=0;i<CANTPAISES;i++)
                visitados[i]=false;
            visitados[posicion]=true;
        };
    public:
        IDFS(TPais ini){
            Inicializar(ini);
            conj=0;
            for(int i=0;i<TEG[ini].CantAdy();i++){
                p.push(TEG[ini].Ady(i));
                visitados[TEG[ini].Ady(i)]=true;
            }
        };
        IDFS(TPais ini,const set<TPais> &s){
            Inicializar(ini);
            conj=&s;
            for(int i=0;i<TEG[ini].CantAdy();i++)
                if(conj->find(TEG[ini].Ady(i))!=conj->end()){//ini pertenece a s
                    p.push(TEG[ini].Ady(i));
                    visitados[TEG[ini].Ady(i)]=true;
                }
        };
		void Siguiente(){
		    posicion=p.top();
		    p.pop();
            for(int i=0;i<TEG[posicion].CantAdy();i++)
                if(visitados[TEG[posicion].Ady(i)]==false && (conj==0 || conj->find(TEG[posicion].Ady(i))!=conj->end())){//ini pertenece a s
                    p.push(TEG[posicion].Ady(i));
                    visitados[TEG[posicion].Ady(i)]=true;
                }
        };
		bool EsFin(){
            if(p.empty())
                return true;
            else
                return false;
        };
};

class TableroTEG::IBestFS:public Iterador{
    private:
        const set<TPais> *conj;
        bool visitados[CANTPAISES];
        TPais antecesores[CANTPAISES];
        class Comparador{
            public:
                bool (*comparador)(TPais,TPais);
                bool operator()(TPais pri,TPais sec){
                    return comparador(pri,sec);
                };
        } comp;
        priority_queue<TPais,vector<TPais>,Comparador> *pq;

        void Inicializar(TPais ini,bool (*_comparador)(TPais,TPais)){
            comp.comparador=_comparador;
            posicion=ini;
            for(TPais i=0;i<CANTPAISES;i++)
                visitados[i]=false;
            visitados[posicion]=true;
            pq=new priority_queue<TPais,vector<TPais>,Comparador>(comp);
        };

    public:
        TPais antecesor;

        IBestFS(TPais ini,bool (*_comparador)(TPais,TPais)){
            Inicializar(ini,_comparador);
            conj=0;
            for(int i=0;i<TEG[ini].CantAdy();i++){
                pq->push(TEG[ini].Ady(i));
                visitados[TEG[ini].Ady(i)]=true;
                antecesores[TEG[ini].Ady(i)]=ini;
            }
        };
        IBestFS(TPais ini,bool (*_comparador)(TPais,TPais),const set<TPais> &s){
            Inicializar(ini,_comparador);
            conj=&s;
            for(int i=0;i<TEG[ini].CantAdy();i++)
                if(conj->find(TEG[ini].Ady(i))!=conj->end()){//ini pertenece a s
                    pq->push(TEG[ini].Ady(i));
                    visitados[TEG[ini].Ady(i)]=true;
                    antecesores[TEG[ini].Ady(i)]=ini;
                }
        };
		void Siguiente(){
		    posicion=pq->top();
		    pq->pop();
            for(int i=0;i<TEG[posicion].CantAdy();i++)
                if(visitados[TEG[posicion].Ady(i)]==false && (conj==0 || conj->find(TEG[posicion].Ady(i))!=conj->end())){//ini pertenece a s
                    pq->push(TEG[posicion].Ady(i));
                    visitados[TEG[posicion].Ady(i)]=true;
                    antecesores[TEG[posicion].Ady(i)]=posicion;
                }
        };
		bool EsFin(){
            if(pq->empty())
                return true;
            else
                return false;
        };
};




#endif // ITERADORES_H_INCLUDED
