#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgc.h"

int main() {
    // Inicialização das estruturas de dados
    struct Produto estoque[100];
    int num_produtos = 0;

    struct Usuario usuarios[100];
    int num_usuarios = 0;

    struct Produto pedidos[100];
    int num_pedidos = 0;

    int adminPassword;

    int opcao;
    
    int i = -1;

    printf("Bem-vindo ao Sistema de Gestão Comercial (SGC)!\n");
    // Carregue o estoque no início do programa
    lerEstoqueArquivo(estoque, &num_produtos);

    // Carregue os dados dos usuários no início do programa
    lerUsuariosArquivo(usuarios, &num_usuarios, &adminPassword);
    
    // Carregue os pedidos no início do programa
    lerPedidosArquivo(pedidos, &num_pedidos);

    while (1) {
        printf("\nMenu de Opções:\n");
        printf("1. Acesso Administrativo\n");
        printf("2. Acesso de Usuário Convencional\n");
        printf("3. Sair\n");
        printf("Escolha a opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Acesso administrativo
            char nomeUsuario[100];
            char senhaUsuario[100];

            printf("Digite seu nome de usuário: ");
            scanf("%s", nomeUsuario);
            printf("Digite sua senha: ");
            scanf("%s", senhaUsuario);

            int nivelPrivilegio = autenticarUsuario(usuarios, num_usuarios, nomeUsuario, senhaUsuario);

            if (nivelPrivilegio == 1) {
                // Menu de opções para administradores
                int opcaoAdmin;
                do {
                    printf("\nAcesso Administrativo\n");
                    printf("1. Adicionar Produto ao Estoque\n");
                    printf("2. Listar Produtos Disponíveis\n");
                    printf("3. Adicionar Usuário\n");
                    printf("4. Excluir Usuário\n");
                    printf("5. Cancelar Pedido\n");
                    printf("6. Encerrar Sessão Administrativa\n");
                    printf("Escolha a opção: ");
                    scanf("%d", &opcaoAdmin);


                switch (opcaoAdmin) {
                    case 1:
                        adicionarProdutoAdmin(estoque, &num_produtos);
                        break;
                    case 2:
                        listarProdutos(estoque, num_produtos);
                        break;
                    case 3:
                        adicionarUsuarioAdmin(usuarios, &num_usuarios, adminPassword);
                        break;
                    case 4:
                        excluirUsuarioAdmin(usuarios, &num_usuarios, adminPassword);
                        break;
                    case 5:
                        cancelarPedidoAdmin(estoque, num_produtos, pedidos, &num_pedidos, adminPassword);
                        break;
                    case 6:
                        // Sair do acesso administrativo
                        break;
                    default:
                        printf("Opção inválida.\n");
                    }
                }while (opcaoAdmin != 6);
            } else {
                printf("Usuário não é administrador ou credenciais inválidas.\n");
            }
        
    } else if (opcao == 2) {
            // Acesso de usuário convencional
             int opcaoUsuario;
            do {
                printf("\nAcesso de Usuário Convencional\n");
                printf("1. Fazer Pedido\n");
                printf("2. Listar Produtos Disponíveis\n");
                printf("3. Listar Pedidos Feitos\n");
                printf("4. Encerrar Sessão de Usuário Convencional\n");
                printf("Escolha a opção: ");
                scanf("%d", &opcaoUsuario);

                switch (opcaoUsuario) {
                    case 1:
                        fazerPedido(estoque, num_produtos, &usuarios[i], pedidos, &num_pedidos);
                        break;
                    case 2:
                        listarProdutos(estoque, num_produtos);
                        break;
                    case 3:
                        listarPedidos(pedidos, num_pedidos);
                        break;
                    case 4:
                        // Sair do acesso de usuário convencional
                        break;
                    default:
                        printf("Opção inválida.\n");
                }
            } while (opcaoUsuario != 4);
        } else if (opcao == 3) {
            salvarPedidosArquivo(pedidos, num_pedidos);
            printf("Saindo do Sistema de Gestão Comercial. Até logo!\n");
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }

    return 0;
}
