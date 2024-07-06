#include "TLSETJ.h"

TLSETJ* TLSETJ_inicializa(void){
  return NULL;
}

TLSETJ* TLSETJ_insere(TLSETJ *l, TJ *elem){
  TLSETJ *novo = (TLSETJ *) malloc(sizeof(TLSETJ));
  novo->prox = l;
  novo->info = elem;
  return novo;
}

void TLSETJ_imprime(TLSETJ *l){
  TLSETJ *p = l;
  while(p){
    printJogador(p->info);
    printf("\n");
    p = p->prox;
  } 
}

void TLSETJ_libera(TLSETJ *l){
  TLSETJ *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
}


TLSETJ* TLSETJ_retira(TLSETJ *l, TJ *elem){
  TLSETJ *p = l, *ant = NULL;
  while((p) && (p->info->id != elem->id)){
    ant = p;
    p = p->prox;
  }
  if(!p) return l;
  if(!ant) l = l->prox;
  else ant->prox = p->prox;
  free(p);
  return l;
}


TLSETJ* TLSETJ_busca(TLSETJ *l, TJ *elem){
  TLSETJ *p = l;
  while((p) && (p->info->id != elem->id)) p = p->prox; 
  return p;
}

