#include "arvore.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define QUANT 4

/*
OFFSET: É a posição de um registro dentro de um arquivo -> Basicamente, é a linha do arquivo.

Algumas funções estão com o TODO com as implementações que deverão ser feitas.
*/

typedef struct Node {
    int quantidade;
    int chaves[QUANT - 1];
   struct Node *filhos[QUANT];
   bool folha;
} niceNode;

struct BTree {
    niceNode *raiz;
};

typedef struct BTree BTree;

/*
 * gravar_no_pre_ordem
 * -------------------
 * Função: percorre a árvore em pré-ordem e grava cada nó no arquivo de índice.
 *
 * Parâmetros:
 * - arquivo_indice: arquivo já aberto para escrita.
 * - no: nó atual a ser gravado.
 *
 * Retorno:
 * - 1 em sucesso.
 * - 0 em erro de escrita.
 */
static int gravar_no_pre_ordem(FILE *arquivo_indice, const niceNode *no)
{
    if (no == NULL) {
        return 1;
    }

    if (fprintf(arquivo_indice, "NO;%p;%d;%d", (void *)no, no->folha ? 1 : 0, no->quantidade) < 0) {
        return 0;
    }

    for (int i = 0; i < no->quantidade; i++) {
        if (fprintf(arquivo_indice, ";%d", no->chaves[i]) < 0) {
            return 0;
        }
    }

    for (int i = no->quantidade; i < QUANT - 1; i++) {
        if (fprintf(arquivo_indice, ";-1") < 0) {
            return 0;
        }
    }

    for (int i = 0; i < QUANT; i++) {
        if (fprintf(arquivo_indice, ";%p", (void *)no->filhos[i]) < 0) {
            return 0;
        }
    }

    if (fprintf(arquivo_indice, "\n") < 0) {
        return 0;
    }

    if (!no->folha) {
        for (int i = 0; i <= no->quantidade; i++) {
            if (!gravar_no_pre_ordem(arquivo_indice, no->filhos[i])) {
                return 0;
            }
        }
    }

    return 1;
}

/*
 * btree_criar
 * -----------
 * Função: cria uma B-Tree em memória com raiz inicial vazia (folha).
 *
 * Parâmetros:
 * - nenhum.
 *
 * Retorno:
 * - ponteiro para BTree em sucesso.
 * - NULL em falha de alocação.
 */
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

/*
 * btree_destruir --------------------------------------- A DESENVOLVER
 * --------------
 * Função: destrói a árvore e libera memória.
 *
 * Status:
 * - implementação parcial (ainda não percorre e libera todos os nós).
 */
void btree_destruir(BTree *arvore){
    if(!arvore)
    {
        printf("Erro: Árvore não existe.\n");
        return -1;
    } 

}

   /*
     * btree_inserir
     * -------------
     * Função: insere uma matrícula na B-Tree, evitando duplicatas.
     *
     * Parâmetros:
     * - arvore: árvore em memória.
     * - matricula: chave a inserir.
     * - offset: posição do registro no arquivo de dados.
     *
     * Retorno:
     * - 1 em sucesso.
     * - 0 em erro ou matrícula já existente.
     *
     * Status:
     * - implementação parcial (etapas de split e inserção em nó não cheio ainda estão em TODO).
     */
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

/*
 * btree_buscar
 * ------------
 * Função: procura uma matrícula na B-Tree percorrendo os nós do topo até folha.
 *
 * Parâmetros:
 * - arvore: árvore onde será feita a busca.
 * - matricula: chave a ser procurada.
 * - offset_encontrado: saída para offset do registro (quando disponível).
 *
 * Retorno:
 * - 1 se encontrou a matrícula.
 * - 0 se não encontrou ou em parâmetros inválidos.
 *
 * Observação:
 * - no estado atual da estrutura, o offset ainda não é armazenado por chave;
 *   por isso, offset_encontrado recebe -1.
 */
int btree_buscar(const BTree *arvore, int matricula, long int *offset_encontrado)
{
    /* 1) Validar parâmetros */
    if (arvore == NULL || arvore->raiz == NULL) {
        if (offset_encontrado != NULL) {
            *offset_encontrado = -1;
        }
        return 0;
    }

    niceNode *atual = arvore->raiz;

    while (atual != NULL) {
        int i = 0;

        while (i < atual->quantidade && matricula > atual->chaves[i]) {
            i++;
        }

        if (i < atual->quantidade && matricula == atual->chaves[i]) {
            if (offset_encontrado != NULL) {
                *offset_encontrado = -1;
            }
            return 1;
        }

        if (atual->folha) {
            break;
        }

        atual = atual->filhos[i];
    }

    /* 3) Se encontrar, preencher offset_encontrado (se não for NULL) */
    if (offset_encontrado != NULL) {
        *offset_encontrado = -1;
    }

    return 0; /* 0 = não encontrou, 1 = encontrou */
}

/*
 * carregar_arquivo_registros
 * --------------------------
 * Função: carrega o arquivo de registros texto para a B-Tree em memória.
 *
 * Parâmetros:
 * - caminho_registros: caminho do arquivo de dados.
 * - arvore: árvore que receberá as matrículas.
 *
 * Formato esperado por linha:
 * - matricula;nome;telefone
 *
 * Retorno:
 * - 1 em sucesso.
 * - 0 em erro de arquivo, parse ou inserção.
 */
int carregar_arquivo_registros(const char *caminho_registros, BTree *arvore)
{
    if (caminho_registros == NULL || arvore == NULL) {
        return 0;
    }

    FILE *arquivo = fopen(caminho_registros, "r");
    if (arquivo == NULL) {
        return 0;
    }

    char linha[256];
    while (1) {
        long int offset = ftell(arquivo);
        if (offset < 0) {
            fclose(arquivo);
            return 0;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            break;
        }

        if (linha[0] == '\n' || linha[0] == '\0') {
            continue;
        }

        int matricula;
        char nome[TAM_NOME];
        long int telefone;

        if (sscanf(linha, "%d;%99[^;];%ld", &matricula, nome, &telefone) != 3) {
            fclose(arquivo);
            return 0;
        }

        if (!btree_inserir(arvore, matricula, offset)) {
            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1; /* 1 = sucesso, 0 = erro */
}

/*
 * cadastrar_registro
 * ------------------
 * Função: cadastra um novo registro no arquivo e no índice da B-Tree.
 *
 * Status:
 * - implementação parcial (ainda contém etapas em TODO).
 */
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

/*
 * buscar_registro_por_matricula -------------- Ainda precisa ser desenvolvida 
 * -----------------------------
 * Função: busca um registro no arquivo de dados a partir da matrícula.
 *
 * Status:
 * - implementação parcial (ainda contém etapas em TODO).
 */
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
    return 0; 
}

/*
 * gravar_indice_arvore
 * --------------------
 * Função: grava a estrutura da B-Tree em arquivo de índice texto.
 *
 * Parâmetros:
 * - caminho_indice: caminho do arquivo de saída.
 * - arvore: árvore a ser serializada.
 *
 * Saída:
 * - primeira linha com o endereço da raiz.
 * - linhas seguintes com os nós em pré-ordem.
 *
 * Retorno:
 * - 1 em sucesso.
 * - 0 em erro de abertura, escrita ou fechamento do arquivo.
 */
int gravar_indice_arvore(const char *caminho_indice, const BTree *arvore)
{
    if (caminho_indice == NULL || arvore == NULL) {
        return 0;
    }

    FILE *arquivo_indice = fopen(caminho_indice, "w");
    if (arquivo_indice == NULL) { 
        return 0;
    }

    if (fprintf(arquivo_indice, "RAIZ;%p\n", (void *)arvore->raiz) < 0) {
        fclose(arquivo_indice);
        return 0;
    }

    if (!gravar_no_pre_ordem(arquivo_indice, arvore->raiz)) {
        fclose(arquivo_indice);
        return 0;
        
    }

    if (fclose(arquivo_indice) != 0) {
        return 0;
    }

    return 1;
}

