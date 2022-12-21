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

//informação de cada  atividade realizada por cada praticante, nomeadamente, número de praticante, data, nome da atividade, 
//hora de início da atividade, tempo de duração da atividade, distância e unidades de medida
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
    int duracao, dist;
    char unidmedida[MAX_LINE_LEN];
} Infativ;

//contendo os dados dos planos de atividades para cada praticante.Cada linha deve identificar o praticante, data e hora de início e fim
//da atividade, atividade, distância e medida a atingir :

typedef struct {
    int num;
    Data datai, dataf;
    Horario horarioi, horariof;
    char nomeativ[MAX_LINE_LEN];
    int dist;
    char unidmedida[MAX_LINE_LEN];
} Planativ;

int transtxt1(FILE* txt1, char linha[MAX_LINE_LEN], int numparti, InfParti infparti[10], int numeros[]) {

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

            numeros[numparti] = parti.num;
            infparti[numparti++] = parti;
        }

        fclose(txt1);
    }
    return numparti;
}

int transtxt2(FILE* txt2, char linha[MAX_LINE_LEN], int numativ, Infativ infativ[10]) {

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
                partiativ.nomeativ, &partiativ.duracao, &partiativ.dist, partiativ.unidmedida);

            infativ[numativ++] = partiativ;
        }

        fclose(txt2);
    }

    return numativ;
}

int transtxt3(FILE* txt3, char linha[MAX_LINE_LEN], int numplanativ, Planativ planativ[10]) {

    Planativ partplan; //Participante nas atividades

    if (txt3 == NULL) {
        perror("Erro ao abrir ficheiro txt3");
        return 0;
    }
    else {

        while (fgets(linha, MAX_LINE_LEN, txt3) != NULL) {
            //0001; 01 - 01 - 2022; 10h30; 20 - 01 - 2022; 11h45; Marcha; 15; km
            //d;d-d-d;dhd;d-d-d;dhd;%[^;];d;s
            sscanf(linha, "%d;%d-%d-%d;%dh%d;%d-%d-%d;%dh%d;%[^;];%d;%s", &partplan.num, &partplan.datai.dia, &partplan.datai.mes, &partplan.datai.ano,
                &partplan.horarioi.hora, &partplan.horarioi.minutos, &partplan.dataf.dia, &partplan.dataf.mes, &partplan.dataf.ano,
                &partplan.horariof.hora, &partplan.horariof.minutos, partplan.nomeativ, &partplan.dist, partplan.unidmedida);

            planativ[numplanativ++] = partplan;
        }

        fclose(txt3);
    }

    return numplanativ;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Organizar as arrays com as informações essenciais
void orgatxt1(InfParti infparti[10], int numparti) {
    char b = 1;
    InfParti k[10];

    while (b == 1) {
        b = 0;
        for (int c = 0; c < numparti - 1; c++) {
            if (infparti[c + 1].num < infparti[c].num) {
                k[0] = infparti[c];
                infparti[c] = infparti[c + 1];
                infparti[c + 1] = k[0];
                b = 1;
            }
        }
    }

}

void orgatxt2(Infativ infativ[10], int numativ) {
    char b = 1;
    Infativ k[10];

    while (b == 1) {
        b = 0;
        for (int c = 0; c < numativ - 1; c++) {
            if (infativ[c + 1].num < infativ[c].num) {
                k[0] = infativ[c];
                infativ[c] = infativ[c + 1];
                infativ[c + 1] = k[0];
                b = 1;
            }
        }
    }
}

void orgatxt3(Planativ planativ[10], int numplanativ) {
    char b = 1;
    Planativ k[10];

    while (b == 1) {
        b = 0;
        for (int c = 0; c < numplanativ - 1; c++) {
            if (planativ[c + 1].num < planativ[c].num) {
                k[0] = planativ[c];
                planativ[c] = planativ[c + 1];
                planativ[c + 1] = k[0];
                b = 1;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int ex4(Infativ infativ[], int numativ) {
    int numero, diai, mesi, anoi, diaf, mesf, anof, total = 0;
    char nomativ[50];
    printf("Atividades registadas:\n");
    printf("Marcha\nBTT\nWindsurfing\nNatacao\n");
    printf("\nNumero da pessoa:");
    scanf("%d", &numero);
    printf("Nome da atividade:");
    scanf("%s", nomativ);
    printf("Primeira data [d-m-a]:");
    scanf("%d-%d-%d", &diai, &mesi, &anoi);
    printf("Segunda data [d-m-a]:");
    scanf("%d-%d-%d", &diaf, &mesf, &anof);


    for (int c = 0; c < numativ; c++) {

        if (numero == infativ[c].num)
            if ((diai <= infativ[c].data.dia && infativ[c].data.dia <= diaf) && (mesi <= infativ[c].data.mes && infativ[c].data.mes <= mesf)
                && (anoi <= infativ[c].data.ano && infativ[c].data.ano <= anof) && !(strcmp(nomativ, infativ[c].nomeativ)))
                total++;

    }

    printf("Total: %d\n", total);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void tabela(int numparti, int numativ, int numplanativ, InfParti infparti[], Infativ infativ[], Planativ planativ[]) {
    //: Número de Praticante, Nome, Atividade planeada, Medida (km, metros, 
    //segundos, outra) da unidade e o Valor dessa medida
    int z = 0;
    for (int c = 0; c < numparti; c++) {
        printf("------------------------------------------------------------------\n");
        printf("Numero: %d", infparti[c].num);
        printf(";    Nome: %s\n", infparti[c].nome);
        for (int d = z; d < numplanativ; d++, z++) {
            if (infparti[c].num != planativ[d].num)
                break;
            else {
                printf("Atividade planeada: %s", planativ[d].nomeativ);
                printf(";    Medida: %s", planativ[d].unidmedida);
                printf(";    Valor da medida: %d\n", planativ[d].dist);
                //Atividade realizada, Data de Início, Data de Fim, 
                //Medida(km, metros, segundos, outra) da unidade e o Valor dessa medida
                printf("Data inicio: %d-%d-%d", planativ[d].datai.dia, planativ[d].datai.mes, planativ[d].datai.ano);
                printf(";    Data fim: %d-%d-%d\n", planativ[d].dataf.dia, planativ[d].dataf.mes, planativ[d].dataf.ano);
                printf("Atividade realizada: %s", infativ[d].nomeativ);
                printf(";    Medida: %s", infativ[d].unidmedida);
                printf(";    Valor da medida: %d\n", infativ[d].dist);
            }

        }
    }

}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int a() {
    setlocale(LC_ALL, "");

    FILE* txt1;
    FILE* txt2;
    FILE* txt3;

    char linha[MAX_LINE_LEN];

    txt1 = fopen("txt1.txt", "r");
    InfParti infparti[10];//Array com informação dos participantes
    int numeros[50];//Lista dos Numeros existentes
    int numparti = 0; //numero de participantes
    numparti = transtxt1(txt1, linha, numparti, infparti, numeros);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    txt2 = fopen("txt2.txt", "r");
    Infativ infativ[10];//Array com informação das atividades
    int numativ = 0;
    numativ = transtxt2(txt2, linha, numativ, infativ);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    txt3 = fopen("txt3.txt", "r");
    Planativ planativ[10];//Array com informação das atividades
    int numplanativ = 0;
    numplanativ = transtxt3(txt3, linha, numplanativ, planativ);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    orgatxt1(infparti, numparti);

    orgatxt2(infativ, numativ);

    orgatxt3(planativ, numplanativ);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    ex4(infativ , numativ);

    tabela(numparti, numativ, numplanativ, infparti, infativ, planativ);

    return 0;
}