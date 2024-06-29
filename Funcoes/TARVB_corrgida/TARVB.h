#include <stdio.h>
#include <stdlib.h>

typedef struct ArvB{
  int nchaves, folha, *chave;
  struct ArvB **filho;
}TARVB;

TARVB *TARVB_Inicializa();
TARVB *TARVB_Cria(int t);
TARVB *TARVB_Libera(TARVB *a);
TARVB *TARVB_Busca(TARVB* x, int ch);
TARVB *TARVB_Insere(TARVB *T, int k, int t);
TARVB* TARVB_Retira(TARVB* arv, int k, int t);
void TARVB_Imprime(TARVB *a);
