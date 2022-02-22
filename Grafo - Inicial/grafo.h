#ifndef GRAFO_H
#define GRAFO_H

#include <assert.h>
#include <memory>
#include <iostream>
#include <unordered_map>

#include "componentesGrafo.h"

/*
    Definição de uma struct auxiliar para ser utilizada
    como tipo de retorno no método verticesA()
*/
typedef struct {
    std::shared_ptr<Vertice> v1;
    std::shared_ptr<Vertice> v2;
} ParVertice;


class Grafo {

    public:

        int ordem;
        int tamanho;
        int dirigido;
        ListaEncadeada<Vertice> lista_vertices;

    public:

        Grafo(int dirigido=0):
            ordem(0), tamanho(0), dirigido(dirigido){
        }

        ~Grafo(){
            No<Vertice> *tmp = lista_vertices.inicio;
            
            while (tmp){
                tmp = tmp->proximo;
                lista_vertices.inicio->elemento->~Vertice();
                
                delete lista_vertices.inicio;
                
                lista_vertices.inicio = tmp;
            }
        }

        int getOrdem(){
            return ordem;
        }

        int getTamanho(){
            return tamanho;
        }
        
        ListaEncadeada<Vertice>& vertices(){
            return lista_vertices;
        }

        ListaEncadeada<Aresta> arestas(){
            /*
                Para garantir que cada aresta seja inserida
                na lista encadeada de retorno apenas uma única
                vez, é utilizado um hashmap como auxiliar.

                As chaves correspondem ao id de cada aresta,
                e o valor (será sempre true, pois o par chave-valor
                só é criado na hora de inserir uma nova aresta na
                lista) denota se a aresta foi inserida na lista.
            */

            ListaEncadeada<Aresta> l;
            std::unordered_map<int, bool> hash;

            No<Vertice> *nv;
            No<Aresta> *na;

            // Percorre todas as listas de arestas para cada vertice do grafo
            for (nv=lista_vertices.inicio; nv; nv=nv->proximo){
                for (na=nv->elemento->lista_arestas.inicio; na; na=na->proximo){
                    // Se o id da aresta não está no hash, essa não foi inserida na lista de retorno ainda
                    if (hash.find(na->elemento->id) == hash.end()){
                        l.inserirNo(na->elemento);
                        hash[na->elemento->id] = true;
                    }
                }
            }

            return l;
        }
        
        void insereV(){
            std::shared_ptr<Vertice> novo_vertice = std::make_shared<Vertice>(Vertice(ordem));
            lista_vertices.inserirNo(novo_vertice);
            ordem++;
        }
        
        // Modificar para Digrafos
        void insereA(int u, int j){
            std::shared_ptr<Vertice> vu = getV(u);
            std::shared_ptr<Vertice> vj = getV(j);

            std::shared_ptr<Aresta> nova_aresta = std::make_shared<Aresta>(Aresta(tamanho, vu, vj));
            
            vu->lista_arestas.inserirNo(nova_aresta);
            vj->lista_arestas.inserirNo(nova_aresta);

            tamanho++;
        }

        // Modificar para Digrafos?
        ListaEncadeada<Vertice> adj(int id_vertice){
            std::shared_ptr<Vertice> v = lista_vertices.getById(id_vertice);
            ListaEncadeada<Vertice> l;

            No<Aresta> *na;

            for (na=v->lista_arestas.inicio; na; na=na->proximo){
                if (na->elemento->v1->id == id_vertice)
                    l.inserirNo(na->elemento->v2);
                else if (na->elemento->v2->id == id_vertice)
                    l.inserirNo(na->elemento->v1);
            }

            return l;
        }

        // Modificar para Digrafos
        std::shared_ptr<Aresta> getA(int id_v1, int id_v2){
            std::shared_ptr<Vertice> v1 = lista_vertices.getById(id_v1);
            No<Aresta> *na;

            for (na=v1->lista_arestas.inicio; na; na=na->proximo){
                if (na->elemento->v1->id == id_v2 || na->elemento->v2->id == id_v2)
                    return na->elemento;
            }
            return nullptr;
        }

        std::shared_ptr<Vertice> getV(int id_vertice){
            return lista_vertices.getById(id_vertice);
        }
        
        // Modificar para Digrafos
        int grau(int id_vertice){
            std::shared_ptr<Vertice> v = lista_vertices.getById(id_vertice);
            return v->lista_arestas.tamanho;
        }
        
        // Modificar para Digrafos
        ParVertice verticesA(int id_aresta){
            ParVertice pv;
            No<Vertice> *nv;
            No<Aresta> *na;
            
            for (nv=lista_vertices.inicio; nv; nv=nv->proximo){
                for (na=nv->elemento->lista_arestas.inicio; na && na->elemento->id != id_aresta; na=na->proximo);   
                if (na){
                    pv.v1 = na->elemento->v1;
                    pv.v2 = na->elemento->v2;
                    return pv;
                }
            }
            pv.v1 = nullptr;
            pv.v2 = nullptr;
            return pv;
        }
        
        // Modificar para Digrafos
        std::shared_ptr<Vertice> oposto(int id_vertice, int id_aresta){
            std::shared_ptr<Vertice> v = lista_vertices.getById(id_vertice);
            std::shared_ptr<Aresta> a = v->lista_arestas.getById(id_aresta);
            
            if (a->v1->id == id_vertice)
                return a->v2;
            else if (a->v2->id == id_vertice)
                return a->v2;
            
            assert(false);
        }
        
        // Modificar para Digrafos?
        ListaEncadeada<Aresta>& arestas(int id_vertice){
            std::shared_ptr<Vertice> v = lista_vertices.getById(id_vertice);
            return v->lista_arestas;
        }

        void print(){
            No<Vertice> *nv;
            No<Aresta> *na;

            std::cout << "<<< Grafo >>>" << std::endl;

            for (nv=lista_vertices.inicio; nv; nv=nv->proximo){
                std::cout << "Vertice " << nv->elemento->id << std::endl;
                for (na=nv->elemento->lista_arestas.inicio; na; na=na->proximo)
                    std::cout << "->\t" << *(na->elemento) << std::endl;
            }
        }

        void getMatriz(){};
};

#endif