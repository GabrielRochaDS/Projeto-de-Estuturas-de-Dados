#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TipoJogador{
    int id, camisa, idade, jogos, gols;
    char *posicao, *nome, *data_nasc, *pais, *pais_jogando, *time;
    struct TipoJogador *prox;
}TJ;

typedef struct TipoArvoreBMS{
    int nchaves, folha;
    TJ ** lista;
    char **filhos;
}TAB;

TAB *TARVB_Inicializa();
TAB *TARVB_Cria(int t);
TAB *TARVB_Libera(TAB *a);
TAB *TARVB_Busca(TAB* x, int ch);
TAB *TARVB_Insere(TAB *T, int k, int t);
TAB* TARVB_Retira(TAB* arv, int k, int t);
void TARVB_Imprime(TAB *a);