#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TipoJogador{
    int id, camisa, idade, jogos, gols;
    char posicao[3], nome[40], data_nasc[40], pais[20], pais_jogando[20], time[40];
}TJ;

typedef struct TipoArvoreBMS{
    int nchaves, folha, prox;
    int *ids;
    TJ *chave;
    int *filhos;
}TAB;

TAB *leitura(char *nome, int t);
void escrita(char *nome, TAB no, int t);
void GeraNome(char *nome, int corrente);
TAB *TAB_Inicializa();
void TAB_Cria(char *arq, int t, int corrente);
// TAB *TAB_Busca(char *raiz, int id);

// void TAB_Insere(char *raiz, TJ *jogador, int t, int corrente);
// void TAB_Retira(TAB* arv, int k, int t);
// void TAB_Imprime(TAB *a);