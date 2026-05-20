# TP (Parte I)_Elisa Andrade de Jesus
Este projeto implementa um sistema de gerenciamento de partidas e times de futebol em linguagem C. O sistema permite consultar times e partidas, gerar a tabela de classificação e possui estrutura preparada para inserção, atualização e remoção de partidas em versões futuras.

---

## Estrutura do Repositório

```
├── BD                # Pasta Base de dados no formato CSV
│   ├── app.py
│   ├── bd_partidas.csv
│   ├── partidas_parcial.csv
│   ├── partidas_vazio.csv
│   └── bd_times.csv
├── include           # Pasta com arquivos .h
│   ├── bdpartidas.h 
│   ├── bdteams.h
│   ├── menu.h
│   ├── partida.h
│   └── team.h
├── src               # Pasta com arquivos .c
│   ├── bdpartidas.c
│   ├── bdteams.c
│   ├── menu.c
│   ├── partida.c
│   └── team.c
├── Makefile          # Automação de compilação e execução
├── main.c            # Ponto de entrada do programa
├── README.md         # Informações de execução e funcionamento do programa
└── tp1.pdf           # Documento guia. Especificações do trabalho.
```

---

### Sobre os arquivos: 

---

- **Makefile:**  
  - `make`: Executa: `clean compile run` nesta sequência;
  - `make run`: roda o programa;
  - `make clean`: remove o executável gerado;
  - `make compile`: compila o programa em um arquivo executável;

- **main.c:** Ponto de entrada do programa.
  - Carrega CSVs
  - Cria os bancos
  - Atualiza estatísticas dos times com base nas partidas
  - Controla loop do menu
  - Libera memória

- **menu.c / menu.h :** Implementam as funções relacionadas à interface textual e interação com o usuário, incluindo exibição do menu principal, limpeza do terminal e operações de consulta e impressão de dados.

- **team.c / team.h :** Implementam o TAD `Team`. 

- **partida.c / partida.h :** Implementam o TAD `Partida`.

- **bdteams.c / bdteams.h :** 
  Implementam o TAD `BDTeams`:
  - Acessa o Banco de Dados e carrega os times registrados no arquivo "bd_times.csv"

 
- **bdpartidas.c / bdpartidas.h :** Definem o TAD `BDPartidas` e funções:   
  - Acessa o Banco de Dados e carrega as partidas registradas no arquivo "bd_partidas.csv";

- **BD :** Pasta com todos os arquivos que emulam o Banco de Dados do projeto.

- **include :** Pasta com os arquivos .h (os headers) criados.

- **src :** Pasta com os arquivos .c referentes às TADs.

- **.gitignore :** Arquivo responsável para garantir que nenhum arquivo .o vá para o repositório do GitHub.

- **tp1.pdf :** Documento utilizado como consulta durante a construção do programa, contém requisitos e outras informações importantes que moldaram as escolhas de codificação.

---

## TADs utilizados:

### 1. Team

O projeto utiliza o TAD **Team**, definido como uma `struct` em `team.c`. Este TAD representa cada time e possui os seguintes campos:

- `id` (int): Número identificador do time.
- `nome` (char[50]): Nome do time.

- `vitorias` (int): Quantas vitórias tiveram.
- `empates` (int): Quantas vezes empataram.
- `derrotas` (int): Quantas vezes perderam.

- `golsMarcados` (int): Quantos gols marcaram.
- `golsSofridos` (int): Quantos gols sofreram.

Este TAD é a base para manipulação dos dados do time.

### 2. Partida

O projeto utiliza o TAD **Partida**, definido como uma `struct` em `partida.c`, que possui os seguintes campos:

struct partida {
    int id;
    int idTime1;
    int idTime2;
    int golsTime1;
    int golsTime2;
};

- `id` (int): Número identificador da partida.

- `idTime1` (int): Número identificador do time mandante.

- `idTime2` (int): Número identificador do time visitante.

- `golsTime1` (int): Quantos gols o time mandante marcou.
- `golsTime2` (int): Quantos gols o time visitante marcou.

Este TAD é a base para manipulação dos dados da partida.

### 3. BDTeams 

O TAD **BDTeams**, definido em `bdteams.h`, representa uma estrutura dinâmica baseada em vetores dinâmicos de ponteiros que armazena múltiplos registros de times. Possui os seguintes campos:

- `nElementos` (int): Número de times armazenados.

- `capacidade` (int): Quantidade máxima de elementos que se pode armazenar.

- `teams` (Team**): Array com ponteiros para os times.

Este TAD manipula os dados de todos os times cadastrados.

### 4. BDPartidas 

O TAD **BDPartidas**, definido em `bdpartidas.h`, também representa uma estrutura baseada em vetores dinâmicos que armazena múltiplos registros de partidas. Possui os seguintes campos:

- `nElementos` (int): Número de partidas armazenadas.

- `capacidade` (int): Quantidade máxima de elementos que se pode armazenar.

- `partidas` (Partida**): Array com ponteiros para as partidas.

O TAD BDPartidas manipula todas as partidas.

---

## Instruções para Execução
Caso esteja seguindo o passo a passo do repositório **EstruturadeDadosPaixao**:
```bash
  cd Trabalho2026_ED
```
Se não:

**Clone o repositório:**
 ```bash
   git https://github.com/ElisaAndradedeJesus/CampeonatoComputacionaldeFutebol_ElisadeJesus.git
   cd CampeonatoComputacionaldeFutebol_ElisadeJesus
   ```

**Para rodar o programa:** 
```bash
  make 
  ```
O comando `make` executa clean, compile e run para facilitar a execução do programa. Porém caso haja a necessidade das etapas serem executadas separadamente:

1. **Compilar**  
   ```bash
   make compile
   ```
---

2. **Executar o programa**  
   ```bash
   make run
   ```

---

3. **Remover arquivo executável**  
   ```bash
   make clean
   ```

---

## Principais Decisões de Implementação



- **Vetores Dinâmicos de Ponteiros:** Os bancos de dados (BDTeams e BDPartidas) foram implementados utilizando vetores dinâmicos de ponteiros, permitindo armazenamento flexível e crescimento conforme necessário.

- **Terminal limpo regularmente:** Para evitar um terminal poluído por múltiplas execuções do programa. Esta decisão foi puramente estética.

<!-- - **Persistência em CSV:** Ao iniciar, lê tudo em memória; ao inserir/atualizar/remover, salva automaticamente no arquivo. (acho que posso adicionar esta linha quando fizer aparte 2 do trabalho, mas no momento n salvo nada no CSV pois n há a necessidade)-->

- **Busca por Prefixo Case Sensitive:** Foi utilizada a função `strncmp`, mantendo diferenciação entre letras maiúsculas e minúsculas durante as buscas por prefixo.

- **Cálculo da classificação a partir das partidas:** Os dados estatísticos dos times (vitórias, derrotas, empates e saldo relacionado a gols) são atualizados dinamicamente com base no banco de partidas carregado em memória.

- **Modularização:** O sistema foi dividido em módulos independentes para separar responsabilidades e melhorar organização/manutenção do código:

  - modelos de dados (`Team` e `Partida`);
  - estruturas de armazenamento (`BDTeams` e `BDPartidas`);
  - interface e interação com o usuário (`menu.c`);
  - fluxo principal de execução (`main.c`).

---

Este README.md oferece uma visão geral da estrutura, funcionamento e principais decisões de implementação do sistema.