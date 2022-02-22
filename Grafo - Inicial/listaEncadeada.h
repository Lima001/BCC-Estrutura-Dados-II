#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <iostream>
#include <memory>
#include <assert.h>

class Aresta;
class Vertice;

template <typename T>
class No {

    public:

        std::shared_ptr<T> elemento;
        No<T> *proximo;
        No<T> *anterior;

        No():
            elemento(nullptr), proximo(nullptr), anterior(nullptr){
        }

        No(std::shared_ptr<T> elemento, No<T> *proximo=nullptr, No<T> *anterior=nullptr):
            elemento(elemento), proximo(proximo), anterior(anterior){
        }

        ~No(){
            // Aqui encontrava-se um dos motivos para o erro discutido...
            // Posso explicar melhor presencialmente em nossa aula de sexta-feira
            //elemento->~T();
            return;
        }

};

/*
    classe Iterator criada para ser utilizada em conjunto da classe
    de ListaEncadeada, permitindo que essa seja iterável. 
*/
template <typename T>
class Iterator {

    private:

        No<T> *ptr;

    public:

        Iterator(No<T> *n = nullptr):
            ptr(n){
        }

        T& operator*() const {
            return *(ptr->elemento);
        }

        No<T>* operator->() const {
            return ptr;
        } 

        Iterator& operator++() {
            ptr = ptr->proximo;
            return *this;
        }

        Iterator operator++(int) {
            No<T> *tmp = ptr;
            ++(*this);
            return Iterator(tmp);
        }

        bool operator==(const Iterator &t) const {
            return t.ptr == this->ptr;
        }

        bool operator!=(const Iterator &t) const {
            return t.ptr != this->ptr;
        }
};

template <typename T>
class ListaEncadeada {

    public:

        int tamanho;
        No<T> *inicio;
        No<T> *fim;

        ListaEncadeada():
            tamanho(0), inicio(nullptr), fim(nullptr){
        }

        ~ListaEncadeada(){
            No<T> *tmp = inicio;
            while (tmp){
                tmp = tmp->proximo;
                delete inicio;
                inicio = tmp;
            }
        }

        void inserirNo(std::shared_ptr<T> elemento){
            if (!inicio){
                inicio = new No<T>(elemento);
                fim = inicio;
            }
            else {
                No<T> *tmp = fim;
                fim = new No<T>(elemento,nullptr,tmp);
                tmp->proximo = fim; 
            }
            tamanho++;
        }

        std::shared_ptr<T> getById(int id_elemento){
            No<T> *tmp;
            for (tmp=inicio; tmp && tmp->elemento->id != id_elemento; tmp=tmp->proximo);
            assert(tmp);
            return tmp->elemento;
        }

        void print(){
            No<T> *tmp;
            for (tmp=inicio; tmp; tmp=tmp->proximo)
                std::cout << *(tmp->elemento) << std::endl;
        }

        Iterator<T> begin(){
            return Iterator<T>(inicio);
        }

        Iterator<T> end(){
            return Iterator<T>(fim->proximo);
        }

};

#endif