/*
Aula 03 - Sistema de pedidos (versao final)
Compilar (Linux/Mac): gcc sistema_final.c -o sistema_final
Executar (Linux/Mac): ./sistema_final
Compilar (Windows): gcc sistema_final.c -o sistema_final.exe
Executar (Windows): sistema_final.exe

Objetivo da Aula 03:
- Continuar a Aula 02, mantendo a modularizacao e evoluindo os dados.
- UT6: manipulacao de memoria (enderecos, ponteiros, operador & e *).
- UT10: registros com struct para organizar os dados do pedido.
- UT11: strings para leitura de textos com espacos.

Continuidade com a Aula 02:
- Mantemos os mesmos subprogramas (procedimentos e funcoes).
- Antes, os dados estavam em vetores paralelos separados.
- Agora, agrupamos tudo em uma struct Produto, mantendo a mesma logica.
*/

#include <stdio.h>

#define MAX_PRODUTOS 3
#define MAX_TEXTO 50

/*
Modularizacao (Aula 02):
- Procedimentos organizam a exibicao.
- Funcoes fazem calculos reutilizaveis.
- A Aula 03 preserva essa estrutura para dar continuidade ao aprendizado.
*/

void exibirCabecalho(void) {
    printf("===========================================\n");
    printf("SISTEMA DE PEDIDOS - AULA 03\n");
    printf("===========================================\n");
}

void exibirLinha(void) {
    printf("-------------------------------------------\n");
}

float calcularTotalItem(float preco, int quantidade) {
    // Funcao com retorno: devolve o total do item.
    return preco * quantidade;
}

float calcularDesconto(float subtotal) {
    // Funcao com retorno: devolve o valor do desconto conforme regra.
    if (subtotal >= 300.0f) { // Desconto de 10% para pedidos de 300 ou mais
        return subtotal * 0.10f;
    } else if (subtotal >= 100.0f) { // Desconto de 5% para pedidos entre 100 e 299.99
        return subtotal * 0.05f;
    }
    return 0.0f;
}

float calcularTotalFinal(float subtotal, float desconto) {
    return subtotal - desconto;
}

/*
O que e uma string em C?
- String e um vetor de caracteres terminado por '\0'.
- Por isso usamos char nome[MAX_TEXTO]: reservamos espaco para texto e terminador.
- Uma string ocupa varias posicoes da memoria, uma para cada caractere.
*/

/*
O que e uma struct?
- struct cria um tipo de dado personalizado que agrupa dados relacionados.
- Uma struct pode conter tipos diferentes no mesmo registro.
- Em vez de varios vetores paralelos, usamos um unico tipo Produto.
- Isso deixa o codigo mais organizado e mais proximo de um sistema real.
*/

typedef struct {
    char nome[MAX_TEXTO];
    int quantidade;
    float precoUnitario;
    float totalItem;
} Produto;

void lerProduto(Produto produtos[], int indice) {
    printf("Nome do produto: ");

    /*
    Por que usamos " %[^\n]" no scanf?
    - O espaco inicial ignora a quebra de linha anterior.
    - [^\n] le tudo ate o fim da linha, permitindo espacos no nome.
    - 49 limita a leitura ao tamanho do vetor e evita estouro.

    Por que nao usamos & ao ler uma string?
    - O nome do vetor ja representa o endereco do primeiro caractere.
    - Por isso scanf recebe produtos[indice].nome diretamente.
    */
    scanf(" %49[^\n]", produtos[indice].nome);

    /*
    Por que scanf usa & para int e float?
    - scanf precisa do endereco da variavel para guardar o valor digitado.
    - O operador & devolve o endereco de memoria.
    */
    do {
        printf("Quantidade (maior que 0): ");
        scanf("%d", &produtos[indice].quantidade);
    } while (produtos[indice].quantidade <= 0);

    do {
        printf("Preco unitario (maior que 0): ");
        scanf("%f", &produtos[indice].precoUnitario);
    } while (produtos[indice].precoUnitario <= 0.0f);

    /*
    Acesso aos campos da struct com o operador ponto (.).
    Exemplo: produtos[indice].quantidade, produtos[indice].precoUnitario.
    */
    produtos[indice].totalItem = calcularTotalItem(produtos[indice].precoUnitario,
                                                   produtos[indice].quantidade);
}

void exibirResumoPedido(char nomeCliente[], Produto produtos[], float subtotal,
                        float desconto, float totalFinal) {
    int i;

    exibirLinha();
    printf("Resumo do pedido\n");
    printf("Cliente: %s\n", nomeCliente);

    printf("\n%-20s %10s %10s %10s\n", "Produto", "Qtd", "Preco", "Total");
    for (i = 0; i < MAX_PRODUTOS; i++) {
        printf("%-20s %10d %10.2f %10.2f\n",
               produtos[i].nome,
               produtos[i].quantidade,
               produtos[i].precoUnitario,
               produtos[i].totalItem);
    }

    exibirLinha();
    printf("Subtotal: %.2f\n", subtotal);
    printf("Desconto: %.2f\n", desconto);
    printf("Total final: %.2f\n", totalFinal);

    // Classificacao do pedido conforme o total final.
    if (totalFinal < 100.0f) {
        printf("Classificacao: pedido pequeno\n");
    } else if (totalFinal < 300.0f) {
        printf("Classificacao: pedido medio\n");
    } else {
        printf("Classificacao: pedido grande\n");
    }
}

void demonstrarPonteiros(float totalFinal) {
    /*
    Memoria e endereco:
    - Memoria e o espaco onde as variaveis ficam armazenadas.
    - Cada variavel tem um endereco de memoria.
    - Um ponteiro guarda esse endereco.

    Operadores:
    - & devolve o endereco da variavel.
    - * acessa o valor apontado pelo ponteiro.

    Por que ponteiros sao importantes em C?
    - Permitem acessar e manipular dados na memoria diretamente.
    - Sao a base de vetores, strings e funcoes como scanf.
    */
    float *ponteiro = &totalFinal;

    printf("\nExemplo simples de ponteiro\n");
    printf("Valor: %.2f\n", totalFinal);
    printf("Endereco: %p\n", (void *)ponteiro);
    printf("Valor apontado (*): %.2f\n", *ponteiro);
}

int main(void) {
    /*
    Vetores paralelos da Aula 02 (explicacao):
    - nome, quantidade, preco e total ficavam em vetores separados.
    - Isso funciona, mas pode confundir e dificultar a manutencao.

    Agora usamos Produto produtos[MAX_PRODUTOS], um vetor de struct:
    - Cada posicao guarda um produto completo (nome, quantidade, preco e total).
    - Um vetor comum guarda varios valores do mesmo tipo.
    - Um vetor de struct guarda varios registros com campos diferentes.
    */

    Produto produtos[MAX_PRODUTOS];
    char nomeCliente[MAX_TEXTO];

    int i;
    float subtotal = 0.0f;
    float desconto = 0.0f;
    float totalFinal = 0.0f;

    exibirCabecalho();

    printf("Nome do cliente: ");
    scanf(" %49[^\n]", nomeCliente);

    for (i = 0; i < MAX_PRODUTOS; i++) {
        printf("\nProduto %d\n", i + 1);
        lerProduto(produtos, i);
        subtotal += produtos[i].totalItem;
    }

    desconto = calcularDesconto(subtotal);
    totalFinal = calcularTotalFinal(subtotal, desconto);

    exibirResumoPedido(nomeCliente, produtos, subtotal, desconto, totalFinal);
    demonstrarPonteiros(totalFinal);

    /*
    Relacao com as UTs:
    - UT6: enderecos, ponteiros, & e * na demonstracao e no scanf.
    - UT10: struct Produto e vetor de Produto para organizar o pedido.
    - UT11: leitura de strings com espacos e uso de char nome[MAX_TEXTO].
    */

    return 0;
}
