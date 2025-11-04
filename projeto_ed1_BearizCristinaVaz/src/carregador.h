#ifndef carregador_h
#define carregador_h

#include <stdio.h>

/**
 * @file carregador.h
 * @brief Interface para manipulação de carregadores do jogo Bocha Geométrica.
 * 
 * Este módulo fornece funções para criar, configurar e manipular carregadores.
 * Um carregador é uma pilha de formas geométricas que pode ser encaixada em
 * um disparador. As formas são carregadas e descarregadas seguindo o princípio
 * LIFO (Last In, First Out).
 */

typedef void* CARREGADOR;
typedef void* Item;
typedef void* AbdTree;

/**
 * @brief Cria um carregador vazio com identificador especificado.
 * 
 * @param id Identificador do carregador.
 * @return CARREGADOR Retorna um ponteiro para o carregador criado.
 */
CARREGADOR cria_carregador(int id);

/**
 * @brief Obtém o identificador do carregador.
 * 
 * @param c Ponteiro para o carregador.
 * @return int Identificador do carregador.
 */
int get_id_carregador(CARREGADOR c);

/**
 * @brief Carrega uma forma no carregador (empilha).
 * 
 * @param c Ponteiro para o carregador.
 * @param forma Forma a ser carregada.
 */
void carrega_forma(CARREGADOR c, Item forma);

/**
 * @brief Descarrega uma forma do carregador (desempilha).
 * 
 * @param c Ponteiro para o carregador.
 * @return Item Retorna a forma descarregada, ou NULL se o carregador estiver vazio.
 */
Item descarrega_forma(CARREGADOR c);

/**
 * @brief Carrega n formas do chão no carregador.
 * 
 * Esta função retira as primeiras n formas do chão (árvore) e as coloca
 * no carregador. Reporta os dados de cada forma carregada no arquivo txt.
 * 
 * @param c Ponteiro para o carregador.
 * @param arvore Árvore contendo as formas no chão.
 * @param n Número de formas a serem carregadas.
 * @param arqtxt Arquivo de texto para reportar as formas carregadas.
 */
void carrega_do_chao(CARREGADOR c, AbdTree arvore, int n, FILE** arqtxt);

/**
 * @brief Verifica se o carregador está vazio.
 * 
 * @param c Ponteiro para o carregador.
 * @return int Retorna 1 se o carregador estiver vazio, 0 caso contrário.
 */
int carregador_vazio(CARREGADOR c);

/**
 * @brief Retorna o número de formas no carregador.
 * 
 * @param c Ponteiro para o carregador.
 * @return int Retorna o tamanho do carregador.
 */
int tamanho_carregador(CARREGADOR c);

/**
 * @brief Libera toda a memória alocada pelo carregador.
 * 
 * @param c Ponteiro para o carregador a ser liberado.
 */
void destroi_carregador(CARREGADOR c);

#endif

