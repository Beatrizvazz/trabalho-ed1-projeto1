#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tratarstrings.h"

char* tratadirentrada(const char* str) {
    
    size_t len = strlen(str);
    char* dir = (char*)malloc(sizeof(char)*(len + 1));
    if(dir==NULL){
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }
    strcpy(dir, str);

    if (dir[len - 1] == '/') {
        dir[len - 1] = '\0'; 
    }

    strcat(dir, "/\0");
    return dir;
}

char* get_nomegeo(const char* arqgeo) {
    
    const char* nomeInicio = strrchr(arqgeo, '/');
    if (!nomeInicio) {
        nomeInicio = arqgeo; 
    } else {
        nomeInicio++; 
    }

    int len = 0;
    while (nomeInicio[len] != '.' && nomeInicio[len] != '\0') {
        len++;
    }
    
    char* nomegeo = (char*)malloc(sizeof(char)*(len + 1));
    if (nomegeo == NULL) {
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) {
        nomegeo[i] = nomeInicio[i];
    }
    nomegeo[len] = '\0';

    return nomegeo;
}

char* get_nomeqry(const char* arqqry) {
   
    const char* nomeInicio = strrchr(arqqry, '/');
    if (!nomeInicio) {
        nomeInicio = arqqry;
    } else {
        nomeInicio++; 
    }
 
   
    const char* ponto = strrchr(nomeInicio, '.');
    if (!ponto) {
        printf("Erro: Nome do arquivo não contém extensão!\n");
        exit(1);
    }

    
    size_t tamanho = ponto - nomeInicio;
    char* nomeqry = (char*)malloc(sizeof(char)*(tamanho + 1)); 
    if (nomeqry == NULL) {
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }

    
    strncpy(nomeqry, nomeInicio, tamanho);
    nomeqry[tamanho] = '\0'; 

    return nomeqry;
}

char* path_qry(const char* dire, const char* arqgeo, int possibilidade) {
    
    size_t len_arqgeo = strlen(arqgeo);
    char* aux = (char*)malloc(sizeof(char)*(len_arqgeo + 1)); 
    if (aux == NULL) {
        printf("Erro na alocação de memória para aux!\n");
        exit(1);
    }
    strcpy(aux, arqgeo);

    
    size_t ext_len = 4;  
    if (len_arqgeo >= ext_len && strcmp(aux + len_arqgeo - ext_len, ".geo") == 0) {
        aux[len_arqgeo - ext_len] = '\0';  
    }

    char* pathqry;
    if (possibilidade == 1) {
       
        size_t len_dire = strlen(dire);
        pathqry = (char*)malloc(sizeof(char)*(len_dire + strlen(aux) + 1));
        if (pathqry == NULL) {
            printf("Erro na alocação de memória para pathqry!\n");
            free(aux);
            exit(1);
        }

       
        strcpy(pathqry, dire);
        strcat(pathqry, aux);
    } else {
       
        pathqry = (char*)malloc(sizeof(char)*(strlen(aux) + 1)); 
        if (pathqry == NULL) {
            printf("Erro na alocação de memória para pathqry!\n");
            free(aux);
            exit(1);
        }

        strcpy(pathqry, aux);
    }

    free(aux);
    return pathqry;
}

char* get_concatnomeqry(const char* nomegeo, const char* nomeqry) {
   
    size_t tamanho = strlen(nomegeo) + strlen(nomeqry) + 2; 
    char* concatnome = (char*)malloc(sizeof(char)*tamanho);

    if (concatnome == NULL) {
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }

   
    concatnome[0] = '\0';

    strcat(concatnome, nomegeo);
    strcat(concatnome, "-");
    strcat(concatnome, nomeqry);
    return concatnome;
}