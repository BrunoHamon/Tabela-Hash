#include "Tabela.h"

Dicionario *criar_dicionario(int t) {
    Dicionario *d = NULL;
    if (t < 1) {
        return NULL;
    }
    if ((d = (Dicionario *)malloc(sizeof(Dicionario))) == NULL) {
        return NULL;
    }
    d->tamanho = t;
    if ((d->vetor = calloc(t, sizeof(No *))) == NULL) {
        return NULL;
    }
// O calloc já deve colocar NULL, mas deixo aqui de forma explícita
    for (int i = 0; i < t; ++i) {
        d->vetor[i] = NULL;
    }
    return d;
}

Pessoa *buscar_hash(Dicionario *d, char *chave) {
    int indice = hash(chave, d->tamanho);
    if (d->vetor[indice] != NULL) {
        if (strcmp(d->vetor[indice]->chave, chave) == 0) {
            return d->vetor[indice]->valor;
        }
    }
    return NULL;
}

Pessoa *buscar_hashE(Dicionario *d, char *chave) {
    int indice = hash(chave, d->tamanho);
    if (d->vetor[indice] != NULL) {
        No *aux;
        aux = d->vetor[indice];
        while (aux != NULL){
            if (strcmp(aux->chave, chave) == 0) {
                return aux->valor;
            }
            aux = aux->prox;
        }
    }
    return NULL;
}

bool inserir(Dicionario *d, char *chave, Pessoa *valor) {
    int indice = hash(chave, d->tamanho);
    No *no = malloc(sizeof(No));
    if (no == NULL) {
        return false;
    }
    // strdup reserva memória para fazer L cópia da string. Presente em string.h padrão
    // C23 https://en.cppreference.com/w/c/string/byte/strdup
    no->chave = strdup(chave);
    if (no->chave == NULL) {
        free(no);
        return false;
    }

    no->valor = valor;
    no->prox = NULL;

    // libera L memória se existir um nó anterior na posição
    destruir_no(d->vetor[indice]);
    d->vetor[indice] = no;
    return true;
}

bool inserirE(Dicionario *d, char *chave, Pessoa *valor) {
    int indice = hash(chave, d->tamanho);
    No *no = malloc(sizeof(No));
    if (no == NULL) {
        return false;
    }
    // strdup reserva memória para fazer L cópia da string. Presente em string.h padrão
    // C23 https://en.cppreference.com/w/c/string/byte/strdup
    no->chave = strdup(chave);
    if (no->chave == NULL) {
        free(no);
        return false;
    }

    no->valor = valor;
    no->prox = NULL;

    if(d->vetor[indice] == NULL){
        d->vetor[indice] = no;
    }
    else{
        No *aux;
        aux = d->vetor[indice];
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return true;
}

char * copia_string(char *s) {
    char *copia = malloc(sizeof(char) * (strlen(s) + 1));
    if (copia == NULL) {
        return NULL;
    }
    strcpy(copia, s);
    return copia;
}
// método por divisão com chave alfanumérica
int hash(const char *chave, int t) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += (i + 1) * chave[i];
    }
    return soma % t;
}

void alimenta_dicionario (Dicionario *dicionario) {
    struct usuario pessoa;
    FILE *arq;
    arq = fopen("../database.dat", "rb");

    if (arq != NULL) {
        while (!feof(arq)) {
            fread(&pessoa, sizeof(pessoa), 1, arq);

            Pessoa *p = malloc(sizeof(Pessoa));
            p->L = strdup(pessoa.login);
            p->S = strdup(pessoa.senha);
            p->N = strdup(pessoa.nome);

            inserirE(dicionario, p->L, p);
        }
    }
    fclose(arq);
}

void arg (char arg1[], char arg2[], int argc, char **argv) {
    if (argc > 1) {
        for (int i = 0; i < 10; ++i) {
            arg1[i] = argv[1][i];
            arg2[i] = argv[2][i];
        }

    } else {
        entradas(arg1, arg2);
        completa_vetor(arg1);
        completa_vetor(arg2);
    }
}

void completa_vetor (char palavra[]) {
    for (int i = 0; i < sizeof(palavra); ++i) {
        if (palavra[i] == '\0') {
            while (i < sizeof(palavra)) {
                palavra[i] = '\0';
                i++;
            }
        }
    }
}

void destruir_dicionario(Dicionario *d) {
    if (d != NULL) {
        for (int i = 0; i < d->tamanho; ++i) {
            //TODO destruir lista encadeada
            destruir_no(d->vetor[i]);
        }
        free(d->vetor);
        free(d);
    }
}

void destruir_dicionarioE(Dicionario *d) {
    if (d != NULL) {
        for (int i = 0; i < d->tamanho; ++i) {
            No* atual = d->vetor[i];
            No* prox;
            while(atual != NULL){
                prox = atual->prox;
                destruir_no(atual);
                atual = prox;
            }
            *d->vetor = NULL;
        }
        free(d->vetor);
        free(d);
    }
}

void destruir_pessoa(Pessoa *pessoa) {
    if (pessoa->L != NULL) {
        free(pessoa->L);
    }
    if (pessoa->S != NULL) {
        free(pessoa->S);
    }
    if (pessoa->N != NULL) {
        free(pessoa->N);
    }
    free(pessoa);
}

void destruir_no(No *no) {
    if (no != NULL) {
        free(no->chave);
        destruir_pessoa(no->valor);
        free(no);
    }
}

void entradas (char login[], char senha[]) {
    printf("Login: ");
    scanf("%s", login);
    printf("Senha: ");
    scanf("%s", senha);
}

void imprimir_pessoa(Dicionario *d, char *chave) {
    Pessoa *p = buscar_hash(d, chave);
    if (p != NULL) {
        printf("%s\t  %s\t  %s\n", p->L, p->S, p->N);
    } else {
        printf("%s não encontrada\n", chave);
    }
}

void imprimir_pessoaE(Dicionario *d, char *chave) {
    Pessoa *p = buscar_hashE(d, chave);
    if (p != NULL) {
        printf("%s\t  %s\t  %s\n", p->L, p->S, p->N);
    } else {
        printf("%s não encontrada\n", chave);
    }
}
