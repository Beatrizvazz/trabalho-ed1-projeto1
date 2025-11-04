#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "formas.h"
#include "lancadores.h"
#include "lista.h"
#include "linha.h"
#include "texto.h"
#include "circulo.h"
#include "arvorebin.h"
#include "retangulo.h"
typedef void* estruturas;

typedef struct{
    estruturas estrutura;
    int numlancador[10];
    int tipoforma;
    int vivo;
}formas;

FORMASGEO setforma(FORMA f, int tipo){
    formas *f1=(formas*)malloc(sizeof(formas));
    f1->estrutura=(estruturas*)f;
    for(int i=0;i<10;i++){
        f1->numlancador[i]=0;
    }
    f1->tipoforma=tipo;
    f1->vivo=1;
    return f1;
}

int gettipoforma(FORMASGEO f){
    formas *f1=(formas*)f;
    return f1->tipoforma;
}

void printtipoformadalista(FORMASGEO f){
    formas *f1=(formas*)f;
    printf("tipo da forma: %d\n",f1->tipoforma);
}


FORMASGEO getformageo(Lista l){
    FORMASGEO f=removePrimeiroElemento(l);
    formas *f1=(formas*)f;
    return f1->estrutura;
}

float acharbaricentroRetX(float eixox, float largura){
    return eixox+largura/2;
}

float acharbaricentroRetY(float eixoy, float altura){
    return eixoy+altura/2;
}

float acharbaricentroLinX(float eixox1, float eixox2){
    return (eixox1+eixox2)/2;
}

float acharbaricentroLinY(float eixoy1, float eixoy2){
    return (eixoy1+eixoy2)/2;
}

int comparaidformas(FORMASGEO f1, FORMASGEO f2){
    formas *f3=(formas*)f1;
    formas *f4=(formas*)f2;
    if(f3->tipoforma!=f4->tipoforma){
        return 0;
    }
    if(f3->tipoforma==1){
        CIRCULO *c1=(CIRCULO*)f3->estrutura;
        CIRCULO *c2=(CIRCULO*)f4->estrutura;
        if(get_idC(c1)==get_idC(c2)){
            return 1;
        }else{
            return 0;
        }
    }
    if(f3->tipoforma==2){
        RETANGULO *r1=(RETANGULO*)f3->estrutura;
        RETANGULO *r2=(RETANGULO*)f4->estrutura;
        if(get_idR(r1)==get_idR(r2)){
            return 1;
        }else{
            return 0;
        }
    }
    if(f3->tipoforma==3){
        LINHA *l1=(LINHA*)f3->estrutura;
        LINHA *l2=(LINHA*)f4->estrutura;
        if(get_idL(l1)==get_idL(l2)){
            return 1;
        }else{
            return 0;
        }
    }
    if(f3->tipoforma==4){
        TEXTO *t1=(TEXTO*)f3->estrutura;
        TEXTO *t2=(TEXTO*)f4->estrutura;
        if(get_idC(t1)==get_idC(t2)){
            return 1;
        }else{
            return 0;
        }
    }
    return 0;   
}

float getX(FORMASGEO f){
    formas *f1=(formas*)f;
    if(f1->tipoforma==1){
        return get_XC(f1->estrutura);
    }
    if(f1->tipoforma==2){
        return get_XR(f1->estrutura);
    }
    if(f1->tipoforma==4){
        if(get_X1L(f1->estrutura)<=get_X2L(f1->estrutura)){
            if(get_X1L(f1->estrutura)==get_X2L(f1->estrutura)){
                if(get_Y1L(f1->estrutura)<=get_Y2L(f1->estrutura)){
                    return get_X1L(f1->estrutura);
                }else{
                    return get_X2L(f1->estrutura);
                }
            } else{
                return get_X1L(f1->estrutura);
            }
        } else{
            return get_X2L(f1->estrutura);
        }
    }
    if(f1->tipoforma==3){
        return get_XT(f1->estrutura);
    }
    return 0;
}

float getY(FORMASGEO f){
    formas *f1=(formas*)f;
    if(f1->tipoforma==1){
        return get_YC(f1->estrutura);
    }
    if(f1->tipoforma==2){
        return get_YR(f1->estrutura);
    }
    if(f1->tipoforma==4){
        if(get_X1L(f1->estrutura)<=get_X2L(f1->estrutura)){
            if(get_X1L(f1->estrutura)==get_X2L(f1->estrutura)){
                if(get_Y1L(f1->estrutura)<=get_Y2L(f1->estrutura)){
                    return get_Y1L(f1->estrutura);
                }else{
                    return get_Y2L(f1->estrutura);
                }
            } else{
                return get_Y1L(f1->estrutura);
            }
        } else{
            return get_Y2L(f1->estrutura);
        }
        
    }
    if(f1->tipoforma==3){
        return get_YT(f1->estrutura);
    }
    return 0;
}

float getArea(FORMASGEO f){
    formas *f1=(formas*)f;
    if(f1->tipoforma==1){
        return get_areaC(f1->estrutura);
    }
    if(f1->tipoforma==2){
        return get_areaR(f1->estrutura);
    }
    if(f1->tipoforma==4){
        return get_areaL(f1->estrutura);
    }
    if(f1->tipoforma==3){
        return get_areaT(f1->estrutura);
    }
    return 0;
}

int getID(FORMASGEO f){
    formas *f1=(formas*)f;
    if(f1->tipoforma==1){
        return get_idC(f1->estrutura);
    }
    if(f1->tipoforma==2){
        return get_idR(f1->estrutura);
    }
    if(f1->tipoforma==4){
        return get_idL(f1->estrutura);
    }
    if(f1->tipoforma==3){
        return get_idT(f1->estrutura);
    }
    return 0;
}

double pdistanciaEuclidiana(float xf, float yf, float xcent, float ycent) {
    double dx = xf - xcent;
    double dy = yf - ycent;
    return sqrt(dx * dx + dy * dy);
}

double distanciaManhattan(float xf, float yf, float xcent, float ycent) {
    double dx = fabs(xf - xcent);
    double dy = fabs(yf - ycent);
    return dx + dy;
}

int comparaEuclidianaCrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent) {
    formas *pontoA = (formas *)a;
    formas *pontoB = (formas *)b;
    double distA = pdistanciaEuclidiana(getX(pontoA), getY(pontoA), xcent, ycent);
    double distB = pdistanciaEuclidiana(getX(pontoB), getY(pontoB), xcent, ycent);
    return (distA > distB) - (distA < distB);
}

int comparaEuclidianaDecrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent) {
    formas *pontoA = (formas *)a;
    formas *pontoB = (formas *)b;
    double distA = pdistanciaEuclidiana(getX(pontoA), getY(pontoA), xcent, ycent);
    double distB = pdistanciaEuclidiana(getX(pontoB), getY(pontoB), xcent, ycent);
    return (distA < distB) - (distA > distB);
}

// Funções de comparação para distância de Manhattan
int comparaManhattanCrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent) {
    formas *pontoA = (formas *)a;
    formas *pontoB = (formas *)b;
    double distA = distanciaManhattan(getX(pontoA), getY(pontoA), xcent, ycent);
    double distB = distanciaManhattan(getX(pontoB), getY(pontoB), xcent, ycent);
    return (distA > distB) - (distA < distB);
}

int comparaManhattanDecrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent) {
    formas *pontoA = (formas *)a;
    formas *pontoB = (formas *)b;
    double distA = distanciaManhattan(getX(pontoA), getY(pontoA), xcent, ycent);
    double distB = distanciaManhattan(getX(pontoB), getY(pontoB), xcent, ycent);
    return (distA < distB) - (distA > distB);
}

// Funções de comparação para área de retângulos
int comparaAreaCrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent) {
    formas *pontoA = (formas *)a;
    formas *pontoB = (formas *)b;
    float soma=0;
    soma+=xcent;
    soma+=ycent; 
    float areaA = getArea(pontoA);
    float areaB = getArea(pontoB);
    return (areaA > areaB) - (areaA < areaB);
}

int comparaAreaDecrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent){
    formas *pontoA = (formas *)a;
    formas *pontoB = (formas *)b;
    float soma=0;
    soma+=xcent;
    soma+=ycent; 
    float areaA = getArea(pontoA);
    float areaB = getArea(pontoB);
    return (areaA < areaB) - (areaA > areaB);
}

void ordenaPorTipo(Lista L, int tipo, float xcent, float ycent){
    switch (tipo) {
        case 1:
            ordena(L, &comparaEuclidianaCrescente, xcent, ycent);
            break;
        case 2:
            ordena(L, &comparaEuclidianaDecrescente, xcent, ycent);
            break;
        case 3:
            ordena(L, &comparaManhattanCrescente, xcent, ycent);
            break;
        case 4:
            ordena(L, &comparaManhattanDecrescente, xcent, ycent);
            break;
        case 5:
            ordena(L, (int (*)(FORMASGEO, FORMASGEO, float, float))&comparaAreaCrescente, 0, 0); // Parâmetros ignorados
            break;
        case 6:
            ordena(L, (int (*)(FORMASGEO, FORMASGEO, float, float))&comparaAreaDecrescente, 0, 0); // Parâmetros ignorados
            break;
        }
}

void aplicarArea(void *info, void *c) {
    formas *forma = (formas *)info;
    float *somaAreas=(float*)c;

    float area = getArea(forma);
    *somaAreas =*somaAreas+ area; // Atualiza a clausura com a área calculada
}

FORMASGEO set_numlancador(FORMASGEO f, void* c){
    formas *f1=(formas*)f;
    int *i=(int*)c;
    f1->numlancador[*i]=1;
    return (FORMASGEO*)f1;
}

int check_forma(FORMASGEO f, void *c) {
    formas *f1 = (formas *)f;
    char *carac = (char*)c;

    switch (*carac) {
        case 'C':
            return (f1->tipoforma == 1) ? 1 : 0;
        case 'R':
            return (f1->tipoforma == 2) ? 1 : 0;
        case 'T':
            return (f1->tipoforma == 3) ? 1 : 0;
        case 'L':
            return (f1->tipoforma == 4) ? 1 : 0;
        default:
            return 0; // Característica inválida
    }
}

FORMASGEO printLista(FORMASGEO f, void *c){
    formas *f1 = (formas *)f;
    FILE *f11 = (FILE*)c;
    if(f1->tipoforma==1){
        fprintf(f11, "FORMA: CIRCULO ID: %d\n", get_idC(f1->estrutura));
    }
    if(f1->tipoforma==2){
        fprintf(f11, "FORMA: RETANGULO ID: %d\n", get_idR(f1->estrutura));
    }
    if(f1->tipoforma==3){
        fprintf(f11, "FORMA: TEXTO ID: %d\n", get_idT(f1->estrutura));
    }
    if(f1->tipoforma==4){
        fprintf(f11, "FORMA: LINHA ID: %d\n", get_idL(f1->estrutura));
    }
    return (FORMASGEO*)f1;
}

void printasvg(float x, float y, FORMASGEO f, float d, void* extra){
    formas *f1 = (formas *)f;
    FILE **arq1 = (FILE**)extra;
    float somatotal=x+y+d;
    somatotal=0;
    if(f1->vivo==1){
        if(f1->tipoforma==1){
            printsvg_circulo(arq1, f1->estrutura);
        }
        if(f1->tipoforma==2){
            printsvg_retangulo(arq1,f1->estrutura);
        }
        if(f1->tipoforma==3){
            printsvg_texto(arq1,f1->estrutura);
        }
        if(f1->tipoforma==4){
            printsvg_linha(arq1,f1->estrutura);
        }
        if(somatotal==1){
            return;
        }
    }
}


void get_maxmin(FORMASGEO f, float *max, float *min, float xcen,float ycen){
    formas *f1 = (formas *)f;
    if(f1->tipoforma==1){
        distanciaCirculo(xcen, ycen, f1->estrutura, min, max);
    }
    if(f1->tipoforma==2){
        distanciaRetangulo(xcen, ycen, f1->estrutura,min,max);
    }
    if(f1->tipoforma==3){
        distanciaTexto(xcen, ycen,f1->estrutura, min,max);
    }
    if(f1->tipoforma==4){
        distanciaLinha(xcen,ycen, f1->estrutura, min, max);
    }
}

void igualarlanc(FORMASGEO f1, FORMASGEO f2){
    formas *f3=(formas*)f1;
    formas *f4=(formas*)f2;
    for(int i=0;i<10;i++){
        f4->numlancador[i]=f3->numlancador[i];
    }
}

void mudar_lanc(FORMASGEO f, float *x1, float *y1, float *x2, float *y2, float d, AbdTree a1, float graus){
    formas *f1 = (formas *)f;
    FORMASGEO ff=setforma(f1->estrutura,f1->tipoforma);
    igualarlanc(f, ff);
    formas *f2=(formas*)ff;
    if(f2->tipoforma==1){
        *x1=get_XC(f2->estrutura);
        *y1=get_YC(f2->estrutura);
        set_xC(f2->estrutura, get_XC(f2->estrutura)+get_novadistX(graus, d));
        set_yC(f2->estrutura, get_YC(f2->estrutura)+get_novadistY(graus, d));
        insertAbd(a1, get_XC(f2->estrutura), get_YC(f2->estrutura), f2);
    }
    if(f2->tipoforma==2){
        *x1=get_XR(f2->estrutura);
        *y1=get_YR(f2->estrutura);
        set_xR(f2->estrutura, get_XR(f2->estrutura)+get_novadistX(graus, d));
        set_yR(f2->estrutura, get_YR(f2->estrutura)+get_novadistY(graus, d));
        insertAbd(a1, get_YR(f2->estrutura), get_XR(f2->estrutura), f2);
    }
    if(f2->tipoforma==3){
        *x1=get_XT(f2->estrutura);
        *y1=get_YT(f2->estrutura);
        set_xT(f2->estrutura, get_XT(f2->estrutura)+get_novadistX(graus, d));
        set_yT(f2->estrutura, get_YT(f2->estrutura)+get_novadistY(graus, d));
        insertAbd(a1, get_XT(f2->estrutura), get_YT(f2->estrutura), f2);
    }
    if(f2->tipoforma==4){
        *x1=get_X1L(f2->estrutura);
        *y1=get_Y1L(f2->estrutura);
        *x2=get_X2L(f2->estrutura);
        *y2=get_Y2L(f2->estrutura);
        set_x1L(f2->estrutura, get_X1L(f2->estrutura)+get_novadistX(graus, d));
        set_y1L(f2->estrutura, get_Y1L(f2->estrutura)+get_novadistY(graus, d));
        set_x2L(f2->estrutura, get_X2L(f2->estrutura)+get_novadistX(graus, d));
        set_y2L(f2->estrutura, get_Y2L(f2->estrutura)+get_novadistY(graus, d));
        if(*x1<*x2){
            insertAbd(a1, get_X1L(f2->estrutura), get_Y1L(f2->estrutura), f2);
        } else{
            if(*x1==*x2){
                if(*y1<*y2){
                    insertAbd(a1, get_X1L(f2->estrutura), get_Y1L(f2->estrutura), f2);
                } else{
                    insertAbd(a1, get_X2L(f2->estrutura), get_Y2L(f2->estrutura), f2);
                }
            } else{
                insertAbd(a1, get_X2L(f2->estrutura), get_Y2L(f2->estrutura), f2);
            }
        }   
    }
    destruir_form(f1);
}


void destruir_form(FORMASGEO f){
    formas *f1=(formas*)f;
    f1->vivo=0;
}

int checkvivo(void *info, void *c){
    int *i= (int*)c;
    formas *(f1)=(formas*)info;
    if(f1->vivo==*i){
        return 1;
    } else{
        return 0;
    }
}

int checkigual(void *info, void *c){
    int *i= (int*)c;
    formas *(f1)=(formas*)info;
    if(getID(f1)==*i){
        return 0;
    } else{
        return 1;
    }
}


int lanc_ogiva(FORMASGEO f, FORMASGEO falv, float x1, float y1, float x2, float y2, FILE **svg, FILE **txt, float d, AbdTree a1, float *pontos, int *formc, int *formdes, int *id, float g){
    formas *f1=(formas*)f;
    formas *f2=(formas*)falv;
    int result;
    float divarea=getArea(f2)/getArea(f1), somaarea=getArea(f1)+getArea(f2);
    if(f1->tipoforma==1){
        result=lanc_circ(f1->estrutura, d,'o',txt, svg, pontos,formc, formdes, id, x1,y1, a1, divarea, somaarea, f1, g);
    }
    if(f1->tipoforma==2){
         result=lanc_ret(f1->estrutura, d, 'o', txt, svg, pontos,formc, formdes, id, x1,y1, a1, divarea, somaarea, f1, g);
    }
    if(f1->tipoforma==3){
     result=lanc_texto(f1->estrutura, d, 'o', txt, svg, pontos,formc, formdes, id, x1,y1, a1, divarea, somaarea, f1, g);
    }
    if(f1->tipoforma==4){
         result=lanc_linha(f1->estrutura, d, 'o', txt, svg, pontos,formc, formdes, id, x1, y1, x2, y2, a1, divarea, somaarea, f1, g);
    }
    if(f2->tipoforma==1){
         result=lanc_circ(f2->estrutura, d,'a',txt, svg, pontos,formc, formdes, id, x1,y1, a1, divarea, somaarea, f2, g);
    }
    if(f2->tipoforma==2){
         result=lanc_ret(f2->estrutura, d, 'a', txt, svg, pontos,formc, formdes, id, x1,y1, a1, divarea, somaarea, f2, g);
    }
    if(f2->tipoforma==3){
         result=lanc_texto(f2->estrutura, d, 'a', txt, svg, pontos,formc, formdes, id, x1,y1, a1, divarea, somaarea, f2, g);
    }
    if(f2->tipoforma==4){
         result=lanc_linha(f2->estrutura, d, 'a', txt, svg, pontos,formc, formdes, id, x1, y1, x2, y2, a1, divarea, somaarea, f2, g);
    }
    return result;
}

Lista get_Listapornum(Lista L0, Lista L1, Lista L2,Lista L3, Lista L4, Lista L5, Lista L6, Lista L7, Lista L8, Lista L9, int l){
    if(l==0){
        return L0;
    }
    if(l==1){
        return L1;
    }
    if(l==2){
        return L2;
    }
    if(l==3){
        return L3;
    }
    if(l==4){
        return L4;
    }
    if(l==5){
        return L5;
    }
    if(l==6){
        return L6;
    }
    if(l==7){
        return L7;
    }
    if(l==8){
        return L8;
    }
    return L9;
}

void retirar_lis(FORMASGEO f, Lista l0,Lista l1,Lista l2,Lista l3,Lista l4,Lista l5,Lista l6,Lista l7,Lista l8,Lista l9, FILE **txt){
    formas *f1=(formas*)f;
    int verifica=0;
    destruir_form(f);
    for(int i=0;i<10;i++){
        if(f1->numlancador[i]==1){
            removeElemento(get_Listapornum(l0,l1,l2, l3,l4, l5,  l6,  l7,  l8,l9, i), f);
            if(verifica==0){
                fprintf(*txt, "Elemento destruido estava no(s) lancador(es): ");
                verifica=1;
            }
            fprintf(*txt, "%d ", i);
        }
    }
    fprintf(*txt,"\n");
}


void lancamento_real(Lista l0, Lista l1,Lista l2,Lista l3,Lista l4,Lista l5,Lista l6,Lista l7,Lista l8,Lista l9,Lista lf, FILE **svg, FILE **txt, float d, AbdTree a1, float xcen, float ycen, float *pontos, int *formc, int *formdes, int *id, float graus){
    Lista alv=createLst();
    int vivo=1;
    float max, min, x1, y1, x2, y2;
    lf=filter(lf,&checkvivo, &vivo);
    while(get_tamanholista(lf)!=0){
        FORMASGEO f=removePrimeiroElemento(lf);
        float g=graus;
        mudar_lanc(f, &x1, &y1, &x2, &y2, d, a1, g);
        get_maxmin(f, &max, &min, xcen, ycen);
        if(findInRegionAbd(a1, min, max, alv)==1){
        alv=filter(alv,&checkvivo, &vivo);
        int idvivo=getID(f);
        alv=filter(alv,&checkigual, &idvivo);
        if(get_tamanholista(alv)==0){
            formas *fogv=(formas*)f;
            fprintf(*txt,"\nCASO 4= ERRO NO LANCAMENTO!\n");
            if(fogv->tipoforma!=3){
                print_detruicaosvg(svg, getX(fogv),getY(fogv));
                if(fogv->tipoforma==1){
                    printatxt_circulo(txt, fogv->estrutura, 'o', 4, x1, y1);
                }
                if(fogv->tipoforma==2){
                    printatxt_retangulo(txt, fogv->estrutura, 'o', 4, x1, y1);
                }
                if(fogv->tipoforma==4){
                    printatxt_linha(txt, fogv->estrutura, 'o', 4, x1, y1, x2, y2);
                }
            } else{
                printsvg_destruicaotexto(svg, fogv->estrutura);
                printatxt_texto(txt, fogv->estrutura, 'o', 4, x1, y1);
                
            }
            retirar_lis(f,l0,l1,l2,l3,l4,l5,l6,l7,l8,l9, txt);
        }
            while(get_tamanholista(alv)>0){
                FORMASGEO falv=removePrimeiroElemento(alv);
                int aval=lanc_ogiva(f, falv,x1, y1, x2, y2, svg, txt, d, a1, pontos, formc, formdes, id, g);
                if(aval==1){
                    retirar_lis(f,l0,l1,l2,l3,l4,l5,l6,l7,l8,l9, txt);
                }
            }
        } else{
            formas *fogv=(formas*)f;
            fprintf(*txt,"\nCASO 4= ERRO NO LANCAMENTO!\n");
            if(fogv->tipoforma!=3){
                print_detruicaosvg(svg, getX(fogv),getY(fogv));
                if(fogv->tipoforma==1){
                    printatxt_circulo(txt, fogv->estrutura, 'o', 4, x1, y1);
                }
                if(fogv->tipoforma==2){
                    printatxt_retangulo(txt, fogv->estrutura, 'o', 4, x1, y1);
                }
                if(fogv->tipoforma==4){
                    printatxt_linha(txt, fogv->estrutura, 'o', 4, x1, y1, x2, y2);
                }
            } else{
                printsvg_destruicaotexto(svg, fogv->estrutura);
                printatxt_texto(txt, fogv->estrutura, 'o', 4, x1, y1);
                
            }
            retirar_lis(f,l0,l1,l2,l3,l4,l5,l6,l7,l8,l9, txt);
        }
    }
}

