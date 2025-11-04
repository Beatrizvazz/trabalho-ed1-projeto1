#ifndef arvorebin_h
#define arvorebin_h

/*
 * Uma Arvore Binaria de Distancias (AbdTree) e' uma arvore binaria de busca que possui uma coordenada global global
 * de referencia e  cujos nos associam uma informacao 'a uma coordenada no plano. 
 * A chave de busca nesta arvore e', portanto, a coordenada.
 * 
 * A arvore prove operacoes de insercao, busca e remocao de uma informacao associada a sua respectiva coordenada.
 * Alem da operacao de busca simples, a arvore prove uma operacao que retorna os nos cujas chaves estao dentro
 * de uma regiao anular (findInRegion), isto é, que esteja a, pelo menos, uma certa distancia minima do centro
 * de referencia e, no maximo, a uma certa distancia maxima do centro de referencia.
 * 
 * Por fim, sao providas operacoes que visitam os nos da arvore. Tais operacoes recebem como parametro 
 * uma funcao que e' invocada em cada no' visitado.
 * 
 * Outras operacoes tambem podem receber funcoes que visitam os nos durante a execucao da 
 * operacao. */


typedef void *AbdTree;
typedef void *TreeNode;
typedef void *Info;
typedef void *Lista;

/* Tipo da funcao invocada quando um no' e' visitado. A funcao recebe os seguintes valores
      x,y     - coordenada (chave)
      info    - a informacao associada a coordenada
      d       - distancia do centro de referencia da arvore
      extra   - apontador passado para operacao de percurso.
 */
typedef void (*VisitaNo)(float x, float y, Info info, float d, void* extra);

/*
  Retorna uma AbdTree vazia.
  A coordenada global de referencia da 'arvore e' a coordenada (x,y)
  Comparar 2 numeros reais por igualdade pode gerar resultados incorretos devido
  a sua representacao em memoria. Assim, ao inves de verificar se x1 == x2,
  verifica-se | x1 - x2 | < epsilon.
*/
AbdTree createAbd(double x, double y, double epsilon);

/*
  Insere na arvore b, a informacao info associada a coordenada  (x,y).
  Retorna NULL, se ja' chave (x,y) ja' existia armazenada na arvore; 
  retorna o apontador para o no' inserido, caso contrario.
*/
void insertAbd(AbdTree b, double x, double y, Info info);

/*
  Procura a chave (x,y) na 'arvore b. Se encontrou, atribui a info a informacao associada
  a tal chave e retorna verdadeiro; caso contrario, retorna falso.
 */
int searchAbd(AbdTree b, double x, double y, Info *info);

/*
  Procura a chave (x,y) na 'arvore. Se encontrar, atribui 'a info a informacao associada, remove o no'
  da 'arvore e retorna verdadeiro; caso contrario, retorna falso.
 */
int removeAbd(AbdTree b, double x, double y, Info *info);

/*
  Adiciona 'a lista lres os nos da arvore (TreeNode) cujas coordenadas (chaves) estejam, pelo menos,
  a uma distancia (euclidiana) distMin do centro global de referencia da arvore e, no maximo, a uma
  distancia distMax.
  Retorna verdadeiro se, pelo menos, 1 no' foi encontrado e inserido em lres; falso,
  caso contrario.
 */
int findInRegionAbd(AbdTree b, double distMin, double distMax, Lista lres);

/*
  Retorna a informacao associada ao no' n.
  O no' n deve ser um no' valido.
 */
Info getInfoAbd(AbdTree b, TreeNode n);

/*
  Faz o percurso simetrico na arvore. A cada no' visitado,
  invoca a funcao vf (se != NULL)
 */
void percursoSimetrico(AbdTree b, VisitaNo vf, void* extra);

/*
  Percorre a arvore em profundidade. A cada no' visitado,
  invoca a funcao vf (se != NULL)
 */
void dfs(AbdTree b, VisitaNo vf, void* extra);

/*
  Percorre a arvore em largura. A cada no' visitado,
  invoca a funcao vf (se != NULL)
 */

void bfs(AbdTree b, VisitaNo vf, void* extra);
#endif