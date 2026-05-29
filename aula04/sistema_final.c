/*
Aula 04: Arquivos e recursao (versao final)

Compilar (Linux/Mac): gcc sistema_final.c -o sistema_final
Executar (Linux/Mac): ./sistema_final
Compilar (Windows): gcc sistema_final.c -o sistema_final.exe
Executar (Windows): sistema_final.exe

Objetivo da Aula 04:
- Continuar a Aula 03 sem recomecar do zero.
- UT9: funcoes recursivas (exemplo didatico).
- UT12: entrada e saida de dados em arquivos.

Por que a Aula 04 continua a Aula 03?
- A aprendizagem e incremental: a cada aula mantemos a base anterior.
- Assim, os alunos reconhecem o codigo, mas veem novas capacidades.
- A struct Produto, os calculos e o resumo seguem iguais.
- Agora mostramos persistencia e recursao, conectando tudo das quatro aulas.
*/

#include <stdio.h>

#define MAX_PRODUTOS 3
#define MAX_TEXTO 50

/*
Modularizacao (Aula 02 e Aula 03):
- Procedimentos organizam a exibicao.
- Funcoes fazem calculos reutilizaveis.
- A Aula 04 preserva essa estrutura para manter a continuidade.
*/

void exibirCabecalho(void) {
    printf("===========================================\n");
    printf("SISTEMA DE PEDIDOS - AULA 04\n");
    printf("===========================================\n");
}

void exibirLinha(void) {
    printf("-------------------------------------------\n");
}

float calcularTotalItem(float preco, int quantidade) {
    return preco * quantidade;
}

float calcularDesconto(float subtotal) {
    if (subtotal >= 300.0f) {
        return subtotal * 0.10f;
    } else if (subtotal >= 100.0f) {
        return subtotal * 0.05f;
    }
    return 0.0f;
}

float calcularTotalFinal(float subtotal, float desconto) {
    return subtotal - desconto;
}

/*
O que e uma struct?
- struct cria um tipo de dado personalizado que agrupa dados relacionados.
- Em vez de varios vetores paralelos, usamos um unico tipo Produto.
- Isso deixa o codigo mais organizado e proximo de um sistema real.
*/

typedef struct {
    char nome[MAX_TEXTO];
    int quantidade;
    float precoUnitario;
    float totalItem;
} Produto;

void lerProduto(Produto produtos[], int indice) {
    printf("Nome do produto: ");
    scanf(" %49[^\n]", produtos[indice].nome);

    do {
        printf("Quantidade (maior que 0): ");
        scanf("%d", &produtos[indice].quantidade);
    } while (produtos[indice].quantidade <= 0);

    do {
        printf("Preco unitario (maior que 0): ");
        scanf("%f", &produtos[indice].precoUnitario);
    } while (produtos[indice].precoUnitario <= 0.0f);

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

    if (totalFinal < 100.0f) {
        printf("Classificacao: pedido pequeno\n");
    } else if (totalFinal < 300.0f) {
        printf("Classificacao: pedido medio\n");
    } else {
        printf("Classificacao: pedido grande\n");
    }
}

/*
Aula 04: arquivos e persistencia

Por que os dados se perdem quando ficam apenas em variaveis?
- Variaveis ficam na memoria RAM, que e temporaria.
- Ao encerrar o programa, a RAM e liberada e os dados somem.

O que e persistencia de dados?
- E guardar informacoes em um local permanente, como um arquivo.
- Assim, os dados continuam existindo apos o fim do programa.

O que e FILE?
- FILE e um tipo da linguagem C que representa um arquivo aberto.
- Um ponteiro para arquivo aponta para a estrutura que controla esse arquivo.
- Por isso usamos FILE *arquivo: guardamos o endereco do arquivo aberto.

Para que serve fopen?
- Abre um arquivo e devolve um ponteiro FILE*.
- Modos principais:
  - "w" cria/reescreve do zero.
  - "a" acrescenta no final sem apagar o que ja existe.
  - "r" abre apenas para leitura.
- Usamos "a" para adicionar pedidos, preservando os anteriores.

Por que verificar if (arquivo == NULL)?
- fopen pode falhar (arquivo protegido, pasta sem permissao, etc.).
- Quando falha, retorna NULL e precisamos tratar o erro.

Para que serve fprintf?
- Escreve texto em arquivo, assim como printf escreve na tela.
- printf -> tela; fprintf -> arquivo.

Para que serve fgets?
- Le uma linha do arquivo para um vetor de char.

Para que serve fclose?
- Fecha o arquivo, liberando recursos do sistema.
- Fechar o arquivo e boa pratica e evita perda de dados.

Como o arquivo pedidos.txt representa persistencia?
- Cada pedido fica registrado no arquivo.
- O arquivo continua existindo mesmo depois de fechar o programa.
*/

void salvarPedidoEmArquivo(char nomeCliente[], Produto produtos[], float subtotal,
                           float desconto, float totalFinal) {
    int i;
    FILE *arquivo = fopen("pedidos.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir pedidos.txt para gravacao.\n");
        return;
    }

    fprintf(arquivo, "===========================================\n");
    fprintf(arquivo, "Cliente: %s\n", nomeCliente);
    fprintf(arquivo, "Produto | Qtd | Preco | Total\n");

    for (i = 0; i < MAX_PRODUTOS; i++) {
        fprintf(arquivo, "%s | %d | %.2f | %.2f\n",
                produtos[i].nome,
                produtos[i].quantidade,
                produtos[i].precoUnitario,
                produtos[i].totalItem);
    }

    fprintf(arquivo, "Subtotal: %.2f\n", subtotal);
    fprintf(arquivo, "Desconto: %.2f\n", desconto);
    fprintf(arquivo, "Total final: %.2f\n", totalFinal);
    fprintf(arquivo, "===========================================\n\n");

    fclose(arquivo);
}

void consultarPedidosSalvos(void) {
    char linha[200];
    FILE *arquivo = fopen("pedidos.txt", "r");

    if (arquivo == NULL) {
        printf("Nenhum pedido salvo ainda ou erro ao abrir o arquivo.\n");
        return;
    }

    printf("\nPedidos salvos (arquivo pedidos.txt)\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
}

/*
Aula 04: recursao

O que e recursao?
- E quando uma funcao chama a si mesma.

O que e chamada recursiva?
- E a chamada da propria funcao dentro dela mesma.

O que e caso base?
- E a condicao de parada.
- Sem o caso base, a recursao seria infinita e causaria erro.

Diferenca entre recursao e repeticao:
- Repeticao usa for/while.
- Recursao resolve o problema dividindo em partes menores.

Risco de recursao infinita:
- Se nao houver condicao de parada, a funcao nunca termina.

Por que o fatorial e adequado como exemplo?
- E simples, conhecido e tem um caso base claro.
- Permite visualizar as chamadas sucessivas.

Exemplo de chamadas:
- fatorial(5) = 5 * fatorial(4)
- fatorial(4) = 4 * fatorial(3)
- fatorial(3) = 3 * fatorial(2)
- fatorial(2) = 2 * fatorial(1)
- fatorial(1) = 1
*/

int calcularFatorialRecursivo(int numero) {
    if (numero <= 1) {
        return 1;
    }

    return numero * calcularFatorialRecursivo(numero - 1);
}

void demonstrarRecursao(void) {
    int numero;

    printf("\nDemonstracao de recursao (fatorial)\n");
    printf("Digite um numero inteiro >= 0: ");
    scanf("%d", &numero);

    if (numero < 0) {
        printf("Numero invalido para fatorial.\n");
        return;
    }

    printf("Fatorial de %d = %d\n", numero, calcularFatorialRecursivo(numero));
}

int main(void) {
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

    // Gravacao do pedido no arquivo (persistencia).
    salvarPedidoEmArquivo(nomeCliente, produtos, subtotal, desconto, totalFinal);

    // Consulta de pedidos ja salvos.
    consultarPedidosSalvos();

    // Demonstracao didatica de recursao.
    demonstrarRecursao();

    /*
    Conexao das quatro aulas:
    - Aula 01: entrada, processamento e saida basica.
    - Aula 02: modularizacao com funcoes e procedimentos.
    - Aula 03: struct e strings para organizar os dados.
    - Aula 04: persistencia em arquivos e recursao.
    */

    return 0;
}
