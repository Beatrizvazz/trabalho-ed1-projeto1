#ifndef str_h
#define str_h
    
    /**
    * Uma biblioteca de funções para manipulação de strings, principalmente voltada para a construção e tratamento de caminhos de arquivos (paths) e nomes de arquivos.
    * 
    * Esta biblioteca fornece funções para garantir que um caminho de diretório termine com uma barra '/', extrair nomes de arquivos de caminhos completos, concatenar nomes de arquivos e construir caminhos completos para arquivos.
    * 
    * As funções são úteis para manipulação de paths em sistemas de arquivos, especialmente em cenários onde é necessário garantir a formatação correta dos caminhos e a construção de nomes de arquivos de saída com base em nomes de arquivos de entrada.
    * 
    * As operações incluem:
    * - Garantir que um caminho termine com uma barra '/'.
    * - Extrair o nome de um arquivo de um caminho completo.
    * - Concatenar nomes de arquivos para formar nomes de saída.
    * - Construir caminhos completos para arquivos com base em diretórios de entrada e nomes de arquivos.
    */

    /**
     * @brief Função para ver se o path tem uma '/' no final e colocar ela caso nao tenha
     * 
     * @param str string contendo o path
     * 
     * @return String contendo o path com a barra no final
     */
    char* tratadirentrada(const char* str);

    /**
     * 
     * @brief Função para pegar o nome do arquivo geo para colocar no nome dos arquivos de saida
     * 
     * @param arqgeo passa toda a string depois do '-f'
     * 
     * @return retorna uma string com o nome do arquivo geo (tudo que esta escrito antes da ultima '/')
     */
    char* get_nomegeo(const char* arqgeo);

    /**
     * 
     * @brief Função para pegar o nome do arquivo qry para colocar no nome dos arquivos de saida, principalmente caso tenham mais d 1 qry
     * 
     * @param arqgeo passa toda a string depois do '-q'
     * 
     * @return retorna uma string com o nome do arquivo geo (tudo que esta escrito antes da ultima '/')
     */
    char* get_nomeqry(const char* arqqry);
    
    /**
     * 
     * @brief Junta os nomes do arquivo geo com o do arquivo qry para serem os nomes do svg e o txt d saida
     * 
     * @param nomegeo nome do arquivo geo
     * @param nomeqry nome do arquivo qry
     * 
     * @return a concatenação dos 2 nomes separados por '-'
     */
    char* get_concatnomeqry(const char* nomegeo, const char* nomeqry);

    /**
     * 
     * @brief cria o path do arquivo qry
     * 
     * @param dire path para o diretorio de entrada que esta no '-e'
     * @param arqgeo o restante do diretorio de entrada
     * @param possibilidade caso nao tenha diretorio de entrada no '-e' ele vai pegar apenas o que esta no '-f'
     * 
     * @return Retorna a string contendo o path para o qry
     */
    char* path_qry(const char* dire, const char* arqgeo, int possibilidade);
#endif