# TP Parte II - Campeonato Computacional de Futebol

Este projeto implementa um sistema de gerenciamento de partidas e times de futebol em linguagem C. Na Parte II, o sistema permite consultar times e partidas, inserir, atualizar e remover partidas, persistir as alterações em CSV e imprimir a tabela de classificação ordenada.

## Estrutura do Repositório

```text
├── BD
│   ├── bd_classificacao.csv
│   ├── bd_partidas.csv
│   ├── bd_times.csv
│   ├── partidas_parcial.csv
│   └── partidas_vazio.csv
├── include
│   ├── bdpartidas.h
│   ├── bdteams.h
│   ├── menu.h
│   ├── partida.h
│   └── team.h
├── src
│   ├── bdpartidas.c
│   ├── bdteams.c
│   ├── menu.c
│   ├── partida.c
│   └── team.c
├── Makefile
├── main.c
└── README.md
```

## Como Executar

```bash
make compile
make run
```

Também é possível executar `make`, que limpa, compila e roda o programa. Para remover o executável gerado:

```bash
make clean
```

## Funcionalidades

- Consultar times por nome ou prefixo, sem diferenciar letras maiúsculas e minúsculas.
- Consultar partidas por time mandante, visitante ou ambos.
- Atualizar o placar de uma partida existente.
- Remover uma partida existente.
- Inserir uma nova partida com ID gerado automaticamente.
- Imprimir a tabela de classificação ordenada por pontos ganhos, vitórias, saldo de gols e gols marcados.
- Persistir alterações em `BD/bd_partidas.csv` e gerar `BD/bd_classificacao.csv`.

## TADs

### Team

Representa um time do campeonato. Guarda o ID, nome e estatísticas calculadas a partir das partidas: vitórias, empates, derrotas, gols marcados e gols sofridos. Pontos ganhos e saldo de gols são calculados por funções de acesso.

### Partida

Representa uma partida. Guarda ID, ID do time mandante, ID do time visitante, gols do mandante e gols do visitante.

### BDTeams

Gerencia os times cadastrados usando lista simplesmente encadeada. É responsável por carregar os times do CSV, buscar times por ID ou prefixo e recalcular as estatísticas a partir do banco de partidas.

### BDPartidas

Gerencia as partidas usando lista simplesmente encadeada. É responsável por carregar partidas do CSV, buscar por prefixo de time, inserir, atualizar, remover e salvar os registros.

## Decisões de Implementação

- **Lista encadeada:** `BDTeams` e `BDPartidas` armazenam seus elementos em listas simplesmente encadeadas, conforme solicitado na Parte II.
- **Busca por prefixo case-insensitive:** a comparação ignora diferenças entre letras maiúsculas e minúsculas para melhorar a experiência do usuário.
- **Persistência em CSV:** inserções, atualizações e remoções salvam novamente o arquivo `BD/bd_partidas.csv`.
- **Classificação recalculada:** após cada alteração, as estatísticas dos times são zeradas e recalculadas com base em todas as partidas.
- **Ordenação da classificação:** a tabela é ordenada por pontos ganhos, vitórias, saldo de gols e gols marcados.
- **Modularização:** os TADs ficam separados da interface textual e do fluxo principal em `main.c`.
