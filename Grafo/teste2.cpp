/*
    Teste para grafos com aresta valoradas

    Teste baseado no grafo valorado utilizado como 1º exemplo durante
    apresentação de slides sobre a unidade 05 - caminhamento. 
*/

#include "grafo.h"

int main(){

    // Criação do grafo
    Grafo g = Grafo();

    // Inserção de 5 vértices - V0 ... V4
    g.insereV();
    g.insereV();
    g.insereV();
    g.insereV();
    g.insereV();

    // Inserção de 6 arestas valoradas - A0 ... V5
    g.insereA(0,1,4);
    g.insereA(0,2,7);
    g.insereA(0,3,6);
    g.insereA(1,2,1);
    g.insereA(1,3,3);
    g.insereA(2,4,3);

    // Exibição da matriz de custo (inicial) do grafo
    g.getMatrizCusto().print();

    return 0;
}