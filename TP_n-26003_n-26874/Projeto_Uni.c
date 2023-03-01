#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_LINE_LEN 400

//Para listar seguidores
typedef struct {
    int num_part[25];
}InfSeg;

typedef struct {
    int num;
    char nome[MAX_LINE_LEN];
    long long numphone;
    InfSeg seguidor;
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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int transtxt1(FILE* txt1, char linha[MAX_LINE_LEN], int numparti, InfParti infparti[25], int numeros[]) {
    //Declaração de variáveis
    InfParti parti; //Participante
    char* token;
    //Caso não seja possivel encontrar o ficheiro, irá aparecer uma mensagem de erro.
    if (txt1 == NULL) {
        printf("Erro ao abrir ficheiro txt1");
        return 0;
    }
    //Caso seja encontrado, enquanto fgets conseguir obter alguma informação de cada linha, irá ser atribuida conforme o formato 
    //no sscanf para cada uma das variáveis de seguida colocadas. E é incrementado o numparti.
    //Também é usado strtok que escolhe qual é o delimitador para cada informação obtida. Por exemplo no primeiro strtok, irá ser apenas o num
    //Participante.
    else {
        while (fgets(linha, MAX_LINE_LEN, txt1) != NULL) {
            sscanf(linha, "%d;%[^;];%lld;%d", &parti.num, parti.nome, &parti.numphone, &parti.idade);

            //The C library function char *strtok(char *str, const char *delim) breaks string str into a series of tokens using the delimiter delim.
            //Para andar até o quinto ";" que é o inicio dos seguidores
            token = strtok(linha, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");

            for (int c = 0; token != NULL; c++) {
                parti.seguidor.num_part[c] = atoi(token);
                //The C library function int atoi(const char *str) converts the string argument str to an integer (type int).
                //Necessario para não copiar \n
                token = strtok(NULL, ";");
            }
            numeros[numparti] = parti.num;
            infparti[numparti++] = parti;
            //Coloca todos os valores da array para 0
            memset(parti.seguidor.num_part, 0, sizeof(parti.seguidor.num_part));
        }

        fclose(txt1);
    }

    return numparti;
}

int transtxt2(FILE* txt2, char linha[MAX_LINE_LEN], int numativ, Infativ infativ[25]) {

    Infativ partiativ; //Participante nas atividades
    //Caso não seja possivel encontrar o ficheiro, irá aparecer uma mensagem de erro.
    if (txt2 == NULL) {
        printf("Erro ao abrir ficheiro txt2");
        return 0;
    }
    //Caso seja encontrado, enquanto fgets conseguir obter alguma informação de cada linha, irá ser atribuida conforme o formato 
    //no sscanf para cada uma das variáveis de seguida colocadas. E é incrementado o numativ.
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
    //Declaração de variáveis
    Planativ partplan; //Participante nas atividades

    //Caso não seja possivel encontrar o ficheiro, irá aparecer uma mensagem de erro.
    //Caso seja encontrado, enquanto fgets conseguir obter alguma informação de cada linha, irá ser atribuida conforme o formato 
    //no sscanf para cada uma das variáveis de seguida colocadas. E é incrementado o numplanativ.
    if (txt3 == NULL) {
        printf("Erro ao abrir ficheiro txt3");
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
void orgatxt1(InfParti infparti[25], int numparti) {
    char b = 1;
    InfParti k[25];

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

void orgatxt2(Infativ infativ[25], int numativ) {
    char b = 1;
    Infativ k[25];

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

void orgatxt3(Planativ planativ[25], int numplanativ) {
    char b = 1;
    Planativ k[25];

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
    //Apresentação do número de praticantes que realizaram uma determinada atividade, num 
    //determinado período, introduzidos pelo utilizador

    //Declaração de variáveis
    int diai, mesi, anoi, diaf, mesf, anof, verificado = 0, total = 0;
    char nomativ[50];
    //É pedido ao utilizador o numero de participante, o nome da atividade, a primeira data e a segunda data para
    //verificar durante aquele período.

    printf("Nome da atividade:");
    scanf("%s", nomativ);
    printf("Primeira data [d-m-a]:");
    scanf("%d-%d-%d", &diai, &mesi, &anoi);
    printf("Segunda data [d-m-a]:");
    scanf("%d-%d-%d", &diaf, &mesf, &anof);

    //É criado um for loop, em que se o numero inserido for correspondente ao numero de utilizador que foi lido da folha a partir da função transtxt2
    //E o resultado da comparação de strings entre o que foi inserido e o que vou lido.
    //De seguida tem um algoritmo para a verificação das datas, para saber quais termos avaliar ou não.
    for (int i = 0; i < numativ; i++, verificado = 0) {
        if (!(strcmp(nomativ, infativ[i].nomeativ))) {
            if (anoi < infativ[i].data.ano && anof > infativ[i].data.ano) {
                verificado = 1;
            }
            else {

                if (anoi == infativ[i].data.ano && anof > infativ[i].data.ano) {

                    if (mesi < infativ[i].data.mes) {
                        verificado = 1;
                    }

                    if (mesi == infativ[i].data.mes) {
                        if (diai <= infativ[i].data.dia) {
                            verificado = 1;
                        }
                    }
                }

                if (!(verificado)) {
                    if (anoi < infativ[i].data.ano && anof == infativ[i].data.ano) {

                        if (mesf > infativ[i].data.mes) {
                            verificado = 1;
                        }

                        if (mesf == infativ[i].data.mes) {
                            if (diaf >= infativ[i].data.dia) {
                                verificado = 1;
                            }
                        }
                    }
                }
                if (!(verificado)) {
                    if (anoi == infativ[i].data.ano && anof == infativ[i].data.ano) {

                        if (mesi < infativ[i].data.mes && mesf > infativ[i].data.mes) {
                            verificado = 1;
                        }
                        if (mesi <= infativ[i].data.mes && mesf > infativ[i].data.mes) {
                            if (diai <= infativ[i].data.dia) {
                                verificado = 1;
                            }
                        }
                        if (mesi < infativ[i].data.mes && mesf >= infativ[i].data.mes) {
                            if (diaf >= infativ[i].data.dia) {
                                verificado = 1;
                            }
                        }
                    }
                }

                if (!(verificado)) {
                    if (anoi == infativ[i].data.ano && anof == infativ[i].data.ano) {

                        if (mesi == infativ[i].data.mes && mesf == infativ[i].data.mes) {
                            if (diai <= infativ[i].data.dia && diaf >= infativ[i].data.dia) {
                                verificado = 1;
                            }
                        }
                    }
                }

                if (verificado == 1) {
                    total++;
                }
            }
        }
    }

    printf("Total: %d\n", total);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ex5(Infativ infativ[], int n)
{
    //Listagem dos praticantes, ordenada por ordem decrescente do número de praticante, que realizaram 
    //alguma atividade desportiva num determinado período introduzido pelo utilizador.

    //Declaração de variáveis
    int  diai, mesi, anoi, diaf, mesf, anof, verificado;
    //É pedido ao utilizador uma data inicial e final.
    printf("Data de inicio: dd-mm-aaaa\n");
    scanf("%d-%d-%d", &diai, &mesi, &anoi);
    printf("Data final: dd-mm-aaaa\n");
    scanf("%d-%d-%d", &diaf, &mesf, &anof);

    printf("\n");
    //Se a data que foi lida para a estrutura infativ estiver entre as datas em cima inseridas iremos ter verificado = 1.
    for (int i = n - 1, verificado = 0; i > 0; i--, verificado = 0) {
        if (anoi < infativ[i].data.ano && anof > infativ[i].data.ano) {
            verificado = 1;
        }
        else {

            if (anoi == infativ[i].data.ano && anof > infativ[i].data.ano) {

                if (mesi < infativ[i].data.mes) {
                    verificado = 1;
                }

                if (mesi == infativ[i].data.mes) {
                    if (diai <= infativ[i].data.dia) {
                        verificado = 1;
                    }
                }
            }

            if (!(verificado)) {
                if (anoi < infativ[i].data.ano && anof == infativ[i].data.ano) {

                    if (mesf > infativ[i].data.mes) {
                        verificado = 1;
                    }

                    if (mesf == infativ[i].data.mes) {
                        if (diaf >= infativ[i].data.dia) {
                            verificado = 1;
                        }
                    }
                }
            }

            if (!(verificado)) {
                if (anoi == infativ[i].data.ano && anof == infativ[i].data.ano) {

                    if (mesi < infativ[i].data.mes && mesf > infativ[i].data.mes) {
                        verificado = 1;
                    }
                    if (mesi <= infativ[i].data.mes && mesf > infativ[i].data.mes) {
                        if (diai <= infativ[i].data.dia) {
                            verificado = 1;
                        }
                    }
                    if (mesi < infativ[i].data.mes && mesf >= infativ[i].data.mes) {
                        if (diaf >= infativ[i].data.dia) {
                            verificado = 1;
                        }
                    }
                }
            }

            if (!(verificado)) {
                if (anoi == infativ[i].data.ano && anof == infativ[i].data.ano) {

                    if (mesi == infativ[i].data.mes && mesf == infativ[i].data.mes) {
                        if (diai <= infativ[i].data.dia && diaf >= infativ[i].data.dia) {
                            verificado = 1;
                        }
                    }
                }
            }
        }
        //Se verificado estiver com o valor de 1 irá dar print do utilizador atual e a sua data atividade etc. 
        if (verificado == 1){
            printf("%d;%d-%d-%d;%d:%d;%s;%d;%d;%s\n", infativ[i].num, infativ[i].data.dia, infativ[i].data.mes, infativ[i].data.ano, infativ[i].inicio.hora, infativ[i].inicio.minutos,
                infativ[i].nomeativ, infativ[i].duracao, infativ[i].dist, infativ[i].unidmedida);

        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ex6(Planativ planativ[], int n)
{
    // Apresentação do plano de atividades de determinado tipo (Corrida, Natação, BTT, outra), para um 
    // determinado período e praticante introduzidos pelo utilizador

    //Declaração de variáveis
    int dia_inicio, mes_inicio, ano_inicio, dia_fim, mes_fim, ano_fim, numero_part, verificado;
    char atividade[20];
    //É mostrado ao utilizador o número de atividades existentes a partir de um for loop, que nos consegue apenas dar print de cada uma das atividades
    //Onde são criados 2 for loop, no primeiro a variavel verificado fica = 0, e de seguida é criado outro for loop. Dentro desse for loop se
    //O valor de i for diferente de j e o nome da atividade no for [i] for igual ao for [j] irá ser colocado o verificado como 1 ou seja irá demonstrar que já foi dado print
    //Desse valor. Resumidamente o algoritmo é começar na posição em que o i está e ir verificando para trás se encontra algum nome da atividade igual, caso encontre irá
    //Colocar o verificado = 1 e não acontece nada, caso não encontre o verificado é mantido a 0 e aí imprime aquele nome de atividade.
    printf("Tem as seguintes atividades:\n");
    for (int i = 0; i < n; i++)
    {
        verificado = 0;
        for (int j = i; j >= 0; j--)
            if (i != j && strcmp(planativ[i].nomeativ, planativ[j].nomeativ) == 0) {
                verificado = 1;
            }
        if (verificado == 0)
        {
            printf("%s\n", planativ[i].nomeativ);
        }
    }

    //É pedido ao utilizador para introduzir uma atividade, num participante, data inicial e data final.
    printf("Introduza uma atividade:\n");
    scanf("%s", atividade);
    printf("Introduza o numero de participante\n");
    scanf("%d", &numero_part);
    printf("Data inicial dd:mm:aa\n");
    scanf("%d-%d-%d", &dia_inicio, &mes_inicio, &ano_inicio);
    printf("Data final dd:mm:aa\n");
    scanf("%d-%d-%d", &dia_fim, &mes_fim, &ano_fim);
    //Pequeno algoritmo para verificação se o numero inserido e atividade existem na estrutura de plano de atividades.
    //De seguida apenas é verificada as datas que foram inseridas e se existir alguma data dentro das mesmas ela irá dar print do que é pedido.
    for (int i = 0; i < n; i++)
    {
        if (numero_part == planativ[i].num && strcmp(atividade, planativ[i].nomeativ) == 0)
        {
            /*if ((dia_inicio <= planativ[i].datai.dia && dia_fim >= planativ[i].dataf.dia) && (mes_inicio <= planativ[i].datai.mes && mes_fim >= planativ[i].dataf.mes) && (ano_inicio <= planativ[i].datai.ano && ano_fim >= planativ[i].dataf.ano))
            {
                printf("O participante %d tem atividade de %s do dia %d:%d:%d ate ao dia %d:%d:%d. \n", planativ[i].num, planativ[i].nomeativ, planativ[i].datai.dia, planativ[i].datai.mes, planativ[i].datai.ano, planativ[i].dataf.dia, planativ[i].dataf.mes, planativ[i].dataf.ano);
                printf("Durante esses dias, a atividade ira decorrer das %d:%d ate as %d:%d.\n", planativ[i].horarioi.hora, planativ[i].horarioi.minutos, planativ[i].horariof.hora, planativ[i].horariof.minutos);
                printf("Onde tera de completar %d %s.\n", planativ[i].dist, planativ[i].unidmedida);
            }*/
            if (ano_inicio < planativ[i].datai.ano && ano_fim > planativ[i].dataf.ano) {
                verificado = 1;
            }
            else{
                if (ano_inicio == planativ[i].datai.ano && ano_fim < planativ[i].dataf.ano) {

                    if (mes_inicio < planativ[i].datai.mes) {
                        verificado = 1;
                    }
                    if (mes_inicio == planativ[i].datai.mes) {
                        if (dia_inicio <= planativ[i].datai.dia) {
                            verificado = 1;
                        }
                    }
                }

                if(!(verificado)){
                    if (ano_inicio == planativ[i].datai.ano && ano_fim == planativ[i].dataf.ano) {

                        if (mes_fim > planativ[i].dataf.mes) {
                            verificado = 1;
                        }
                        if (mes_fim == planativ[i].dataf.mes) {
                            if (dia_fim >= planativ[i].datai.dia) {
                                verificado = 1;
                            }
                        }
                    }
                }

                if (!(verificado)) {
                    if (ano_inicio == planativ[i].datai.ano && ano_fim == planativ[i].datai.ano) {

                        if (mes_inicio == planativ[i].datai.mes && mes_fim == planativ[i].datai.mes) {
                            if (dia_inicio <= planativ[i].datai.dia && dia_fim >= planativ[i].datai.dia) {
                                verificado = 1;
                            }
                        }
                    }
                }
            }
            //Se verificado estiver com o valor de 1 irá dar print do utilizador atual e a sua data atividade etc. 
            if (verificado == 1)
            {
                printf("O participante %d tem atividade de %s do dia %d:%d:%d ate ao dia %d:%d:%d. \n", planativ[i].num, planativ[i].nomeativ, planativ[i].datai.dia, planativ[i].datai.mes, planativ[i].datai.ano, planativ[i].dataf.dia, planativ[i].dataf.mes, planativ[i].dataf.ano);
                printf("Durante esses dias, a atividade ira decorrer das %d:%d ate as %d:%d.\n", planativ[i].horarioi.hora, planativ[i].horarioi.minutos, planativ[i].horariof.hora, planativ[i].horariof.minutos);
                printf("Onde tera de completar %d %s.\n", planativ[i].dist, planativ[i].unidmedida);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ex7(Infativ infativ[], int n)
{
    //Cálculo dos tempos totais e médias dos tempos por atividade em que cada praticante esteve 
    //envolvido num determinado período introduzido pelo utilizador.

    //Declaração de variáveis.
    char atividade[20], aux_string[20];
    int num_part, resultado_total = 0, media_total = 0, vezes = 0, diai, mesi, anoi, diaf, mesf, anof, total_mes, total_dia, verificado = 0;

    //O algoritmo abaixo é começar na posição em que o i está e ir verificando para trás se encontra algum nome da atividade igual, caso encontre irá
    //Colocar o verificado = 1 e não acontece nada, caso não encontre o verificado é mantido a 0 e aí imprime aquele nome de atividade.
    printf("Atividades existentes:\n");
    for (int i = 0; i < n; i++)
    {
        verificado = 0;
        for (int j = i; j >= 0; j--)
            if (i != j && strcmp(infativ[i].nomeativ, infativ[j].nomeativ) == 0) {
                verificado = 1;
            }
        if (verificado == 0)
        {
            printf("%s\n", infativ[i].nomeativ);
        }
    }
    //Colocado o verificado = 0, para ser usado novamente.
    verificado = 0;
    //É pedido ao utilizador para introduzir uma atividade, num participante, data inicial e data final.
    //É pedido ao utilizador para introduzir uma atividade, num participante, data inicial e data final.
    printf("Introduza uma atividade:\n");
    scanf("%s", atividade);
    printf("Introduza um n de participante:\n");
    scanf("%d", &num_part);
    printf("Data inicial dd:mm:aa\n");
    scanf("%d-%d-%d", &diai, &mesi, &anoi);
    printf("Data final dd:mm:aa\n");
    scanf("%d-%d-%d", &diaf, &mesf, &anof);
    int b = 0;
    //For loop para verificar se a data inserida está dentro das existentes.
    for (int i = 0; i < n; i++) {

        if (num_part == infativ[i].num && !(strcmp(atividade, infativ[i].nomeativ))) {

            if (anoi < infativ[i].data.ano && anof > infativ[i].data.ano) {
                verificado = 1;
            }
            else {

                if (anoi == infativ[i].data.ano && anof > infativ[i].data.ano) {

                    if (mesi < infativ[i].data.mes) {
                        verificado = 1;
                    }

                    if (mesi == infativ[i].data.mes) {
                        if (diai <= infativ[i].data.dia) {
                            verificado = 1;
                        }
                    }
                }

                if (!(verificado)) {
                    if (anoi < infativ[i].data.ano && anof == infativ[i].data.ano) {

                        if (mesf > infativ[i].data.mes) {
                            verificado = 1;
                        }

                        if (mesf == infativ[i].data.mes) {
                            if (diaf >= infativ[i].data.dia) {
                                verificado = 1;
                            }
                        }
                    }
                }
                if (!(verificado)) {
                    if (anoi == infativ[i].data.ano && anof == infativ[i].data.ano) {

                        if (mesi < infativ[i].data.mes && mesf > infativ[i].data.mes) {
                            verificado = 1;
                        }
                        if (mesi <= infativ[i].data.mes && mesf > infativ[i].data.mes) {
                            if (diai <= infativ[i].data.dia) {
                                verificado = 1;
                            }
                        }
                        if (mesi < infativ[i].data.mes && mesf >= infativ[i].data.mes) {
                            if (diaf >= infativ[i].data.dia) {
                                verificado = 1;
                            }
                        }
                    }
                }

                if (!(verificado)) {
                    if (anoi == infativ[i].data.ano && anof == infativ[i].data.ano) {

                        if (mesi == infativ[i].data.mes && mesf == infativ[i].data.mes) {
                            if (diai <= infativ[i].data.dia && diaf >= infativ[i].data.dia) {
                                verificado = 1;
                            }
                        }
                    }
                }
            }
        }

        if (verificado == 1) {
            vezes++;
            resultado_total += infativ[i].duracao;
            verificado = 0;
        }
    }
    //Caso "vezes" não incremente quer dizer que não foi verificado nenhuma data dentro da inserida.
    if (vezes == 0) {
        printf("Não foi inserida uma data existente no registo de atividades.\n");
    }
    //Caso contrário é calculada a média dividindo o tempo total pelo numero de vezes que foi exercida tal atividade.
    else {
        media_total = resultado_total / vezes;
        printf("O participante %d praticou %s durante um tempo total de %d minutos, com uma media de %d minutos.\n", num_part, atividade, resultado_total, media_total);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ex8(int numparti, int numativ, int numplanativ, InfParti infparti[], Infativ infativ[], Planativ planativ[]) {
    //: Número de Praticante, Nome, Atividade planeada, Medida (km, metros, 
    //segundos, outra) da unidade e o Valor dessa medida

    //Gerar a tabela das atividades planeadas e realizadas para todos os praticantes, onde deve constar a 
    //seguinte informação : Número de Praticante, Nome, Atividade planeada, Medida(km, metros,
    //segundos, outra) da unidade e o Valor dessa medida, Atividade realizada, Data de Início, Data de Fim,
    //Medida(km, metros, segundos, outra) da unidade e o Valor dessa medida

    //Declaração de variáveis
    int z = 0;
    //Criado um for loop, que irá dar print do numero na posição infarti[c].num e de seguida o nome em infparti[c].nome
    //Se no proximo loop o numero de infparti[c].num for diferente do planativ[d].num o for loop para
    //Caso sejam iguais é listado o nome da atividade, unidade medida etc...
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
void adicionar_seguidores(InfParti infparti[], int n)
{
    //Acrescentar uma funcionalidade para registar que um praticante segue a atividade de outros 
    //praticantes.Apresente uma listagem de todos os praticantes e seus seguidores.

    //Declaração de variáveis
    int utl, b = 1, i = 0, seg = 0, utl_seguir, aux, z = 0, verificado = 0, choice1, choice2 = 1, booleano = 1;


    //Criado while loop conforme a variável choice2, que vai ser utilizada para inserir novos seguidores para utilizadores diferentes.
    //Começamos por pedir um utilizador para adicionar seguidores. É apresentado uma lista dos participantes existentes menos o inserido.
    //Caso o utilizador insira um numero de participante que já está lido como seguidor de outro participante booleano = 0 e é dado uma mensagem
    //A dizer erro. De seguida é perguntado se quer inserir mais seguidores para o participante escolhido.
    //No final do while loop é perguntado se quer adicionar mais seguidores a outro participante.
    //Depois é feita a listagem de todos os participantes e os seus seguidores, no caso de não existir seguidores
    //É apresentado que o participante x não tem seguidores.
    while (choice2) {
        printf("Insira um utilizador para seguir: ");
        scanf("%d", &utl);
        aux = utl;
        utl -= 1;
        do {
            z = 0;
            printf("Insira um n_utilizador para seguir o utilizador %d:\n", aux);
            for (i = 0; i < n; i++)
            {
                if (aux == infparti[i].num)
                    continue;
                printf("%d ", infparti[i].num);
            }
            printf("\nA sua escolha: ");
            scanf("%d", &utl_seguir);
            for (int c = 0; infparti[utl].seguidor.num_part[c] > 0; c++)
                z++;
            booleano = 1;
            for (int c = 0; c < z; c++) {
                if (utl_seguir == infparti[utl].seguidor.num_part[c]) {
                    booleano = 0;
                    break;
                }
            }
            if (booleano && 0 < utl_seguir && utl_seguir <= n && utl_seguir != aux) {
                printf("Utilizador %d adicionado com sucesso!\n\n", utl_seguir);

                infparti[utl].seguidor.num_part[z] = utl_seguir;
            }
            else {
                printf("Erro! Digitou um numero fora do esperado ou repetido.\n\n");
            }

            printf("Deseja introduzir outro seguidor para o utilizador %d ? (1-Sim/0-Nao)\n", aux);
            printf("A sua escolha: ");
            scanf("%d", &choice1);
            seg++;
        } while (choice1);
        printf("Deseja adicionar seguidores a outros participantes? (1-Sim/0-Nao) ");
        scanf("%d", &choice2);
    }
    b = 0;
    printf("Listagem dos seguidores inseridos:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (infparti[i].seguidor.num_part[j] == 0 || infparti[i].seguidor.num_part[j] < 0)
                break;
            if (j == 0)
                printf("O utilizador P%d e seguido por:\n", infparti[i].num);
            if (infparti[i].seguidor.num_part[j] > 0) {
                printf("P%d\n", infparti[i].seguidor.num_part[j]);
                verificado = 1;
            }
        }
        if (verificado == 0) {
            printf("O utilizador P%d nao tem seguidores\n\n", infparti[i].num);
        }
        printf("\n");
        verificado = 0;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ex10(InfParti infparti[25], int numparti, Infativ infativ[10], int numativ) {
    //Apresentar uma listagem por atividade com o praticante com o maior tempo de prática dessa 
    //atividade, e o respetivo tempo, de entre os seguidores de um determinado praticante definido pelo utilizador.

    //Declaração de variáveis
    int num, i = 0, b, maior = 0;
    char nomativ[20][20];
    int nmaior[20], nparti[20];

    //Pedido ao utilizador para inserir um participante para ver o tempo dos seguidores.
    printf("Qual participante quer ver o tempo dos seguidores? ");
    scanf("%d", &num);

    //for loop que verifica se o participante inserido tem seguidores. Caso tenha, fica b = 1 e é copiada a atividade para a array bidimensional acima criada nomativ
    //Caso seja diferente, fica b = 0 e não é copiada. 
    for (int c = 0; c < numativ; c++) {
        b = 0;
        for (int d = 0; infparti[num - 1].seguidor.num_part[d] > 0; d++) {
            if (infativ[c].num == infparti[num - 1].seguidor.num_part[d]) {
                b = 1;
                break;
            }
        }

        for (int d = 0; d < i; d++)
            if (!(strcmp(nomativ[d], infativ[c].nomeativ)))
                b = 0;

        if (b) {
            strcpy(nomativ[i], infativ[c].nomeativ);
            i++;
        }
    }
    //for loop que irá verificar qual é o seguidor com maior tempo em determinada atividade, dependendo do praticante inserido.
    //Se o existir um seguidor no numero inserido acima, verificamos a condição de os numeros serem iguais e caso o sejam b fica = 1.
    //Caso b seja 1, se a comparação entre o nome das atividades não for igual e de seguida a duração for maior do que a variável maior
    //maior vai ficar = à duração, nmaior fica = maior e o nparti fica igual ao numero que está gravado na estrutura infparti.num
    for (int c = 0; c < i; c++) {
        maior = 0;
        b = 0;
        for (int d = 0; d < numativ; d++) {

            for (int e = 0; infparti[num - 1].seguidor.num_part[e] > 0; e++)
                if (infativ[d].num == infparti[num - 1].seguidor.num_part[e]) {
                    b = 1;
                    break;
                }
            if (b) {
                if (!(strcmp(infativ[d].nomeativ, nomativ[c])))
                    if (maior < infativ[d].duracao) {
                        maior = infativ[d].duracao;
                        nmaior[c] = maior;
                        nparti[c] = infativ[d].num;
                    }

            }
        }
    }
    //Aqui é dado print de toda a informação obtida acima.
    for (int c = 0; c < i; c++) {
        printf("%s\n", nomativ[c]);
        printf("Participante:%d     Tempo:%d\n\n", nparti[c], nmaior[c]);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ex11(InfParti infparti[25], int numparti, Infativ infativ[25], int numativ) {
    //Apresentar uma listagem por atividade com o praticante com o maior tempo de prática dessa 
    //Atividade, e o respetivo tempo, de entre os praticantes seguidos por um determinado praticante
    //Definido pelo utilizador.

    int num, inum = 0, inom = 0, b, maior = 0;
    char nomativ[10][20];
    int numseg[10], nmaior[10], nparti[10];

    printf("Qual participante quer ver o tempo dos que segue? ");
    scanf("%d", &num);

    for (int c = 0; c < numparti; c++) {
        b = 0;
        for (int d = 0; infparti[c].seguidor.num_part[d] > 0; d++)
            if (infparti[c].seguidor.num_part[d] == num) {
                b = 1;
                break;
            }
        if (b) {
            numseg[inum] = infparti[c].num;
            inum++;
        }
    }

    for (int c = 0; c < numativ; c++) {
        b = 0;
        for (int d = 0; d < inum; d++) {
            if (infativ[c].num == numseg[d]) {
                b = 1;
                break;
            }
        }

        for (int d = 0; d < inom; d++)
            if (!(strcmp(nomativ[d], infativ[c].nomeativ)))
                b = 0;


        if (b) {
            strcpy(nomativ[inom], infativ[c].nomeativ);
            inom++;
        }
    }

    for (int c = 0; c < inom; c++) {
        maior = 0;

        for (int d = 0; d < numativ; d++) {
            b = 0;
            for (int e = 0; numseg[e] > 0; e++)
                if (infativ[d].num == numseg[e]) {
                    b = 1;
                    break;
                }

            if (b) {
                if (!(strcmp(infativ[d].nomeativ, nomativ[c])))
                    if (maior < infativ[d].duracao) {
                        maior = infativ[d].duracao;
                        nmaior[c] = maior;
                        nparti[c] = infativ[d].num;
                    }

            }
        }
    }

    for (int c = 0; c < inom; c++) {
        printf("%s\n", nomativ[c]);
        printf("Participante:%d     Tempo:%d\n\n", nparti[c], nmaior[c]);
    }
}

void escrtxt1(FILE* txt1, InfParti infparti[25], int numparti) {
    //Caso não seja possível abrir o ficheiro irá mostrar uma mensagem de erro.
    //De seguida enquanto numparti, for maior que c, irá copiar toda a informação dos praticante para o ficheiro txt1.
    int d = 0;

    if (txt1 == NULL) {
        printf("Erro ao abrir ficheiro txt1");
        return 0;
    }
    else {
        for (int c = 0; c < numparti; c++) {
            // fscanf reads from the named input stream. sscanf reads from the character string s.
            // fscanf(): fscanf() reads formatted data from file and stores it into variables.
            // sscanf(): sscanf() is used to read formatted input from the string.
            fprintf(txt1, "%d;%s;%lld;%d", infparti[c].num, infparti[c].nome, infparti[c].numphone, infparti[c].idade);
         
            while (infparti[c].seguidor.num_part[d] > 0) {
                fprintf(txt1, ";%d", infparti[c].seguidor.num_part[d++]);
            }
            fprintf(txt1, "\n");
            d = 0;
        }
        fclose(txt1);
    }
}

void escrtxt2(FILE* txt2, int numativ, Infativ infativ[25]) {
    //Caso não seja possível abrir o ficheiro irá mostrar uma mensagem de erro.
    //De seguida enquanto numativ, for maior que c, irá ser escrito todas as atividades realizadas para o ficheiro txt2.
    if (txt2 == NULL) {
        printf("Erro ao abrir ficheiro txt2");
        return 0;
    }
    else {

        for (int c = 0; c < numativ; c++) {
            fprintf(txt2, "%d;%d-%d-%d;%d:%d;%s;%d;%d;%s\n", infativ[c].num, infativ[c].data.dia, infativ[c].data.mes, infativ[c].data.ano, infativ[c].inicio.hora, infativ[c].inicio.minutos,
                infativ[c].nomeativ, infativ[c].duracao, infativ[c].dist, infativ[c].unidmedida);
        }

        fclose(txt2);
    }
}

void escrtxt3(FILE* txt3, int numplanativ, Planativ planativ[25]) {
    //Caso não seja possível abrir o ficheiro irá mostrar uma mensagem de erro.
    //De seguida enquanto numplanativ, for maior que c, irá ser escrito todas as atividades planeadas para o ficheiro txt3.
    if (txt3 == NULL) {
        printf("Erro ao abrir ficheiro txt3");
        return 0;
    }
    else {
        for (int c = 0; c < numplanativ; c++) {

            fprintf(txt3, "%d;%d-%d-%d;%dh%d;%d-%d-%d;%dh%d;%s;%d;%s\n", planativ[c].num, planativ[c].datai.dia, planativ[c].datai.mes, planativ[c].datai.ano,
                planativ[c].horarioi.hora, planativ[c].horarioi.minutos, planativ[c].dataf.dia, planativ[c].dataf.mes, planativ[c].dataf.ano,
                planativ[c].horariof.hora, planativ[c].horariof.minutos, planativ[c].nomeativ, planativ[c].dist, planativ[c].unidmedida);
        }
        fclose(txt3);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() {
    setlocale(LC_ALL, "");

    FILE* txt1;
    FILE* txt2;
    FILE* txt3;
    int op;
    char linha[MAX_LINE_LEN];

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    txt1 = fopen("txt1.txt", "r");
    InfParti infparti[25];//Array com informação dos participantes
    int numeros[50];//Lista dos Numeros existentes
    int numparti = 0; //numero de participantes
    numparti = transtxt1(txt1, linha, numparti, infparti, numeros);
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    txt2 = fopen("txt2.txt", "r");
    Infativ infativ[25];//Array com informação das atividades
    int numativ = 0, nativ = 0;
    numativ = transtxt2(txt2, linha, numativ, infativ);
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    txt3 = fopen("txt3.txt", "r");
    Planativ planativ[25];//Array com informação das atividades
    int numplanativ = 0;
    numplanativ = transtxt3(txt3, linha, numplanativ, planativ);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    orgatxt1(infparti, numparti);

    orgatxt2(infativ, numativ);

    orgatxt3(planativ, numplanativ);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //Do while loop para criar um menu.
    do
    {
        printf("Que deseja fazer?\n");
        printf("1- Apresentacao do numero de praticantes que realizaram uma determinada atividade, numa determinada data.\n");
        printf("2- Listagem dos praticantes, por ordem decrescente que realizaram uma atividade num determinado periodo.\n");
        printf("3- Apresentacao do plano de atividades de determinado tipo.\n");
        printf("4- Medias de tempo.\n");
        printf("5- Tabela de atividades realizadas e planeadas dos praticantes.\n");
        printf("6- Adicionar seguidores.\n");
        printf("7- Apresentar listagem por atividade com o praticante com maior pratica dessa atividade, de entre os seus seguidores.\n");
        printf("8- Apresentar listagem por atividade com o seguidor com maior pratica dessa atividade, de entre os seus praticantes.\n");
        printf("0- Parar\n");
        printf("A sua escolha:");
        scanf("%d", &op);
        system("cls");
        switch (op)
        {
        case 0:
            break;
        case 1:
            ex4(infativ, numativ);
            break;
        case 2:
            ex5(infativ, numativ);
            break;
        case 3:
            ex6(planativ, numplanativ);
            break;
        case 4:
            ex7(infativ, numativ);
            break;
        case 5:
            ex8(numparti, numativ, numplanativ, infparti, infativ, planativ);
            break;
        case 6:
            adicionar_seguidores(infparti, numparti);
            break;
        case 7:
            ex10(infparti, numparti, infativ, numativ);
            break;
        case 8:
            ex11(infparti, numparti, infativ, numativ);
            break;
        default:
            printf("Insira um numero entre 1-8\n");
            break;
        }
    } while (op != 0);

    txt1 = fopen("txt1.txt", "w");
    escrtxt1(txt1, infparti, numparti);

    txt2 = fopen("txt2.txt", "w");
    escrtxt2(txt2, numativ, infativ);

    txt3 = fopen("txt3.txt", "w");
    escrtxt3(txt3, numplanativ, planativ);

    return 0;
}