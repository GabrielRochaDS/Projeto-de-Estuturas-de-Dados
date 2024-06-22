#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 1/1/GK/Manuel Neuer/27 March 1986 (aged 38)/118/0/Germany/Bayern Munich



typedef struct TipoJogador{
    int id, camisa, idade, jogos, gols;
    char *posicao, *nome, *data_nasc, *pais, *pais_jogando, *time;
}TJ;

int pais(char *nome){
    size_t i = 0;
    while(i < strlen(nome)){
        if(nome[i] == '/')return 0;
        i ++;
    }
    return 1;
} 

TJ *preencherJogador(const char *string) {
    TJ *jogador = (TJ *)malloc(sizeof(TJ));
    int i = 0;
    int atual = 0;
    char buffer[100];

    // id
    while (string[atual] != '/' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->id = atoi(buffer);
    atual++;
    i = 0;

    // camisa
    while (string[atual] != '/' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->camisa = atoi(buffer);
    atual++;
    i = 0;

    // posicao
    while (string[atual] != '/' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->posicao = strdup(buffer);
    atual++;
    i = 0;

    // nome
    while (string[atual] != '/' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->nome = strdup(buffer);
    atual++;
    i = 0;

    // data_nasc
    while (string[atual] != '(' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->data_nasc = strdup(buffer);
    atual++;
    i = 0;

    while (string[atual] != ' ' && string[atual] != '\0')atual++;

    // idade
    while (string[atual] != ')' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->idade = atoi(strtok(buffer, " "));
    atual=+2;
    i = 0;

    // jogos
    while (string[atual] != '/' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->jogos = atoi(buffer);
    atual++;
    i = 0;

    // gols
    while (string[atual] != '/' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->gols = atoi(buffer);
    atual++;
    i = 0;

    // pais
    jogador->pais = "abuble";

    // pais_jogando
    while (string[atual] != '/' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->pais_jogando = strdup(buffer);
    atual++;
    i = 0;

    // time
    while (string[atual] != '/' && string[atual] != '\0') {
        buffer[i++] = string[atual++];
    }
    buffer[i] = '\0';
    jogador->time = strdup(buffer);

    return jogador;
}

int main(void){
    FILE *fp  = fopen("EURO.txt", "r");
    int a=1;
    char leitura[1000];
    int i=0;    
    while (1 && i<10){
        a = fscanf(fp, "%[^\n]\n", leitura);
        if(a!=1)break;

        if(!pais(leitura)){
            TJ *jogador = preencherJogador(leitura);
                printf("ID: %d\n", jogador->id);
                printf("Camisa: %d\n", jogador->camisa);
                printf("Posição: %s\n", jogador->posicao);
                printf("Nome: %s\n", jogador->nome);
                printf("Data de Nascimento: %s\n", jogador->data_nasc);
                printf("Idade: %d\n", jogador->idade);
                printf("Jogos: %d\n", jogador->jogos);
                printf("Gols: %d\n", jogador->gols);
                printf("País: %s\n", jogador->pais);
                printf("País Jogando: %s\n", jogador->pais_jogando);
                printf("Time: %s\n", jogador->time);
                printf("\n\n");
        }
        i++;
     }
    fclose(fp);
    return 0;
}