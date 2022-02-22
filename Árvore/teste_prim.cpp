/*
    Teste desenvolvido conforme exemplo apresentado na aula sobre Árvores.
*/

#include "prim.h"

int main(){

    // Criação do grafo (não dirigido)
    Grafo g = Grafo();

    // Inserção de vértices
    for (int i=0; i<9; i++)
        g.insereV();

    /*
        Mapeamento lógico dos vértices do exemplo para os vértices do grafo G
        a -> V0
        b -> V1
        c -> V2
        d -> V3
        e -> V4
        f -> V5
        g -> V6
        h -> V7
        i -> V8
    */
    
    // Inserção das arestas
    g.insereA(0,1,4);       // A0
    g.insereA(1,2,8);       // A1
    g.insereA(2,3,7);       // A2
    g.insereA(3,4,9);       // A3
    g.insereA(4,5,10);      // A4
    g.insereA(5,6,2);       // A5
    g.insereA(6,7,1);       // A6
    g.insereA(7,0,8);       // A7
    g.insereA(2,8,2);       // A8
    g.insereA(2,5,4);       // A9
    g.insereA(3,5,14);      // A10
    g.insereA(6,8,6);       // A11
    g.insereA(7,8,7);       // A12
    g.insereA(7,1,11);      // A13

    // Execução do algoritmo de prim considerando como raiz o vértice V0 (a)
    prim(&g,0);

    // Como o resultado do algoritmo é armazenado nos atributos do vértice,
    // abaixo é exibido o vértice (id), seu predecessor e sua chave
    for (Vertice &v: g.lista_vertices){
        std::cout << v.id << ":";
        if (v.predecessor)
            std::cout << " Predecessor - " << v.predecessor->id;
        std::cout << " Chave - " << v.chave << std::endl;
    }

    return 0;
}