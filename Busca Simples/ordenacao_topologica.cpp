/*
    Teste do algoritmo de ordenação topológica.
    Exemplo criado baseado nos slides apresentados
    em aula sobre o tema.

    Obs.

    Ao invés de usar uma lista encadeada para ir armazenando
    os vértices que já tiveram o tempo de fechamento calculados,
    eu decidi usar uma pilha.

    Sendo assim basta eu imprimir os vértices conforme esses são
    retirados da pilha.
*/

#include "../Grafo v2/grafo.h"
#include <stack>

/*
    Adaptação do algoritmo para funcionar com a ordenação topológica
*/

int tempo = 0;

void dfs_visit(Grafo *g, std::shared_ptr<Vertice> v, std::stack<std::shared_ptr<Vertice>> *sv){
    v->cor = 1;
    tempo++;
    v->tempo_descoberta = tempo;

    ListaEncadeada<Vertice> lv = g->adj(v->id);
    No<Vertice> *nv = lv.inicio;

    for (nv; nv; nv=nv->proximo){
        if (nv->elemento->cor == 0){
            nv->elemento->predecessor = v;
            dfs_visit(g,nv->elemento,sv);
        }
    }

    v->cor = 2;
    tempo++;
    v->tempo_fechamento = tempo;
    sv->push(v);                    // Modificação realizada -> inclusão do vértice (visitado) na pilha
}

void dfs(Grafo *g, std::stack<std::shared_ptr<Vertice>> *sv){
    for (Vertice &v: g->vertices()){
        v.cor = 0;
        v.predecessor = nullptr;
    }
    
    tempo = 0;
    ListaEncadeada<Vertice> lv = g->vertices();
    No<Vertice> *nv = lv.inicio;

    for (nv; nv; nv=nv->proximo){
        if (nv->elemento->cor == 0)
            dfs_visit(g,nv->elemento,sv);
    }
}

void ordenacaoTopologica(Grafo *g){
    assert(g->dirigido == true);
    
    std::stack<std::shared_ptr<Vertice>> ordenacao;
    dfs(g,&ordenacao);

    while (!ordenacao.empty()){
        std::cout << *(ordenacao.top()) << std::endl;
        ordenacao.pop();
    }
    
}

int main(){

    Grafo g = Grafo(true);

    /*
        Cuecas      -> 0
        Calça       -> 1
        Cinto       -> 2
        Camisa      -> 3
        Gravata     -> 4
        Paletó      -> 5
        Meias       -> 6
        Sapatos     -> 7
        Relógio     -> 8
    */

    g.insereV();
    g.insereV();
    g.insereV();
    g.insereV();
    g.insereV();
    g.insereV();
    g.insereV();
    g.insereV();
    g.insereV();

    g.insereA(0,1);
    g.insereA(1,2);
    g.insereA(2,5);
    g.insereA(3,2);
    g.insereA(3,4);
    g.insereA(4,5);
    g.insereA(0,7);
    g.insereA(1,7);
    g.insereA(6,7);

    ordenacaoTopologica(&g);

    return 0;
}