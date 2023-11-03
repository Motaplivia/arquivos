#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgc.h" 
void fazerPedido(struct Produto *estoque, int num_produtos, struct Usuario *usuario, struct Produto *pedidos, int *num_pedidos) {
    printf("\nFazer Pedido\n");

    int opcao;
    do {
        listarProdutos(estoque, num_produtos);
        printf("Escolha o produto pelo código ou digite 0 para encerrar o pedido: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            // Encerrar o pedido
            break;
        } else if (opcao < 1 || opcao > num_produtos) {
            printf("Código do produto inválido. Tente novamente.\n");
        } else {
            int quantidade;
            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidade);

            if (quantidade > estoque[opcao - 1].quantidade) {
                printf("Quantidade indisponível em estoque.\n");
            } else {
                // Adicionar o produto ao pedido
                pedidos[*num_pedidos] = estoque[opcao - 1];
                pedidos[*num_pedidos].quantidade = quantidade;
                (*num_pedidos)++;
                estoque[opcao - 1].quantidade -= quantidade;
                printf("Produto adicionado ao pedido.\n");
            }
        }
    } while (1);
}
void salvarPedidosArquivo(struct Produto pedidos[], int num_pedidos) {
    FILE *arquivo = fopen("pedidos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de pedidos.\n");
        return;
    }

    for (int i = 0; i < num_pedidos; i++) {
        fprintf(arquivo, "%d %s %.2f %d\n", pedidos[i].codigo, pedidos[i].nome, pedidos[i].preco, pedidos[i].quantidade);
    }

    fclose(arquivo);
}


