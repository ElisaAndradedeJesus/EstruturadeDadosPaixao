int converte_nota(char nota) {
    if (nota == "A")
        return 10;
    if (nota == "B")
        return 8;
    if (nota == "C")
        return 6;
    if (nota == "D")
        return 4;
    if (nota == "F")
        return 0;
    return -1;
}

int main () {
    char nota;
    int Nnota;

    printf("Nota alfabética: ");
    scanf("%s", &nota);
    Nnota = converte_nota(nota);
    if (Nnota == -1){
        printf("%s não consta no Banco de Dados!", nota); 
    } else {
        printf("%d", Nnota);
    }
    return 0;

}