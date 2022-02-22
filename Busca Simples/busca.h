/*
    Algoritmos implementados:
        Busca em Largura
        Busca em Profunidade

    
    Obs.

    Mapeamento de Cores
    -- Branco   -> 0
    -- Cinza    -> 1
    -- Preto    -> 2
*/

#include <limits>
#include <queue>
#include "../Grafo v2/grafo.h"


void bfs(Grafo *g, int id_inicio){
    for (Vertice &v: g->vertices()){
        v.cor = 0;
        v.predecessor = nullptr;
        v.distancia = std::numeric_limits<int>::max();
    }

    std::shared_ptr<Vertice> s = g->getV(id_inicio);

    s->distancia = 0;
    s->cor = 1;
    
    std::queue<std::shared_ptr<Vertice>> q;
    q.push(s);
    
    while (!q.empty()){
        std::shared_ptr<Vertice> u = q.front();
        q.pop();

        ListaEncadeada<Vertice> adj = g->adj(u->id);

        for (No<Vertice> *nv = adj.inicio; nv; nv=nv->proximo){
            if (nv->elemento->cor == 0){
                q.push(nv->elemento);
                nv->elemento->cor = 1;
                nv->elemento->predecessor = u;
                nv->elemento->distancia = u->distancia+1;
            }
        }
        u->cor = 2;
    }
}

void imprimirCaminho(Grafo *g, int id_s, int id_v){
    std::shared_ptr<Vertice> v = g->getV(id_v);

    if (v->id == id_s)
        std::cout << id_s;
    else {
        if (v->predecessor == nullptr)
            std::cout << "Não existe caminho de " << id_s << " para " << id_v << std::endl;
        else
            imprimirCaminho(g,id_s,v->predecessor->id);
            std::cout << " " << id_v;
    }
}

int tempo = 0;

void dfs_visit(Grafo *g, std::shared_ptr<Vertice> v){
    v->cor = 1;
    tempo++;
    v->tempo_descoberta = tempo;

    ListaEncadeada<Vertice> lv = g->adj(v->id);
    No<Vertice> *nv = lv.inicio;

    for (nv; nv; nv=nv->proximo){
        if (nv->elemento->cor == 0){
            nv->elemento->predecessor = v;
            dfs_visit(g,nv->elemento);
        }
    }

    v->cor = 2;
    tempo++;
    v->tempo_fechamento = tempo;
}

void dfs(Grafo *g){
    for (Vertice &v: g->vertices()){
        v.cor = 0;
        v.predecessor = nullptr;
    }
    
    tempo = 0;
    ListaEncadeada<Vertice> lv = g->vertices();
    No<Vertice> *nv = lv.inicio;

    for (nv; nv; nv=nv->proximo){
        if (nv->elemento->cor == 0)
            dfs_visit(g,nv->elemento);
    }
}