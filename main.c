#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcoes/TLSE.c"
#include "TABM.c"

// typedef struct TipoJogador{
//     int id, camisa, idade, jogos, gols;
//     char posicao[3], nome[40], data_nasc[40], pais[20], pais_jogando[20], time[40];
// }TJ;

//===================================Printa um TJ===================================
void printJogador(TJ jogador) {
    printf("ID: %d\n", jogador.id);
    printf("Nome: %s\n", jogador.nome);
    printf("Camisa: %d\n", jogador.camisa);
    printf("Idade: %d\n", jogador.idade);
    printf("Jogos: %d\n", jogador.jogos);
    printf("Gols: %d\n", jogador.gols);
    printf("Posição: %s\n", jogador.posicao);
    printf("Data de Nascimento: %s\n", jogador.data_nasc);
    printf("País de Origem: %s\n", jogador.pais);
    printf("País Jogando: %s\n", jogador.pais_jogando);
    printf("Time: %s\n", jogador.time);
}


//===================================Boolean para ver se uma string é pais===================================
int pais(char *nome){
    size_t i = 0;
    while(i < strlen(nome)){
        if(nome[i] == '/')return 0;
        i ++;
    }
    return 1;
} 

//===================================retorna TLSE de quais linhas são paises===================================
TLSE *linhasPais(char *arquivo){
    FILE *fp  = fopen(arquivo, "r");
    if(!fp)exit(1);

    TLSE *linhas = NULL;

    int a = 1, i = 0;
    char leitura[1000];    
    while (1){
        a = fscanf(fp, "%[^\n]\n", leitura);
        if(a!=1)break;
        if(pais(leitura)){
            linhas = TLSE_insere(linhas, i);
        }
        i++;
    }
    fclose(fp);
    return linhas;
}

//===================================Le o arquivo e gera a struct Jogador===================================
void preencherJogador(char *arquivo){
    TLSE *linhas = linhasPais(arquivo);
    FILE *fp  = fopen(arquivo, "r");
    
    TJ jogador;
    char pais[30];
    int a = 1, i = 0;

    while(1){
        if(TLSE_busca(linhas, i)){
            a = fscanf(fp, "%[^\n]\n", pais);
            if(a!=1)break;
            printf("%s\n\n", pais);
        }
        else{
            a = fscanf(fp, "%i/", &jogador.id);
            if(a!=1)break;

            a = fscanf(fp, "%i/", &jogador.camisa);
            if(a!=1)break;

            a = fscanf(fp, "%[^/]/", jogador.posicao);

            a = fscanf(fp, "%[^/]/", jogador.nome);
            if(a!=1)break;

            a = fscanf(fp, "%[^(](aged", jogador.data_nasc);
            if(a!=1)break;

            a = fscanf(fp, "%i)/", &jogador.idade);
            if(a!=1)break;

            a = fscanf(fp, "%i/", &jogador.jogos);
            if(a!=1)break;

            a = fscanf(fp, "%i/", &jogador.gols);
            if(a!=1)break;

            a = fscanf(fp, "%[^/]/", jogador.pais_jogando);
            if(a!=1)break;

            a = fscanf(fp, "%[^\n]\n", jogador.time);
            if(a!=1)break;

            strcpy(jogador.pais, pais);

            //==============================Jogador Lido || Falta inserir==============================//
            printJogador(jogador);
            printf("\n\n");
            //==============================Jogador Lido || Falta inserir==============================//


        }
        i++;
    }

}


int main(void){
    
    TABM *arvore = TABM_Cria(3);
    arvore->folha = 0;
    arvore->nchaves = 1;
    arvore->ids[0] = 10;
    arvore->filhos[0] = 2;
    arvore->filhos[1] = 3;
    escrita("11", arvore);
    TABM *resp = leitura("11");
    printf("%d \n\n", resp->ids[0]);

}