/*
Meta -> Criar a TAD arvore_b
criar arvore.h e criar o arvore.c

Trabalho fonte.txt -> Pegar os dados por linha do arquivo
1 -> Cadastrar
2 -> Pesquisar -------------------- Mat, Nome, Telefone
3 -> Gravar índicce
4 -> Sair


Exemplo - indice.txt
No_Pai
Linha 1 Nó Nó Nó
Linha 2 Nó Nó Nó

*/

#include <stdio.h>
#include "arvore.h"

int main() {
    int opcao;

    
    do {
        printf("Menu:\n");
        printf("Escolha uma opção: ");
        printf("1. Cadastrar\n");
        printf("2. Pesquisar\n");
        printf("3. Gravar índice\n");
        printf("4. Sair\n");
        
        scanf("%i", &opcao);
        
        switch (opcao) {
            case 1:
           // Criação da função bacana
           
                break;
            case 2:
            // Criação da função bacana

                break;
            case 3:
           // Criação da função bacana


                break;
            case 4:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (1);

    return 0;
}
