/*
    Teste do algoritmo para verificar se um grafo é conexo
    utilizando a estrutura de conjuntos.
    
    Exemplo do grafo g criado baseado nos slides apresentados
    em aula sobre o tema

    Exemplo do grafo f criado baseado nos slides apresentados
    em aula sobre busca - utilizado em outro teste também!
*/

#include "set.h"

int main(){

    // Grafo não conexo
    Grafo g;

    for (int i=0; i<10; i++)
        g.insereV();

    /*
        a -> 0
        b -> 1
        c -> 2
        d -> 3
        e -> 4
        f -> 5
        g -> 6
        h -> 7
        i -> 8
        j -> 9
    */

    g.insereA(0,1);
    g.insereA(0,2);
    g.insereA(1,2);
    g.insereA(2,3);
    g.insereA(4,5);
    g.insereA(4,6);
    g.insereA(7,8);

    if (verificarConexo(&g))
        std::cout << "G Conexo" << std::endl;
    else
        std::cout << "G Não Conexo" << std::endl;


    // Grafo conexo
    Grafo f;

    for (int i=0; i<8; i++)
        f.insereV();

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

    f.insereA(0,1);
    f.insereA(0,4);
    f.insereA(1,5);
    f.insereA(5,2);
    f.insereA(5,6);
    f.insereA(2,6);
    f.insereA(2,3);
    f.insereA(6,7);
    f.insereA(6,3);
    f.insereA(3,7);

    if (verificarConexo(&f))
        std::cout << "F Conexo" << std::endl;
    else
        std::cout << "F Não Conexo" << std::endl;

    return 0;
}