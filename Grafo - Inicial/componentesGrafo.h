#ifndef COMPONENTES_GRAFO_H
#define COMPONENTES_GRAFO_H

#include "listaEncadeada.h"

class Vertice {

    public:

        int id;
        ListaEncadeada<Aresta> lista_arestas;

        Vertice(int id=-1):
            id(id){
        }

        ~Vertice(){
            lista_arestas.~ListaEncadeada();
        }

        friend std::ostream& operator<<(std::ostream &out, const Vertice &v){
            out << "Vertice: " << v.id << " - "
                << "End. Memória: " << v << std::endl;
            return out;
        }

};

class Aresta {

    public:

        int id;
        std::shared_ptr<Vertice> v1;
        std::shared_ptr<Vertice> v2;

        Aresta(int id, std::shared_ptr<Vertice> v1=nullptr, std::shared_ptr<Vertice> v2=nullptr):
            id(id), v1(v1), v2(v2){
        }

        ~Aresta(){
            v1.reset();
            v2.reset();
        }

        friend std::ostream& operator<<(std::ostream &out, const Aresta &a){
            out << "Aresta: " << a.id 
                << " (" << a.v1->id << "," 
                << a.v2->id << ")";
            return out;
        }

};

#endif