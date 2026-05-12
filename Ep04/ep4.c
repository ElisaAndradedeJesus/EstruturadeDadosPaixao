#include <stdio.h>
#include <stdlib.h>


//alocando memória
int **allocate_matrix(int rows, int cols){
    int **matriz = (int **)malloc(rows * sizeof(int*));
    if (matriz == NULL){
        printf("Erro ao alocar memória pra matriz");
        return 0;
    } else{
        for (int i = 0; i <rows; i++){
            matriz[i] = (int*)malloc(cols * sizeof(int*));
            if (matriz[i] == NULL){
                printf("Erro ao alocar memória pra matriz");
                for (int j = 0; j< i; j++){
                    free(matriz[j]);

                }
                free(matriz);
                return 0;
            }
        }
        return matriz;
    }
}

void deallocate_matrix(int **matrix, int rows){
    for (int i = 0; i<rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}
void read_matrix_values(int rows, int cols, int **matrix){
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("matrix[%d,%d]=", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

int* cria_vetor(int tamanho){
    int *vetor = (int*)malloc(tamanho*sizeof(int));
    return vetor;
}
void preenche_vetor(int *vetor, int **matrix,int rows){
    int cont = 0;
    for(int i = 0; i < rows; i++){
        for(int j =0;j<= i;j++){
            vetor[cont] = matrix[i][j];
            cont++;

        }

    }
}
void print_vetor(int *vetor,int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("vetor[%d]=%d\n", i, vetor[i]);
    }
}


int main(){
    int rows = 3, cols = 3;
    int tamanho = (rows*(rows+1))/2;

    int **matrix = allocate_matrix(rows,cols);
    int *vetor = cria_vetor(tamanho);
    read_matrix_values(rows, cols, matrix);
    preenche_vetor(vetor,matrix,rows);
    print_vetor(vetor,tamanho);
    
    
    return 0;
}
