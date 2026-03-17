#ifndef ARVORE_H
#define ARVORE_H

/*
*/
#define TAM 100

typedef struct {
    int mat;
    char nome[TAM];
    long int tel;
} registro_st;

typedef registro_st *registro;

typedef struct {
    registro registros;
    int chave;
} node_st;

typedef struct {
    int chaves;

    
}

  typedef struct {
 int quantidade;
 int chave;
int folha;
int posicao;
 *filho;
} noBacana;



struct tree_st {
    node_st *nodes;
};

registro 
criar_registro();

void 
apagar_registro(registro r);

registro 
pesquisar(int mat);

#endif // ARVORE_H
