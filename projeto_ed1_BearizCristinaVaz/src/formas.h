#ifndef formas_h
#define formas_h


/*
O arquivo formas.h define a interface para manipulação de uma estrutura de dados que representa diferentes formas geométricas, como círculos, retângulos, linhas e textos. Este header fornece funções para criar, acessar, modificar e liberar recursos relacionados a essas formas, além de oferecer funcionalidades para calcular distâncias, áreas e ordenar as formas com base em critérios específicos.

A estrutura principal (formas) encapsula uma forma geométrica genérica, representada por um ponteiro para void, e inclui informações sobre o tipo da forma e um array para rastrear lançadores associados. O uso de um tipo opaco (FORMASGEO) esconde os detalhes de implementação da estrutura interna, promovendo encapsulamento e modularidade.

As funções fornecidas permitem:

Criar e configurar formas geométricas.

Acessar atributos como coordenadas, áreas e IDs.

Calcular distâncias euclidianas e de Manhattan.

Ordenar formas com base em distâncias ou áreas.

Verificar e manipular lançadores associados às formas.

Imprimir informações sobre as formas.

*/

// Definição do tipo FORMASGEO como um ponteiro para void
typedef void* FORMASGEO;
typedef void* FORMA;
typedef void* Lista;
typedef void* AbdTree;
typedef void* LANC;
/**
 * @brief Cria e configura uma forma geométrica com base no tipo fornecido.
 * 
 * @param f Ponteiro para a forma geométrica.
 * @param tipo Tipo da forma (1: Círculo, 2: Retângulo, 3: Linha, 4: Texto).
 * @return FORMASGEO Retorna um ponteiro para a estrutura da forma criada.
 */
FORMASGEO setforma(FORMA f, int tipo);

/**
 * @brief Obtém o tipo da forma geométrica.
 * 
 * @param f Ponteiro para a estrutura da forma.
 * @return int Retorna o tipo da forma (1: Círculo, 2: Retângulo, 3: Linha, 4: Texto).
 */
int gettipoforma(FORMASGEO f);

/**
 * @brief Obtém a forma geométrica de uma lista.
 * 
 * @param l Lista contendo as formas.
 * @return FORMASGEO Retorna a forma geométrica removida da lista.
 */
FORMASGEO getformageo(Lista l);


/**
 * @brief Calcula a coordenada x do baricentro de um retângulo.
 * 
 * @param eixox Coordenada x do canto superior esquerdo do retângulo.
 * @param largura Largura do retângulo.
 * @return float Retorna a coordenada x do baricentro.
 */
float acharbaricentroRetX(float eixox, float largura);

void printtipoformadalista(FORMASGEO f);

/**
 * @brief Calcula a coordenada y do baricentro de um retângulo.
 * 
 * @param eixoy Coordenada y do canto superior esquerdo do retângulo.
 * @param altura Altura do retângulo.
 * @return float Retorna a coordenada y do baricentro.
 */
float acharbaricentroRetY(float eixoy, float altura);

/**
 * @brief Calcula a coordenada x do baricentro de uma linha.
 * 
 * @param eixox1 Coordenada x do primeiro ponto da linha.
 * @param eixox2 Coordenada x do segundo ponto da linha.
 * @return float Retorna a coordenada x do baricentro.
 */
float acharbaricentroLinX(float eixox1, float eixox2);

/**
 * @brief Calcula a coordenada y do baricentro de uma linha.
 * 
 * @param eixoy1 Coordenada y do primeiro ponto da linha.
 * @param eixoy2 Coordenada y do segundo ponto da linha.
 * @return float Retorna a coordenada y do baricentro.
 */
float acharbaricentroLinY(float eixoy1, float eixoy2);

/**
 * @brief Compara os IDs de duas formas geométricas.
 * 
 * @param f1 Ponteiro para a primeira forma.
 * @param f2 Ponteiro para a segunda forma.
 * @return int Retorna 1 se os IDs forem iguais, 0 caso contrário.
 */
int comparaidformas(FORMASGEO f1, FORMASGEO f2);

/**
 * @brief Obtém a coordenada x da forma geométrica.
 * 
 * @param f Ponteiro para a estrutura da forma.
 * @return float Retorna a coordenada x.
 */
float getX(FORMASGEO f);

/**
 * @brief Obtém a coordenada y da forma geométrica.
 * 
 * @param f Ponteiro para a estrutura da forma.
 * @return float Retorna a coordenada y.
 */
float getY(FORMASGEO f);

/**
 * @brief Obtém a área da forma geométrica.
 * 
 * @param f Ponteiro para a estrutura da forma.
 * @return float Retorna a área da forma.
 */
float getArea(FORMASGEO f);

/**
 * @brief Calcula a distância euclidiana entre dois pontos.
 * 
 * @param xf Coordenada x do primeiro ponto.
 * @param yf Coordenada y do primeiro ponto.
 * @param xcent Coordenada x do segundo ponto.
 * @param ycent Coordenada y do segundo ponto.
 * @return double Retorna a distância euclidiana.
 */
double pdistanciaEuclidiana(float xf, float yf, float xcent, float ycent);

/**
 * @brief Calcula a distância de Manhattan entre dois pontos.
 * 
 * @param xf Coordenada x do primeiro ponto.
 * @param yf Coordenada y do primeiro ponto.
 * @param xcent Coordenada x do segundo ponto.
 * @param ycent Coordenada y do segundo ponto.
 * @return double Retorna a distância de Manhattan.
 */
double distanciaManhattan(float xf, float yf, float xcent, float ycent);

/**
 * @brief Compara duas formas geométricas com base na distância euclidiana (crescente).
 * 
 * @param a Ponteiro para a primeira forma.
 * @param b Ponteiro para a segunda forma.
 * @param xcent Coordenada x do ponto de referência.
 * @param ycent Coordenada y do ponto de referência.
 * @return int Retorna 1 se a distância de 'a' for maior que a de 'b', -1 caso contrário.
 */
int comparaEuclidianaCrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent);

/**
 * @brief Compara duas formas geométricas com base na distância euclidiana (decrescente).
 * 
 * @param a Ponteiro para a primeira forma.
 * @param b Ponteiro para a segunda forma.
 * @param xcent Coordenada x do ponto de referência.
 * @param ycent Coordenada y do ponto de referência.
 * @return int Retorna 1 se a distância de 'a' for menor que a de 'b', -1 caso contrário.
 */
int comparaEuclidianaDecrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent);

/**
 * @brief Compara duas formas geométricas com base na distância de Manhattan (crescente).
 * 
 * @param a Ponteiro para a primeira forma.
 * @param b Ponteiro para a segunda forma.
 * @param xcent Coordenada x do ponto de referência.
 * @param ycent Coordenada y do ponto de referência.
 * @return int Retorna 1 se a distância de 'a' for maior que a de 'b', -1 caso contrário.
 */
int comparaManhattanCrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent);

/**
 * @brief Compara duas formas geométricas com base na distância de Manhattan (decrescente).
 * 
 * @param a Ponteiro para a primeira forma.
 * @param b Ponteiro para a segunda forma.
 * @param xcent Coordenada x do ponto de referência.
 * @param ycent Coordenada y do ponto de referência.
 * @return int Retorna 1 se a distância de 'a' for menor que a de 'b', -1 caso contrário.
 */
int comparaManhattanDecrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent);

/**
 * @brief Compara duas formas geométricas com base na área (crescente).
 * 
 * @param a Ponteiro para a primeira forma.
 * @param b Ponteiro para a segunda forma.
 * @param xcent Coordenada x do ponto de referência (ignorada).
 * @param ycent Coordenada y do ponto de referência (ignorada).
 * @return int Retorna 1 se a área de 'a' for maior que a de 'b', -1 caso contrário.
 */
int comparaAreaCrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent);

/**
 * @brief Compara duas formas geométricas com base na área (decrescente).
 * 
 * @param a Ponteiro para a primeira forma.
 * @param b Ponteiro para a segunda forma.
 * @param xcent Coordenada x do ponto de referência (ignorada).
 * @param ycent Coordenada y do ponto de referência (ignorada).
 * @return int Retorna 1 se a área de 'a' for menor que a de 'b', -1 caso contrário.
 */
int comparaAreaDecrescente(FORMASGEO a, FORMASGEO b, float xcent, float ycent);

/**
 * @brief Ordena uma lista de formas geométricas com base no tipo de ordenação especificado.
 * 
 * @param L Lista a ser ordenada.
 * @param tipo Tipo de ordenação (1: Euclidiana Crescente, 2: Euclidiana Decrescente, 3: Manhattan Crescente, 4: Manhattan Decrescente, 5: Área Crescente, 6: Área Decrescente).
 * @param xcent Coordenada x do ponto de referência (usado para distâncias).
 * @param ycent Coordenada y do ponto de referência (usado para distâncias).
 */
void ordenaPorTipo(Lista L, int tipo, float xcent, float ycent);

/**
 * @brief Aplica uma função de cálculo de área a uma forma geométrica.
 * 
 * @param info Ponteiro para a forma geométrica.
 * @param c Ponteiro para a variável que armazenará a soma das áreas.
 */
void aplicarArea(void *info, void *c);

/**
 * @brief Define o número do lançador associado à forma.
 * 
 * @param f Ponteiro para a estrutura da forma.
 * @param c Ponteiro para o número do lançador.
 */
FORMASGEO set_numlancador(FORMASGEO f, void* c);

/**
 * @brief Verifica se a forma corresponde a uma característica específica.
 * 
 * @param f Ponteiro para a estrutura da forma.
 * @param c Ponteiro para a característica a ser verificada ('C': Círculo, 'R': Retângulo, 'T': Texto, 'L': Linha).
 * @return int Retorna 1 se a forma corresponder à característica, 0 caso contrário.
 */
int check_forma(FORMASGEO f, void *c);

/**
 * @brief Imprime as informações da forma em um arquivo.
 * 
 * @param f Ponteiro para a estrutura da forma.
 * @param c Ponteiro para o arquivo de saída.
 */
FORMASGEO printLista(FORMASGEO f, void *c);

/**
 * @brief Printa a forma no svg 
 * 
 * @param x coordenada x na arvore
 * @param y coordenada y na arvore
 * @param f Void pointer para a informação dentro da arvore
 * @param d distancia da forma ate o centro de gravidade
 * @param extra arquivo svg passado como void*
 * 
 * @return Retorna um void
 */
void printasvg(float x, float y, FORMASGEO f, float d, void* extra);

void destruir_form(FORMASGEO f);

int checkvivo(void *info, void *c);

int checkigual(void *info, void *c);

void igualarlanc(FORMASGEO f1, FORMASGEO f2);

void lancamento_real(Lista l0, Lista l1,Lista l2,Lista l3,Lista l4,Lista l5,Lista l6,Lista l7,Lista l8,Lista l9,Lista lf, FILE **svg, FILE **txt, float d, AbdTree a1, float xcen, float ycen, float *pontos, int *formc, int *formdes, int *id, float graus);

#endif