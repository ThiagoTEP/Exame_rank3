#include <stdio.h> // Inclui funções de I/O (printf, scanf, fprintf, fscanf).
#include <stdlib.h> // Inclui funções gerais (como EXIT_SUCCESS/FAILURE).
#include <math.h> // Inclui funções matemáticas (como sqrtf).

#define MAX 11 // Define o número máximo de cidades que o programa pode lidar.

// --- Estruturas de Dados ---

typedef struct {
    float x, y; // Coordenadas (x, y) de cada cidade.
} City;

City cities[MAX]; // Array global para armazenar as coordenadas de até MAX cidades.

int n; // Variável global: número real de cidades lidas.
float dist[MAX][MAX]; // Matriz global: armazena a distância pré-calculada entre todas as cidades.
int used[MAX]; // Array de controle: marca se uma cidade já foi incluída na rota atual (1=usada, 0=não usada).
int path[MAX]; // Array: armazena os índices das cidades na ordem em que são visitadas na rota atual.
float best = 1e9; // Variável global: armazena o comprimento da rota mais curta encontrada até agora (inicializada com um valor grande).

// --- Função de Distância ---

// Calcula a distância Euclidiana entre duas cidades.
float distance(City a, City b) {
    // Retorna a raiz quadrada da soma dos quadrados das diferenças de coordenadas.
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

// --- Função de Busca (Backtracking) ---

// Função recursiva que explora todas as permutações possíveis de rotas.
// k: o índice da cidade que estamos tentando colocar na rota (posição no array path).
// length: o comprimento total da rota construída até agora.
void search(int k, float length) {
    if (k == n) { // CASO BASE: A rota tem o tamanho N (todas as cidades foram visitadas).
        // Fecha o ciclo: adiciona a distância da última cidade (path[n-1]) de volta à primeira cidade (path[0]).
        length += dist[path[n-1]][path[0]];

        if (length < best) // Verifica se a rota atual é mais curta que a melhor encontrada.
            best = length; // Atualiza a melhor rota.

        return; // Retrocede.
    }

    // PASSO RECURSIVO: Tenta colocar cada cidade na posição 'k' da rota.
    for (int i = 0; i < n; i++) { // Itera sobre todas as cidades.
        if (!used[i]) { // Restrição: Verifica se a cidade 'i' ainda não foi visitada.

            // FAZ A ESCOLHA:
            used[i] = 1; // Marca a cidade 'i' como usada.
            path[k] = i; // Adiciona a cidade 'i' à rota na posição 'k'.

            float new_length = length; // Inicializa o novo comprimento com o comprimento atual.

            if (k > 0) // Se não for a primeira cidade da rota (k > 0)...
                // ...adiciona a distância da cidade anterior (path[k-1]) até a cidade atual (i).
                new_length += dist[path[k-1]][i];

            // AVANÇA: Chamada recursiva para preencher a próxima posição (k+1).
            search(k+1, new_length);

            // DESFAZ A ESCOLHA (RETROCESSO):
            used[i] = 0; // Marca a cidade 'i' como não usada, permitindo que seja explorada em outros caminhos.
        }
    }
}

// --- Função Principal ---

int main(void) {
    n = 0; // Inicializa o contador de cidades.

    // Leitura das coordenadas das cidades a partir da entrada padrão (stdin).
    // O loop continua enquanto fscanf conseguir ler duas floats (coordenadas x e y).
    while (fscanf(stdin, " %f , %f", &cities[n].x, &cities[n].y) == 2)
        n++; // Incrementa o contador de cidades.

    // Pré-calcula todas as distâncias entre todas as cidades.
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = distance(cities[i], cities[j]);

    // Inicia a busca (Backtracking).
    // Começa na primeira posição (k=0) com comprimento total 0.0.
    // Como a ordem inicial não importa, o algoritmo explorará todas as permutações,
    // e a cidade 0 acabará sendo a primeira em pelo menos um ciclo.
    search(0, 0.0);

    // Imprime o resultado final (a menor distância encontrada) formatado com duas casas decimais.
    fprintf(stdout, "%.2f\n", best);

    return 0; // Retorna sucesso.
}
