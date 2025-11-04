#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct no {
    Item info;
    struct no* prox;
} No;

typedef struct pilha {
    No* topo;
    int tamanho;
} Pilha;

PILHA cria_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro na alocação de memória da pilha!\n");
        exit(1);
    }
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

void empilha(PILHA p, Item info) {
    Pilha* pilha = (Pilha*)p;
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro na alocação de memória do nó da pilha!\n");
        exit(1);
    }
    novo->info = info;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
}

Item desempilha(PILHA p) {
    Pilha* pilha = (Pilha*)p;
    if (pilha->topo == NULL) {
        return NULL;
    }
    No* temp = pilha->topo;
    Item info = temp->info;
    pilha->topo = temp->prox;
    free(temp);
    pilha->tamanho--;
    return info;
}

Item topo_pilha(PILHA p) {
    Pilha* pilha = (Pilha*)p;
    if (pilha->topo == NULL) {
        return NULL;
    }
    return pilha->topo->info;
}

int pilha_vazia(PILHA p) {
    Pilha* pilha = (Pilha*)p;
    return (pilha->topo == NULL);
}

int tamanho_pilha(PILHA p) {
    Pilha* pilha = (Pilha*)p;
    return pilha->tamanho;
}

void destroi_pilha(PILHA p) {
    Pilha* pilha = (Pilha*)p;
    while (pilha->topo != NULL) {
        No* temp = pilha->topo;
        pilha->topo = temp->prox;
        free(temp);
    }
    free(pilha);
}

