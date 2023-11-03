#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgc.h"  




// Funções específicas para administradores

void adicionarProdutoAdmin(struct Produto *estoque, int *num_produtos) {
    if (*num_produtos < 100) {  // Verifique se o estoque não está cheio
        struct Produto novoProduto;

        printf("Digite o nome do novo produto: ");
        scanf("%s", novoProduto.nome);

        printf("Digite o preço do novo produto: ");
        scanf("%f", &novoProduto.preco);

        printf("Digite a quantidade do novo produto: ");
        scanf("%d", &novoProduto.quantidade);

        estoque[*num_produtos] = novoProduto;  // Adicione o novo produto ao estoque
        (*num_produtos)++;  // Incremente o número de produtos no estoque

        printf("Produto adicionado com sucesso!\n");
    } else {
        printf("O estoque está cheio. Não é possível adicionar mais produtos.\n");
    }
}

void lerEstoqueArquivo(struct Produto *estoque, int *num_produtos) {
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n");
        return;
    }

    *num_produtos = 0;  // Inicialize o número de produtos lidos

    while (*num_produtos < 100 && fscanf(arquivo, "%s %f %d", estoque[*num_produtos].nome, &estoque[*num_produtos].preco, &estoque[*num_produtos].quantidade) == 3) {
        (*num_produtos)++;
    }

    fclose(arquivo);
}

void salvarEstoqueArquivo(struct Produto estoque[], int num_produtos) {
    FILE *arquivo = fopen("estoque.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < num_produtos; i++) {
        fprintf(arquivo, "%d %s %d %.2f\n", estoque[i].codigo, estoque[i].nome, estoque[i].quantidade, estoque[i].preco);
    }

    fclose(arquivo);
}

void carregarEstoque(struct Produto *estoque, int *num_produtos) {
    FILE *arquivo = fopen("estoque.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n");
        return;
    }

    while (!feof(arquivo)) {
        char linha[100];
        if (fgets(linha, sizeof(linha), arquivo) != NULL) {
            char *token = strtok(linha, " ");
            if (token != NULL) {
                strcpy(estoque[*num_produtos].nome, token);
            }

            token = strtok(NULL, ",");
            if (token != NULL) {
                estoque[*num_produtos].quantidade = atoi(token);
            }

            token = strtok(NULL, ",");
            if (token != NULL) {
                estoque[*num_produtos].preco = atof(token);
            }

            (*num_produtos)++;
        }
    }

    fclose(arquivo);
}

void listarProdutos(struct Produto *estoque, int num_produtos) {
    printf("\nProdutos Disponíveis:\n");
    for (int i = 0; i < num_produtos; i++) {
        printf("Código: %d\n", i + 1);  // Mostra o código do produto
        printf("Nome: %s\n", estoque[i].nome);
        printf("Preço: %.2f\n", estoque[i].preco);
        printf("Quantidade: %d\n\n", estoque[i].quantidade);
    }
}

void adicionarUsuarioAdmin(struct Usuario *usuarios, int *num_usuarios, int adminPassword) {
    if (*num_usuarios < 100) {  // Verifique se o limite de usuários não foi atingido
        int senhaAdmin;
        printf("Digite a senha de administrador para adicionar um novo usuário: ");
        scanf("%d", &senhaAdmin);

        if (senhaAdmin == adminPassword) {
            struct Usuario novoUsuario;

            printf("Digite o nome do novo usuário: ");
            scanf("%s", novoUsuario.nome);

            printf("Digite a senha do novo usuário: ");
            scanf("%s", novoUsuario.senha);

            printf("Defina o nível de privilégio do novo usuário (0 para usuário convencional, 1 para administrador): ");
            scanf("%d", &novoUsuario.nivel_de_privilegio);

            usuarios[*num_usuarios] = novoUsuario;  // Adicione o novo usuário ao sistema
            (*num_usuarios)++;  // Incremente o número de usuários no sistema

            printf("Usuário adicionado com sucesso!\n");
        } else {
            printf("Senha de administrador incorreta. Não é possível adicionar o usuário.\n");
        }
    } else {
        printf("O limite de usuários foi atingido. Não é possível adicionar mais usuários.\n");
    }
}

void excluirUsuarioAdmin(struct Usuario *usuarios, int *num_usuarios, int adminPassword) {
    printf("\nLista de Usuários:\n");
    for (int i = 0; i < *num_usuarios; i++) {
        printf("Número: %d, Nome: %s, Privilegio: %s\n", i + 1, usuarios[i].nome, (usuarios[i].nivel_de_privilegio == 1) ? "Admin" : "Convencional");
    }

    int numeroUsuario;
    printf("Digite o número do usuário que deseja excluir: ");
    scanf("%d", &numeroUsuario);
    numeroUsuario--;  // Ajusta o número do usuário para o índice do array.

    if (numeroUsuario >= 0 && numeroUsuario < *num_usuarios) {
        if (usuarios[numeroUsuario].nivel_de_privilegio == 1 && adminPassword == 0) {
            printf("Você não tem permissão para excluir o administrador.\n");
        } else {
            for (int i = numeroUsuario; i < *num_usuarios - 1; i++) {
                usuarios[i] = usuarios[i + 1];
            }
            (*num_usuarios)--;
            printf("Usuário excluído com sucesso.\n");
        }
    } else {
        printf("Número de usuário inválido.\n");
    }
}

void cancelarPedidoAdmin(struct Produto *estoque, int num_produtos, struct Produto *pedidos, int *num_pedidos, int adminPassword) {
    if (*num_pedidos == 0) {
        printf("Não há pedidos para cancelar.\n");
        return;
    }

    int senhaAdmin;
    printf("Digite a senha de administrador para cancelar um pedido: ");
    scanf("%d", &senhaAdmin);

    if (senhaAdmin == adminPassword) {
        // Listar os pedidos disponíveis para cancelamento
        printf("Pedidos Disponíveis para Cancelamento:\n");
        for (int i = 0; i < *num_pedidos; i++) {
            printf("%d. Produto: %s (Quantidade: %d)\n", i + 1, pedidos[i].nome, pedidos[i].quantidade);
        }

        int escolha_pedido;
        printf("Escolha o número do pedido que deseja cancelar: ");
        scanf("%d", &escolha_pedido);

        // Validar a escolha do pedido
        if (escolha_pedido < 1 || escolha_pedido > *num_pedidos) {
            printf("Escolha de pedido inválida.\n");
            return;
        }

        // Restaurar a quantidade de produtos cancelados ao estoque
        int indice_produto = encontrarIndiceProduto(estoque, num_produtos, pedidos[escolha_pedido - 1].nome);
        estoque[indice_produto].quantidade += pedidos[escolha_pedido - 1].quantidade;

        // Remover o pedido cancelado da lista, deslocando os outros pedidos, se necessário
        for (int i = escolha_pedido - 1; i < *num_pedidos - 1; i++) {
            pedidos[i] = pedidos[i + 1];
        }

        (*num_pedidos)--;  // Reduza o número de pedidos

        printf("Pedido cancelado com sucesso!\n");
    } else {
        printf("Senha de administrador incorreta. Não é possível cancelar o pedido.\n");
    }
}

void listarPedidos(struct Produto *pedidos, int num_pedidos) {
    if (num_pedidos == 0) {
        printf("Não há pedidos disponíveis.\n");
    } else {
        printf("Pedidos Disponíveis:\n");
        for (int i = 0; i < num_pedidos; i++) {
            printf("Pedido %d: Produto: %s (Quantidade: %d)\n", i + 1, pedidos[i].nome, pedidos[i].quantidade);
        }
    }
}

int encontrarIndiceProduto(struct Produto *estoque, int num_produtos, const char *nome_produto) {
    for (int i = 0; i < num_produtos; i++) {
        if (strcmp(estoque[i].nome, nome_produto) == 0) {
            return i;  // Encontrou o índice do produto com o nome correspondente
        }
    }
    return -1;  // Retornar -1 se o produto não for encontrado
}

int autenticarUsuario(struct Usuario *usuarios, int num_usuarios, const char *nomeUsuario, const char *senhaUsuario) {
    for (int i = 0; i < num_usuarios; i++) {
        if (strcmp(usuarios[i].nome, nomeUsuario) == 0 && strcmp(usuarios[i].senha, senhaUsuario) == 0) {
            return usuarios[i].nivel_de_privilegio;
        }
    }
    return -1; // Retorna -1 se a autenticação falhar
}

void lerUsuariosArquivo(struct Usuario *usuarios, int *num_usuarios, int *adminPassword) {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    *num_usuarios = 0;  // Inicialize o número de usuários lidos

    while (*num_usuarios < 100 && fscanf(arquivo, "%s %s %d", usuarios[*num_usuarios].nome, usuarios[*num_usuarios].senha, &usuarios[*num_usuarios].nivel_de_privilegio) == 3) {
        if (usuarios[*num_usuarios].nivel_de_privilegio == 1) {
            *adminPassword = atoi(usuarios[*num_usuarios].senha);  // Converta a senha do admin para int
        }
        (*num_usuarios)++;
    }

    fclose(arquivo);
}
void lerPedidosArquivo(struct Produto *pedidos, int *num_pedidos) {
    FILE *arquivo = fopen("pedidos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pedidos.\n");
        return;
    }

    *num_pedidos = 0;  // Inicialize o número de pedidos lidos

    while (*num_pedidos < 100 && fscanf(arquivo, "%d %s %f %d", &pedidos[*num_pedidos].codigo, pedidos[*num_pedidos].nome, &pedidos[*num_pedidos].preco, &pedidos[*num_pedidos].quantidade) == 4) {
        (*num_pedidos)++;
    }

    fclose(arquivo);
}
