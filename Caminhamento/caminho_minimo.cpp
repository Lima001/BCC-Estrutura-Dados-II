/*
    Teste do algoritmo de floyd-warshall para caminhos mínimos.
    Exemplo criado baseado nos slides apresentados em aula sobre o tema
*/
#include "floyd_warshall.h"

int main(){

    Grafo g = Grafo(true);

    for (int i=0; i<5; i++)
        g.insereV();

    g.insereA(0,1,3);
    g.insereA(0,2,8);
    g.insereA(0,4,-4);
    g.insereA(1,3,1);
    g.insereA(1,4,7);
    g.insereA(2,1,4);
    g.insereA(3,0,2);
    g.insereA(3,2,-5);
    g.insereA(4,3,6);

    RetornoFloydWarshall r = floydWarshall(&g);

    std::cout << "Matriz Caminho Mínimo" << std::endl;
    r.custo_minimo.print();

    std::cout << std::endl;

    std::cout << "Matriz Predecessor" << std::endl;
    r.predecessor.print();

    std::cout << std::endl;

    std::cout << "Caminho Mínimo de 0 a 0" << std::endl;
    printMenorCaminho(&r.predecessor,0,0);
    
    std::cout << std::endl;

    std::cout << "Caminho Mínimo de 0 a 2" << std::endl;
    printMenorCaminho(&r.predecessor,0,2);
    
    std::cout << std::endl;

    return 0;
}