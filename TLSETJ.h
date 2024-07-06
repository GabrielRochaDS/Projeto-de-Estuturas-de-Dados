#include <stdio.h>
#include <stdlib.h>
#include "TABM.c"

typedef struct tjlse{
  TJ *info;
  struct tjlse *prox;
}TLSETJ;

TLSETJ* TLSETJ_inicializa(void);
TLSETJ* TLSETJ_insere(TLSETJ *l, TJ *elem);
void TLSETJ_imprime(TLSETJ *l);

void TLSETJ_libera(TLSETJ *l);
TLSETJ* TLSETJ_retira(TLSETJ *l, TJ *elem);
TLSETJ* TLSETJ_busca(TLSETJ *l, TJ *elem);



