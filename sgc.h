#ifndef SGC_H
#define SGC_H

// Definição da estrutura produto
struct Produto {
    int codigo;
    char nome[100];
    float preco;
    int quantidade;
};

// Definição da estrutura usuario
struct Usuario {
    char nome[100];
    char senha[100];
    int nivel_de_privilegio; // 0 para usuário convencional, 1 para administrador
};

// Assinaturas de funções para administradores
void lerUsuariosArquivo(struct Usuario *usuarios, int *num_usuarios, int *adminPassword);
void adicionarProdutoAdmin(struct Produto *estoque, int *num_produtos);
void adicionarUsuarioAdmin(struct Usuario *usuarios, int *num_usuarios, int adminPassword);
void excluirUsuarioAdmin(struct Usuario *usuarios, int *num_usuarios, int adminPassword);
int autenticarUsuario(struct Usuario *usuarios, int num_usuarios, const char *nomeUsuario, const char *senhaUsuario);
void cancelarPedidoAdmin(struct Produto *estoque, int num_produtos, struct Produto *pedidos, int *num_pedidos, int adminPassword);

// Outras funções
void listarProdutos(struct Produto *estoque, int num_produtos);
void carregarEstoque(struct Produto *estoque, int *num_produtos);
void salvarEstoqueArquivo(struct Produto estoque[], int num_produtos);
void lerEstoqueArquivo(struct Produto *estoque, int *num_produtos);
void fazerPedido(struct Produto *estoque, int num_produtos, struct Usuario *usuario, struct Produto *pedidos, int *num_pedidos);
void lerPedidosArquivo(struct Produto *pedidos, int *num_pedidos);
void salvarPedidosArquivo(struct Produto pedidos[], int num_pedidos);
void listarPedidos(struct Produto *pedidos, int num_pedidos);
int encontrarIndiceProduto(struct Produto *estoque, int num_produtos, const char *nome_produto);


#endif
