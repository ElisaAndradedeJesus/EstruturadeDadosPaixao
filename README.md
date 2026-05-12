# Estrutura de Dados — 2026

Repositório dedicado às atividades, exercícios e trabalhos desenvolvidos durante a disciplina de Estrutura de Dados.

<!-- TODO: adicionar Makefiles -->
<!-- TODO: Escrever algo sobre o trabalho -->

## Objetivos
- Organizar os estudos da disciplina
- Documentar evolução ao longo do semestre
- Centralizar implementações e experimentos em C

## Estrutura

```
├── EPs               # Atividades avaliativas
    ├── EP1
    ├── EP2
    ├── EP3
    ├── EP4
    ├── EP5
    ├── EP6
    ├── EP7
    └── EP8
├── Exercicios        # Alguns exercícios feitos
├── Trabalho2026_ED   # Trabalho de ED 2026
├── README.md         # Auto explicativo né, pelo amor de Deus!

```

### Sobre os arquivos:

- **EPs:** As pastas EP dentro de EPs são independentes entre si. Todas possuem o próprio Makefile para automatização de compilação e execução.

- **Exercicios:** Pasta com alguns exercícios realizados. Possui também o caderno de Exercícios para consulta.

- **Trabalho2026_ED:** Projeto principal da disciplina desenvolvido em C utilizando modularização, TADs e estruturas dinâmicas para gerenciamento e processamento de dados.



## Instruções para Execução

**Clone o repositório:**
 ```bash
   git clone https://github.com/ElisaAndradedeJesus/EstruturadeDadosPaixao.git
    cd EstruturadeDadosPaixao
   ```

### Como Executar o Trabalho:

Passo a passo detalhado no README da pasta "Trabalho2026_ED". 

### Como Executar as EPs:
Cada EP tem um Makefile próprio. Para executar a EP desejada primeiro  é necessário entrar diretório da EP.



1. **Acessar diretório:**  
Abra a pasta no VSCode ou execute no terminal:

    ```bash
    cd EPs/EPXX
    ```

    Substitua `XX` pelo número da EP desejada.

2. **Compilar:**
   ```bash
   make
   ```

3. **Executar o programa:**
   ```bash
   make run
   ```

---
