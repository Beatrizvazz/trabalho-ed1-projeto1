#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "fila.h"
#include "formas.h"

typedef struct arena {
    FILA fila_formas;
    int num_formas;
} Arena;

ARENA cria_arena() {
    Arena* a = (Arena*)malloc(sizeof(Arena));
    if (a == NULL) {
        printf("Erro na alocação de memória da arena!\n");
        exit(1);
    }
    a->fila_formas = cria_fila();
    a->num_formas = 0;
    return a;
}

void adiciona_forma_arena(ARENA a, Item forma) {
    Arena* arena = (Arena*)a;
    enfileira(arena->fila_formas, forma);
    arena->num_formas++;
}

void processa_arena(ARENA a, AbdTree arvore, FILE** arqtxt, FILE** arqsvg, 
                   float* pontuacao, int* formas_esmagadas, int* formas_clonadas, int* id) {
    Arena* arena = (Arena*)a;
    
    fprintf(*arqtxt, "[*] calc\n");
    fprintf(*arqtxt, "Processando formas da arena:\n");
    
    float area_round = 0.0;
    int formas_destruidas_round = 0;
    
    // Processar pares de formas consecutivas
    while (tamanho_fila(arena->fila_formas) >= 2) {
        Item forma_i = desenfileira(arena->fila_formas);
        Item forma_j = desenfileira(arena->fila_formas);
        
        // Verificar sobreposição entre forma_i e forma_j
        // int sobrepoe = verifica_sobreposicao(forma_i, forma_j);
        // float area_i = calcula_area_forma(forma_i);
        // float area_j = calcula_area_forma(forma_j);
        
        // Placeholder para lógica de processamento
        // if (sobrepoe) {
        //     if (area_i < area_j) {
        //         // I é destruído, J volta ao chão
        //         area_round += area_i;
        //         formas_destruidas_round++;
        //         // marcar destruição no SVG
        //         // devolver J ao chão
        //     } else {
        //         // I muda cor da borda de J, cores trocadas
        //         // I é clonado com cores invertidas
        //         // Todos voltam ao chão
        //     }
        // } else {
        //     // Ambos voltam ao chão
        // }
    }
    
    // Processar forma restante se houver
    if (!fila_vazia(arena->fila_formas)) {
        Item forma_restante = desenfileira(arena->fila_formas);
        // Devolver ao chão
    }
    
    *pontuacao += area_round;
    *formas_esmagadas += formas_destruidas_round;
    
    fprintf(*arqtxt, "Área total esmagada no round: %.2f\n", area_round);
    fprintf(*arqtxt, "Formas destruídas no round: %d\n", formas_destruidas_round);
    fprintf(*arqtxt, "Pontuação acumulada: %.2f\n", *pontuacao);
    fprintf(*arqtxt, "\n");
    
    arena->num_formas = 0;
}

int tamanho_arena(ARENA a) {
    Arena* arena = (Arena*)a;
    return arena->num_formas;
}

int arena_vazia(ARENA a) {
    Arena* arena = (Arena*)a;
    return (arena->num_formas == 0);
}

void destroi_arena(ARENA a) {
    Arena* arena = (Arena*)a;
    if (arena != NULL) {
        destroi_fila(arena->fila_formas);
        free(arena);
    }
}

