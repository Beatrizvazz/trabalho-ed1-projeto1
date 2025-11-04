#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lancadores.h"
#include "processageo.h"
#include "tratarstrings.h"
#include "processaqry.h"
#include "arvorebin.h"

// main com entrada dos argumentos que serao lidos
int main(int argc, char* argv[]) {
    // criacao de strings pra dirEntrada, geo, qry e dirSaida
    char *dirEntrada = NULL, *arquivoGeo = NULL, *arquivoQry = NULL, *dirSaida = NULL;
    int existegeo=0, existeqry=0;

    // loop para leitura dos parametros
    for (int i = 1; i < argc; i++) {
        // acoes no diretorio de dirEntrada
        if (strcmp(argv[i], "-e") == 0 ) {
            dirEntrada = tratadirentrada(argv[i+1]);
            existegeo=1;
        // passagem dos argumentos para a string aquivoGeo
        } else if (strcmp(argv[i], "-f") == 0 ) {
            arquivoGeo = (char*)malloc(sizeof(char)*(strlen(argv[i + 1]) + 5));
            if(arquivoGeo==NULL){
            printf("Erro na alocação de memória da string!\n");
            exit(1);
            }
            strcpy(arquivoGeo, argv[i + 1]);
        // passagem dos argumentos para a strigng arquivoQry
        } else if (strcmp(argv[i], "-q") == 0 ) {
            arquivoQry = (char*)malloc(sizeof(char)*(strlen(argv[i + 1]) + 5));
            if(arquivoQry==NULL){
            printf("Erro na alocação de memória da string!\n");
            exit(1);
            }
            strcpy(arquivoQry, argv[i + 1]);
            existeqry=1;
        // acoes no dirSaida
        } else if (strcmp(argv[i], "-o") == 0 ) {
            dirSaida =tratadirentrada(argv[i+1]);
        }
    }

    int instru=0, formcriadas=0, id=0;
    float xcent, ycent;
    char* nomegeo = get_nomegeo(arquivoGeo);
    AbdTree arvore;
    if(existegeo==1){
        char* entradageo = (char*)malloc(sizeof(char)*(strlen(dirEntrada)+strlen(arquivoGeo)+1));
        strcat(entradageo, dirEntrada);
        strcat(entradageo, arquivoGeo);
        arvore=processa_geo(entradageo, dirSaida, nomegeo, &instru, &formcriadas, &id, &xcent, &ycent);
    } else{
        arvore=processa_geo(arquivoGeo, dirSaida, nomegeo, &instru, &formcriadas, &id, &xcent, &ycent);
    }

   if(existeqry==1){
     char* nomearqsaida= get_concatnomeqry(nomegeo, get_nomeqry(arquivoQry));
     processa_qry(dirEntrada, dirSaida, nomearqsaida, arquivoQry, &instru, &formcriadas, &id, arvore, &xcent, &ycent);
   }
    
    return 0;
}