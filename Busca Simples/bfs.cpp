/*
    Teste do algoritmo de busca em largura.
    Exemplo criado baseado nos slides apresentados
    em aula sobre o tema
*/

#include "busca.h"

int main(){

    Grafo g = Grafo();

    for (int i=0; i<8; i++)
        g.insereV();

    /*

        Mapeamento de vertices

        V0 -> r
        V1 -> s
        V2 -> t
        V3 -> u
        V4 -> v
        V5 -> w
        V6 -> x
        V7 -> y
        V8 -> z
    */

    g.insereA(0,1);
    g.insereA(0,4);
    g.insereA(1,5);
    g.insereA(5,2);
    g.insereA(5,6);
    g.insereA(2,6);
    g.insereA(2,3);
    g.insereA(6,7);
    g.insereA(6,3);
    g.insereA(3,7);

    //g.print();
    // Busca considerando o vértice V1 como inicial
    bfs(&g,1);

    std::cout << "Vertice Inicial -> V1\n" << std::endl;

    for (Vertice &v: g.vertices()){
        if (v.id != 1){
            std::cout << "Caminho entre V1 para V" << v.id << std::endl;
            imprimirCaminho(&g,1,v.id);
            std::cout << std::endl; 
        }
    }

    return 0;
}