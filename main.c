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
void printJogador(TJ *jogador) {
    printf("ID: %d\n", jogador->id);
    printf("Nome: %s\n", jogador->nome);
    printf("Camisa: %d\n", jogador->camisa);
    printf("Idade: %d\n", jogador->idade);
    printf("Jogos: %d\n", jogador->jogos);
    printf("Gols: %d\n", jogador->gols);
    printf("Posição: %s\n", jogador->posicao);
    printf("Data de Nascimento: %s\n", jogador->data_nasc);
    printf("País de Origem: %s\n", jogador->pais);
    printf("País Jogando: %s\n", jogador->pais_jogando);
    printf("Time: %s\n", jogador->time);
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
void preencherJogador(char *arquivo, char *raiz, int t){
    TLSE *linhas = linhasPais(arquivo);
    FILE *fp  = fopen(arquivo, "r");
    
    TJ *jogador_alocado = (TJ *) malloc (sizeof(TJ));
    TJ jogador;
    char pais[30];
    int a = 1, i = 0;

    while(1 && i < 3){
        if(TLSE_busca(linhas, i)){
            a = fscanf(fp, "%[^\n]\n", pais);
            if(a!=1)break;
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

            jogador_alocado->id = jogador.id;
            jogador_alocado->camisa = jogador.camisa;
            strcpy(jogador_alocado->posicao, jogador.posicao);
            strcpy(jogador_alocado->nome , jogador.nome);
            strcpy(jogador_alocado->data_nasc, jogador.data_nasc);
            jogador_alocado->idade = jogador.idade;
            jogador_alocado->jogos = jogador.jogos;
            jogador_alocado->gols = jogador.gols;
            strcpy(jogador_alocado->pais_jogando, jogador.pais_jogando);
            strcpy(jogador_alocado->pais, jogador.pais);
            strcpy(jogador_alocado->time, jogador.time);

            //==============================Jogador Lido || Falta inserir==============================//
            TABM_Insere(raiz, jogador_alocado, t, 0);

            //==============================Jogador Lido || Falta inserir==============================//s
        }
        i++;
    }

}

int main(void){

    char raiz[10] = "raiz.bin";
    FILE *fp = fopen(raiz, "wb");
    int num = -1;
    fwrite(&num, sizeof(int), 1, fp);
    fclose(fp);
    int t = 3;
    
    preencherJogador("EURO.txt", raiz, t);

    
    fp = fopen(raiz, "rb");
    fread(&num, sizeof(int), 1, fp);
    fclose(fp);

    char novo_nome[10];
    GeraNome(novo_nome, num);
    TABM *resp = leitura(novo_nome, 3);
    
    // printJogador(resp->chave[0]);
    // printJogador(resp->chave[1]);
    // printJogador(resp->chave[2]);

    TABM_Libera_no(resp, t);

    return 0;
}