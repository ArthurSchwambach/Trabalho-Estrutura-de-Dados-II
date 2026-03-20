#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

static void limpar_buffer_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static void ler_string(const char *mensagem, char *saida, size_t tamanho_saida) {
    printf("%s", mensagem);
    if (fgets(saida, (int)tamanho_saida, stdin) != NULL) {
        size_t tamanho = strlen(saida);
        if (tamanho > 0 && saida[tamanho - 1] == '\n') {
            saida[tamanho - 1] = '\0';
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo_registros.txt> <arquivo_indice.txt>\n", argv[0]);
        return 1;
    }

    const char *arquivo_registros = argv[1];
    const char *arquivo_indice = argv[2];

    BTree *arvore = btree_criar();
    if (arvore == NULL) {
        printf("Erro: não foi possível criar a árvore B em memória.\n");
        return 1;
    }

    if (!carregar_arquivo_registros(arquivo_registros, arvore)) {
        printf("Erro ao carregar arquivo de registros: %s\n", arquivo_registros);
        btree_destruir(arvore);
        return 1;
    }

    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar\n");
        printf("2. Pesquisar\n");
        printf("3. Gravar\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida.\n");
            limpar_buffer_entrada();
            continue;
        }
        limpar_buffer_entrada();
        
        switch (opcao) {
            case 1:
            {
                Registro novo;
                printf("Matrícula: ");
                if (scanf("%d", &novo.mat) != 1) {
                    printf("Matrícula inválida.\n");
                    limpar_buffer_entrada();
                    break;
                }
                limpar_buffer_entrada();

                ler_string("Nome: ", novo.nome, sizeof(novo.nome));

                printf("Telefone: ");
                if (scanf("%ld", &novo.tel) != 1) {
                    printf("Telefone inválido.\n");
                    limpar_buffer_entrada();
                    break;
                }
                limpar_buffer_entrada();

                if (cadastrar_registro(arquivo_registros, arvore, &novo)) {
                    printf("Cadastro realizado com sucesso.\n");
                } else {
                    printf("Não foi possível cadastrar (matrícula já existe ou erro de arquivo).\n");
                }
                break;
            }
            case 2:
            {
                int matricula;
                Registro encontrado;
                printf("Matrícula para pesquisa: ");
                if (scanf("%d", &matricula) != 1) {
                    printf("Matrícula inválida.\n");
                    limpar_buffer_entrada();
                    break;
                }
                limpar_buffer_entrada();

                if (buscar_registro_por_matricula(arquivo_registros, arvore, matricula, &encontrado)) {
                    printf("Encontrado:\n");
                    printf("Matrícula: %d\n", encontrado.mat);
                    printf("Nome: %s\n", encontrado.nome);
                    printf("Telefone: %ld\n", encontrado.tel);
                } else {
                    printf("Matrícula não encontrada.\n");
                }
                break;
            }
            case 3:
                if (gravar_indice_arvore(arquivo_indice, arvore)) {
                    printf("Índice gravado em: %s\n", arquivo_indice);
                } else {
                    printf("Erro ao gravar índice.\n");
                }

                break;
            case 4:
                printf("Saindo...\n");
                btree_destruir(arvore);
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (1);
}
