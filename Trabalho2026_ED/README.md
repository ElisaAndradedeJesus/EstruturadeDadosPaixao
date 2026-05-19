# TP (Parte I)_Elisa Andrade de Jesus

Este projeto implementa um sistema de cadastro, consulta, inserção, atualização e remoção de pacientes usando uma lista ligada em C. Os dados são carregados de e salvos em um arquivo CSV, e o usuário interage via terminal por meio de menus, com validações que garantem a integridade dos dados inseridos. (A MODIFICAR)

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
├── README.md         # Auto explicativo né, pelo amor de Deus!
└── tp1.pdf           # Documento guia. Especificações do trabalho.
```

---

### Sobre os arquivos: (TEM QUE MUDAR TUDO)

---

- **Makefile:**  
  - `make`: Executa: `clean compile run` nesta sequência;
  - `make run`: roda o programa;
  - `make clean`: remove objetos e executáveis  ;
  - `make compile`: compila oprograma em umarquivo .o;

- **main.c:** Ponto de entrada do programa. Carrega a interface de usuário.

- **time.c / time.h :** Implementam o TAD `Time`. 

- **partida.c / partida.h :** Implementam o TAD `Partida`.

- **bdtime.c / bdtime.h** 
  Implementam o TAD `BDTime`:
  - Acessa o Banco de Dados a carrega os times registrados no arquivo "times.csv"

 
- **paciente.c / paciente.h**  
  Definem o TAD `Paciente` e funções:  
  - `paciente_parse()` — converte linha CSV em struct  
  - `paciente_imprimir()` — formata e exibe um registro  

- **ui.c / ui.h**  
  Contêm toda a lógica de interação:  
  - menus de consulta, inserção, atualização e remoção  
  - paginação na impressão  
  - validações de CPF, nome, idade e data  

- **util.c / util.h:** Fornecem `strcasestr_custom()`, uma busca de substring **case-insensitive**.

---

## TADs utilizados: (TEM QUE MUDAR TUDO)

### 1. Time
O projeto utiliza o TAD **Paciente**, definido como uma `struct` em `time.c`, que possui os seguintes campos:

- `id` (int): Número identificador do time.
- `nome` (char[50]): Nome do time.

- `vitorias` (int): Quantas vitórias tiveram.
- `empates` (int): Quantas vezes empataram.
- `derrotas` (int): Quantos vazes perderam.

- `golsMarcados` (int): Quantos gols marcaram.
- `golsSofridos` (int): Quantos gols sofreram.

Este TAD é a base para manipulação dos dados, permitindo que as operações de consulta e impressão sejam realizadas de forma consistente e organizada.

### 2. BDTimes (lista ligada)

O TAD **BDTimes**, definido em `bdtimes.h`, representa uma estrutura dinâmica baseada em lista ligada que armazena múltiplos registros de pacientes. Ela é composta por nós (`struct No`), onde cada nó guarda um `Paciente` e aponta para o próximo na sequência.

- `No`:  
  - `paciente` (Paciente): Estrutura contendo os dados do paciente.  
  - `proximo` (No*): Ponteiro para o próximo nó da lista.

- `BDPaciente`:  
  - `inicio` (No*): Ponteiro para o primeiro nó da lista, que representa o início da base de dados.

Este TAD permite o gerenciamento flexível da coleção de pacientes, possibilitando operações como inserção, busca, atualização, remoção, leitura e escrita em arquivo CSV. 

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



1. **Compilar**  
   ```bash
   make
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

- **Lista Ligada:** Facilita inserção e remoção sem realocar estruturas inteiras.

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