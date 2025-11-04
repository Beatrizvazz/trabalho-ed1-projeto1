#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "formas.h"
#include "lancadores.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "arvorebin.h"
#include "lista.h"

typedef struct{
    float graus;
    int numlanc;
    Lista lis;
}lanc;

LANC cria_lanc(int i){
    lanc *l=malloc(sizeof(lanc));
    l->lis=createLst();
    l->graus=0;
    l->numlanc=i;
    return l;
}

int getnumlancador(LANC l){
    lanc *l1=(lanc*)l;
    return l1->numlanc;
}

void printsvg_circulo(FILE **arq, FORMA f){
    CIRCULO *c=((CIRCULO*)f);
    fprintf(*arq, "<circle style=\"fill:%s;fill-opacity:0.5;stroke:%s\" r=\"%0.2f\" cy=\"%0.2f\" cx=\"%0.2f\" />\n", get_cpC(c), get_cbC(c), get_rC(c), get_YC(c), get_XC(c));
}

void printsvg_retangulo(FILE **arq, FORMA f){
    RETANGULO *r=((RETANGULO*)f);
    fprintf(*arq, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\"  fill=\"%s\"/>\n", 
            get_XR(r), get_YR(r), get_wR(r), get_hR(r), get_cbR(r), get_cpR(r));
}

void printsvg_linha(FILE **arq, FORMA f){
    LINHA *l=((LINHA*)f);
    fprintf(*arq, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" />\n",  get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), get_cL(l));
}

void printsvg_texto(FILE **arq, FORMA f){
    TEXTO *t=((TEXTO*)f);
    fprintf(*arq, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"%s\" fill=\"%s\" stroke=\"%s\" font-family=\"%s\" font-weight=\"%s\" text-anchor=\"%s\" >%s</text>\n",get_XT(t), get_YT(t), get_fsT(t), get_cpT(t), get_cbT(t), get_ffT(t), get_fwT(t), get_ancoraT(t), get_txtT(t));
}

void carrega_lancador(LANC l, AbdTree a1, float dmin, float dmax, FILE **arq, int sort, char t, float xcent, float ycent){
    lanc *l1=((lanc*)l);
    int i=findInRegionAbd(a1, dmin, dmax, l1->lis);
    float soma=0;
    if(i==0){
        fprintf(*arq, "Nenhuma forma, dentro das distancias fornecidas do centro de gravidade, foi encontrada!\n");
    } else{
        if(t!='*'){
            l1->lis=filter(l1->lis,&check_forma, &t);
            if(get_tamanholista(l1->lis)==0){
                fprintf(*arq, "Não foi possível encontrar nenhuma forma do tipo escolhido!\n");
                return;
            }
        }
        ordenaPorTipo(l1->lis, sort, xcent, ycent);
        fprintf(*arq, "Formas inseridas no lançador:\n");
        int numlancadorr=getnumlancador(l1);
        l1->lis=map(l1->lis, &set_numlancador, &numlancadorr);
        l1->lis=map(l1->lis, &printLista, *arq);
        fold(l1->lis, &aplicarArea, &soma);
        fprintf(*arq, "Soma das áreas das formas do lançador: %f\n", soma);
    }
}

void faz_lancamento(LANC l0,LANC l1,LANC l2,LANC l3,LANC l4,LANC l5,LANC l6,LANC l7,LANC l8,LANC l9, LANC lc, FILE **arqsvg, FILE **arqtxt, float dista, AbdTree a1, float xcen, float ycen, float *pontos, int *formc, int *formdes, int *id, float graus){
    lanc *l01=(lanc*)l0,*l11=(lanc*)l1,*l21=(lanc*)l2,*l31=(lanc*)l3,*l41=(lanc*)l4,*l51=(lanc*)l5,*l61=(lanc*)l6,*l71=(lanc*)l7,*l81=(lanc*)l8,*l91=(lanc*)l9,*lc1=(lanc*)lc;
    lancamento_real(l01->lis, l11->lis,l21->lis,l31->lis,l41->lis,l51->lis,l61->lis,l71->lis,l81->lis,l91->lis,lc1->lis, arqsvg, arqtxt,dista, a1, xcen, ycen, pontos, formc, formdes, id, graus);
}

void print_detruicaosvg(FILE **arq, float x, float y){
    fprintf(*arq, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"20\" fill=\"red\" font-family=\"arial\" text-anchor=\"middle\" >*</text>\n", x, y);
}

void printsvg_destruicaotexto(FILE **arq, FORMA f){
    TEXTO *t=((TEXTO*)f);
    fprintf(*arq, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"%s\" fill=\"red\" font-family=\"%s\" font-weight=\"%s\" text-anchor=\"%s\" >*%s*</text>\n",get_XT(t), get_YT(t), get_fsT(t), get_ffT(t), get_fwT(t),get_ancoraT(t), get_txtT(t));
    }

void printatxt_cabecalhort(FILE **arq, int l, float g){
    fprintf(*arq, "[*] rt %d %0.2f\n",l, g);
}

void printatxt_cabecalhosel(FILE **arq, int l, char t, float dmin, float dmax, char* co){
    fprintf(*arq, "[*] sel %d %c %0.2f %0.2f %s\n",l, t, dmin, dmax, co);
}

void printatxt_cabecalholc(FILE **arq, int la, float dista){
    fprintf(*arq, "[*] lc %d %0.2f\n",la, dista);
}

void printatxt_circulo(FILE **arq, FORMA f, char a, int ac, float xini, float yini){
    CIRCULO *c=((CIRCULO*)f);
    if(a=='a'){
        if(ac==1){
        fprintf(*arq, "Círculo = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nRaio: %0.2f\nCentro do circulo: x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nSTATUS: CLONADO\n", get_idC(c), xini, yini, get_rC(c), get_XC(c), get_YC(c), get_cbC(c), get_cpC(c));
        }
        if(ac==2){
        fprintf(*arq, "Círculo = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nRaio: %0.2f\nCentro do circulo: x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nSTATUS: DESTRUIDO\n", get_idC(c), xini, yini, get_rC(c), get_XC(c), get_YC(c), get_cbC(c), get_cpC(c)); 
        }
        if(ac==3){
        fprintf(*arq, "Círculo = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nRaio: %0.2f\nCentro do circulo: x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nSTATUS: VIVO\n", get_idC(c), xini, yini, get_rC(c), get_XC(c), get_YC(c), get_cbC(c), get_cpC(c));    
        }
        if(ac==4){
        fprintf(*arq, "Círculo = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nRaio: %0.2f\nCentro do circulo: x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nSTATUS: RECARREGADO\n", get_idC(c), xini, yini, get_rC(c), get_XC(c), get_YC(c), get_cbC(c), get_cpC(c));    
        }
    } else{
        if(ac==1){
            fprintf(*arq, "Círculo = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nRaio: %0.2f\nCentro do circulo: x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nSTATUS: CLONADO\n", get_idC(c), xini, yini, get_rC(c), get_XC(c), get_YC(c), get_cbC(c), get_cpC(c));
        }
        if(ac==2){
            fprintf(*arq, "Círculo = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nRaio: %0.2f\nCentro do circulo: x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nSTATUS: RECARREGADO\n", get_idC(c), xini, yini, get_rC(c), get_XC(c), get_YC(c), get_cbC(c), get_cpC(c));
        }
        if(ac==3){
            fprintf(*arq, "Círculo = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nRaio: %0.2f\nCentro do circulo: x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nSTATUS: VIVO\n", get_idC(c), xini, yini, get_rC(c), get_XC(c), get_YC(c), get_cbC(c), get_cpC(c));
        }
        if(ac==4){
            fprintf(*arq, "Círculo = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nRaio: %0.2f\nCentro do circulo: x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nSTATUS: DESTRUIDO\n", get_idC(c), xini, yini, get_rC(c), get_XC(c), get_YC(c), get_cbC(c), get_cpC(c));
        
        }   
    }
}

void printatxt_retangulo(FILE **arq, FORMA f, char a, int ac, float xini, float yini){
    RETANGULO *r=((RETANGULO*)f);
    if(a=='a'){
        if(ac==1){
            fprintf(*arq, "Retangulo = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nAltura= %f\nComprimento= %f\nÂncora: x=%0.2f y=%0.2f\nCor borda: %s\n Cor preenchimento: %s\nSTATUS: CLONADO\n", get_idR(r), xini, yini, get_hR(r), get_wR(r), get_XR(r), get_YR(r), get_cbR(r), get_cpR(r));
        }
        if(ac==2){
            fprintf(*arq, "Retangulo = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nAltura= %f\nComprimento= %f\nÂncora: x=%0.2f y=%0.2f\nCor borda: %s\n Cor preenchimento: %s\nSTATUS: DESTRUIDO\n", get_idR(r), xini, yini, get_hR(r), get_wR(r), get_XR(r), get_YR(r), get_cbR(r), get_cpR(r));
        }
        if(ac==3){
            fprintf(*arq, "Retangulo = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nAltura= %f\nComprimento= %f\nÂncora: x=%0.2f y=%0.2f\nCor borda: %s\n Cor preenchimento: %s\nSTATUS: VIVO\n", get_idR(r), xini, yini, get_hR(r), get_wR(r), get_XR(r), get_YR(r), get_cbR(r), get_cpR(r));
        }
        if(ac==4){
             fprintf(*arq, "Retangulo = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nAltura= %f\nComprimento= %f\nÂncora: x=%0.2f y=%0.2f\nCor borda: %s\n Cor preenchimento: %s\nSTATUS: RECARREGADO\n", get_idR(r), xini, yini, get_hR(r), get_wR(r), get_XR(r), get_YR(r), get_cbR(r), get_cpR(r));
        }
    } else{
        if(ac==1){
            fprintf(*arq, "Retangulo = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nAltura= %f\nComprimento= %f\nÂncora: x=%0.2f y=%0.2f\nCor borda: %s\n Cor preenchimento: %s\nSTATUS: CLONADO\n", get_idR(r), xini, yini, get_hR(r), get_wR(r), get_XR(r), get_YR(r), get_cbR(r), get_cpR(r));
        }
        if(ac==2){
            fprintf(*arq, "Retangulo = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nAltura= %f\nComprimento= %f\nÂncora: x=%0.2f y=%0.2f\nCor borda: %s\n Cor preenchimento: %s\nSTATUS: RECARREGADO\n", get_idR(r), xini, yini, get_hR(r), get_wR(r), get_XR(r), get_YR(r), get_cbR(r), get_cpR(r));
        }
        if(ac==3){
             fprintf(*arq, "Retangulo = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nAltura= %f\nComprimento= %f\nÂncora: x=%0.2f y=%0.2f\nCor borda: %s\n Cor preenchimento: %s\nSTATUS: VIVO\n", get_idR(r), xini, yini, get_hR(r), get_wR(r), get_XR(r), get_YR(r), get_cbR(r), get_cpR(r));
        }
        if(ac==4){
             fprintf(*arq, "Retangulo = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nAltura= %f\nComprimento= %f\nÂncora: x=%0.2f y=%0.2f\nCor borda: %s\n Cor preenchimento: %s\nSTATUS: DESTRUIDO\n", get_idR(r), xini, yini, get_hR(r), get_wR(r), get_XR(r), get_YR(r), get_cbR(r), get_cpR(r));
        }
    }
}

void printatxt_linha(FILE **arq, FORMA f, char a, int ac, float xini1, float yini1, float xini2, float yini2){
    LINHA *l=((LINHA*)f);
    if(a=='a'){
        if(ac==1){
            fprintf(*arq, "Linha = ALVO\nID= %d\nX1 inicial:%0.2f Y1 inicial: %0.2f X2 inicial:%0.2f Y2 inicial: %0.2f\nÂncora Inicial: x=%0.2f y=%0.2f\nÂncora final: x=%0.2f y=%0.2f\nCor: %s\nSTATUS: CLONADO\n", get_idL(l), xini1, yini1, xini2, yini2, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), get_cL(l));
        }
        if(ac==2){
            fprintf(*arq, "Linha = ALVO\nID= %d\nX1 inicial:%0.2f Y1 inicial: %0.2f X2 inicial:%0.2f Y2 inicial: %0.2f\nÂncora Inicial: x=%0.2f y=%0.2f\nÂncora final: x=%0.2f y=%0.2f\nCor: %s\nSTATUS: DESTRUIDO\n", get_idL(l), xini1, yini1, xini2, yini2, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), get_cL(l));
        }
        if(ac==3){
            fprintf(*arq, "Linha = ALVO\nID= %d\nX1 inicial:%0.2f Y1 inicial: %0.2f X2 inicial:%0.2f Y2 inicial: %0.2f\nÂncora Inicial: x=%0.2f y=%0.2f\nÂncora final: x=%0.2f y=%0.2f\nCor: %s\nSTATUS: VIVO\n", get_idL(l), xini1, yini1, xini2, yini2, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), get_cL(l));
        }
        if(ac==4){
            fprintf(*arq, "Linha = ALVO\nID= %d\nX1 inicial:%0.2f Y1 inicial: %0.2f X2 inicial:%0.2f Y2 inicial: %0.2f\nÂncora Inicial: x=%0.2f y=%0.2f\nÂncora final: x=%0.2f y=%0.2f\nCor: %s\nSTATUS: RECARREGADO\n", get_idL(l), xini1, yini1, xini2, yini2, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), get_cL(l));
        }
    } else{
        if(ac==1){
            fprintf(*arq, "Linha = OGIVA\nID= %d\nX1 inicial:%0.2f Y1 inicial: %0.2f X2 inicial:%0.2f Y2 inicial: %0.2f\nÂncora Inicial: x=%0.2f y=%0.2f\nÂncora final: x=%0.2f y=%0.2f\nCor: %s\nSTATUS: CLONADO\n", get_idL(l), xini1, yini1, xini2, yini2, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), get_cL(l));
        }
        if(ac==2){
            fprintf(*arq, "Linha = OGIVA\nID= %d\nX1 inicial:%0.2f Y1 inicial: %0.2f X2 inicial:%0.2f Y2 inicial: %0.2f\nÂncora Inicial: x=%0.2f y=%0.2f\nÂncora final: x=%0.2f y=%0.2f\nCor: %s\nSTATUS: RECARREGADO\n", get_idL(l), xini1, yini1, xini2, yini2, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), get_cL(l));
        }
        if(ac==3){
            fprintf(*arq, "Linha = OGIVA\nID= %d\nX1 inicial:%0.2f Y1 inicial: %0.2f X2 inicial:%0.2f Y2 inicial: %0.2f\nÂncora Inicial: x=%0.2f y=%0.2f\nÂncora final: x=%0.2f y=%0.2f\nCor: %s\nSTATUS: VIVO\n", get_idL(l), xini1, yini1, xini2, yini2, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), get_cL(l));
        }
        if(ac==4){
            fprintf(*arq, "Linha = OGIVA\nID= %d\nX1 inicial:%0.2f Y1 inicial: %0.2f X2 inicial:%0.2f Y2 inicial: %0.2f\nÂncora Inicial: x=%0.2f y=%0.2f\nÂncora final: x=%0.2f y=%0.2f\nCor: %s\nSTATUS: DESTRUIDO\n", get_idL(l), xini1, yini1, xini2, yini2, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), get_cL(l));
        }
    }
}

void printatxt_texto(FILE **arq, FORMA f, char a, int ac, float xini, float yini){
    TEXTO *t=((TEXTO*)f);
    if(a=='a'){
        if(ac==1){
            fprintf(*arq, "Texto = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nÂncora: a=%s x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nFamily: %s\nWeight: %s\nSize: %s\nTexto: %s\nSTATUS: CLONADO\n", get_idT(t), xini, yini,get_ancoraT(t), get_XT(t), get_YT(t), get_cbT(t), get_cpT(t), get_ffT(t), get_fwT(t), get_fsT(t), get_txtT(t));
        }
        if(ac==2){
            fprintf(*arq, "Texto = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nÂncora: a=%s x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nFamily: %s\nWeight: %s\nSize: %s\nTexto: %s\nSTATUS: DESTRUIDO\n", get_idT(t), xini, yini,get_ancoraT(t), get_XT(t), get_YT(t), get_cbT(t), get_cpT(t), get_ffT(t), get_fwT(t), get_fsT(t), get_txtT(t));
        }
        if(ac==3){
            fprintf(*arq, "Texto = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nÂncora: a=%s x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nFamily: %s\nWeight: %s\nSize: %s\nTexto: %s\nSTATUS: VIVO\n", get_idT(t), xini, yini,get_ancoraT(t), get_XT(t), get_YT(t), get_cbT(t), get_cpT(t), get_ffT(t), get_fwT(t), get_fsT(t), get_txtT(t));
        }
        if(ac==4){
            fprintf(*arq, "Texto = ALVO\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nÂncora: a=%s x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nFamily: %s\nWeight: %s\nSize: %s\nTexto: %s\nSTATUS: RECARREGADO\n", get_idT(t), xini, yini,get_ancoraT(t), get_XT(t), get_YT(t), get_cbT(t), get_cpT(t), get_ffT(t), get_fwT(t), get_fsT(t), get_txtT(t));
        }
    } else{
        if(ac==1){
            fprintf(*arq, "Texto = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nÂncora: a=%s x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nFamily: %s\nWeight: %s\nSize: %s\nTexto: %s\nSTATUS: CLONADO\n", get_idT(t), xini, yini,get_ancoraT(t), get_XT(t), get_YT(t), get_cbT(t), get_cpT(t), get_ffT(t), get_fwT(t), get_fsT(t), get_txtT(t));
        }
        if(ac==2){
            fprintf(*arq, "Texto = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nÂncora: a=%s x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nFamily: %s\nWeight: %s\nSize: %s\nTexto: %s\nSTATUS: RECARREGADO\n", get_idT(t), xini, yini,get_ancoraT(t), get_XT(t), get_YT(t), get_cbT(t), get_cpT(t), get_ffT(t), get_fwT(t), get_fsT(t), get_txtT(t));
        }
        if(ac==3){
            fprintf(*arq, "Texto = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nÂncora: a=%s x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nFamily: %s\nWeight: %s\nSize: %s\nTexto: %s\nSTATUS: VIVO\n", get_idT(t), xini, yini,get_ancoraT(t), get_XT(t), get_YT(t), get_cbT(t), get_cpT(t), get_ffT(t), get_fwT(t), get_fsT(t), get_txtT(t));
        }
        if(ac==4){
            fprintf(*arq, "Texto = OGIVA\nID= %d\nX inicial:%0.2f Y inicial: %0.2f\nÂncora: a=%s x=%0.2f y=%0.2f\nCor borda: %s\nCor preenchimento: %s\nFamily: %s\nWeight: %s\nSize: %s\nTexto: %s\nSTATUS: DESTRUIDO\n", get_idT(t), xini, yini,get_ancoraT(t), get_XT(t), get_YT(t), get_cbT(t), get_cpT(t), get_ffT(t), get_fwT(t), get_fsT(t), get_txtT(t));
        }
    }
}

FORMA descarrega_lanc(LANC l){
    lanc *l1=((lanc*)l);
    FORMA f=getformageo(l1->lis);
    return f;
}

int lanc_circ(FORMA fc, float dista, char a, FILE **arqtxt, FILE **arqsvg, float *pontos, int *formc, int *formdestr, int *id, float axini, float ayini, AbdTree a1, float divarea, float somaarea, FORMASGEO ff1, float g){
    CIRCULO *c=((CIRCULO*)fc);
    int resultado=0;
    FORMASGEO f1, f2;
    if(a=='a'){
        if(divarea>=0.9 && divarea<=1.1){
            //Caso a diferença entre as áreas seja de apenas 90%, ambas as formas sao 'clonadas' recarregadas e depois os clones sao carregados tambem
            *id=*id+1;
            printatxt_circulo(arqtxt, c, 'a', 1,get_XC(c), get_YC(c));
            CIRCULO c2=cria_circulo(*id, get_XC(c), get_YC(c), get_rC(c), "#d400aa", get_cpC(c));
            set_xC(c, get_XC(c)-get_novadistX(g, dista)/2);
            set_yC(c, get_YC(c)-get_novadistY(g, dista)/2);
            f1=setforma(c2, 1);
            f2=setforma(c, 1);
            igualarlanc(ff1, f2);
            destruir_form(ff1);
            insertAbd(a1, get_XC(c2), get_YC(c2), f1);
            insertAbd(a1, get_XC(c), get_YC(c), f2);
            *formc=*formc+1;
        }
            if(divarea<0.9){
                print_detruicaosvg(arqsvg, get_XC(c), get_YC(c));
                printatxt_circulo(arqtxt, fc, 'a', 2,get_XC(c), get_YC(c));
                fprintf(*arqtxt, "Pontos atribuidos do lançamento: %0.2f!\n", divarea*100);
                *pontos=*pontos+(divarea*100);
                resultado=1;
            }
            if(divarea>1.1){
                //Caso a area do alvo seja maior do que a area da ogiva, eles retrocedem em relação a area do outro sobre a area total
                float ar1=(somaarea-get_areaC(c))/(somaarea);
                float xccc=get_XC(c), yccc=get_YC(c);
                set_xC(c, get_XC(c)-get_novadistX(g, dista)*ar1);
                set_yC(c, get_YC(c)-get_novadistY(g, dista)*ar1);
                f1=setforma(c, 1);
                igualarlanc(ff1, f1);
                destruir_form(ff1);
                insertAbd(a1, get_XC(c), get_YC(c), f1);
                printatxt_circulo(arqtxt, c, 'a', 3,xccc, yccc);   
            }
    }else{
        if(divarea>=0.9 && divarea<=1.1){
            //Caso a diferença entre as áreas seja de apenas 90%, ambas as formas sao 'clonadas' recarregadas e depois os clones sao carregados tambem
            *id=*id+1;
            fprintf(*arqtxt,"\nCASO 1= COLISÃO COM AREAS MUITO PRÓXIMAS!\n");
            CIRCULO c2=cria_circulo(*id, get_XC(c), get_YC(c), get_rC(c), "#d400aa", get_cpC(c));
            f1=setforma(c2, 1);
            insertAbd(a1, get_XC(c2), get_YC(c2), f1);
            printatxt_circulo(arqtxt, fc, 'o', 1, axini, ayini);
            *formc=*formc+1;
        }
            if(divarea<0.9){
                //Caso a proporção entre a area das duas formas seja maior doq 10% o alvo é destruido e a ogiva é recarregada
                fprintf(*arqtxt,"\nCASO 2= COLISÃO COM ÁREAS DIFERENTES E ATRIBUIÇÃO DE PONTOS!\n");
                printatxt_circulo(arqtxt, fc, 'o', 2, axini, ayini);
                *formdestr=*formdestr+1;
            }
            if(divarea>1.1){
                //Caso a area do alvo seja maior do que a area da ogiva, eles retrocedem em relação a area do outro sobre a area total
                fprintf(*arqtxt,"\nCASO 3= COLISÃO COM ÁREA DO ALVO MAIOR DO QUE DA OGIVA!\n");
                printatxt_circulo(arqtxt, c, 'o', 3, axini, ayini);
            }
    }
    return resultado;
}




int lanc_ret(FORMA fr, float dista, char a, FILE **arqtxt, FILE **arqsvg, float *pontos, int *formc, int *formdestr, int *id, float axini, float ayini, AbdTree a1, float divarea, float somaarea, FORMASGEO ff1, float g){
    RETANGULO *r=((RETANGULO*)fr);
    int resultado=0;
    FORMASGEO f1, f2;
    if(a=='o'){
        if(divarea>=0.9 && divarea<=1.1){
            //Caso a diferença entre as áreas seja de apenas 90%, ambas as formas sao 'clonadas' recarregadas e depois os clones sao carregados tambem
            *id=*id+1;
            fprintf(*arqtxt,"\nCASO 1= COLISÃO COM AREAS MUITO PRÓXIMAS!\n");
            RETANGULO r2=cria_retangulo(*id, get_XR(r), get_YR(r), get_wR(r), get_hR(r), "#d400aa", get_cpR(r));
            printatxt_retangulo(arqtxt,fr, 'o', 1, axini, ayini);
            f1=setforma(r2, 2);
            insertAbd(a1, get_XR(r2), get_YR(r2), f1);
            *formc=*formc+1;
        }
            if(divarea<0.9){
                //Caso a proporção entre a area das duas formas seja maior doq 10% o alvo é destruido e a ogiva é recarregada
                fprintf(*arqtxt,"\nCASO 2= COLISÃO COM ÁREAS DIFERENTES E ATRIBUIÇÃO DE PONTOS!\n");
                printatxt_retangulo(arqtxt,fr, 'o', 2,axini, ayini);
                *formdestr=*formdestr+1;
            }
            if(divarea>1.1){
                //Caso a area do alvo seja maior do que a area da ogiva, eles retrocedem em relação a area do outro sobre a area total
                fprintf(*arqtxt,"\nCASO 3= COLISÃO COM ÁREA DO ALVO MAIOR DO QUE DA OGIVA!\n");
                printatxt_retangulo(arqtxt, r, 'o', 3,axini, ayini);
            }
    } else{
        if(divarea>=0.9 && divarea<=1.1){
            //Caso a diferença entre as áreas seja de apenas 90%, ambas as formas sao 'clonadas' recarregadas e depois os clones sao carregados tambem
            *id=*id+1;
            printatxt_retangulo(arqtxt,r, 'a', 1,get_XR(r), get_YR(r));
            RETANGULO r2=cria_retangulo(*id, get_XR(r), get_YR(r), get_wR(r), get_hR(r), "#d400aa", get_cpR(r));
            set_xR(r, get_XR(r)-get_novadistX(g, dista)/2);
            set_yR(r, get_YR(r)-get_novadistX(g, dista)/2);
            f1=setforma(r2, 2);
            f2=setforma(r, 2);
            igualarlanc(ff1, f2);
            destruir_form(ff1);
            insertAbd(a1, get_XR(r2), get_YR(r2), f1);
            insertAbd(a1, get_XR(r), get_YR(r), f1);
            *formc=*formc+1;
        }
            if(divarea<0.9){
                //Caso a proporção entre a area das duas formas seja maior doq 10% o alvo é destruido e a ogiva é recarregada
                print_detruicaosvg(arqsvg, get_XR(r), get_YR(r));
                printatxt_retangulo(arqtxt,fr, 'a', 2,get_XR(r), get_YR(r));
                fprintf(*arqtxt, "Pontos atribuidos do lançamento: %0.2f!\n", divarea*100);
                *pontos=*pontos+(divarea*100);
                resultado=1;
            }
            if(divarea>1.1){
                //Caso a area do alvo seja maior do que a area da ogiva, eles retrocedem em relação a area do outro sobre a area total
                float ar2=(somaarea-get_areaR(r))/(somaarea), xrrr=get_XR(r), yrrr=get_YR(r);
                set_xR(r, get_XR(r)-get_novadistX(g, dista)*ar2);
                set_yR(r, get_YR(r)-get_novadistY(g, dista)*ar2);
                printatxt_retangulo(arqtxt, r, 'a', 3,xrrr, yrrr);
                f1=setforma(r, 2);
                igualarlanc(ff1, f1);
                destruir_form(ff1);
                insertAbd(a1, get_XR(r), get_YR(r), f1);
        }
    }
    return resultado;
}



int lanc_linha(FORMA fl, float dista, char a, FILE **arqtxt, FILE **arqsvg, float *pontos, int *formc, int *formdestr, int *id, float lxini1, float lyini1, float lxini2, float lyini2, AbdTree a1, float divarea, float somaarea, FORMASGEO ff1, float g){
    LINHA *l=((LINHA*)fl);
    int resultado=0;
    FORMASGEO f1, f2;
    if(a=='o'){
            if(divarea>=0.9 && divarea<=1.1){
                //Caso a diferença entre as áreas seja de apenas 90%, ambas as formas sao 'clonadas' recarregadas e depois os clones sao carregados tambem
                *id=*id+1;
                fprintf(*arqtxt,"\nCASO 1= COLISÃO COM AREAS MUITO PRÓXIMAS!\n");
                LINHA l2=cria_linha(*id, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), "#d400aa");
                f1=setforma(l2, 4);
                if(get_X1L(l2)<get_X2L(l2)){
                    insertAbd(a1, get_X1L(l2), get_Y1L(l2), f1);
                } else{
                    insertAbd(a1, get_X2L(l2), get_Y2L(l2), f1);
                }
                printatxt_linha(arqtxt, l, 'o', 1,lxini1, lyini1, lxini2, lyini2);
                *formc=*formc+1;
            }
            if(divarea<0.9){
                //Caso a proporção entre a area das duas formas seja maior doq 10% o alvo é destruido e a ogiva é recarregada
                fprintf(*arqtxt,"\nCASO 2= COLISÃO COM ÁREAS DIFERENTES E ATRIBUIÇÃO DE PONTOS!\n");
                printatxt_linha(arqtxt,fl, 'o', 2,lxini1, lyini1, lxini2, lyini2);
                *formdestr=*formdestr+1;
            }
            if(divarea>1.1){
                //Caso a area do alvo seja maior do que a area da ogiva, eles retrocedem em relação a area do outro sobre a area total
                fprintf(*arqtxt,"\nCASO 3= COLISÃO COM ÁREA DO ALVO MAIOR DO QUE DA OGIVA!\n");
                printatxt_linha(arqtxt, l, 'o', 3,lxini1, lyini1, lxini2, lyini2);
            }
    } else{
            if(divarea>=0.9 && divarea<=1.1){
                //Caso a diferença entre as áreas seja de apenas 90%, ambas as formas sao 'clonadas' recarregadas e depois os clones sao carregados tambem
                *id=*id+1;
                printatxt_linha(arqtxt, l, 'a', 1,get_X2L(l), get_Y1L(l),get_X2L(l), get_Y2L(l));
                LINHA l2=cria_linha(*id, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l), "#d400aa");
                set_x1L(l,get_X1L(l)-get_novadistX(g, dista)/2);
                set_y1L(l,get_Y1L(l)-get_novadistY(g, dista)/2);
                set_x2L(l,get_X2L(l)-get_novadistX(g, dista)/2);
                set_y2L(l,get_Y2L(l)-get_novadistY(g, dista)/2);
                f2=setforma(l, 4);
                igualarlanc(ff1, f2);
                destruir_form(ff1);
                f1=setforma(l2, 4);
                if(get_X1L(l)<get_X2L(l) || (get_X1L(l)==get_X2L(l) && get_Y1L(l)<get_Y2L(l))){
                    insertAbd(a1, get_X1L(l), get_Y1L(l), f2);
                } else{
                    insertAbd(a1, get_X2L(l), get_Y2L(l), f2);
                }
                if(get_X1L(l2)<get_X2L(l2) || (get_X1L(l2)==get_X2L(l2) && get_Y1L(l2)<get_Y2L(l2))){
                    insertAbd(a1, get_X1L(l2), get_Y1L(l2), f1);
                } else{
                    insertAbd(a1, get_X2L(l2), get_Y2L(l2), f1);
                }
                *formc=*formc+1;
            }
            if(divarea<0.9){
                //Caso a proporção entre a area das duas formas seja maior doq 10% o alvo é destruido e a ogiva é recarregada
                print_detruicaosvg(arqsvg, get_X1L(l), get_Y1L(l));
                printatxt_linha(arqtxt,fl, 'a', 2,get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l));
                fprintf(*arqtxt, "Pontos atribuidos do lançamento: %0.2f!\n", divarea*100);
                *pontos=*pontos+(divarea*100);
                resultado=1;
            }
            if(divarea>1.1){
                //Caso a area do alvo seja maior do que a area da ogiva, eles retrocedem em relação a area do outro sobre a area total
                        float ar2=(somaarea-get_areaL(l))/(somaarea), xlll1=get_X1L(l), ylll1=get_Y1L(l), xlll2=get_X2L(l), ylll2=get_Y2L(l);
                        set_x1L(l, get_X1L(l)-get_novadistX(g, dista)*ar2);
                        set_y1L(l, get_Y1L(l)-get_novadistY(g, dista)*ar2);
                        set_x2L(l, get_X2L(l)-get_novadistX(g, dista)*ar2);
                        set_y2L(l, get_Y2L(l)-get_novadistY(g, dista)*ar2);
                        printatxt_linha(arqtxt, l, 'a', 3,xlll1, ylll1, xlll2, ylll2);
                        f1=setforma(l, 4);
                        igualarlanc(ff1, f1);
                        destruir_form(ff1);
                        if(get_X1L(l)<get_X2L(l)){
                            insertAbd(a1, get_X1L(l), get_Y1L(l), f1);
                        } else{
                            insertAbd(a1, get_X2L(l), get_Y2L(l), f1);
                        }
            }
    }
    return resultado;
}

int lanc_texto(FORMA ft, float dista, char a, FILE **arqtxt, FILE **arqsvg, float *pontos, int *formc, int *formdestr, int *id, float txini, float tyini, AbdTree a1, float divarea, float somaarea, FORMASGEO ff1, float g){
    TEXTO *t=((TEXTO*)ft);
    int resultado=0;
    FORMASGEO f1, f2;
    if(a=='o'){
            if(divarea>=0.9 && divarea<=1.1){
                //Caso a diferença entre as áreas seja de apenas 90%, ambas as formas sao 'clonadas' recarregadas e depois os clones sao carregados tambem
                *id=*id+1;
                fprintf(*arqtxt,"\nCASO 1= COLISÃO COM AREAS MUITO PRÓXIMAS!\n");
                TEXTO t2=cria_texto(*id, get_XT(t), get_YT(t), "#d400aa", get_cpT(t), get_charancoraT(t), get_txtT(t),get_ffT(t), get_fwT(t), get_fsT(t));
                f1=setforma(t2, 3);
                insertAbd(a1, get_XT(t2), get_YT(t2), f1);
                printatxt_texto(arqtxt, t, 'o', 1,txini, tyini);
                *formc=*formc+1;
            }
            if(divarea<0.9){
                //Caso a proporção entre a area das duas formas seja maior doq 10% o alvo é destruido e a ogiva é recarregada
                fprintf(*arqtxt,"\nCASO 2= COLISÃO COM ÁREAS DIFERENTES E ATRIBUIÇÃO DE PONTOS!\n");
                printatxt_texto(arqtxt,ft, 'o', 2,txini, tyini);
                *formdestr=*formdestr+1;
            }
            if(divarea>1.1){
                //Caso a area do alvo seja maior do que a area da ogiva, eles retrocedem em relação a area do outro sobre a area total
                fprintf(*arqtxt,"\nCASO 3= COLISÃO COM ÁREA DO ALVO MAIOR DO QUE DA OGIVA!\n");
                printatxt_texto(arqtxt, t, 'o', 3,txini, tyini);
            }
    } else{

            if(divarea>=0.9 && divarea<=1.1){
                //Caso a diferença entre as áreas seja de apenas 90%, ambas as formas sao 'clonadas' recarregadas e depois os clones sao carregados tambem
                *id=*id+1;
                printatxt_texto(arqtxt, t, 'a', 1,get_XT(t), get_YT(t));
                TEXTO t2=cria_texto(*id, get_XT(t), get_YT(t), "#d400aa", get_cpT(t), get_charancoraT(t), get_txtT(t),get_ffT(t), get_fwT(t), get_fsT(t));
                set_xT(t, get_XT(t)-get_novadistX(g, dista)/2);
                set_yT(t, get_YT(t)-get_novadistY(g, dista)/2);
                f1=setforma(t2, 3);
                f2=setforma(t, 3);
                igualarlanc(ff1, f2);
                destruir_form(ff1);
                insertAbd(a1, get_XT(t2), get_YT(t2), f1);
                insertAbd(a1, get_XT(t), get_YT(t), f2);
                *formc=*formc+1;
            }
            if(divarea<0.9){
                //Caso a proporção entre a area das duas formas seja maior doq 10% o alvo é destruido e a ogiva é recarregada
                printsvg_destruicaotexto(arqsvg, t);
                printatxt_texto(arqtxt,ft, 'a', 2,get_XT(t), get_YT(t));
                fprintf(*arqtxt, "Pontos atribuidos do lançamento: %0.2f!\n", divarea*100);
                *pontos=*pontos+(divarea*100);
                resultado=1;
            }
            if(divarea>1.1){
                //Caso a area do alvo seja maior do que a area da ogiva, eles retrocedem em relação a area do outro sobre a area total
                float ar2=(somaarea-get_areaT(t))/(somaarea), xttt=get_XT(t), yttt=get_YT(t);
                set_xT(t, get_XT(t)-get_novadistX(g, dista)*ar2);
                set_yT(t, get_YT(t)-get_novadistY(g, dista)*ar2);
                printatxt_texto(arqtxt, t, 'a', 3,xttt, yttt);
                f1=setforma(t, 3);
                igualarlanc(ff1, f1);
                destruir_form(ff1);
                insertAbd(a1, get_XT(t), get_YT(t), f1);
            }
    }
    return resultado;
}

void set_grausLANC(LANC l, float g){
    lanc *l1=((lanc*)l);
    l1->graus=g;
}

float get_novadistX(float g, float d){
    return cos((g*3.1415)/180)*d; 
}

float get_novadistY(float g, float d){
    return sin((g*3.1415)/180)*d; 
}

int qtt_elemen_lanc(LANC l){
    lanc *l1=((lanc*)l);
    return get_tamanholista(l1->lis);
}

void destroi_LANC(LANC l){
    lanc *l1=((lanc*)l);
    free(l1->lis);
    free(l1);
}

void distanciaCirculo(float xcen, float ycen, FORMA f, float *min, float *max){
    CIRCULO *c=(CIRCULO*)f;
    float distanciaCentro = sqrt(pow(xcen - get_XC(c), 2) + pow(ycen - get_YC(c), 2));
    *min = distanciaCentro - get_rC(c);
    if(*min<0){
        *min=*min*-1;
    }
    *max = distanciaCentro + get_rC(c); 
}

void distanciaLinha(float xcen, float ycen, FORMA f, float *min, float *max){
    LINHA *l=(LINHA*)f;
    *min= sqrt(pow(xcen - get_X1L(l), 2) + pow(ycen - get_Y1L(l),2));
    *max= sqrt(pow(xcen - get_X2L(l), 2) + pow(ycen - get_Y2L(l),2));
    float temp;
    if(*min>*max){
        temp=*min;
        *min=*max;
        *max=temp;
    }
}

void distanciaRetangulo(float xcen, float ycen, FORMA f, float *min, float *max) {
    RETANGULO *r=(RETANGULO*)f;
    double xMin = get_XR(r);
    double yMin = get_YR(r);
    double xMax = get_XR(r)+get_wR(r);
    double yMax = get_YR(r)+get_hR(r);

   
    if (xcen >= xMin && xcen <= xMax && ycen >= yMin && ycen <= yMax) {
       
        *min = 0;
    } else {
       
        float dx = fmax(xMin - xcen, fmax(0, xcen - xMax));
        float dy = fmax(yMin - ycen, fmax(0, ycen - yMax));
        *min = sqrt(dx * dx + dy * dy);
    }

   
    float dist1 = sqrt(pow(xcen - xMin, 2) + pow(ycen - yMin, 2));
    float dist2 = sqrt(pow(xcen - xMax, 2) + pow(ycen - yMin, 2));
    float dist3 = sqrt(pow(xcen - xMin, 2) + pow(ycen - yMax, 2));
    float dist4 = sqrt(pow(xcen - xMax, 2) + pow(ycen - yMax, 2));
    *max = fmax(fmax(dist1, dist2), fmax(dist3, dist4));
}

void distanciaTexto(float xcen, float ycen, FORMA f, float *min, float *max){
    TEXTO *t=(TEXTO*)f;
    *min= sqrt(pow(xcen - get_eixoX1T(t), 2) + pow(ycen - get_YT(t),2));
    *max= sqrt(pow(xcen - get_eixoX2T(t), 2) + pow(ycen - get_YT(t),2));
    float temp;
    if(*min>*max){
        temp=*min;
        *min=*max;
        *max=temp;
    }
}


