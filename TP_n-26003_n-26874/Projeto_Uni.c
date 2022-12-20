#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
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
    int duracao, distancia;
    char unidmedida[MAX_LINE_LEN];
} Infativ;

//contendo os dados dos planos de atividades para cada praticante.Cada linha deve identificar o praticante, data e hora de início e fim
//da atividade, atividade, distância e medida a atingir :

typedef struct {
    int num;
    Data datainicio, datafim;
    Horario horarioinicio, horariofim;
    char nomeativ[MAX_LINE_LEN];
    int distancia;
    char unidmedida[MAX_LINE_LEN];
} Planativ;


int main() {
    setlocale(LC_ALL, "pt_PT.UTF-8");

    FILE* txt1;
    FILE* txt2;
    FILE* txt3;

    int numparti = 0; //numero de participantes
    char linha[MAX_LINE_LEN];

    txt1 = fopen("txt1.txt", "r");

    InfParti parti; //Participante
    InfParti infparti[10];//Array com informação dos participantes

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
    
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    txt2 = fopen("txt2.txt", "r");

    Infativ partiativ; //Participante nas atividades
    Infativ infativ[10];//Array com informação das atividades
    int numativ = 0;

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

    
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    txt3 = fopen("txt3.txt", "r");

    Planativ partplan; //Participante nas atividades
    Planativ planativ[10];//Array com informação das atividades
    int numplanativ = 0;

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

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    int numero, diai, mesi, anoi, diaf, mesf, anof, total = 0;
    char nomativ[50];
    printf("Atividades registadas:\n");
    printf("Marcha\nBTT\nWindsurfing\nNatação\n");
    printf("\nNumero da pessoa:");
    scanf("%d", &numero);
    printf("Nome da atividade:");
    scanf("%s", nomativ);
    printf("Primeira data [d-m-a]:");
    scanf("%d-%d-%d", &diai, &mesi, &anoi);
    printf("Segunda data [d-m-a]:");
    scanf("%d-%d-%d", &diaf, &mesf, &anof);


    for (int c = 0; c < numativ; c++) {

        if(numero == infativ[c].num)
            if ((diai <= infativ[c].data.dia && infativ[c].data.dia <= diaf) && (mesi <= infativ[c].data.mes && infativ[c].data.mes <= mesf) 
                && (anoi <= infativ[c].data.ano && infativ[c].data.ano <= anof) && !(strcmp(nomativ,infativ[c].nomeativ)))
                total++;
   
    }

    printf("Total: %d", total);

    return 0;
}