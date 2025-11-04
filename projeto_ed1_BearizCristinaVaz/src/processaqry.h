#ifndef processaqry_h
#define processaqry_h
    

    /*
    Esse cabeçalho header abre um arquivo do tipo .qry e pega as suas instruições e aplica na árvore binária de busca, criando os lançadores(com as listas ligadas dentro), ele é rsponsável por gerar os arquivos de visualização(svg) e os arquivos de texto(txt)
    */

    typedef void* FORMA;
    typedef void* Abdtree;

    /**
     * 
     * @brief Função para abrir e ler o arquivo qry e criar os o svg 2 e o txt de saida para as operações depois do qry
     * 
     * @param pathqry String contendo o path para o arquivo qry
     * @param dirsaida String contendo o path para os diretórios de saida
     * @param nomearqsaida String contendo o nome dos arquivos de saida svg e txt
     * @param nomeqry String com o nome do arquivo qry
     * @param instru ponteiro para saber quantas instruções foram feitas no arquivo qry
     * @param formcriadas ponteiro para saber quantas formas foram criadas de acordo com os lançamentos
     * @param id ponteiro para colocar o novo id nos clones
     * @param a1 Estrutura de uma arvore binaria de busca em que as formas estão armazenadas
     * 
     * @return void
     */
    void processa_qry(const char* pathqry, const char* dirsaida, const char* nomearqsaida, const char* nomeqry, int *instru, int *formcriadas, int *id, Abdtree a1, float *xcent, float *ycent);

#endif