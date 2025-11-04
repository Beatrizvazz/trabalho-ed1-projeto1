#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lista.h"
#include "formas.h"


typedef void* item;


typedef struct Node {
    item info;          
    struct Node *next; 
} Node;


typedef struct {
    Node *first;        
    Node *last;         
    int size;          
} ListaStruct;


void troca(item *a, item *b) {
    item temp = *a;
    *a = *b;
    *b = temp;
}

Node *particiona(Node *low, Node *high, int (*compara)(item, item, float, float), float xcent, float ycent) {
    if (!low || !high) return NULL;

    item pivot = high->info;
    Node *i = low, *prev_i = NULL;

    for (Node *j = low; j != high; j = j->next) {
        if (compara(j->info, pivot, xcent, ycent) <= 0) {
            if (i != j) troca(&(i->info), &(j->info));
            prev_i = i;
            i = i->next;
        }
    }
    if (i != high) troca(&(i->info), &(high->info));

    return prev_i ? prev_i->next : low;
}

void quickSort(Node *low, Node *high, int (*compara)(item, item, float, float), float xcent, float ycent) {
    if (low == NULL || high == NULL || low == high || low == high->next) return;
    
    Node *pivot = particiona(low, high, compara, xcent, ycent);

    
    if (pivot && pivot != low) {
        Node *prev = low;
        while (prev->next != pivot) prev = prev->next;  
        quickSort(low, prev, compara, xcent, ycent);
    }

    
    if (pivot && pivot->next && pivot->next != high) {
        quickSort(pivot->next, high, compara, xcent, ycent);
    }
}

void ordena(Lista L, int (*compara)(item, item, float, float), float xcent, float ycent) {
    ListaStruct *lista = (ListaStruct *)L;
    if (!lista || lista->size <= 1) return;

    quickSort(lista->first, lista->last, compara, xcent, ycent);
}


Lista createLst() {
    ListaStruct *L = (ListaStruct *)malloc(sizeof(ListaStruct));
    if (L == NULL){
        printf("Erro na alocação de memória!\n");
        exit(1);
    }

    L->first = NULL;
    L->last = NULL;
    L->size = 0;

    return (Lista)L;
}


void insertLst(Lista L, Item info) {
    ListaStruct *lista = (ListaStruct *)L;

    
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return;

    newNode->info = info;
    newNode->next = NULL;

    
    if (lista->first == NULL) {
        lista->first = newNode;
    } else {
        lista->last->next = newNode;
    }
    lista->last = newNode;
    lista->size++;
}


Item getInfo(Lista L, int p) {
    ListaStruct *lista = (ListaStruct *)L;
    Node *node = lista->first;
    int pos = 0;

    while (node != NULL && pos < p) {
        node = node->next;
        pos++;
    }

    if (node != NULL) {
        return node->info;
    }
    return NULL; 
}

int get_tamanholista(Lista L){
    ListaStruct *lista = (ListaStruct *)L;
    return lista->size;
}


void killLst(Lista L) {
    ListaStruct *lista = (ListaStruct *)L;
    Node *node = lista->first;
    Node *nextNode;

    while (node != NULL) {
        nextNode = node->next;
        free(node);
        node = nextNode;
    }

    free(lista);
}

void removeElemento(Lista l, Item i) {
    ListaStruct *lista=(ListaStruct*)l;
    item *info=(item*)i;
    
    if (lista->first == NULL) {
        return;
    }

    Node *atual = lista->first;
    Node *anterior = NULL;

   
    while (atual != NULL && atual->info != info) {
        anterior = atual;
        atual = atual->next;
    }

    
    if (atual == NULL) {
        return;
    }

    
    if (anterior == NULL) {
        lista->first = atual->next;
        if (lista->first == NULL) {
            
            lista->last = NULL;
        }
    }
    
    else {
        anterior->next = atual->next;
        if (atual->next == NULL) {
            
            lista->last = anterior;
        }
    }

    
    free(atual);
    lista->size=lista->size-1;
}

Item removePrimeiroElemento(Lista l) {
    ListaStruct *lista = (ListaStruct*)l;

    
    if (lista->first == NULL) {
        return NULL; 
    }

    
    Node *primeiro = lista->first;

    
    lista->first = primeiro->next;

    
    if (lista->first == NULL) {
        lista->last = NULL;
    }

    
    lista->size = lista->size - 1;

    
    Item itemRemovido = primeiro->info;

    

    
    return itemRemovido;
}


Lista map(Lista L, Apply f, Clausura c) {
    ListaStruct *lista = (ListaStruct *)L;
    Lista novaLista = createLst();

    Node *node = lista->first;
    while (node != NULL) {
        Item novoItem = f(node->info, c);
        insertLst(novaLista, novoItem);
        node = node->next;
    }
    return novaLista;
}


Lista filter(Lista L, Check f, Clausura c) {
    ListaStruct *lista = (ListaStruct *)L;
    Lista novaLista = createLst();

    Node *node = lista->first;
    while (node != NULL) {
        if (f(node->info, c)==1) {
            insertLst(novaLista, node->info);
        }
        node = node->next;
    }

    return novaLista;
}

void fold(Lista L, ApplyClosure f, Clausura c) {
    ListaStruct *lista = (ListaStruct *)L;
    Node *node = lista->first;

    while (node != NULL) {
        f(node->info, c);
        node = node->next;
    }
}
