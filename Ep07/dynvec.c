#include "dynvec.h" // Tem que incluir o .h
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct dynvec{
    int n; // Numeros de elementos
    int n_max; // capacidade do vetor
    float *v; // dados do vetor
};

// Função para criar um novo vetor dinâmico
DynVec *dvCreate(){
    DynVec *dv = (DynVec *)malloc(sizeof(DynVec));

    dv->n = 0; //seta que tem 0 elementos no inicio
    dv ->n_max = 4; // começa com espaçosuficiente para 4 elementos
    dv->v = (float *)malloc(dv->n_max * sizeof(float)); //aloca memoriapra os 4 primeiros elementos 
    
    return dv;
}

//Criar Vetor de um arquivo externo
DynVec *dvCreateFromFile(const char *filename){
    FILE *f = fopen(filename,"rt"); //Abri a file para reading
    if(f==NULL)
        return NULL;

    DynVec *dv = dvCreate();
    float x;

    while (fscanf(f,"%f", &x) == 1)
        dvInsert(dv,x);

    fclose(f);
    return dv;


}

//Função pra almentar o tamanho do espaço disponível para o vetor
static void reallocate(DynVec *dv){
    dv->n_max *= 2;
    dv ->v = (float *)realloc(dv->v,dv->n_max * sizeof(float));
}

//Função para inserir Um valor no vetor
void dvInsert(DynVec *dv,float x){
    // Checar se há espaço no vetor
    if (dv->n == dv->n_max)
        reallocate(dv);

    dv->v[dv->n++] = x; //adiciona um elemento na lista.
}

//Função ŕa saber o tamanho do DynVec
int dvSize(DynVec *dv){
    return dv->n;
}

//Função pra saber a capacidade do Vetor
int dvCapacity(DynVec *dv){
    return dv->n_max;
}
float dvGet(DynVec *dv, int i){

    assert(i >= 0 && i < dv->n);

    return dv->v[i];
}

//Função ra liberar a memóriado vetor dinâmico
void dvFree(DynVec *dv){
    free(dv->v);
    free(dv);
}
//Fução pra printar os valores do vetor dinâmico
void dvPrintValues(DynVec *dv){
    for(int i = 0; i < dvSize(dv); i++){
        printf("%.2f ", dvGet(dv,i));
    }
    printf("\n");
}

DynVec *dvConcatenate(DynVec *dv1, DynVec *dv2){
    DynVec *dv = dvCreate();
    for(int i = 0; i < dvSize(dv1); i++){
        float number = dvGet(dv1,i);
        dvInsert(dv,number);
    }
    for(int i = 0; i < dvSize(dv2); i++){
        float number = dvGet(dv2,i);
        dvInsert(dv,number);
    }
    return dv;
}

//  TAREFA DO EP7
// ========================================================

//Checa se um número já está na lista
int checkIfExist(DynVec *dv, float n){
    for(int i = 0; i < dvSize(dv); i++){
        if (dv->v[i] == n)
            return 1;
    }
    return 0;
}

// União de dv1 e dv2
DynVec *dvUnion(DynVec *dv1, DynVec *dv2) {
    DynVec *dv = dvCreate();
    for (int i = 0; i < dvSize(dv1); i++){
        float number = dvGet(dv1,i);
        dvInsert(dv,number);
    }
    for (int i = 0; i < dvSize(dv2); i++){
        float number = dvGet(dv2,i);
        if(checkIfExist(dv, number) == 0)
            dvInsert(dv,number);
    }
    return dv;
    
}

//interseção de dv1 e dv2
DynVec *dvIntersection(DynVec *dv1, DynVec *dv2){
    DynVec *dv = dvCreate();
    for (int i = 0; i < dvSize(dv1); i++){
        float number = dvGet(dv1,i);
        if(checkIfExist(dv2, number) == 1)
            dvInsert(dv,number);
    
    }
    return dv; 
}
