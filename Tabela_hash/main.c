#include "Tabela.h"

int main () {

    char loginE[10];
    char senhaE[10];

    entradas(loginE, senhaE);
    completa_vetor(loginE);
    completa_vetor(senhaE);

    Dicionario *dicionario = criar_dicionario(100);
    if (dicionario == NULL) {
        printf("Não foi possível reservar memória\n");
        exit(EXIT_FAILURE);
    }

    alimenta_dicionario(dicionario);

    Pessoa *aux = (buscar_hashE(dicionario, loginE));

    int C = 0;

    if (aux == NULL) {
        printf("Usuário não encontrado\n");
    } else {
        for (int i = 0; i < (sizeof(aux->S)); ++i) {
            if (aux->S[i] != senhaE[i]) {
                C++;
            }
        }
        if (C == 0) {
            printf("Bem vindo %s\n", aux->N);
        } else {
            printf("Senha incorreta\n");
        }
    }

    destruir_dicionarioE(dicionario);

    return 0;
}