#ifndef lancadores_h
#define lancadores_h

/*
O arquivo lancadores.h define a interface para manipulação de uma estrutura de dados que representa lançadores de formas geométricas. Este header fornece funções para criar, configurar, manipular e liberar recursos relacionados a lançadores, que são utilizados para disparar formas geométricas (como círculos, retângulos, linhas e textos) em um plano bidimensional.

A estrutura do lançador (lanc) contém informações sobre o ângulo de lançamento, o número de lançamentos realizados e uma lista de formas geométricas associadas. O header utiliza um tipo opaco (LANC), que é um ponteiro para void, para esconder os detalhes de implementação da estrutura interna do lançador. Isso garante que o usuário da biblioteca não precise conhecer os detalhes internos da estrutura, promovendo um uso mais seguro e modular.

As funções fornecidas permitem:

Criar e configurar um lançador.

Realizar lançamentos de formas geométricas com base em critérios específicos.

Calcular distâncias e áreas relacionadas às formas lançadas.

Imprimir informações sobre os lançamentos em arquivos de texto e SVG.

Liberar a memória alocada para o lançador quando ele não for mais necessário.
*/

// Definição do tipo LANC como um ponteiro para void
typedef void* LANC;
typedef void* AbdTree;
typedef void* Lista;
typedef void* FORMA;
typedef void* FORMASGEO;
/**
 * @brief Cria e configura um lançador com o número fornecido.
 * 
 * @param i Número do lançador.
 * @return LANC Retorna um ponteiro para a estrutura do lançador criado.
 */
LANC cria_lanc(int i);

/**
 * @brief Obtém o número do lançador.
 * 
 * @param l Ponteiro para a estrutura do lançador.
 * @return int Retorna o número do lançador.
 */
int getnumlancador(LANC l);

/**
 * @brief Imprime um círculo em um arquivo SVG.
 * 
 * @param arq Ponteiro para o arquivo SVG.
 * @param f Ponteiro para a forma geométrica (círculo).
 */
void printsvg_circulo(FILE **arq, FORMA f);

/**
 * @brief Imprime um retângulo em um arquivo SVG.
 * 
 * @param arq Ponteiro para o arquivo SVG.
 * @param f Ponteiro para a forma geométrica (retângulo).
 */
void printsvg_retangulo(FILE **arq, FORMA f);

/**
 * @brief Imprime uma linha em um arquivo SVG.
 * 
 * @param arq Ponteiro para o arquivo SVG.
 * @param f Ponteiro para a forma geométrica (linha).
 */
void printsvg_linha(FILE **arq, FORMA f);

/**
 * @brief Imprime um texto em um arquivo SVG.
 * 
 * @param arq Ponteiro para o arquivo SVG.
 * @param f Ponteiro para a forma geométrica (texto).
 */
void printsvg_texto(FILE **arq, FORMA f);

/**
 * @brief Carrega formas geométricas no lançador com base em critérios de distância e tipo.
 * 
 * @param l Ponteiro para a estrutura do lançador.
 * @param a1 Árvore binária contendo as formas geométricas.
 * @param dmin Distância mínima para seleção das formas.
 * @param dmax Distância máxima para seleção das formas.
 * @param arq Ponteiro para o arquivo de saída.
 * @param sort Tipo de ordenação das formas.
 * @param t Tipo de forma a ser filtrada.
 * @param xcent Coordenada x do ponto de referência.
 * @param ycent Coordenada y do ponto de referência.
 */
void carrega_lancador(LANC l, AbdTree a1, float dmin, float dmax, FILE **arq, int sort, char t, float xcent, float ycent);

/**
 * @brief Imprime um marcador de destruição em um arquivo SVG.
 * 
 * @param arq Ponteiro para o arquivo SVG.
 * @param x Coordenada x do marcador.
 * @param y Coordenada y do marcador.
 */
void print_detruicaosvg(FILE **arq, float x, float y);

/**
 * @brief Imprime um texto de destruição em um arquivo SVG.
 * 
 * @param arq Ponteiro para o arquivo SVG.
 * @param f Ponteiro para a forma geométrica (texto).
 */
void printsvg_destruicaotexto(FILE **arq, FORMA f);

/**
 * @brief Imprime o cabeçalho de um lançamento em um arquivo de texto.
 * 
 * @param arq Ponteiro para o arquivo de texto.
 * @param l Número do lançador.
 * @param g Ângulo de lançamento.
 */
void printatxt_cabecalhort(FILE **arq, int l, float g);

/**
 * @brief Imprime o cabeçalho de seleção de formas em um arquivo de texto.
 * 
 * @param arq Ponteiro para o arquivo de texto.
 * @param l Número do lançador.
 * @param t Tipo de forma.
 * @param dmin Distância mínima.
 * @param dmax Distância máxima.
 * @param co Cor da forma.
 */
void printatxt_cabecalhosel(FILE **arq, int l, char t, float dmin, float dmax, char* co);

/**
 * @brief Imprime o cabeçalho de lançamento de formas em um arquivo de texto.
 * 
 * @param arq Ponteiro para o arquivo de texto.
 * @param la Lançador.
 * @param dista Distância do lançamento.
 */
void printatxt_cabecalholc(FILE **arq, int la, float dista);

/**
 * @brief função para iniciar os lançamentos
 * 
 * @param l0 lançador 0
 * @param l1 lançador 1
 * @param l2 lançador 2
 * @param l3 lançador 3
 * @param l4 lançador 4
 * @param l5 lançador 5
 * @param l6 lançador 6
 * @param l7 lançador 7
 * @param l8 lançador 8
 * @param l9 lançador 9
 * @param lc lançador para fazer o lançamento
 * @param arqsvg arquivo svg para printar as formas
 * @param arqtxt arquivo txt para comentar sobre os acontecimentos
 * @param dista distancia do lançamento
 * 
 * @return void
 * 
 */
void faz_lancamento(LANC l0,LANC l1,LANC l2,LANC l3,LANC l4,LANC l5,LANC l6,LANC l7,LANC l8,LANC l9, LANC lc, FILE **arqsvg, FILE **arqtxt, float dista, AbdTree a1, float xcen, float ycen, float *pontos, int *formc, int *formdest, int *id, float graus);

/**
 * @brief Imprime informações de um círculo em um arquivo de texto.
 * 
 * @param arq Ponteiro para o arquivo de texto.
 * @param f Ponteiro para a forma geométrica (círculo).
 * @param a Tipo de forma (alvo ou ogiva).
 * @param ac Ação realizada (clonado, destruído, etc.).
 * @param xini Coordenada x inicial.
 * @param yini Coordenada y inicial.
 */
void printatxt_circulo(FILE **arq, FORMA f, char a, int ac, float xini, float yini);

/**
 * @brief Imprime informações de um retângulo em um arquivo de texto.
 * 
 * @param arq Ponteiro para o arquivo de texto.
 * @param f Ponteiro para a forma geométrica (retângulo).
 * @param a Tipo de forma (alvo ou ogiva).
 * @param ac Ação realizada (clonado, destruído, etc.).
 * @param xini Coordenada x inicial.
 * @param yini Coordenada y inicial.
 */
void printatxt_retangulo(FILE **arq, FORMA f, char a, int ac, float xini, float yini);

/**
 * @brief Imprime informações de uma linha em um arquivo de texto.
 * 
 * @param arq Ponteiro para o arquivo de texto.
 * @param f Ponteiro para a forma geométrica (linha).
 * @param a Tipo de forma (alvo ou ogiva).
 * @param ac Ação realizada (clonado, destruído, etc.).
 * @param xini1 Coordenada x inicial do primeiro ponto.
 * @param yini1 Coordenada y inicial do primeiro ponto.
 * @param xini2 Coordenada x inicial do segundo ponto.
 * @param yini2 Coordenada y inicial do segundo ponto.
 */
void printatxt_linha(FILE **arq, FORMA f, char a, int ac, float xini1, float yini1, float xini2, float yini2);

/**
 * @brief Imprime informações de um texto em um arquivo de texto.
 * 
 * @param arq Ponteiro para o arquivo de texto.
 * @param f Ponteiro para a forma geométrica (texto).
 * @param a Tipo de forma (alvo ou ogiva).
 * @param ac Ação realizada (clonado, destruído, etc.).
 * @param xini Coordenada x inicial.
 * @param yini Coordenada y inicial.
 */
void printatxt_texto(FILE **arq, FORMA f, char a, int ac, float xini, float yini);

/**
 * @brief Descarrega uma forma geométrica do lançador.
 * 
 * @param l Ponteiro para a estrutura do lançador.
 * @return FORMA Retorna a forma geométrica descarregada.
 */
FORMA descarrega_lanc(LANC l);

/**
 * @brief Realiza o lançamento de um círculo.
 * 
 * @param lc Ponteiro para a estrutura do lançador.
 * @param fc Ponteiro para a forma geométrica (círculo).
 * @param dista Distância do lançamento.
 * @param a Tipo de forma (alvo ou ogiva).
 * @param arqtxt Ponteiro para o arquivo de texto.
 * @param arqsvg Ponteiro para o arquivo SVG.
 * @param pontos Pontuação acumulada.
 * @param formc Contador de formas clonadas.
 * @param formdestr Contador de formas destruídas.
 * @param id Identificador da forma.
 * @param axini Coordenada x inicial.
 * @param ayini Coordenada y inicial.
 * @param a1 Árvore binária contendo as formas geométricas.
 * @param divarea Divisão da área.
 * @param somaarea Soma das áreas.
 * @return int Retorna 1 se o lançamento resultar em destruição, 0 caso contrário.
 */
int lanc_circ(FORMA fc, float dista, char a, FILE **arqtxt, FILE **arqsvg, float *pontos, int *formc, int *formdestr, int *id, float axini, float ayini, AbdTree a1, float divarea, float somaarea, FORMASGEO ff1, float graus);

/**
 * @brief Realiza o lançamento de um retângulo.
 * 
 * @param lr Ponteiro para a estrutura do lançador.
 * @param fr Ponteiro para a forma geométrica (retângulo).
 * @param dista Distância do lançamento.
 * @param a Tipo de forma (alvo ou ogiva).
 * @param arqtxt Ponteiro para o arquivo de texto.
 * @param arqsvg Ponteiro para o arquivo SVG.
 * @param pontos Pontuação acumulada.
 * @param formc Contador de formas clonadas.
 * @param formdestr Contador de formas destruídas.
 * @param id Identificador da forma.
 * @param axini Coordenada x inicial.
 * @param ayini Coordenada y inicial.
 * @param a1 Árvore binária contendo as formas geométricas.
 * @param divarea Divisão da área.
 * @param somaarea Soma das áreas.
 * @return int Retorna 1 se o lançamento resultar em destruição, 0 caso contrário.
 */
int lanc_ret(FORMA fr, float dista, char a, FILE **arqtxt, FILE **arqsvg, float *pontos, int *formc, int *formdestr, int *id, float axini, float ayini, AbdTree a1, float divarea, float somaarea, FORMASGEO ff1, float graus);

/**
 * @brief Realiza o lançamento de uma linha.
 * 
 * @param lc Ponteiro para a estrutura do lançador.
 * @param fl Ponteiro para a forma geométrica (linha).
 * @param dista Distância do lançamento.
 * @param a Tipo de forma (alvo ou ogiva).
 * @param arqtxt Ponteiro para o arquivo de texto.
 * @param arqsvg Ponteiro para o arquivo SVG.
 * @param pontos Pontuação acumulada.
 * @param formc Contador de formas clonadas.
 * @param formdestr Contador de formas destruídas.
 * @param id Identificador da forma.
 * @param lxini1 Coordenada x inicial do primeiro ponto.
 * @param lyini1 Coordenada y inicial do primeiro ponto.
 * @param lxini2 Coordenada x inicial do segundo ponto.
 * @param lyini2 Coordenada y inicial do segundo ponto.
 * @param a1 Árvore binária contendo as formas geométricas.
 * @param divarea Divisão da área.
 * @param somaarea Soma das áreas.
 * @return int Retorna 1 se o lançamento resultar em destruição, 0 caso contrário.
 */
int lanc_linha(FORMA fl, float dista, char a, FILE **arqtxt, FILE **arqsvg, float *pontos, int *formc, int *formdestr, int *id, float lxini1, float lyini1, float lxini2, float lyini2, AbdTree a1, float divarea, float somaarea, FORMASGEO ff1, float graus);

/**
 * @brief Realiza o lançamento de um texto.
 * 
 * @param lt Ponteiro para a estrutura do lançador.
 * @param ft Ponteiro para a forma geométrica (texto).
 * @param dista Distância do lançamento.
 * @param a Tipo de forma (alvo ou ogiva).
 * @param arqtxt Ponteiro para o arquivo de texto.
 * @param arqsvg Ponteiro para o arquivo SVG.
 * @param pontos Pontuação acumulada.
 * @param formc Contador de formas clonadas.
 * @param formdestr Contador de formas destruídas.
 * @param id Identificador da forma.
 * @param txini Coordenada x inicial.
 * @param tyini Coordenada y inicial.
 * @return int Retorna 1 se o lançamento resultar em destruição, 0 caso contrário.
 */
int lanc_texto(FORMA ft, float dista, char a, FILE **arqtxt, FILE **arqsvg, float *pontos, int *formc, int *formdestr, int *id, float txini, float tyini, AbdTree a1, float divarea, float somaarea, FORMASGEO ff1, float graus);

/**
 * @brief Define o ângulo de lançamento.
 * 
 * @param l Ponteiro para a estrutura do lançador.
 * @param g Ângulo de lançamento.
 */
void set_grausLANC(LANC l, float g);

/**
 * @brief Calcula a nova distância no eixo x com base no ângulo de lançamento.
 * 
 * @param l Ponteiro para a estrutura do lançador.
 * @param d Distância do lançamento.
 * @return float Retorna a nova distância no eixo x.
 */
float get_novadistX(float graus, float d);

/**
 * @brief Calcula a nova distância no eixo y com base no ângulo de lançamento.
 * 
 * @param l Ponteiro para a estrutura do lançador.
 * @param d Distância do lançamento.
 * @return float Retorna a nova distância no eixo y.
 */
float get_novadistY(float graus, float d);

/**
 * @brief Obtém a quantidade de elementos no lançador.
 * 
 * @param l Ponteiro para a estrutura do lançador.
 * @return int Retorna a quantidade de elementos.
 */
int qtt_elemen_lanc(LANC l);

/**
 * @brief Libera a memória alocada para o lançador.
 * 
 * @param l Ponteiro para a estrutura do lançador.
 */
void destroi_LANC(LANC l);

/**
 * @brief Calcula a distância mínima e máxima de um círculo em relação a um ponto.
 * 
 * @param xcen Coordenada x do ponto de referência.
 * @param ycen Coordenada y do ponto de referência.
 * @param f Ponteiro para a forma geométrica (círculo).
 * @param min Ponteiro para armazenar a distância mínima.
 * @param max Ponteiro para armazenar a distância máxima.
 */
void distanciaCirculo(float xcen, float ycen, FORMA f, float *min, float *max);

/**
 * @brief Calcula a distância mínima e máxima de uma linha em relação a um ponto.
 * 
 * @param xcen Coordenada x do ponto de referência.
 * @param ycen Coordenada y do ponto de referência.
 * @param f Ponteiro para a forma geométrica (linha).
 * @param min Ponteiro para armazenar a distância mínima.
 * @param max Ponteiro para armazenar a distância máxima.
 */
void distanciaLinha(float xcen, float ycen, FORMA f, float *min, float *max);

/**
 * @brief Calcula a distância mínima e máxima de um retângulo em relação a um ponto.
 * 
 * @param xcen Coordenada x do ponto de referência.
 * @param ycen Coordenada y do ponto de referência.
 * @param f Ponteiro para a forma geométrica (retângulo).
 * @param min Ponteiro para armazenar a distância mínima.
 * @param max Ponteiro para armazenar a distância máxima.
 */
void distanciaRetangulo(float xcen, float ycen, FORMA f, float *min, float *max);

/**
 * @brief Calcula a distância mínima e máxima de um texto em relação a um ponto.
 * 
 * @param xcen Coordenada x do ponto de referência.
 * @param ycen Coordenada y do ponto de referência.
 * @param f Ponteiro para a forma geométrica (texto).
 * @param min Ponteiro para armazenar a distância mínima.
 * @param max Ponteiro para armazenar a distância máxima.
 */
void distanciaTexto(float xcen, float ycen, FORMA f, float *min, float *max);

#endif