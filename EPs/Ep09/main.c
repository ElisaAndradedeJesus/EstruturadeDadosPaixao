#include "stack.h"
#include <stdio.h>
#include <string.h>

int main(){
    
    char arquivo[] = "arquivos/erro.csv";
    FILE *file = fopen(arquivo, "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        return 1;
    }
    char msg[20] = "";
    char c;
    Stack *s = s_create();

    while((c = fgetc(file)) != EOF){
        printf("%c", c);
        if(c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}'){

            if(c == ']' || c == ')' || c == '}'){
                if(s_is_empty(s)){
                    strcpy(msg, "fail");
                    break;
                }
                char top = s_top(s);
                if((c == ']' && top != '[') || (c == ')' && top != '(') || (c == '}' && top != '{')){
                    strcpy(msg, "fail");
                    break;
                }
                s_pop(s);
            } else {

                strcpy(msg, "success");
                // printf("%s%c", msg, c);
                s_push(s, c);
            }

        }   
    } 

    printf("%s\n", msg);
    fclose(file);
   return 0;
}