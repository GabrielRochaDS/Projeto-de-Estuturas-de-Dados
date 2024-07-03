#include "TABM.h"

void GeraNome(char *nome, int corrente){
    sprintf(nome, "%d.bin", corrente);
}

TABM *leitura(char *nome, int t){
    TABM *no = TABM_Cria(t);


    FILE *fp = fopen(nome, "rb");
    if (!fp) exit(1);
    int i;

    fread(&no->nome, sizeof(int), 1, fp);
    fread(&no->nchaves, sizeof(int), 1, fp);
    fread(&no->folha, sizeof(int), 1, fp);
    
    if (no->folha){
        for (i = 0; i < no->nchaves; i++){
            no->chave[i] = (TJ *) malloc (sizeof(TJ));
            fread(no->chave[i], 1, sizeof(TJ), fp);
        }
        fread(&no->prox, sizeof(int), 1, fp);
        fclose(fp);
        return no;
    }

    
    for (i = 0; i < no->nchaves; i++) fread(&no->ids[i], sizeof(int), 1, fp);
    for (i = 0; i < no->nchaves+1 ; i++) fread(&no->filhos[i], sizeof(int), 1, fp);
    
    fclose(fp);
    return no;
}

void escrita(char *nome, TABM *no){
    FILE *fp = fopen(nome, "wb");
    if(!fp) exit(1);

    fwrite(&no->nome, sizeof(int), 1, fp);
    fwrite(&no->nchaves, sizeof(int), 1, fp);
    fwrite(&no->folha, sizeof(int), 1, fp);

    int i;

    for (i = 0; i < no->nchaves; i++){
        if (no->folha) fwrite(no->chave[i], sizeof(TJ), 1, fp);
        else fwrite(&no->ids[i], sizeof(int), 1, fp);
    }
    if (no->folha) fwrite(&no->prox, sizeof(int), 1, fp);
    else for(i = 0; i < no->nchaves+1; i++) fwrite(&no->filhos[i], sizeof(int), 1, fp);

    fclose(fp);
}


TABM *TABM_Inicializa(){
    return NULL;
}


TABM *TABM_Cria(int t){
    TABM* novo = (TABM*) malloc (sizeof(TABM));

    novo->nchaves = 0;

    novo->folha = 1;

    novo->chave = (TJ**) malloc (sizeof(TJ*)*((2 * t)-1));

    novo->ids = (int *) malloc (sizeof(int) * ((2 * t) - 1));

    for(int i = 0; i < (2 * t); i++){
        novo->chave[i] = (TJ *) malloc (sizeof(TJ));
        novo->chave[i] = NULL;
    }
    
    novo->filhos = (int*)malloc(sizeof(int) * 2 * t);

    novo->prox = -1;

    return novo;
}

TABM *TABM_Busca(char *raiz, int id, int t){
    FILE *fp = fopen(raiz, "rb");
    if (!fp) exit(1);

    int num;
    fread(&num, sizeof(int), 1, fp);

    char novo_nome[10];
    GeraNome(novo_nome, num);

    TABM *no = leitura(novo_nome, t);

    int i = 0;
    if (no->folha){
        while (i < no->nchaves && id > no->chave[i]->id) i++;
        if ((i < no->nchaves) && (id == no->chave[i]->id)){
            fclose(fp);
            return no;
        }
        else{
            fclose(fp);
            return NULL;
        }
    }
    else while (i < no->nchaves && id >= no->ids[i]) i++;
    
    fclose(fp);
    char prox[10];
    GeraNome(prox, no->filhos[i]);
    
    return TABM_Busca(prox, id, t);
}

void divisao(TABM *x, int i, TABM *y, int t){
    
}

void insere_nao_completo(TABM *x, TJ *jogador, int t){
    int i = x->nchaves - 1;
    if (x->folha){
        while((i>=0) && (jogador->id < x->chave[i]->id)){
            x->chave[i+1] = x->chave[i];
            i--;
        }
        x->chave[i+1] = jogador;
        x->nchaves++;
        char novo_nome[10];
        GeraNome(novo_nome, x->nome);
        escrita(novo_nome, x);
        return;
    }

    while((i>=0) && (jogador->id < x->chave[i]->id)) i--;
    i++;

    char novo_nome[10];
    GeraNome(novo_nome, x->filhos[i]);
    TABM *no_filho = leitura(novo_nome, t);

    if(no_filho->nchaves == ((2*t)-1)){
        divisao(x, (i+1), no_filho, t);
        if(jogador->id > x->chave[i]->id) i++;
    }
    //TABM_Libera_no(x, t);
    insere_nao_completo(no_filho, jogador, t);
}

void TABM_Insere(char *raiz, TJ *jogador, int t, int *corrente){

    FILE *fp = fopen(raiz, "rb+");
    if (!fp) exit(1);

    int prim_arq;
    fread(&prim_arq, sizeof(int), 1, fp);

    if (prim_arq == -1){            //Árvore Vazia
        TABM *novo = TABM_Cria(t);
        novo->nchaves = 1;
        novo->folha = 1;
        novo->chave[0] = jogador;
        novo->nome = 0;

        char nome_novo[10];
        GeraNome(nome_novo, 0);

        (*corrente) = 0;
    
        rewind(fp);
        fwrite(&novo->nome, sizeof(int), 1, fp);
        
        escrita(nome_novo, novo);
        //TABM_Libera_no(novo, t);
        fclose(fp);
        return;
    }

    // TABM *aux = TABM_Busca(raiz, jogador->id, t);
    // if (aux){
    //     printf("\nElemento já se encontra na árvore.\n");
    //     return;
    // }
    
    char novo_nome[10];
    GeraNome(novo_nome, prim_arq);
    TABM *no = leitura(novo_nome, t);


    // if (no->nchaves == ((2 * t) - 1)){
    //     TABM *S = TABM_Cria(t);
    //     S->nchaves = 0;
    //     S->folha = 0;
    //     S->filhos[0] = prim_arq;
    //     S->nome = (*corrente);

    //     char novo_nome2[10];
    //     GeraNome(novo_nome2, (*corrente));
    //     fwrite(corrente, sizeof(int), 1, fp);
    //     (*corrente) = (*corrente) + 1;

    //     divisao(S, 1, no, t);
    //     insere_nao_completo(S, jogador, t);
    //     fclose(fp);
    //     return;
    // }
    insere_nao_completo(no, jogador, t);
    fclose(fp);
}

// void TABM_Retira(TABM* arv, int k, int t){

// }


void TABM_Imprime_No(TABM *a){
    int i;

    if (a->folha){
        printf("Nó da árvore:\n");
        printf("\n");
        printf("Número de chaves: %d\n", a->nchaves);
        printf("Folha: %d\n", a->folha);
        for (i = 0; i < a->nchaves; i++) printf("ID Jogador[%d] = %d\n", i, a->chave[i]->id);
        for(i = 0; i < (a->nchaves+1); i++) printf("Nome do filho[%d] = %d\n", i, a->filhos[i]);
    }
    else{
        printf("Nó da árvore:\n");
        printf("\n");
        printf("Número de chaves: %d\n", a->nchaves);
        printf("Folha: %d\n", a->folha);
        for (i = 0; i < a->nchaves; i++) printf("ID Jogador[%d] = %d\n", i, a->ids[i]);
        for(i = 0; i < (a->nchaves+1); i++) printf("Nome do filho[%d] = %d\n", i, a->filhos[i]);
    }
}

void 
TABM_Libera_no(TABM *no, int t){
    if (!no) return;
    for (int i = 0; i < (2 * t); i++) free(no->chave[i]);
    free(no->chave);
    free(no->ids);
    free(no->filhos);
}