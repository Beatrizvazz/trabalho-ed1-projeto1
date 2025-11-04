#ifndef arena_h
#define arena_h

#include <stdio.h>

/**
 * @file arena.h
 * @brief Interface para manipulação da arena do jogo Bocha Geométrica.
 * 
 * Este módulo fornece funções para gerenciar a arena onde as formas são
 * lançadas e processadas. A arena mantém uma fila de formas lançadas
 * e processa colisões entre elas conforme as regras do jogo.
 */

typedef void* ARENA;
typedef void* Item;
typedef void* AbdTree;

/**
 * @brief Cria uma arena vazia.
 * 
 * @return ARENA Retorna um ponteiro para a arena criada.
 */
ARENA cria_arena();

/**
 * @brief Adiciona uma forma lançada na arena.
 * 
 * @param a Ponteiro para a arena.
 * @param forma Forma a ser adicionada.
 */
void adiciona_forma_arena(ARENA a, Item forma);

/**
 * @brief Processa as formas na arena conforme as regras do jogo.
 * 
 * Processa as formas na ordem em que foram lançadas:
 * - Se área(I) < área(J): I é destruído, J volta ao chão
 * - Se área(I) > área(J): I muda cor da borda de J, cores são trocadas,
 *   I é clonado com cores invertidas
 * - Se não há sobreposição: ambos voltam ao chão
 * 
 * @param a Ponteiro para a arena.
 * @param arvore Árvore para devolver formas ao chão.
 * @param arqtxt Arquivo de texto para reportar resultados.
 * @param arqsvg Arquivo SVG para marcar formas esmagadas.
 * @param pontuacao Ponteiro para acumular pontuação.
 * @param formas_esmagadas Ponteiro para contar formas esmagadas.
 * @param formas_clonadas Ponteiro para contar formas clonadas.
 * @param id Ponteiro para o próximo ID disponível.
 */
void processa_arena(ARENA a, AbdTree arvore, FILE** arqtxt, FILE** arqsvg, 
                   float* pontuacao, int* formas_esmagadas, int* formas_clonadas, int* id);

/**
 * @brief Retorna o número de formas na arena.
 * 
 * @param a Ponteiro para a arena.
 * @return int Número de formas na arena.
 */
int tamanho_arena(ARENA a);

/**
 * @brief Verifica se a arena está vazia.
 * 
 * @param a Ponteiro para a arena.
 * @return int Retorna 1 se a arena estiver vazia, 0 caso contrário.
 */
int arena_vazia(ARENA a);

/**
 * @brief Libera toda a memória alocada pela arena.
 * 
 * @param a Ponteiro para a arena a ser liberada.
 */
void destroi_arena(ARENA a);

#endif

