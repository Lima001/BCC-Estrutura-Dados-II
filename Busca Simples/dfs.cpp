/*
    Teste do algoritmo de busca em profunidade.
    Exemplo criado baseado nos slides apresentados
    em aula sobre o tema
*/

#include "busca.h"

int main(){

    Grafo g = Grafo(true);

    for (int i=0; i<6; i++)
        g.insereV();

    /*
        V0 -> u
        V1 -> v
        V2 -> w
        V3 -> x
        V4 -> y
        V5 -> z
    */

    g.insereA(0,1);
    g.insereA(1,4);
    g.insereA(4,3);
    g.insereA(0,3);
    g.insereA(3,1);
    g.insereA(2,4);
    g.insereA(2,5);
    g.insereA(5,5);

    dfs(&g);

    std::cout << "IdVertice: (TempoDescoberta; TempoFechamento)" << std::endl;
    for (Vertice &v: g.vertices())
        std::cout << v.id << ": (" << v.tempo_descoberta << "; " << v.tempo_fechamento << ")" << std::endl;

    std::cout << std::endl;

    std::cout << "Vertice Inicial -> V0" << std::endl;
    for (Vertice &v: g.vertices()){
        if (v.id != 0){
            std::cout << "Caminho entre V0 para V" << v.id << std::endl;
            imprimirCaminho(&g,0,v.id);
            std::cout << std::endl; 
        }
    }

    return 0;
}