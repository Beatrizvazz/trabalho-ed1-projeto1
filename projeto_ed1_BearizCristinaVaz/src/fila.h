#ifndef fila_h
#define fila_h

/**
 * @file fila.h
 * @brief Interface para manipulação de uma estrutura de dados do tipo Fila (Queue).
 * 
 * Este módulo fornece funções para criar, manipular e liberar recursos relacionados
 * a uma fila. A fila segue o princípio FIFO (First In, First Out), onde o primeiro
 * elemento inserido é o primeiro a ser removido.
 * 
 * A estrutura da fila é opaca, ou seja, os detalhes de implementação são escondidos
 * do usuário através do uso de um ponteiro void (FILA). Isso promove encapsulamento
 * e uso seguro da estrutura.
 */

typedef void* FILA;
typedef void* Item;

/**
 * @brief Cria e inicializa uma fila vazia.
 * 
 * @return FILA Retorna um ponteiro para a fila criada.
 */
FILA cria_fila();

/**
 * @brief Insere um item no final da fila (operação enqueue).
 * 
 * @param f Ponteiro para a fila.
 * @param info Item a ser inserido no final da fila.
 */
void enfileira(FILA f, Item info);

/**
 * @brief Remove e retorna o item do início da fila (operação dequeue).
 * 
 * @param f Ponteiro para a fila.
 * @return Item Retorna o item removido do início da fila, ou NULL se a fila estiver vazia.
 */
Item desenfileira(FILA f);

/**
 * @brief Retorna o item do início da fila sem removê-lo (operação peek).
 * 
 * @param f Ponteiro para a fila.
 * @return Item Retorna o item do início da fila, ou NULL se a fila estiver vazia.
 */
Item inicio_fila(FILA f);

/**
 * @brief Verifica se a fila está vazia.
 * 
 * @param f Ponteiro para a fila.
 * @return int Retorna 1 se a fila estiver vazia, 0 caso contrário.
 */
int fila_vazia(FILA f);

/**
 * @brief Retorna o número de elementos na fila.
 * 
 * @param f Ponteiro para a fila.
 * @return int Retorna o tamanho da fila.
 */
int tamanho_fila(FILA f);

/**
 * @brief Libera toda a memória alocada pela fila.
 * 
 * @param f Ponteiro para a fila a ser liberada.
 */
void destroi_fila(FILA f);

#endif

