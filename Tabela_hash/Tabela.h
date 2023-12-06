#ifndef UNTITLED2_TABELA_H
#define UNTITLED2_TABELA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct usuario {
    char login[10];
    char senha[10];
    char nome[30];
};

typedef struct {
    char *L;
    char *S;
    char *N;
} Pessoa;

typedef struct no {
    char *chave;
    Pessoa *valor;
    struct no *prox;
} No;

typedef struct dicionario {
    int tamanho; // tamanho do vetor
    No **vetor;
} Dicionario;

Dicionario *criar_dicionario (int t);
Pessoa *buscar_hash (Dicionario *d, char *chave);
Pessoa *buscar_hashE (Dicionario *d, char *chave);
bool inserir (Dicionario *d, char *chave, Pessoa *valor);
bool inserirE (Dicionario *d, char *chave, Pessoa *valor);
char *copia_string (char *s);
int hash (const char *chave, int t);
void alimenta_dicionario (Dicionario *dicionario);
void arg (char arg1[], char arg2[], int argc, char **argv);
void completa_vetor (char palavra[]);
void destruir_dicionario (Dicionario *d);
void destruir_dicionarioE (Dicionario *d);
void destruir_pessoa (Pessoa *pessoa);
void destruir_no (No *no);
void entradas (char login[], char senha[]);
void imprimir_pessoa (Dicionario *d, char *chave);
void imprimir_pessoaE (Dicionario *d, char *chave);

#endif //UNTITLED2_TABELA_H
