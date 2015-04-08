#ifndef GRAFOACICLICO_H_INCLUDED
#define GRAFOACICLICO_H_INCLUDED

#include <cassert>
#include <map>
#include <list>

template <typename V, typename C>
class GrafoAciclico{
public:
	GrafoAciclico();
	~GrafoAciclico();

    //observadores:
    bool estaVacio();
    int Orden();
    int Tamano();
	bool existeVertice(const V &id);
	bool existeArco(const V &origen,const V &destino);


	void devolverVertices(list<V> & vertices);
	void devolverAdyacentes(const V &origen, list<pair<V, C> > & adyacentes);
    C & costoArco(const V &origen,const V &destino);

    //modificadores:
	void agregarVertice(const V & vertice);
        //poscondicion: true: el grafo se mantiene aciclico, se agrega corectamente el arco
        //              false: no se puede agregar el arco porque el grafo deja de ser aciclico
	bool agregarArco(const V &origen,const V &destino, const C & costo);
	void eliminarVertice(const V &id);
	void eliminarArco(const V &origen,const V &destino);

	void limpiar();

private:
    map<V, map<V, C> > arcosDestino;
	map<V, map<V, C> > arcos;

};




//implementaciones:


template <typename V, typename C>
GrafoAciclico<V,C>::GrafoAciclico()
{
}

template <typename V, typename C>
GrafoAciclico<V,C>::~GrafoAciclico()
{
}

template <typename V, typename C>
bool GrafoAciclico<V,C>::estaVacio(){
    return arcos.empty();
};

template <typename V, typename C>
void GrafoAciclico<V,C>::limpiar(){
    arcosDestino.clear();
    arcos.clear();
};

template <typename V, typename C>
int GrafoAciclico<V,C>::Orden()
{
    int orden=0;
    for(typename map<V,map<V,C> >::const_iterator im=arcos.begin();im!=arcos.end();im++)
       orden++;
    return orden;
}
template <typename V, typename C>
int GrafoAciclico<V,C>::Tamano()
{
    int tamano=0;
    for(typename map<V,map<V,C> >::const_iterator im=arcos.begin();im!=arcos.end();im++)
        for(typename map<V,C> ::const_iterator imm=im->second.begin();imm!=im->second.end();imm++)
            tamano++;
    return tamano;
}

template <typename V, typename C>
bool GrafoAciclico<V,C>::existeVertice(const V &id)
{
	typename map<V, map<V,C> >::const_iterator vertice = arcos.find(id);
	return (vertice != arcos.end());
}


template <typename V, typename C>
bool GrafoAciclico<V,C>::existeArco(const V &origen,const V &destino)
{
	if(existeVertice(origen) && existeVertice(destino)){
        typename map<V, map<V, C> >::const_iterator adyMap = arcos.find(origen);
        typename map<V, C>::const_iterator arco = adyMap->second.find(destino);
        return (arco != adyMap->second.end());
	}else
        return false;
}


template <typename V, typename C>
void GrafoAciclico<V,C>::devolverVertices(list<V> & resultado)
{
	resultado.clear();
	typename map<V, map<V,C> >::iterator vertice = arcosDestino.begin();
	while (vertice != arcosDestino.end()) {
	    if((vertice->second).size()==0)
            resultado.push_back(vertice->first);
		vertice++;
	}
}

template <typename V, typename C>
void GrafoAciclico<V,C>::devolverAdyacentes(const V &origen, list<pair<V, C> > & adyacentes)
{
    adyacentes.clear();
	if(existeVertice(origen)){
        typename map<V, map<V, C> >::const_iterator adyMap = arcos.find(origen);
        if (adyMap != arcos.end()) {
            typename map<V, C>::const_iterator adyacente = adyMap->second.begin();
            while (adyacente != adyMap->second.end()) {
                adyacentes.push_back(*adyacente);
                adyacente++;
            }
        }
	}
};


template <typename V, typename C>
C & GrafoAciclico<V,C>::costoArco(const V &origen,const V &destino)
{
	assert(existeArco(origen, destino));
	return arcos.find(origen)->second.find(destino)->second;
}

template <typename V, typename C>
void GrafoAciclico<V,C>::agregarVertice(const V &id)
{
	arcos[id];
	arcosDestino[id];
}

template <typename V, typename C>
void GrafoAciclico<V,C>::eliminarVertice(const V &id)
{
	arcos.erase(id);
    arcosDestino.erase(id);

	typename map<V, map<V,C> >::iterator vertice = arcos.begin();
	while (vertice != arcos.end()) {
		vertice->second.erase(id);
		vertice++;
	}
	vertice = arcosDestino.begin();
	while (vertice != arcosDestino.end()) {
		vertice->second.erase(id);
		vertice++;
	}
}


template <typename V, typename C>
bool GrafoAciclico<V,C>::agregarArco(const V &origen,const V &destino, const C & costo)
{
    if(existeVertice(origen) && existeVertice(destino)){
        arcos[origen][destino] = costo;
        arcosDestino[destino][origen] = costo;
        return true;
    }else
        return false;
}

template <typename V, typename C>
void GrafoAciclico<V,C>::eliminarArco(const V &origen,const V &destino)
{
	typename map<V, map<V, C> >::iterator adyMap = arcos.find(origen);
	if (adyMap != arcos.end()) {
		adyMap->second.erase(destino);
	}
	adyMap = arcosDestino.find(destino);
	if (adyMap != arcosDestino.end()) {
		adyMap->second.erase(origen);
	}
}


#endif // GRAFOACICLICO_H_INCLUDED

