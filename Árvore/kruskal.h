#include "../Grafo/grafo.h"
#include "../Conexidade/set.h"

// Implementação do algoritmo de Kruskal
Grafo kruskal(Grafo *g){
    // Grafo para armazenar a estrutura da árvore
    Grafo arvore;
    
    No<Vertice> *nv = g->lista_vertices.inicio;
    
    for (nv; nv; nv=nv->proximo){
        makeSet(nv->elemento);              // Criando os diversos conjuntos - floresta
        
        /*
            Usei um método auxiliar para inserir os vértices na árvore.
            Anteriormente estava usando o método insereV, que insere
            vértices com id sequencial começando em 0.

            Como a lista de vértices do grafo G não estava considerando
            remoções, não tinha problema em usar esse método, pois ao fim
            teria uma árvore com os 'mesmos' vértices que o grafo G.

            Porém, considerando remoção de vértices, eu preciso de um método
            que insere vértices com o mesmo id na árvore conforme o grafo G,
            pois o id é importante posteriormente para inserção de arestas.

            Caso contrário, eu poderia ter um vertice id 6 no grafo G na 5ª
            posição da lista de vertices, porém na hora da inserção usando
            insereV como estou dentro de um laço, eu estaria executando
            o método pela 5ª vez e isso iria inserir o vertice de id 4...
            causando problemas no algoritmo posteriormente. 
        */
        arvore.insereCopiaV(nv->elemento);  // Inserção de Vertices na árvore
    }
    
    /*
        Ordenação das arestas em ordem crescente
    
        Pretendia implementar um algoritmo mais eficiente, como um mergeSort,
        porém tive alguns problemas com a complexidade do código, tomando o fato
        de estar lidando com listas encadeadas e shared_ptr.

        Por fim percebi que fazendo os devidos ajustes para o mergeSort operar
        considerando a complexidade do código atual, eu teria uma perda de desempenho
        no algoritmo que não compensaria implementá-lo.

        Por isso deixei uma espécie de selectSort, criando uma nova lista encadeada
        com as Arestas ordenadas
    */
    ListaEncadeada<Aresta> la = g->arestas();
    ListaEncadeada<Aresta> la_ordenada;
    
    No<Aresta> *na = la.inicio;
    No<Aresta> *na_menor;
    double menor;

    for (int i=0; i<la.tamanho; i++){

        menor = std::numeric_limits<double>::infinity();

        for (na=la.inicio; na; na=na->proximo){
            if (!na->elemento->visitada && na->elemento->custo < menor){
                menor = na->elemento->custo;
                na_menor = na;
            }
        }

        la_ordenada.inserirNo(na_menor->elemento);
        
        // Elementos visitados não podem mais serem usados como "menor" valor para comparação.
        // Usei essa flag para evitar ter que ficar modificando a estrutura da lista encadeada
        // e apenas realizar inserções em uma nova lista ordenada.
        na_menor->elemento->visitada = true;
    }

    na = la_ordenada.inicio;

    // Geração da ávore - união dos conjuntos
    for (na; na; na=na->proximo){
        if (findSet(na->elemento->v1) != findSet(na->elemento->v2)){
            setUnion(na->elemento->v1, na->elemento->v2);
            arvore.insereA(na->elemento->v1->id,na->elemento->v2->id);
        }
    }

    return arvore;
}