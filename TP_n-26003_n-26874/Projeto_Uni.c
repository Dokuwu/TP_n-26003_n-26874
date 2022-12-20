#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256

typedef struct {
    int num;
    char nome[MAX_LINE_LEN];
    long long numphone;
    int idade;
} InfParti;

int main() {
    FILE* txt1 = fopen("txt1.txt", "r");
    InfParti infparti[3];//Array com informação dos participantes
    InfParti parti; //Participante
    int numparti = 0; //numero de participantes
    char linha[MAX_LINE_LEN];

    if (txt1 == NULL) {
        perror("Erro ao abrir ficheiro");
        return 1;
    }
    else {
        while (fgets(linha, MAX_LINE_LEN, txt1) != NULL) {
            // fscanf reads from the named input stream. sscanf reads from the character string s.
            // fscanf(): fscanf() reads formatted data from file and stores it into variables.
            // sscanf(): sscanf() is used to read formatted input from the string.
            sscanf(linha, "%d;%[^;];%lld;%d", &parti.num, parti.nome, &parti.numphone, &parti.idade);

            infparti[numparti++] = parti;
        }
        fclose(txt1);
    }

    for(int c = 0; c < numparti; c++){
    printf("Practitioner number: %d\n", infparti[c].num);
    printf("Practitioner name: %s\n", infparti[c].nome);
    printf("Practitioner telephone: %lld\n", infparti[c].numphone);
    printf("Practitioner age: %d\n", infparti[c].idade);
    printf("\n");
    }

        return 0;
}