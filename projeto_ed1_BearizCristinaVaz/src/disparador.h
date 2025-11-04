#ifndef disparador_h
#define disparador_h

#include <stdio.h>

/**
 * @file disparador.h
 * @brief Interface para manipulação de disparadores do jogo Bocha Geométrica.
 * 
 * Este módulo fornece funções para criar, configurar e manipular disparadores.
 * Um disparador possui:
 * - Posição (x, y) na arena
 * - 2 carregadores (esquerda e direita)
 * - 1 posição de disparo
 * - Botões de seleção de carga (marrom para direita, lilás para esquerda)
 * 
 * Os carregadores são implementados como pilhas (LIFO), onde formas são
 * empilhadas e desempilhadas conforme os botões são pressionados.
 */

typedef void* DISPARADOR;
typedef void* CARREGADOR;
typedef void* Item;

/**
 * @brief Cria um disparador na posição especificada.
 * 
 * @param id Identificador do disparador.
 * @param x Coordenada x do disparador.
 * @param y Coordenada y do disparador.
 * @return DISPARADOR Retorna um ponteiro para o disparador criado.
 */
DISPARADOR cria_disparador(int id, float x, float y);

/**
 * @brief Obtém a coordenada x do disparador.
 * 
 * @param d Ponteiro para o disparador.
 * @return float Coordenada x do disparador.
 */
float get_x_disparador(DISPARADOR d);

/**
 * @brief Obtém a coordenada y do disparador.
 * 
 * @param d Ponteiro para o disparador.
 * @return float Coordenada y do disparador.
 */
float get_y_disparador(DISPARADOR d);

/**
 * @brief Obtém o identificador do disparador.
 * 
 * @param d Ponteiro para o disparador.
 * @return int Identificador do disparador.
 */
int get_id_disparador(DISPARADOR d);

/**
 * @brief Encaixa carregadores no disparador.
 * 
 * @param d Ponteiro para o disparador.
 * @param carg_esq Carregador da esquerda.
 * @param carg_dir Carregador da direita.
 */
void encaixa_carregadores(DISPARADOR d, CARREGADOR carg_esq, CARREGADOR carg_dir);

/**
 * @brief Pressiona o botão esquerdo (lilás) do disparador.
 * 
 * Move a forma da posição de disparo para o topo do carregador esquerdo,
 * depois move o topo do carregador esquerdo para a posição de disparo.
 * 
 * @param d Ponteiro para o disparador.
 * @param arqtxt Arquivo de texto para reportar a operação.
 * @return Item Retorna a forma que ficou na posição de disparo.
 */
Item pressiona_botao_esquerdo(DISPARADOR d, FILE** arqtxt);

/**
 * @brief Pressiona o botão direito (marrom) do disparador.
 * 
 * Move a forma da posição de disparo para o topo do carregador esquerdo,
 * depois move o topo do carregador direito para a posição de disparo.
 * 
 * @param d Ponteiro para o disparador.
 * @param arqtxt Arquivo de texto para reportar a operação.
 * @return Item Retorna a forma que ficou na posição de disparo.
 */
Item pressiona_botao_direito(DISPARADOR d, FILE** arqtxt);

/**
 * @brief Obtém a forma em posição de disparo.
 * 
 * @param d Ponteiro para o disparador.
 * @return Item Retorna a forma em posição de disparo, ou NULL se não houver.
 */
Item get_forma_disparo(DISPARADOR d);

/**
 * @brief Define a forma em posição de disparo.
 * 
 * @param d Ponteiro para o disparador.
 * @param forma Forma a ser colocada em posição de disparo.
 */
void set_forma_disparo(DISPARADOR d, Item forma);

/**
 * @brief Obtém o carregador esquerdo do disparador.
 * 
 * @param d Ponteiro para o disparador.
 * @return CARREGADOR Retorna o carregador esquerdo.
 */
CARREGADOR get_carregador_esquerdo(DISPARADOR d);

/**
 * @brief Obtém o carregador direito do disparador.
 * 
 * @param d Ponteiro para o disparador.
 * @return CARREGADOR Retorna o carregador direito.
 */
CARREGADOR get_carregador_direito(DISPARADOR d);

/**
 * @brief Libera toda a memória alocada pelo disparador.
 * 
 * @param d Ponteiro para o disparador a ser liberado.
 */
void destroi_disparador(DISPARADOR d);

#endif

