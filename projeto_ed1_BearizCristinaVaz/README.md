# Projeto de Estrutura de Dados I - Bocha Geométrica

**Aluno:** Beatriz Cristina Vaz  
**Matrícula:** 202500560227  
**Disciplina:** Estrutura de Dados I  
**Professor:** Evandro Baccarin

## Descrição

Este projeto implementa o jogo "Bocha Geométrica", um sistema que gerencia disparadores que lançam formas geométricas em uma arena. O programa processa arquivos de entrada contendo definições de formas e comandos de manipulação, gerando saídas em formato SVG e TXT.

## Estruturas de Dados Implementadas

O projeto faz uso extensivo das seguintes estruturas de dados:

### Pilha (LIFO - Last In, First Out)
Utilizada para implementar os **carregadores** de formas. Cada carregador é uma pilha onde formas são empilhadas e desempilhadas conforme os botões do disparador são pressionados.

### Fila (FIFO - First In, First Out)
Utilizada para implementar a **arena**, onde as formas lançadas são enfileiradas e processadas na ordem em que foram disparadas.

### Árvore Binária
Utilizada para armazenar e organizar as formas geométricas no "chão", permitindo busca e manipulação eficiente.

## Compilação

Para compilar o projeto, execute:

```bash
cd src
make
```

Isso gerará o executável `ted` no mesmo diretório.

Para limpar os arquivos objeto e o executável:

```bash
make clean
```

## Execução

O programa aceita os seguintes argumentos:

```bash
./ted -e [dir_entrada] -f [arquivo.geo] -o [dir_saida] [-q [arquivo.qry]]
```

### Parâmetros

| Parâmetro | Obrigatório | Descrição |
|-----------|-------------|-----------|
| `-e` | Sim | Diretório base de entrada |
| `-f` | Sim | Arquivo `.geo` com descrição das formas |
| `-o` | Sim | Diretório base de saída |
| `-q` | Não | Arquivo `.qry` com comandos de processamento |

### Exemplo de Uso

```bash
./ted -e ./entrada/ -f formas.geo -o ./saida/ -q comandos.qry
```

## Arquivos de Entrada

### Arquivo .geo

Define as formas geométricas básicas. Comandos suportados:

- `c i x y r corb corp` - Círculo
- `r i x y w h corb corp` - Retângulo
- `l i x1 y1 x2 y2 cor` - Linha
- `t i x y corb corp a txto` - Texto
- `ts fFamily fWeight fSize` - Estilo de texto

### Arquivo .qry

Define os comandos de processamento:

- `pd l x y` - Posiciona disparador
- `lc c n` - Carrega formas no carregador
- `atch d cesq cdir` - Encaixa carregadores no disparador
- `shft d [e|d] n` - Pressiona botão do disparador
- `dsp d dx dy [v|i]` - Dispara forma
- `rjd d [e|d] dx dy ix iy` - Rajada de disparos
- `calc` - Processa formas na arena

## Arquivos de Saída

O programa gera dois tipos de saída:

### Arquivo .svg
Representação gráfica das formas geométricas resultantes do processamento.

### Arquivo .txt
Relatório textual detalhado contendo:
- Resultado de cada comando executado
- Pontuação final
- Número de instruções executadas
- Número de disparos realizados
- Número de formas esmagadas
- Número de formas clonadas

## Estrutura do Código

O projeto está organizado de forma modular:

- **pilha.c/h** - Implementação de pilha genérica
- **fila.c/h** - Implementação de fila genérica
- **carregador.c/h** - Gerenciamento de carregadores
- **disparador.c/h** - Gerenciamento de disparadores
- **arena.c/h** - Gerenciamento da arena do jogo
- **formas.c/h** - Manipulação de formas geométricas
- **processageo.c/h** - Processamento de arquivos .geo
- **processaqry.c/h** - Processamento de arquivos .qry
- **main.c** - Ponto de entrada do programa




