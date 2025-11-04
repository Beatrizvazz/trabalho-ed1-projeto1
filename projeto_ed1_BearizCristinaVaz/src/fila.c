#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct no {
    Item info;
    struct no* prox;
} No;

typedef struct fila {
    No* inicio;
    No* fim;
    int tamanho;
} Fila;

FILA cria_fila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if (f == NULL) {
        printf("Erro na alocação de memória da fila!\n");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

void enfileira(FILA f, Item info) {
    Fila* fila = (Fila*)f;
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro na alocação de memória do nó da fila!\n");
        exit(1);
    }
    novo->info = info;
    novo->prox = NULL;
    
    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->tamanho++;
}

Item desenfileira(FILA f) {
    Fila* fila = (Fila*)f;
    if (fila->inicio == NULL) {
        return NULL;
    }
    No* temp = fila->inicio;
    Item info = temp->info;
    fila->inicio = temp->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(temp);
    fila->tamanho--;
    return info;
}

Item inicio_fila(FILA f) {
    Fila* fila = (Fila*)f;
    if (fila->inicio == NULL) {
        return NULL;
    }
    return fila->inicio->info;
}

int fila_vazia(FILA f) {
    Fila* fila = (Fila*)f;
    return (fila->inicio == NULL);
}

int tamanho_fila(FILA f) {
    Fila* fila = (Fila*)f;
    return fila->tamanho;
}

void destroi_fila(FILA f) {
    Fila* fila = (Fila*)f;
    while (fila->inicio != NULL) {
        No* temp = fila->inicio;
        fila->inicio = temp->prox;
        free(temp);
    }
    free(fila);
}

