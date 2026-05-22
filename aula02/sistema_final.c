/*
Aula 02 - Sistema de pedidos (versao final)
Objetivo: evoluir o sistema da Aula 01 com vetores, matriz e modularizacao.
UTs trabalhadas: UT4 (vetores), UT5 (matrizes), UT7 (procedimentos), UT8 (funcoes).

Compilar (Linux/Mac):
  gcc sistema_final.c -o sistema_final
  ./sistema_final
Compilar (Windows):
  gcc sistema_final.c -o sistema_final.exe
  sistema_final.exe
*/

#include <stdio.h>

#define MAX_PRODUTOS 3
#define MAX_TEXTO 50

/*
Modularizacao: dividir o problema em pequenas partes.
Isso melhora a legibilidade, manutencao e reaproveitamento do codigo.
Procedimento (void): executa uma tarefa e nao retorna valor.
Funcao com retorno: executa e devolve um resultado com return.
Parametros: dados de entrada usados pela funcao ou procedimento.
*/

void exibirCabecalho(void) {
    printf("===========================================\n");
    printf("SISTEMA DE PEDIDOS - AULA 02\n");
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

int main(void) {
    /*
    Vetor: estrutura que guarda varios valores do mesmo tipo em sequencia.
    Usamos vetores para evitar varias variaveis separadas (produto1, produto2...).
    Declaracao de vetor em C: tipo nome[tamanho];
    Acesso a uma posicao: nome[indice];
    Indices comecam em 0, entao o primeiro item esta na posicao 0.

    Vetor de caracteres (string): um array de char que guarda um texto.
    char produtos[3][50] e uma matriz de caracteres: 3 linhas, 50 colunas.
    Cada linha guarda uma string (nome de um produto).

    Matriz: estrutura bidimensional (linhas e colunas).
    Declaracao de matriz: tipo nome[linhas][colunas];
    Diferenca entre vetor e matriz: vetor tem 1 dimensao, matriz tem 2.
    Uma matriz e util para representar dados tabulares.
    */

    char nomeCliente[MAX_TEXTO];

    // Vetores paralelos: mesmo indice aponta para dados do mesmo produto.
    char produtos[MAX_PRODUTOS][MAX_TEXTO];
    int quantidades[MAX_PRODUTOS];
    float precos[MAX_PRODUTOS];
    float totais[MAX_PRODUTOS];

    /*
    Matriz simples para tabela de valores:
    coluna 0: preco unitario
    coluna 1: total do item
    */
    float tabela[MAX_PRODUTOS][2];

    int i;
    float subtotal = 0.0f;
    float desconto = 0.0f;
    float totalFinal = 0.0f;

    exibirCabecalho();

    printf("Nome do cliente: ");
    // Leitura de string com espacos usando scanf e conjunto de caracteres.
    scanf(" %49[^\n]", nomeCliente);

    // For percorre o vetor do inicio (0) ate o tamanho - 1.
    for (i = 0; i < MAX_PRODUTOS; i++) {
        printf("\nProduto %d\n", i + 1);

        printf("Nome do produto: ");
        scanf(" %49[^\n]", produtos[i]);

        printf("Quantidade: ");
        scanf(" %d", &quantidades[i]);

        printf("Preco unitario: ");
        scanf(" %f", &precos[i]);

        // Funcao com retorno aplicada ao item atual.
        totais[i] = calcularTotalItem(precos[i], quantidades[i]);

        // Guardamos preco e total em uma matriz para formato tabular.
        tabela[i][0] = precos[i];
        tabela[i][1] = totais[i];

        subtotal += totais[i];
    }

    desconto = calcularDesconto(subtotal);
    totalFinal = calcularTotalFinal(subtotal, desconto);

    exibirLinha();
    printf("Resumo do pedido\n");
    printf("Cliente: %s\n", nomeCliente);

    printf("\n%-20s %10s %10s %10s\n", "Produto", "Qtd", "Preco", "Total");
    for (i = 0; i < MAX_PRODUTOS; i++) {
        printf("%-20s %10d %10.2f %10.2f\n",
               produtos[i],
               quantidades[i],
               tabela[i][0],
               tabela[i][1]);
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

    /*
    Relacao com as UTs:
    - UT4: vetores para guardar varios produtos.
    - UT5: matriz para visualizar dados em linhas e colunas.
    - UT7: procedimentos para cabecalho e separacao visual.
    - UT8: funcoes para calculos reutilizaveis.
    */

    return 0;
}
