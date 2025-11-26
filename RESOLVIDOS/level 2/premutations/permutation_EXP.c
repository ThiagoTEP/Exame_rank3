#include "permutation_a.h" // Inclui o arquivo de cabeçalho (para protótipos e funções padrão como malloc, puts).

// Declaração: Função auxiliar para calcular o comprimento da string.
static size_t   ft_strlen(char *s);
// Declaração: Função recursiva de Backtracking para gerar permutações.
static void     backtrack(char *s, size_t s_len, char *buf, size_t b_len, int *used);

int main(int ac, char **av)
{
    char    *s, *buf; // s: string de entrada; buf: buffer para construir a permutação.
    size_t      s_len;  // Armazena o comprimento da string.
    int         *used;  // Array de controle para marcar caracteres já usados (evita repetição na permutação).
    char        tmp;    // Variável temporária para a troca de caracteres.

    if (ac != 2) // Checa se o programa foi chamado com exatamente um argumento de string.
        return (1); // Retorna erro se o argumento estiver faltando.

    s = av[1]; // Atribui a string de entrada do argumento à variável 's'.
    s_len = ft_strlen(s); // Calcula o comprimento da string.

    if (s_len == 0) // Checa se a string de entrada está vazia.
        return (1); // Retorna erro se estiver vazia.

    buf = malloc(s_len + 1); // Aloca memória para o buffer da permutação (+1 para o '\0').
    // Aloca e inicializa a 0 o array 'used' (tamanho s_len). 0 significa 'não usado'.
    used = calloc(s_len, sizeof(int));

    if (!buf || !used) // Trata a falha na alocação de memória.
    {
        // Libera a memória que foi alocada antes de sair com erro.
        if (buf)
            free(buf);
        if (used)
            free(used);
        return (1); // Retorna erro.
    }

    // --- INÍCIO DA ORDENAÇÃO DA STRING DE ENTRADA (Bubble Sort Simples) ---
    // A ordenação é feita para garantir que as permutações sejam impressas em ordem lexicográfica.
    for (size_t i = 0; i < (s_len - 1); i++)
    {
        for (size_t j = i + 1; j < s_len; j++)
        {
            if (s[i] > s[j]) // Se o caractere atual for maior que o próximo...
            {
                // Realiza a troca (swap) para ordenar a string.
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }
    }
    // --- FIM DA ORDENAÇÃO ---

    // Inicia o Backtracking. buf: buffer de permutação, b_len=0: começa na posição 0, used: array de controle.
    backtrack(s, s_len, buf, 0, used);

    free(buf); // Libera a memória do buffer.
    free(used); // Libera a memória do array de controle.

    return (0); // Retorna sucesso.
}

// 📏 Função auxiliar: Calcula o comprimento da string (ft_strlen)
static size_t   ft_strlen(char *s)
{
    int i = 0; // Contador de caracteres.

    if (!s) // Checa se o ponteiro é nulo.
        return (0); // Retorna 0.

    while (s[i]) // Loop: conta caracteres até encontrar o terminador nulo ('\0').
        i++;

    return (i); // Retorna o comprimento.
}

// 👑 Função de Backtracking: Gera todas as permutações
static void backtrack(char *s, size_t s_len, char *buf, size_t b_len, int *used)
{
    // 1. CASO BASE (SUCESSO)
    // Se o comprimento atual do buffer (b_len) for igual ao comprimento total da string (s_len).
    if (b_len == s_len)
    {
        buf[b_len] = '\0'; // Adiciona o terminador nulo para formar a string final.
        puts(buf); // Imprime a permutação completa.
        return ; // Retrocede (volta ao nível de recursão anterior).
    }

    // 2. PASSO RECURSIVO (TENTATIVA E ERRO)
    for (size_t i = 0; i < s_len; i++) // Itera sobre cada caractere da string de entrada 's'.
    {
        // VERIFICAÇÃO DE RESTRIÇÃO:
        if (!used[i]) // Checa se o caractere na posição 'i' JÁ foi usado nesta permutação.
        {
            // FAZ A ESCOLHA (Avançar):
            used[i] = 1; // Marca o caractere na posição 'i' como usado (1).
            buf[b_len] = s[i]; // Coloca o caractere 's[i]' na posição atual do buffer.

            // AVANÇA: Chamada recursiva para preencher a próxima posição (b_len + 1).
            backtrack(s, s_len, buf, b_len + 1, used);

            // DESFAZ A ESCOLHA (RETROCESSO):
            // Quando a chamada acima retorna (find(b_len+1) terminou), limpamos a marcação.
            used[i] = 0; // Marca o caractere 's[i]' como 'não usado' (0) novamente.
            // O caractere em buf[b_len] será sobrescrito na próxima iteração do loop 'for'.
        }
    }
}
