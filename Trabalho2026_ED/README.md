# TP (Parte I)_Elisa Andrade de Jesus
Este projeto implementa um sistema de gerenciamento de partidas e times de futebol em linguagem C. O sistema permite consultar times e partidas, inserir, atualizar e remover partidas, além de gerar a tabela de classificação com base nos resultados registrados em arquivos CSV.

---

## Estrutura do Repositório

```
├── BD                # Pasta Base de dados no formato CSV
│   ├── app.py
│   ├── partidas_completo.csv
│   ├── partidas_parcial.csv
│   ├── partidas_vazio.csv
│   └── times.csv
├── include           # Pasta com arquivos .h
│   ├── bdpartidas.h 
│   ├── bdtimes.h
│   ├── partida.h
│   └── time.h
├── src               # Pasta com arquivos .c
│   ├── bdpartidas.c
│   ├── bdtimes.c
│   ├── partida.c
│   └── time.c
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
  - `make clean`: remove objetos e executáveis  ;
  - `make compile`: compila oprograma em umarquivo .o;

- **main.c:** Ponto de entrada do programa. Carrega a interface de usuário.

- **team.c / team.h :** Implementam o TAD `Time`. 

- **partida.c / partida.h :** Implementam o TAD `Partida`.

- **bdteams.c / bdteams.h :** 
  Implementam o TAD `BDTime`:
  - Acessa o Banco de Dados a carrega os times registrados no arquivo "times.csv"

 
- **bdpartidas.c / bdpartidas.h :** Definem o TAD `BDPartida` e funções:   
  - Acessa o Banco de Dados a carrega os times registrados no arquivo "partidas.csv";

- **BD :** Pasta com todos os arquivos que emulam o Banco de Dados do projeto.

- **include :** Pasta com os arquivos .h (os headers) criados.

- **src :** Pasta com os arquivos .c referentes as TADs.

- **.gitignore :** Arquivo responsável para garantir que nenhum arquivo .o vá para o repositório do GitHub.

- **tp1.pdf :** Documento utilizado como consuta durante a construão do programa, contém requisitos e outras informações importantes que moldaram as escolhas de codificação.

---

## TADs utilizados: (TEM QUE MUDAR TUDO)

### 1. Time

O projeto utiliza o TAD **Time**, definido como uma `struct` em `team.c`, que possui os seguintes campos:

- `id` (int): Número identificador do time.
- `nome` (char[50]): Nome do time.

- `vitorias` (int): Quantas vitórias tiveram.
- `empates` (int): Quantas vezes empataram.
- `derrotas` (int): Quantos vazes perderam.

- `golsMarcados` (int): Quantos gols marcaram.
- `golsSofridos` (int): Quantos gols sofreram.

Este TAD é a base para manipulação dos dados do time.
### 2. BDTimes 

O TAD **BDTimes**, definido em `bdtimes.h`, representa uma estrutura dinâmica baseada em lista ligada que armazena múltiplos registros de times. Possui os seguintes campos:

- `nElementos` (int): Número de times armazenados.

- `capacidade` (int): Quantidade máxima de elementos que se pode armazenar.

- `teams` (Team**): Arrey com ponteiros para os teams.

Este TAD é a base para manipulação dos dados de todos os times cadastrados.

### 2. BDPartidas 

O TAD **BDTimes**, definido em `bdtimes.h`, representa uma estrutura dinâmica baseada em lista ligada que armazena múltiplos registros de times. Possui os seguintes campos:

- `nElementos` (int): Número de times armazenados.

- `capacidade` (int): Quantidade máxima de elementos que se pode armazenar.

- `teams` (Team**): Arrey com ponteiros para os teams.

Este TAD é a base para manipulação de todas as partidas.

---

## Instruções para Execução
Caso esteja seguindo o passo a passo do repositório **EstruturadeDadosPaixao**:
```bash
  cd Trabalho2026_ED
```
Se não:

**Clone o repositório:**
 ```bash
   git clone https://github.com/exemplo.git
    cd exemplo
   ```

**Para rodar o programa:** 
```bash
  make 
  ```
O comando `make` executa clean, compile e run para facilitar a execução do programa. Porém casoaja a nescessidade das etapas serem executadas separadamente:

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

3. **Limpeza dos arquivos objeto**  
   ```bash
   make clean
   ```

---

## Principais Decisões de Implementação



- **Vetores Dinâmicos de Ponteiros:** Os bancos de dados (BDTeams e BDPartidas) foram implementados utilizando vetores dinâmicos de ponteiros, permitindo armazenamento flexível e crescimento conforme necessário.

- **Validação de Entrada:**  
  - CPF: 11 dígitos numéricos, formatado como `xxx.xxx.xxx-xx`  
  - Idade: valor entre 1 e 130  
  - Data: formato `AAAA-MM-DD`, com checagem de ano, mês e dia  

- **Persistência em CSV:** Ao iniciar, lê tudo em memória; ao inserir/atualizar/remover, salva automaticamente no arquivo.

- **Busca por Prefixo e Insensível a Caso:**  
  - `strncasecmp` para nomes  
  - `strncmp` para CPFs  
  - `strcasestr_custom` para buscas arbitrárias  

- **Interface Intuitiva:** Contem paginação de 20 registros por tela e confirmações explícitas para operações destrutivas.  

- **Modularização:** Fornece uma separação clara entre:
  - lógica de dados (`bd.*`),
  - definição do modelo (`paciente.*`),
  - UI (`ui.*`),
  - utilitários (`util.*`).


---

Este README.md oferece uma visão completa do sistema, desde a estrutura dos arquivos até as principais decisões tomadas para que o sistema tenha uma funcionalidade plena.