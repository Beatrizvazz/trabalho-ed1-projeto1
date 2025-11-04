#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "arvorebin.h"
#include "lista.h"

typedef void* Iinfo;


typedef struct TreeNodeStruct {
    double x, y;                    
    Iinfo info;                     
    struct TreeNodeStruct *left;    
    struct TreeNodeStruct *right;   
} TreeNodeStruct;


typedef struct {
    double x_ref, y_ref;          
    double epsilon;                 
    TreeNodeStruct *root;           
} AbdTreeStruct;


double distanciaEuclidiana(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


AbdTree createAbd(double x, double y, double epsilon) {
    AbdTreeStruct *tree = (AbdTreeStruct *)malloc(sizeof(AbdTreeStruct));
    if (tree == NULL){
        printf("Erro na alocação de memória!\n");
        exit(1);
    }

    tree->x_ref = x;
    tree->y_ref = y;
    tree->epsilon = epsilon;
    tree->root = NULL;

    return (AbdTree)tree;
}


TreeNodeStruct *createTreeNode(double x, double y, Info info) {
    TreeNodeStruct *node = (TreeNodeStruct *)malloc(sizeof(TreeNodeStruct));
    if (node == NULL) return NULL;

    node->x = x;
    node->y = y;
    node->info = info;
    node->left = NULL;
    node->right = NULL;

    return node;
}


void insertAbd(AbdTree b, double x, double y, Info info){
    AbdTreeStruct *tree = (AbdTreeStruct *)b;
    TreeNodeStruct **current = &(tree->root);

    double distNovo = distanciaEuclidiana(x, y, tree->x_ref, tree->y_ref);

    while (*current != NULL) {
        
        double distAtual = distanciaEuclidiana((*current)->x, (*current)->y, tree->x_ref, tree->y_ref);

        
        if (fabs(distNovo - distAtual) < tree->epsilon) {
            
            if (x < (*current)->x) {
                current = &((*current)->left); 
            } 
            else if (x > (*current)->x) {
                current = &((*current)->right); 
            } 
            else {
                
                if (y < (*current)->y) {
                    current = &((*current)->left); 
                } 
                else if (y > (*current)->y) {
                    current = &((*current)->right); 
                } 
                else {
                    
                    return;
                }
            }
        }
        
        else if (distNovo < distAtual) {
            current = &((*current)->left); 
        } 
        else {
            current = &((*current)->right); 
        }
    }

    
    *current = createTreeNode(x, y, info);
}


int searchAbd(AbdTree b, double x, double y, Info *info) {
    AbdTreeStruct *tree = (AbdTreeStruct *)b;
    TreeNodeStruct *current = tree->root;

    while (current != NULL) {
        if (fabs(current->x - x) < tree->epsilon && fabs(current->y - y) < tree->epsilon) {
            *info = current->info;
            return 1;
        }

        if (x < current->x || (fabs(x - current->x) < tree->epsilon && y < current->y)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return 0;
}


TreeNodeStruct *findMin(TreeNodeStruct *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}


int removeAbd(AbdTree b, double x, double y, Info *info){
    
    AbdTreeStruct *tree = (AbdTreeStruct *)b;
    TreeNodeStruct **current = &(tree->root), *temp;
   
    while (*current){
        
        if (fabs((*current)->x - x) < tree->epsilon && fabs((*current)->y - y) < tree->epsilon){
            *info = (*current)->info;
           
            if ((*current)->left && (*current)->right){
                TreeNodeStruct **succ = &((*current)->right);
               
                while ((*succ)->left){
                    succ = &((*succ)->left);
                }

                (*current)->x = (*succ)->x;
                (*current)->y = (*succ)->y;
                (*current)->info = (*succ)->info;
                temp = *succ;
                *succ = (*succ)->right;
            } 
            
            else{
                
                temp = *current;
                *current = (*current)->left ? (*current)->left : (*current)->right;
            }
            
            free(temp);
            return 1;
        }
        current = (x < (*current)->x) ? &((*current)->left) : &((*current)->right);
    }
    return 0;
}


int findInRegionAbd(AbdTree b, double distMin, double distMax, Lista lres) {
    if (b == NULL || lres == NULL) return 0; 

    AbdTreeStruct *tree = (AbdTreeStruct *)b;
    int found = 0;

    
    void percorre(TreeNodeStruct *node, int isRoot) {
        if (node == NULL) return;

        double dist = distanciaEuclidiana(node->x, node->y, tree->x_ref, tree->y_ref);

        
        if ((dist >= distMin - tree->epsilon && dist <= distMax + tree->epsilon) && !isRoot) {
            insertLst(lres, node->info);
            found = 1;
        }

        
        percorre(node->left, 0);
        percorre(node->right, 0);
    }

    if (tree->root != NULL) {
        
        percorre(tree->root, 1);
    }

    return found;
}

Info getInfoAbd(AbdTree b, TreeNode n) {
    AbdTreeStruct *a1=(AbdTreeStruct*)b;
    TreeNodeStruct *node = (TreeNodeStruct *)n;
    if(searchAbd(a1,node->x,node->y,node->info)==1){
        return node->info;
    } else{
        return NULL;
    }
}


void percursoSimetrico(AbdTree b, VisitaNo vf, void* extra) {
    AbdTreeStruct *tree = (AbdTreeStruct *)b;
    void percorre(TreeNodeStruct *node) {
        if (node == NULL) return;

        percorre(node->left);
        if (vf != NULL) {
            double dist = distanciaEuclidiana(node->x, node->y, tree->x_ref, tree->y_ref);
            vf(node->x, node->y, node->info, dist, extra);
        }
        percorre(node->right);
    }

    percorre(tree->root);
}


void dfs(AbdTree b, VisitaNo vf, void* extra) {
    AbdTreeStruct *tree = (AbdTreeStruct *)b;

    void percorre(TreeNodeStruct *node) {
        if (node == NULL) return;

        if (vf != NULL) {
            double dist = distanciaEuclidiana(node->x, node->y, tree->x_ref, tree->y_ref);
            vf(node->x, node->y, node->info, dist, extra);
        }

        percorre(node->left);
        percorre(node->right);
    }

    percorre(tree->root);
}

void bfs(AbdTree b, VisitaNo vf, void* extra) {
    AbdTreeStruct *tree = (AbdTreeStruct *)b;
    if (tree->root == NULL) return;

    
    TreeNodeStruct *queue[1000]; 
    int front = 0, rear = 0;

    queue[rear++] = tree->root;

    while (front < rear) {
        TreeNodeStruct *node = queue[front++];

        if (vf != NULL) {
            double dist = distanciaEuclidiana(node->x, node->y, tree->x_ref, tree->y_ref);
            vf(node->x, node->y, node->info, dist, extra);
        }

        if (node->left != NULL) queue[rear++] = node->left;
        if (node->right != NULL) queue[rear++] = node->right;
    }
}