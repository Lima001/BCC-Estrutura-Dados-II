#include "grafo.h"

int main(){

    Grafo g = Grafo();

    // Inserção de Vertices
    g.insereV();        // V0
    g.insereV();        // V1
    g.insereV();        // V2
    g.insereV();        // V3
    g.insereV();        // V4

    // Inserção de Arestas
    g.insereA(0,1);     // A0(V0,V1)
    g.insereA(0,2);     // A1(V0,V2)
    g.insereA(0,3);     // A2(V0,V3)
    g.insereA(0,4);     // A3(V0,V4)
    g.insereA(1,2);     // A4(V1,V2)
    g.insereA(1,3);     // A5(V1,V3)
    g.insereA(1,4);     // A6(V1,V4)
    g.insereA(2,3);     // A7(V2,V3)
    g.insereA(2,4);     // A8(V2,V4)
    g.insereA(3,4);     // A9(V3,V4)

    for (Aresta &a: g.arestas())
        std::cout << a.id << ": " << a.custo << std::endl;

    ListaEncadeada<Aresta> la = g.arestas();
    la.inicio->elemento->custo = 1000;

    ListaEncadeada<Vertice> lv = g.vertices();
    lv.inicio->elemento->rank = 25;

    for (Aresta &a: g.arestas()){
        a.v2->rank = 15;
        std::cout << a.id << ": " << a.v1->rank << "/" << a.v2->rank << std::endl;
    }

    for (No<Vertice> *nv = g.lista_vertices.inicio; nv; nv=nv->proximo)
        std::cout << nv->elemento->id << " " << nv->elemento->rank << std::endl; 
    

    return 0;
}