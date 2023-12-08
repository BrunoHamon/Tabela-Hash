//
// Created by aluno on 08/12/23.
//

#ifndef TABELA_HASH_ARVORES_H
#define TABELA_HASH_ARVORES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no {
    int valor;
    struct no *esquerda;
    struct no *direita;
} No;

No *criar_no (int valor);
No *inserir_valor (No *raiz, int valor);
bool busca (No *raiz, int valor);
void destruir_no (No *no);

#endif //TABELA_HASH_ARVORES_H
