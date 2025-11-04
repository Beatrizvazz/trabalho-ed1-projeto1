#include <stdio.h>
#include <stdlib.h>
#include "carregador.h"
#include "pilha.h"
#include "formas.h"

typedef struct carregador {
    int id;
    PILHA pilha;
} Carregador;

CARREGADOR cria_carregador(int id) {
    Carregador* c = (Carregador*)malloc(sizeof(Carregador));
    if (c == NULL) {
        printf("Erro na alocação de memória do carregador!\n");
        exit(1);
    }
    c->id = id;
    c->pilha = cria_pilha();
    return c;
}

int get_id_carregador(CARREGADOR c) {
    Carregador* carr = (Carregador*)c;
    return carr->id;
}

void carrega_forma(CARREGADOR c, Item forma) {
    Carregador* carr = (Carregador*)c;
    empilha(carr->pilha, forma);
}

Item descarrega_forma(CARREGADOR c) {
    Carregador* carr = (Carregador*)c;
    return desempilha(carr->pilha);
}

void carrega_do_chao(CARREGADOR c, AbdTree arvore, int n, FILE** arqtxt) {
    Carregador* carr = (Carregador*)c;
    
    fprintf(*arqtxt, "[*] lc %d %d\n", carr->id, n);
    fprintf(*arqtxt, "Carregando %d formas do chão no carregador %d:\n", n, carr->id);
    
    // Carregar n formas da árvore para o carregador
    for (int i = 0; i < n; i++) {
        // Aqui seria necessário implementar a lógica para retirar formas da árvore
        // Por enquanto, deixamos como placeholder
        // Item forma = retira_forma_do_chao(arvore);
        // if (forma != NULL) {
        //     carrega_forma(c, forma);
        //     // Reportar dados da forma
        //     reporta_forma(arqtxt, forma);
        // }
    }
    
    fprintf(*arqtxt, "\n");
}

int carregador_vazio(CARREGADOR c) {
    Carregador* carr = (Carregador*)c;
    return pilha_vazia(carr->pilha);
}

int tamanho_carregador(CARREGADOR c) {
    Carregador* carr = (Carregador*)c;
    return tamanho_pilha(carr->pilha);
}

void destroi_carregador(CARREGADOR c) {
    Carregador* carr = (Carregador*)c;
    if (carr != NULL) {
        destroi_pilha(carr->pilha);
        free(carr);
    }
}

