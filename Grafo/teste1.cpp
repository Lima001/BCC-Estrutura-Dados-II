/*
    Teste das funcionalidades básicas implementadas para
    representar a estrutura de grafo.
*/

#include "grafo.h"

int main(){

    // Criação do Grafo
    // Caso você deseja criar um grafo dirigido, informe true como parâmetro do construtor
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
    
    std::cout << "Ordem: " <<  g.ordem << " Tamanho: " << g.tamanho << std::endl;
    
    std::cout << std::endl;

    std::cout << "Exibindo Vertices..." << std::endl;
    g.vertices().print();
    
    std::cout << std::endl;

    std::cout << "Vertices Adjacentes a V0..." << std::endl;
    g.adj(0).print();

    std::cout << std::endl;
    
    std::cout << "Exibindo Todas as Arestas..." << std::endl;
    g.arestas().print();
    
    std::cout << std::endl;
    
    std::cout << "Aresta entre V0 e V1: " << *(g.getA(0,1)) << std::endl;
    std::cout << "Vértice de id 4: " << *(g.getV(4)) << std::endl;
    std::cout << "Vertice oposto ao vertice 2 pela aresta 8: "<< *(g.oposto(2,8)) << std::endl;
    std::cout << "V0 Grau Entrada: " << g.grauE(0) << " V2 Grau Entrada: " << g.grauE(2) << std::endl;
    std::cout << "V0 Grau Saida: " << g.grauS(0) << " V2 Grau Saida: " << g.grauS(2) << std::endl;

    std::cout << std::endl;

    std::cout << "Arestas de Entrada de V0..." << std::endl;
    for (Aresta &a: g.arestasE(0))
        std::cout << a << std::endl;

    std::cout << std::endl;

    std::cout << "Arestas de Saida de V0..." << std::endl;
    for (Aresta &a: g.arestasS(0))
        std::cout << a << std::endl;

    std::cout << std::endl;

    ParVertice pv1 = g.verticesA(0); 
    ParVertice pv2 = g.verticesA(5);

    std::cout << "ParVertice A0..." << std::endl;
    std::cout << *pv1.v1 << " / " << *pv1.v2 << std::endl;
    std::cout << "ParVertice A5..." << std::endl;
    std::cout << *pv2.v1 << " / " << *pv2.v2 << std::endl;

    std::cout << std::endl;

    std::cout << "Exibindo o grafo pelo método print()" << std::endl;
    g.print();

    std::cout << std::endl;

    std::cout << "Exibindo Matriz de Adjacência do grafo" << std::endl;
    g.getMatrizAdj().print();
    
    return 0;
}