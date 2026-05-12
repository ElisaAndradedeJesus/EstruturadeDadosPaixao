#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int split_text(char *text, char* part1, char * part2){
    char *espaco = strchr(text,' ');
    if (espaco == NULL){
        return 0;
    }
    int indice = espaco - text;
    for(int i=0;i< indice;i++){
        part1[i] = text[i];
    }
    part1[indice] = '\0';

    int j = 0;
    for(int i = indice+1 ; text[i] != '\0' ;i++){
        part2[j] = text[i];
        j++;
    }
    part2[j] = '\0';
    return 1;
}

int main(){
    char text[] = "Bom dia";  
    char part1[20], part2[20];
    split_text(text,part1,part2);
    printf("%s\n%s\n%s\n", text,part1,part2);
    return 0;
}