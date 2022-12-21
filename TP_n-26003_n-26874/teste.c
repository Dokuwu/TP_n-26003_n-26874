#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_LINE_LEN 256

typedef struct {
    int num;
    char nome[MAX_LINE_LEN];
    long long numphone;
    int idade;
} InfParti;

//informa��o de cada  atividade realizada por cada praticante, nomeadamente, n�mero de praticante, data, nome da atividade, 
//hora de in�cio da atividade, tempo de dura��o da atividade, dist�ncia e unidades de medida
typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    int hora, minutos;
} Horario;

typedef struct {
    int num;
    Data data;
    char nomeativ[MAX_LINE_LEN];
    Horario inicio;
    int duracao, distancia;
    char unidmedida[MAX_LINE_LEN];
} Infativ;

//contendo os dados dos planos de atividades para cada praticante.Cada linha deve identificar o praticante, data e hora de in�cio e fim
//da atividade, atividade, dist�ncia e medida a atingir :

typedef struct {
    int num;
    Data datainicio, datafim;
    Horario horarioinicio, horariofim;
    char nomeativ[MAX_LINE_LEN];
    int distancia;
    char unidmedida[MAX_LINE_LEN];
} Planativ;

int uno(FILE* txt1, char linha[MAX_LINE_LEN], int numparti, InfParti infparti[10]) {

    InfParti parti; //Participante

    if (txt1 == NULL) {
        printf("Erro ao abrir ficheiro txt1");
        return 0;
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
    return numparti;
}

int dos(FILE* txt2, char linha[MAX_LINE_LEN], int numativ, Infativ infativ[10]) {

    Infativ partiativ; //Participante nas atividades

    if (txt2 == NULL) {
        printf("Erro ao abrir ficheiro txt2");
        return 0;
    }
    else {

        while (fgets(linha, MAX_LINE_LEN, txt2) != NULL) {

            //0001;12-07-2022;10:55;Marcha;23;2;km
            //d;d-d-d;d:d:s:d:d:s
            sscanf(linha, "%d;%d-%d-%d;%d:%d;%[^;];%d;%d;%s", &partiativ.num, &partiativ.data.dia, &partiativ.data.mes, &partiativ.data.ano, &partiativ.inicio.hora, &partiativ.inicio.minutos,
                partiativ.nomeativ, &partiativ.duracao, &partiativ.distancia, partiativ.unidmedida);

            infativ[numativ++] = partiativ;
        }

        fclose(txt2);
    }

    return numativ;
}

int tres(FILE* txt3, char linha[MAX_LINE_LEN], int numplanativ, Planativ planativ[10]) {

    Planativ partplan; //Participante nas atividades

    if (txt3 == NULL) {
        perror("Erro ao abrir ficheiro txt3");
        return 0;
    }
    else {

        while (fgets(linha, MAX_LINE_LEN, txt3) != NULL) {
            //0001; 01 - 01 - 2022; 10h30; 20 - 01 - 2022; 11h45; Marcha; 15; km
            //d;d-d-d;dhd;d-d-d;dhd;%[^;];d;s
            sscanf(linha, "%d;%d-%d-%d;%dh%d;%d-%d-%d;%dh%d;%[^;];%d;%s", &partplan.num, &partplan.datainicio.dia, &partplan.datainicio.mes, &partplan.datainicio.ano,
                &partplan.horarioinicio.hora, &partplan.horarioinicio.minutos, &partplan.datafim.dia, &partplan.datafim.mes, &partplan.datafim.ano,
                &partplan.horariofim.hora, &partplan.horariofim.minutos, partplan.nomeativ, &partplan.distancia, partplan.unidmedida);

            planativ[numplanativ++] = partplan;
        }

        fclose(txt3);
    }

    return numplanativ;
}

void organizetxt1(InfParti infparti[10], int numparti) {
    char b = 1;
    InfParti k[10];

    while (b == 1) {
        b = 0;
        for (int c = 0; c < numparti - 1; c++) {
            if (infparti[c+1].num < infparti[c].num) {
                k[0] = infparti[c];
                infparti[c] = infparti[c + 1];
                infparti[c + 1] = k[0];
                b = 1;
            }
        }
    }

}

int a() {
    setlocale(LC_ALL, "");

    FILE* txt1;
    FILE* txt2;
    FILE* txt3;

    int numparti = 0; //numero de participantes
    char linha[MAX_LINE_LEN];

    txt1 = fopen("txt1.txt", "r");
    InfParti infparti[10];//Array com informa��o dos participantes
    numparti = transtxt1(txt1, linha, numparti, infparti);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    txt2 = fopen("txt2.txt", "r");
    Infativ infativ[10];//Array com informa��o das atividades
    int numativ = 0;
    numativ = transtxt2(txt2, linha, numativ, infativ);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    txt3 = fopen("txt3.txt", "r");
    Planativ planativ[10];//Array com informa��o das atividades
    int numplanativ = 0;
    numplanativ = transtxt3(txt3, linha, numplanativ, planativ);

    for (int c = 0; c < numparti; c++)
        printf("%d;%s;%lld;%d\n", infparti[c].num, infparti[c].nome, infparti[c].numphone, infparti[c].idade);
    printf("\n");
   
    organizetxt1(infparti, numparti);

    for (int c = 0; c < numparti; c++)
        printf("%d;%s;%lld;%d\n", infparti[c].num, infparti[c].nome, infparti[c].numphone, infparti[c].idade);
    printf("\n");
}