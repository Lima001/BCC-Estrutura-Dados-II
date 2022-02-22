/*
    Implementação de funções para a estrutura de conjuntos 
    + 
    Funções para verificação de conexidade (usando a estrutura de conjuntos)
*/

#include "../Grafo/grafo.h"

void makeSet(std::shared_ptr<Vertice> v){
    v->predecessor = v;
}

std::shared_ptr<Vertice> findSet(std::shared_ptr<Vertice> v){    
    if (v->predecessor != v)
        v->predecessor = findSet(v->predecessor);
    
    return v->predecessor;
}

void link(std::shared_ptr<Vertice> x, std::shared_ptr<Vertice> y){

    if (x->rank > y->rank)
        y->predecessor = x;
    
    else {
        x->predecessor = y;
        
        if (x->rank == y->rank)
            y->rank++; 
    }
}

void setUnion(std::shared_ptr<Vertice> x, std::shared_ptr<Vertice> y){
    link(findSet(x),findSet(y));
}

void connectedComponents(Grafo *g){
    ListaEncadeada<Vertice> lv = g->vertices();
    ListaEncadeada<Aresta> la = g->arestas();

    No<Vertice> *nv = lv.inicio;
    No<Aresta> *na = la.inicio;

    while (nv){
        makeSet(nv->elemento);
        nv=nv->proximo;
    }
    
    while (na){
        if (findSet(na->elemento->v1) != findSet(na->elemento->v2))
            setUnion(na->elemento->v1, na->elemento->v2);
        
        na=na->proximo;
    }
}

bool sameComponent(std::shared_ptr<Vertice> v, std::shared_ptr<Vertice> u){
    return (findSet(v) == findSet(u));
}

bool verificarConexo(Grafo *g){
    connectedComponents(g);
    
    ListaEncadeada<Vertice> lv = g->vertices();
    
    No<Vertice> *inicio = lv.inicio;
    No<Vertice> *no = inicio->proximo;
    
    while (no){
        if (!sameComponent(inicio->elemento,no->elemento))
            return false;
        
        no=no->proximo;
    }
    
    return true;
}