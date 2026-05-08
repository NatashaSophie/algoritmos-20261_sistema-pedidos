/*
Aula 01 - Sistema de pedidos (versao final)
Objetivo da aula: introduzir a base do pensamento computacional em C,
mostrando entrada, processamento e saida com regras de negocio.
Unidades Tematicas: UT1 (Fundamentos), UT2 (Condicionais), UT3 (Repeticao)

Problema: registrar ate 3 itens de um pedido, calcular subtotal, desconto
por faixa e total final, classificando o pedido.

Compilacao (Linux/macOS):
  gcc sistema_final.c -o sistema_final
  ./sistema_final

Compilacao (Windows):
  gcc sistema_final.c -o sistema_final.exe
  sistema_final.exe
*/

// Biblioteca: conjunto de funcoes prontas que podemos usar no programa.
// #include <stdio.h> permite usar entrada e saida padrao, como scanf e printf.
#include <stdio.h>

// int main() e o ponto inicial do programa; tudo comeca aqui.
int main() {
    // Variaveis guardam dados temporarios para o processamento.
    // Tipos: int para inteiros, float para reais, char para caracteres.
    // Uma string em C e um vetor (array) de char com varios caracteres.
    char nomeCliente[50];
    char nomeProduto[50];

    int quantidade = 0;       // quantidade do produto (inteiro)
    float precoUnitario = 0.0f; // preco unitario (real)
    float totalItem = 0.0f;     // total do item (real)

    float subtotal = 0.0f;        // acumulador do pedido
    float descontoPercentual = 0.0f;
    float valorDesconto = 0.0f;
    float totalFinal = 0.0f;

    int i = 0; // contador do laco

    printf("=== Sistema de Pedidos (Aula 01) ===\n");

    // Entrada: leitura do nome do cliente.
    printf("Digite o nome do cliente: ");
    // scanf le dados digitados; " %[^\n]" le a linha inteira com espacos.
    scanf(" %[^\n]", nomeCliente);

    // Repeticao: precisamos registrar mais de um item.
    // for e um laco que repete um bloco um numero fixo de vezes.
    for (i = 1; i <= 3; i++) {
        printf("\nItem %d\n", i);

        printf("Produto: ");
        scanf(" %[^\n]", nomeProduto);

        // Validacao: evita dados incoerentes no processamento.
        // Operadores relacionais: >, <, >=, <=, ==, !=
        // Operadores logicos: && (E), || (OU), ! (NAO)
        do {
            printf("Quantidade: ");
            scanf("%d", &quantidade);
        } while (quantidade <= 0);

        do {
            printf("Preco unitario: ");
            scanf("%f", &precoUnitario);
        } while (precoUnitario <= 0.0f);

        // Processamento: operadores aritmeticos +, -, *, /
        totalItem = quantidade * precoUnitario;

        // Acumulador: soma varios valores em uma unica variavel.
        subtotal = subtotal + totalItem;

        // Saida parcial para acompanhar o calculo.
        printf("Total do item: %.2f\n", totalItem);
    }

    // Regra de negocio com condicionais if, else if e else.
    if (subtotal < 100.0f) {
        descontoPercentual = 0.0f;
    } else if (subtotal < 300.0f) {
        descontoPercentual = 0.05f;
    } else {
        descontoPercentual = 0.10f;
    }

    valorDesconto = subtotal * descontoPercentual;
    totalFinal = subtotal - valorDesconto;

    // Classificacao do pedido por faixa de subtotal.
    // Um algoritmo pode representar regras de negocio de forma clara.
    printf("\nResumo do pedido\n");
    printf("Cliente: %s\n", nomeCliente);
    printf("Subtotal: %.2f\n", subtotal);
    printf("Desconto: %.2f\n", valorDesconto);
    printf("Total final: %.2f\n", totalFinal);

    if (subtotal <= 99.99f) {
        printf("Classificacao: pedido pequeno\n");
    } else if (subtotal <= 299.99f) {
        printf("Classificacao: pedido medio\n");
    } else {
        printf("Classificacao: pedido grande\n");
    }

    // Importancia da legibilidade: nomes claros e codigo organizado.
    // Entrada -> processamento -> saida formam a estrutura basica de algoritmos.

    return 0;
}
