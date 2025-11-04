#ifndef pilha_h
#define pilha_h

/**
 * @file pilha.h
 * @brief Interface para manipulação de uma estrutura de dados do tipo Pilha (Stack).
 * 
 * Este módulo fornece funções para criar, manipular e liberar recursos relacionados
 * a uma pilha. A pilha segue o princípio LIFO (Last In, First Out), onde o último
 * elemento inserido é o primeiro a ser removido.
 * 
 * A estrutura da pilha é opaca, ou seja, os detalhes de implementação são escondidos
 * do usuário através do uso de um ponteiro void (PILHA). Isso promove encapsulamento
 * e uso seguro da estrutura.
 */

typedef void* PILHA;
typedef void* Item;

/**
 * @brief Cria e inicializa uma pilha vazia.
 * 
 * @return PILHA Retorna um ponteiro para a pilha criada.
 */
PILHA cria_pilha();

/**
 * @brief Insere um item no topo da pilha (operação push).
 * 
 * @param p Ponteiro para a pilha.
 * @param info Item a ser inserido no topo da pilha.
 */
void empilha(PILHA p, Item info);

/**
 * @brief Remove e retorna o item do topo da pilha (operação pop).
 * 
 * @param p Ponteiro para a pilha.
 * @return Item Retorna o item removido do topo da pilha, ou NULL se a pilha estiver vazia.
 */
Item desempilha(PILHA p);

/**
 * @brief Retorna o item do topo da pilha sem removê-lo (operação peek).
 * 
 * @param p Ponteiro para a pilha.
 * @return Item Retorna o item do topo da pilha, ou NULL se a pilha estiver vazia.
 */
Item topo_pilha(PILHA p);

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param p Ponteiro para a pilha.
 * @return int Retorna 1 se a pilha estiver vazia, 0 caso contrário.
 */
int pilha_vazia(PILHA p);

/**
 * @brief Retorna o número de elementos na pilha.
 * 
 * @param p Ponteiro para a pilha.
 * @return int Retorna o tamanho da pilha.
 */
int tamanho_pilha(PILHA p);

/**
 * @brief Libera toda a memória alocada pela pilha.
 * 
 * @param p Ponteiro para a pilha a ser liberada.
 */
void destroi_pilha(PILHA p);

#endif

