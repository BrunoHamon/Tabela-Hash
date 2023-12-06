#include "Tabela.h"

int main (int argc, char **argv) {

    char loginE[10];
    char senhaE[10];

    arg (loginE, senhaE, argc, argv);

    Dicionario *dicionario = criar_dicionario(500);
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
