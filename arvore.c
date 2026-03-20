#include "arvore.h"
#include <stdbool.h>
#include <stdlib.h>

#define QUANT 4

typedef struct Node {
    int quantidade;
    int chaves[QUANT - 1];
   struct Node *filhos[QUANT];
   bool folha;
} niceNode;

struct BTree {
    niceNode *raiz;
};
/*
 Algumas funções estão com o TODO com as implementações que deverão ser feitas.
*/

typedef struct BTree BTree;

BTree *btree_criar(void){
    BTree *arvore = (BTree *)malloc(sizeof(BTree));
    if (arvore == NULL) {
        return NULL;
    }

    niceNode *raiz = (niceNode *)malloc(sizeof(niceNode));
    if (raiz == NULL) {
        free(arvore);
        return NULL;
    }

    raiz->quantidade = 0;
    raiz->folha = true;

    for (int i = 0; i < QUANT; i++) {
        raiz->filhos[i] = NULL;
    }

    arvore->raiz = raiz;
    return arvore;
}

void btree_destruir(BTree *arvore){
    if(!arvore)
    {
        printf("Erro: Árvore não existe.\n");

        return -1;
    } 

}


int btree_inserir(BTree *arvore, int matricula, long int offset)
{
    if (arvore == NULL) {
        return 0;
    }

    if (btree_buscar(arvore, matricula, NULL)) {
        return 0;
    }

    /* 3) Se raiz cheia, fazer split da raiz */
    /* TODO: verificar se raiz está cheia */
    /* TODO: criar nova raiz */
    /* TODO: dividir raiz antiga */

    /* 4) Inserir em nó não cheio */
    /* TODO: chamar função auxiliar inserir_nao_cheio(...) */

    (void)offset; 
    return 1;
}

int btree_buscar(const BTree *arvore, int matricula, long int *offset_encontrado)
{
    /* 1) Validar parâmetros */
    if (arvore == NULL) {
        return 0;
    }

    /* 2) Percorrer a árvore procurando a matrícula */
    /* TODO */

    /* 3) Se encontrar, preencher offset_encontrado (se não for NULL) */
    if (offset_encontrado != NULL) {
        *offset_encontrado = -1;
    }

    (void)matricula;
    return 0; /* 0 = não encontrou, 1 = encontrou */
}

int carregar_arquivo_registros(const char *caminho_registros, BTree *arvore)
{
    /* 1) Abrir arquivo de registros */
    /* TODO */

    /* 2) Ler linha por linha */
    /* TODO */

    /* 3) Extrair matrícula/nome/telefone e inserir matrícula+offset na B-Tree */
    /* TODO */

    (void)caminho_registros;
    (void)arvore;
    return 0; /* 1 = sucesso, 0 = erro */
}

int cadastrar_registro(const char *caminho_registros, BTree *arvore, const Registro *registro)
{
    /* 1) Validar parâmetros */
    if (caminho_registros == NULL || arvore == NULL || registro == NULL) {
        return 0;
    }

    /* 2) Verificar matrícula duplicada na árvore */
    /* TODO */

    /* 3) Abrir arquivo em append, pegar offset do fim */
    /* TODO */

    /* 4) Gravar registro no arquivo */
    /* TODO */

    /* 5) Inserir matrícula+offset na B-Tree */
    /* TODO */

    return 0; /* 1 = sucesso, 0 = erro */
}

int buscar_registro_por_matricula(const char *caminho_registros, const BTree *arvore, int matricula, Registro *registro_saida)
{
    long int offset = -1;

    /* 1) Buscar matrícula na B-Tree para obter offset */
    /* TODO: chamar btree_buscar(...) */

    /* 2) Acessar arquivo diretamente no offset */
    /* TODO */

    /* 3) Ler o registro e preencher registro_saida */
    /* TODO */

    (void)caminho_registros;
    (void)arvore;
    (void)matricula;
    (void)registro_saida;
    (void)offset;
    return 0; /* 1 = encontrou, 0 = não encontrou/erro */
}

int gravar_indice_arvore(const char *caminho_indice, const BTree *arvore)
{
    /* 1) Abrir arquivo de índice para escrita */
    /* TODO */

    /* 2) Gravar endereço da raiz na primeira linha */
    /* TODO */

    /* 3) Percorrer árvore e gravar todos os nós */
    /* TODO */

    (void)caminho_indice;
    (void)arvore;
    return 0; 
}

