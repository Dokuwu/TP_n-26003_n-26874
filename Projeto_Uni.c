#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include <string.h>

#define linhas 20
#define colunas 50


void dados_participantes() {
    int i, j, num, tel, idade, tamanho_fich = 0;
    FILE* dados_part;
    char strings[linhas][colunas];
    char nome[linhas][colunas];
    int aux;
    i = 0;
    dados_part = fopen("dados_participantes.txt","r");
    printf("Conteudo do ficheiro:\n");
    if (dados_part != NULL)
    {
        while (!feof(dados_part))
        {
            fgets(strings, linhas, dados_part);
            strcpy(nome[i], strings);
            i++;
            tamanho_fich++;
        }
     
        fclose(dados_part);
    }
    else
    {
        printf("Impossivel abrir o ficheiro");
    }

    for (i = 0; i < tamanho_fich; i++)
    {
        printf("%s", nome[i]);
    }
}


void main()
{
    setlocale(LC_ALL, "Portuguese");
    dados_participantes();
}
