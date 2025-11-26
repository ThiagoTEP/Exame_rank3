#include "rip_a.h" // Inclui o arquivo de cabeçalho (para protótipos e funções padrão como malloc, puts).

// Declaração: Função recursiva principal de Backtracking.
// Parâmetros principais: left/right (parênteses a remover), open (parênteses abertos no buf).
static void backtrack(char *s, int index, int left, int right, int open, char *buf);
// Declaração: Função auxiliar que verifica se uma string de parênteses é válida.
static int    is_valid(char *s);

int    main(int ac, char **av)
{
    char    *s, *buf; // s: string de entrada; buf: buffer da solução.
    int        i = 0, left = 0, right = 0; // i: contador; left/right: número de parênteses a serem removidos.

    if (ac != 2) // Checa se foi passado exatamente um argumento de string.
        return (1); // Retorna erro.

    s = av[1]; // Atribui a string de entrada.

    // --- PRÉ-ANÁLISE: Calcula o número mínimo de parênteses a remover ---
    while (s[i]) // Loop que percorre a string para determinar 'left' e 'right' iniciais.
    {
        if (s[i] == '(') // Se for um parêntese de abertura...
            left++; // Incrementa 'left' (potencialmente extra).
        else if (s[i] == ')') // Se for um parêntese de fechamento...
        {
            if (left > 0) // Se houver um '(' anterior pendente...
                left--; // ...o ')' o equilibra, decrementa 'left'.
            else // Se não houver '(' pendente, este ')' é um excesso no início.
                right++; // Incrementa 'right' (precisa ser removido).
        } // (Outros caracteres são ignorados nesta fase).
        i++;
    }
    // Ao final, 'left' é o número de '(' extras e 'right' é o número de ')' extras.

    buf = malloc(i + 1); // Aloca memória para o buffer de saída (tamanho da string original + '\0').
    if (!buf) // Trata a falha na alocação.
        return (1); // Retorna erro.

    // Inicia o Backtracking: index=0, left/right (contadores de remoção), open=0 (parênteses abertos no buf).
    backtrack(s, 0, left, right, 0, buf);

    free(buf); // Libera a memória do buffer.
    return (0); // Retorna sucesso.
}

// 👑 Função de Backtracking: Constrói a string de saída.
static void backtrack(char *s, int index, int left, int right, int open, char *buf)
{
    // --- 1. CASO BASE ---
    if (s[index] == '\0') // Se atingiu o final da string de entrada.
    {
        buf[index] = '\0'; // Finaliza a string no buffer.

        // Verifica se a string final é válida (checa se 'open' é 0 e a ordem é correta).
        if (is_valid(buf))
            puts(buf); // Imprime a solução se for válida.

        return ; // Retrocede.
    }
    // --- 2. PASSO RECURSIVO ---
    else if (s[index] == '(') // Se o caractere atual é '('.
    {
        // TENTATIVA A: REMOVER O '(' (substituir por espaço).
        if (left > 0) // Só podemos remover se ainda tivermos 'left' para remover.
        {
            buf[index] = ' '; // FAZ A ESCOLHA: Marca o caractere para remoção (espaço).
            // AVANÇA: Decrementa 'left' (uma remoção feita) e mantém 'open' (não foi adicionado).
            backtrack(s, index + 1, left - 1, right, open, buf);
        }

        // TENTATIVA B: MANTER O '(' (incluir no buf).
        buf[index] = '('; // FAZ A ESCOLHA: Coloca o '(' no buffer.
        // AVANÇA: Mantém 'left', incrementa 'open' (adicionou um parêntese aberto).
        backtrack(s, index + 1, left, right, open + 1, buf);
    }

    else if (s[index] == ')') // Se o caractere atual é ')'.
    {
        // TENTATIVA A: REMOVER O ')' (substituir por espaço).
        if (right > 0) // Só podemos remover se ainda tivermos 'right' para remover.
        {
            buf[index] = ' '; // FAZ A ESCOLHA: Marca o caractere para remoção.
            // AVANÇA: Decrementa 'right' (uma remoção feita) e mantém 'open'.
            backtrack(s, index + 1, left, right - 1, open, buf);
        }

        // TENTATIVA B: MANTER O ')' (incluir no buf).
        if (open > 0) // Só podemos manter o ')' se houver um '(' pendente ('open' > 0).
        {
            buf[index] = ')'; // FAZ A ESCOLHA: Coloca o ')' no buffer.
            // AVANÇA: Mantém 'right', decrementa 'open' (fechou um parêntese aberto).
            backtrack(s, index + 1, left, right, open - 1, buf);
        }
    }
    // Note que não há código para retroceder (desfazer) caracteres que não sejam '(' ou ')'.
    // Isso porque eles são simplesmente incluídos no buffer de forma não-recursiva.
    else // Para qualquer outro caractere (ex: letras, números).
    {
        buf[index] = s[index]; // Simplesmente copia o caractere para o buffer.
        // Avança para o próximo caractere. left, right e open permanecem inalterados.
        backtrack(s, index + 1, left, right, open, buf);
    }
}

// 🛡️ Função de Validação Final
static int    is_valid(char *s)
{
    int    count = 0; // Contador de parênteses abertos.

    while (*s) // Loop que percorre a string do buffer.
    {
        if (*s == '(') // Se for '(', incrementa o contador.
            count++;
        else if (*s == ')') // Se for ')', verifica a validade.
        {
            if (count == 0) // Se count for 0, encontramos um ')' sem um '(' anterior.
                return (0); // Inválido.

            count--; // Decrementa (o ')' fecha um '(').
        }
        // Se for um espaço ' ' (marcador de remoção) ou outro caractere, o contador não muda.
        s++; // Avança o ponteiro.
    }
    // Válido se, e somente se, o contador final for 0 (todos os '(' foram fechados).
    return (count == 0);
}
