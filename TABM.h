#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TipoJogador{
    int id, camisa, idade, jogos, gols;
    char posicao[3], nome[40], data_nasc[40], pais[20], pais_jogando[20], time[40];
}TJ;

typedef struct TipoArvoreBMS{
    int nome;
    int nchaves, folha;
    int *ids;
    TJ **chave;
    int *filhos;
    int prox;
}TABM;

TABM *leitura(char *nome, int t);

void escrita(char *nome, TABM *no);

void GeraNome(char *nome, int corrente);

TABM *TABM_Inicializa();

TABM *TABM_Cria(int t);

TABM *TABM_Busca(char *raiz, int id, int t);

void TABM_Insere(char *raiz, TJ *jogador, int t, int *corrente);

void TABM_Libera_no(TABM *no, int t);

// void TABM_Retira(TAB* arv, int k, int t);

void TABM_Imprime_no(TABM *a);