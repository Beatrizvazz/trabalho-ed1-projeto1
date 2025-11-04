#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
#include "carregador.h"

typedef struct disparador {
    int id;
    float x;
    float y;
    CARREGADOR carg_esquerdo;
    CARREGADOR carg_direito;
    Item forma_disparo;
} Disparador;

DISPARADOR cria_disparador(int id, float x, float y) {
    Disparador* d = (Disparador*)malloc(sizeof(Disparador));
    if (d == NULL) {
        printf("Erro na alocação de memória do disparador!\n");
        exit(1);
    }
    d->id = id;
    d->x = x;
    d->y = y;
    d->carg_esquerdo = NULL;
    d->carg_direito = NULL;
    d->forma_disparo = NULL;
    return d;
}

float get_x_disparador(DISPARADOR d) {
    Disparador* disp = (Disparador*)d;
    return disp->x;
}

float get_y_disparador(DISPARADOR d) {
    Disparador* disp = (Disparador*)d;
    return disp->y;
}

int get_id_disparador(DISPARADOR d) {
    Disparador* disp = (Disparador*)d;
    return disp->id;
}

void encaixa_carregadores(DISPARADOR d, CARREGADOR carg_esq, CARREGADOR carg_dir) {
    Disparador* disp = (Disparador*)d;
    disp->carg_esquerdo = carg_esq;
    disp->carg_direito = carg_dir;
}

Item pressiona_botao_esquerdo(DISPARADOR d, FILE** arqtxt) {
    Disparador* disp = (Disparador*)d;
    
    // Se há forma em posição de disparo, coloca no topo do carregador esquerdo
    if (disp->forma_disparo != NULL) {
        carrega_forma(disp->carg_esquerdo, disp->forma_disparo);
        disp->forma_disparo = NULL;
    }
    
    // Move o topo do carregador esquerdo para posição de disparo
    if (disp->carg_esquerdo != NULL) {
        disp->forma_disparo = descarrega_forma(disp->carg_esquerdo);
    }
    
    return disp->forma_disparo;
}

Item pressiona_botao_direito(DISPARADOR d, FILE** arqtxt) {
    Disparador* disp = (Disparador*)d;
    
    // Se há forma em posição de disparo, coloca no topo do carregador esquerdo
    if (disp->forma_disparo != NULL) {
        carrega_forma(disp->carg_esquerdo, disp->forma_disparo);
        disp->forma_disparo = NULL;
    }
    
    // Move o topo do carregador direito para posição de disparo
    if (disp->carg_direito != NULL) {
        disp->forma_disparo = descarrega_forma(disp->carg_direito);
    }
    
    return disp->forma_disparo;
}

Item get_forma_disparo(DISPARADOR d) {
    Disparador* disp = (Disparador*)d;
    return disp->forma_disparo;
}

void set_forma_disparo(DISPARADOR d, Item forma) {
    Disparador* disp = (Disparador*)d;
    disp->forma_disparo = forma;
}

CARREGADOR get_carregador_esquerdo(DISPARADOR d) {
    Disparador* disp = (Disparador*)d;
    return disp->carg_esquerdo;
}

CARREGADOR get_carregador_direito(DISPARADOR d) {
    Disparador* disp = (Disparador*)d;
    return disp->carg_direito;
}

void destroi_disparador(DISPARADOR d) {
    Disparador* disp = (Disparador*)d;
    if (disp != NULL) {
        free(disp);
    }
}

