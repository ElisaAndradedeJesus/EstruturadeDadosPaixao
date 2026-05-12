#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynvec.h" // Tem que incluir o .h


int main()
{
  //Cria e popula os Dynvec
  DynVec *dv1 = dvCreate();
  dv1 = dvCreateFromFile("dv1.txt");

  DynVec *dv2 = dvCreate();
  dv2 = dvCreateFromFile("dv2.txt");

  // Printa os vetores e suas informações
  printf("Valores de DV1:  ");
  dvPrintValues(dv1);
  printf("size=%d capacity=%d\n", dvSize(dv1), dvCapacity(dv1));
  printf("\n");

  printf("Valores de DV2:  ");
  dvPrintValues(dv2);
  printf("size=%d capacity=%d\n", dvSize(dv2), dvCapacity(dv2));
  printf("\n");

  DynVec *uniao = dvCreate();
  uniao = dvUnion(dv1,dv2);
  
  printf("Valores de UNIAO:  ");
  dvPrintValues(uniao);
  printf("size=%d capacity=%d\n", dvSize(uniao), dvCapacity(uniao));
  printf("\n");

  DynVec *intersecao = dvCreate();
  intersecao = dvIntersection(dv1,dv2);
  
  printf("Valores de INTERSECAO:  ");
  dvPrintValues(intersecao);
  printf("size=%d capacity=%d\n", dvSize(intersecao), dvCapacity(intersecao));
  printf("\n");

  return 0;
}