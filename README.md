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
├── CampeonatoComputacionaldeFutebol_ElisadeJesus   # Trabalho de ED 2026
├── README.md         # Auto explicativo né, pelo amor de Deus!

```

### Sobre os arquivos:

- **EPs:** As pastas EP dentro de EPs são independentes entre si. Todas possuem o próprio Makefile para automatização de compilação e execução.

- **Exercicios:** Pasta com alguns exercícios realizados. Possui também o caderno de Exercícios para consulta.

- **CampeonatoComputacionaldeFutebol_ElisadeJesus:** Projeto principal da disciplina desenvolvido em C utilizando modularização, TADs e estruturas dinâmicas para gerenciamento e processamento de dados.



## Instruções para Execução

**Clone o repositório:**
 ```bash
   git clone https://github.com/ElisaAndradedeJesus/EstruturadeDadosPaixao.git
   cd EstruturadeDadosPaixao
   ```

### Como Executar o Trabalho:

Passo a passo detalhado no README da pasta `CampeonatoComputacionaldeFutebol_ElisadeJesus`. 

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

## Subtree

A pasta `CampeonatoComputacionaldeFutebol_ElisadeJesus` também possui um repositório próprio:

`https://github.com/ElisaAndradedeJesus/CampeonatoComputacionaldeFutebol_ElisadeJesus.git`

Essa separação foi adotada para facilitar a entrega e melhorar a visibilidade do trabalho final, mantendo um repositório dedicado apenas ao projeto.

As alterações feitas neste repositório podem ser sincronizadas com o repositório específico do trabalho seguindo os passos abaixo:

   1. **Atualizar o repositório principal:**
      ```bash
      git add .
      git commit -m "alterações"
      git push origin main   # repositório principal
      ```
      Também é possível fazer isso pela interface do VSCode.

   2. **Sincronizar a subpasta com o repositório independente**
      ```bash
      make sync-campeonato  # repositório independente
      ```
      O comando `make sync-campeonato` executa internamente `git subtree push`, que envia apenas a pasta `CampeonatoComputacionaldeFutebol_ElisadeJesus/` para o repositório independente, preservando o restante da estrutura do repositório principal.

Isso permite manter dois repositórios sincronizados sem duplicar arquivos manualmente.

---

