#ifndef ARVORE_H
#define ARVORE_H

#define TAM_NOME 100

typedef struct {
    int mat;
    char nome[TAM_NOME];
    long int tel;
} Registro;

typedef struct BTree BTree;

BTree *btree_criar(void);
void btree_destruir(BTree *arvore);

int btree_inserir(BTree *arvore, int matricula, long int offset);
int btree_buscar(const BTree *arvore, int matricula, long int *offset_encontrado);

int carregar_arquivo_registros(const char *caminho_registros, BTree *arvore);
int cadastrar_registro(const char *caminho_registros, BTree *arvore, const Registro *registro);
int buscar_registro_por_matricula(const char *caminho_registros, const BTree *arvore, int matricula, Registro *registro_saida);
int gravar_indice_arvore(const char *caminho_indice, const BTree *arvore);

#endif // ARVORE_H
