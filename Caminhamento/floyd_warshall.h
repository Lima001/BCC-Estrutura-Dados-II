/*
    Implementação do algoritmo de Floyd-Warshall para caminhos mínimos.
*/

#include "../Grafo v2/grafo.h"

// Retorno das matrizes obtidas com a execução do algoritmo
typedef struct {
    Matriz<double> custo_minimo;
    Matriz<int> predecessor;
} RetornoFloydWarshall;

// Função auxiliar para achar o valor mínimo entre 'a' e 'b'
double min(double a, double b){    
    if (a <= b)
        return a;
    return b;
}

RetornoFloydWarshall floydWarshall(Grafo *g){

    // Inicialização das matrizes de Custo
    Matriz<double> d = g->getMatrizCusto();
    // Matriz de custo temporaria - constantemente modificada
    Matriz<double> tmp_d = g->getMatrizCusto();
    
    int n = g->getOrdem();

    // Matriz de predecessores
    Matriz<int> p = Matriz<int>(n,n,-1);

    // Configuração da matriz de predecessores com os valores iniciais

    No<Vertice> *nv = g->lista_vertices.inicio;

    for (int i=0; i<n; i++){    
        for (int j=0; j<n; j++)
            if (i != j && d[i][j] < std::numeric_limits<double>::infinity())
                p[i][j] = nv->elemento->id;
        nv = nv->proximo;
    }
    
    // Matriz de predecessores temporaria - constantemente modificada
    Matriz<int> tmp_p = p;

    // Execução da parte principal do algoritmo para calcular os custos e achar os predecessores
    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                if (tmp_d[i][k] + tmp_d[k][j] < tmp_d[i][j]){
                    d[i][j] = tmp_d[i][k] + tmp_d[k][j];
                    p[i][j] = tmp_p[k][j];
                }
                else {
                    d[i][j] = tmp_d[i][j];
                    p[i][j] = tmp_p[i][j];
                }
            }
        }
        tmp_d = d;
        tmp_p = p;
        
        // Use para analisar a execução do código acima
        // Descomente as 3 linhas abaixo para verificar as matrizes geradas durante a execução do algoritmo
        //d.print();
        //std::cout << std::endl;
        //p.print();
    }

    RetornoFloydWarshall r;
    
    r.custo_minimo = d;
    r.predecessor = p;

    return r;
}

void printMenorCaminho(Matriz<int> *predecessor, int i, int j){
    if (i == j)
        std::cout << i << " ";
    else {
        if ((*predecessor)[i][j] == -1)
            std::cout << "Não existe caminho" << std::endl;
        else {
            printMenorCaminho(predecessor,i,(*predecessor)[i][j]);
            std::cout << j << " ";
        }
    }
}