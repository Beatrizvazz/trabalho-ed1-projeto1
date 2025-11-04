#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lancadores.h"
#include "linha.h"
#include "circulo.h"
#include "texto.h"
#include "retangulo.h"
#include "arvorebin.h"
#include "formas.h"
#include "disparador.h"
#include "carregador.h"
#include "arena.h"

// Array de disparadores (0-9)
DISPARADOR disparadores[10];
// Array de carregadores
CARREGADOR carregadores[100];
int num_carregadores = 0;
// Arena global
ARENA arena_global;

void inicializa_estruturas() {
    for (int i = 0; i < 10; i++) {
        disparadores[i] = NULL;
    }
    arena_global = cria_arena();
}

void leitura_qry(FILE *arqqry, FILE **stxt, FILE **ssvg2, int *instru, int *formcriadas, int *id, AbdTree a1, float *xcent, float *ycent){
    float pontos = 0.0;
    int formasdestruidas = 0, numdisparos = 0, formasclonadas = 0;
    
    inicializa_estruturas();
    
    char* str = (char*)malloc(500 * sizeof(char));
    char* tipo = (char*)malloc(5 * sizeof(char));
    
    while(fgets(str, 500, arqqry)){
        strncpy(tipo, str, 4);  
        tipo[4] = '\0';
        
        // Comando pd: posiciona disparador
        if(strcmp(tipo, "pd l") == 0 || strncmp(str, "pd ", 3) == 0){
            int l;
            float x, y;
            sscanf(str + 3, "%d %f %f", &l, &x, &y);
            
            fprintf(*stxt, "[*] pd %d %.2f %.2f\n", l, x, y);
            fprintf(*stxt, "Disparador %d posicionado em (%.2f, %.2f)\n\n", l, x, y);
            
            if (disparadores[l] != NULL) {
                destroi_disparador(disparadores[l]);
            }
            disparadores[l] = cria_disparador(l, x, y);
            *instru = *instru + 1;
        }
        
        // Comando lc: carrega formas no carregador
        else if(strcmp(tipo, "lc c") == 0 || strncmp(str, "lc ", 3) == 0){
            int c, n;
            sscanf(str + 3, "%d %d", &c, &n);
            
            // Criar carregador se não existir
            if (c >= num_carregadores) {
                carregadores[c] = cria_carregador(c);
                num_carregadores = c + 1;
            }
            
            carrega_do_chao(carregadores[c], a1, n, stxt);
            *instru = *instru + 1;
        }
        
        // Comando atch: encaixa carregadores no disparador
        else if(strcmp(tipo, "atch") == 0){
            int d, cesq, cdir;
            sscanf(str + 5, "%d %d %d", &d, &cesq, &cdir);
            
            fprintf(*stxt, "[*] atch %d %d %d\n", d, cesq, cdir);
            fprintf(*stxt, "Encaixando carregadores %d (esquerda) e %d (direita) no disparador %d\n\n", 
                    cesq, cdir, d);
            
            if (disparadores[d] != NULL) {
                encaixa_carregadores(disparadores[d], carregadores[cesq], carregadores[cdir]);
            }
            *instru = *instru + 1;
        }
        
        // Comando shft: pressiona botão do disparador
        else if(strcmp(tipo, "shft") == 0){
            int d, n;
            char lado;
            sscanf(str + 5, "%d %c %d", &d, &lado, &n);
            
            fprintf(*stxt, "[*] shft %d %c %d\n", d, lado, n);
            fprintf(*stxt, "Pressionando botão %c do disparador %d %d vezes:\n", lado, d, n);
            
            for (int i = 0; i < n; i++) {
                Item forma;
                if (lado == 'e') {
                    forma = pressiona_botao_esquerdo(disparadores[d], stxt);
                } else {
                    forma = pressiona_botao_direito(disparadores[d], stxt);
                }
                // Reportar dados da forma que ficou em posição de disparo
            }
            fprintf(*stxt, "\n");
            *instru = *instru + 1;
        }
        
        // Comando dsp: dispara forma
        else if(strcmp(tipo, "dsp ") == 0){
            int d;
            float dx, dy;
            char vis;
            sscanf(str + 4, "%d %f %f %c", &d, &dx, &dy, &vis);
            
            fprintf(*stxt, "[*] dsp %d %.2f %.2f %c\n", d, dx, dy, vis);
            
            Item forma = get_forma_disparo(disparadores[d]);
            if (forma != NULL) {
                // Calcular posição final da forma
                float x_disp = get_x_disparador(disparadores[d]);
                float y_disp = get_y_disparador(disparadores[d]);
                
                // Mover forma para posição de disparo + deslocamento
                // set_posicao_forma(forma, x_disp + dx, y_disp + dy);
                
                // Adicionar forma na arena
                adiciona_forma_arena(arena_global, forma);
                set_forma_disparo(disparadores[d], NULL);
                
                numdisparos++;
                fprintf(*stxt, "Forma disparada para posição (%.2f, %.2f)\n\n", x_disp + dx, y_disp + dy);
                
                // Se vis == 'v', anotar dimensões do disparo no SVG
            }
            *instru = *instru + 1;
        }
        
        // Comando rjd: rajada de disparos
        else if(strcmp(tipo, "rjd ") == 0){
            int d;
            float dx, dy, ix, iy;
            char lado;
            sscanf(str + 4, "%d %c %f %f %f %f", &d, &lado, &dx, &dy, &ix, &iy);
            
            fprintf(*stxt, "[*] rjd %d %c %.2f %.2f %.2f %.2f\n", d, lado, dx, dy, ix, iy);
            fprintf(*stxt, "Rajada de disparos do disparador %d:\n", d);
            
            int i = 0;
            CARREGADOR carg;
            if (lado == 'e') {
                carg = get_carregador_esquerdo(disparadores[d]);
            } else {
                carg = get_carregador_direito(disparadores[d]);
            }
            
            while (!carregador_vazio(carg)) {
                // Equivalente a shft d [e|d] 1
                Item forma;
                if (lado == 'e') {
                    forma = pressiona_botao_esquerdo(disparadores[d], stxt);
                } else {
                    forma = pressiona_botao_direito(disparadores[d], stxt);
                }
                
                // Equivalente a dsp d dx+i*ix dy+i*iy
                if (forma != NULL) {
                    float x_disp = get_x_disparador(disparadores[d]);
                    float y_disp = get_y_disparador(disparadores[d]);
                    float x_final = x_disp + dx + i * ix;
                    float y_final = y_disp + dy + i * iy;
                    
                    // set_posicao_forma(forma, x_final, y_final);
                    adiciona_forma_arena(arena_global, forma);
                    set_forma_disparo(disparadores[d], NULL);
                    
                    numdisparos++;
                    fprintf(*stxt, "  Disparo %d: forma para posição (%.2f, %.2f)\n", i+1, x_final, y_final);
                }
                i++;
            }
            fprintf(*stxt, "\n");
            *instru = *instru + 1;
        }
        
        // Comando calc: processa arena
        else if(strcmp(tipo, "calc") == 0){
            processa_arena(arena_global, a1, stxt, ssvg2, &pontos, &formasdestruidas, &formasclonadas, id);
            *instru = *instru + 1;
        }
    }
    
    // Imprimir formas remanescentes no chão
    percursoSimetrico(a1, &printasvg, ssvg2);
    
    // Resultado final
    fprintf(*stxt, "\n=== RESULTADO FINAL ===\n");
    fprintf(*stxt, "Pontuação final: %.2f\n", pontos);
    fprintf(*stxt, "Número total de instruções executadas: %d\n", *instru);
    fprintf(*stxt, "Número total de disparos: %d\n", numdisparos);
    fprintf(*stxt, "Número total de formas esmagadas: %d\n", formasdestruidas);
    fprintf(*stxt, "Número total de formas clonadas: %d\n", formasclonadas);
    
    free(str);
    free(tipo);
}

void processa_qry(const char* pathqry, const char* dirsaida, const char* nomearqsaida, const char* nomeqry, int *instru, int *formcriadas, int *id, AbdTree a1, float *xcent, float *ycent){

    char* pathqry2=(char*)malloc(sizeof(char)*(strlen(pathqry)+6+strlen(nomeqry)));
    pathqry2[0]='\0';
    strcpy(pathqry2, pathqry);
    strcat(pathqry2, nomeqry);
    printf("Diretório do arquivo qry: %s\n", pathqry2);
    FILE* arqqry = fopen(pathqry2, "r");
    if (arqqry==NULL) {
        fprintf(stderr, "Erro na abertura do arquivo QRY: %s\n", pathqry2);
        exit(1);
    }
    printf("Diretorio de saida: %s\n", dirsaida);
    char saidasvg2[512];
    saidasvg2[0]='\0';
    strcat(saidasvg2, dirsaida);
    strcat(saidasvg2, nomearqsaida);
    strcat(saidasvg2, ".svg");

    char saidatxt[512];
    saidatxt[0]='\0';
    strcat(saidatxt, dirsaida);
    strcat(saidatxt, nomearqsaida);
    strcat(saidatxt, ".txt");
    printf("Diretório do arquivo svg2: %s\nDiretório do arquivo txt: %s\n", saidasvg2, saidatxt);
    FILE* ssvg2 = fopen(saidasvg2, "w");
    if (ssvg2==NULL) {
        fprintf(stderr, "Erro na criação do arquivo SVG: %s\n", saidasvg2);
        fclose(arqqry);
        exit(1);
    }

    fprintf(ssvg2, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(ssvg2, "<svg width=\"2000\" height=\"2000\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    FILE* stxt = fopen(saidatxt, "w");
    if (stxt==NULL) {
        fprintf(stderr, "Erro na criação do arquivo TXT: %s\n", saidatxt);
        fclose(arqqry);
        fclose(ssvg2);
        exit(1);
    }

    leitura_qry(arqqry, &stxt, &ssvg2,instru, formcriadas, id, a1, xcent, ycent);

    fprintf(ssvg2, "</svg>\n");
    fclose(arqqry);
    fclose(ssvg2);
    fclose(stxt);
    free(pathqry2);
}

