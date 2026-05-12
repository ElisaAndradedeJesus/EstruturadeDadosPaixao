#ifndef DYNVEC_H
#define DYNVEC_H

typedef struct dynvec DynVec;

//Funções

// Função para criar um novo vetor dinâmico
DynVec *dvCreate();

//Criar Vetor de um arquivo externo
DynVec *dvCreateFromFile(const char *filename);

//Função para inserir Um valor no vetor
void dvInsert(DynVec *dv,float x);

//Função ŕa saber o tamanho do DynVec
int dvSize(DynVec *dv);

//Função pra saber a capacidade do Vetor
int dvCapacity(DynVec *dv);

float dvGet(DynVec *dv, int i);

//Função ra liberar a memóriado vetor dinâmico
void dvFree(DynVec *dv);

//Fução pra printar os valores do vetor dinâmico
void dvPrintValues(DynVec *dv);

//Função para juntar duas funções  independente de conteúdo repetido ou não
DynVec *dvConcatenate(DynVec *dv1, DynVec *dv2);

//  TAREFA DO EP7
// ========================================================


// União de dv1 e dv2
DynVec *dvUnion(DynVec *dv1, DynVec *dv2);

//interseção de dv1 e dv2
DynVec *dvIntersection(DynVec *dv1, DynVec *dv2);


#endif