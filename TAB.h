#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TipoJogador{
    int id, camisa, idade, jogos, gols;
    char *posicao, *nome, *data_nasc, *pais, *pais_jogando, *time;
}TJ;

typedef struct TipoArvoreBMS{
    int nchaves, folha;
    TJ *lista;
    int *filhos;
}TAB;

TAB *TAB_Inicializa();
void TAB_Cria(int t, int corrente);
TAB *TAB_Busca(char *raiz, int id);

void TAB_Insere(char *raiz, TJ *jogador, int t, int corrente);
void TAB_Retira(TAB* arv, int k, int t);
void TAB_Imprime(TAB *a);