/*
    Conforme discutido com o professor no último encontro,
    pretendia implementar uma estrutura de heap para criar uma
    fila de prioridades capaz de ser atualizada.

    Todavia tive alguns problemas, muito relacionado com a complexidade
    em integrar o código da estrutura de grafos já existente com as
    necessidades a estrutura e algoritmo de heap.

    Para não deixar o algortimo de prim com aquele problema que mostrei na 
    última aula (após cada iteração, ter que limpar e reinserir os itens na fila
    de prioridade), eu dei uma pesquisada em uma solução usando os recursos da STL
    do C++.

    Eu vi que a priority_queue usava por debaixo dos panos um vector transformado em heap,
    e mantinha as propriedades do heap usando funções da STL para isso. Confesso que não
    compreendi o porque da estrutura não conseguir utilizar os valores do vértices atualizados
    já que opera com heap... Não sei se tem haver com o modo que implementei as estruturas do grafo,
    ou se a priority_queue não trabalha com update de valores... Fica um ponto para eu ir atrás.

    Mas resumindo, ao invés de usar a priority_queue, eu fui direto para o uso de vector e das funções
    para criar e manter um heap oferecidas pela linguagem (e usadas por baixo dos panos da fila
    de prioridade como mencionado) manualmente.
*/

#include <algorithm>
#include <vector> 
#include "../Grafo/grafo.h"

// Função para comparação de valores - usado para definir como o heap estará organizado
// (Min-heap - que nos interessa - ou Max-heap)
bool function(const std::shared_ptr<Vertice> &v1, const std::shared_ptr<Vertice> &v2){
    return v1->chave >= v2->chave;
}

// Ponteiro para função que irá receber a função function. Usado pelas funções
// da STL que operam sobre o heap
bool (*foo)(const std::shared_ptr<Vertice>&, const std::shared_ptr<Vertice>&);

void prim(Grafo *g, int id_raiz){
    // Criação do vetor que será utilizado como heap
    std::vector<std::shared_ptr<Vertice>> q;
    
    // Fazendo o ponteiro de função referenciar uma função válida
    foo = &function;
    

    // Configuração inicial dos vértices conforme algoritmo de prim
    No<Vertice> *nv;
    
    for (nv=g->lista_vertices.inicio; nv; nv=nv->proximo){
        nv->elemento->chave = std::numeric_limits<double>::infinity();
        // Inserção dos vértices no vector
        q.push_back(nv->elemento);
    }

    // Configuração do vértice usado como raiz da árvore
    std::shared_ptr<Vertice> raiz = g->lista_vertices.getById(id_raiz);
    raiz->chave = 0;
    raiz->predecessor = nullptr;

    // Criação de um heap sobre o vector (do início ao fim), utilizando
    // a função function (passada via o ponteiro foo) para organização em Min-heap 
    std::make_heap(q.begin(),q.end(),foo);

    std::shared_ptr<Vertice> tmp;

    // Execução do laço principal do algoritmo de prim
    while(!q.empty()){
        // "Pegando o topo da fila de prioridade"...
        // No caso como o vetor é um heap mínimo, basta pegar
        // o primeiro elemento que esse será o menor.
        tmp = q.front();
        tmp->visitado = true;

        // Calculando os atributos para vértices adjacentes ao vértice retirado da "fila de prioridade"
        for (Vertice &v: g->adj(tmp->id)){
            std::shared_ptr<Aresta> a = g->getA(tmp->id, v.id);

            if (!v.visitado && a->custo < v.chave){
                v.predecessor = tmp;
                v.chave = a->custo;
            }
        }

        // Remoção do elemento de menor valor do heap.
        // Por valor, entenda o atributo "chave" de um vértice.
        // Obs. pop_heap() remove do heap criado mantendo as propriedades
        // desse mesmo heap, mas o elemento ainda está presente no conteiner
        // cujo o heap foi montado... No caso, o elemento é passado para a
        // última posição do vector.
        std::pop_heap(q.begin(),q.end(),foo);
        
        // Remoção do elemento de menor valor (que acabou de ser usado no algoritmo)
        // que encontra-se no fim do vector
        q.pop_back();
    }
}