#include "TABM.h"

void GeraNome(char *nome, int corrente){
    sprintf(nome, "%d", corrente);
}


TABM *leitura(char *nome){
    TABM *no = (TABM *) malloc (sizeof(TABM));

    FILE *fp = fopen(nome, "rb");
    if (!fp) exit(1);
    int i;
    fread(&no->nchaves, 1, sizeof(int), fp);


    fread(&no->folha, 1, sizeof(int), fp);
    
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
    for (i = 0; i < no->nchaves+1 ; i++) fread(&no->filhos, sizeof(int), 1, fp);
    
    fclose(fp);
    return no;
}

void escrita(char *nome, TABM *no){
    FILE *fp = fopen(nome, "wb");
    if(!fp) exit(1);

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

TABM *TABM_Busca(char *raiz, int id){
    FILE *fp = fopen(raiz, "rb");
    if (!fp) exit(1);

    TABM *no = leitura(raiz);

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
    
    return TABM_Busca(prox, id);
}

// void TABM_Insere(char *raiz, TJ jogador, int t, int *corrente){

//     TABM aux = TAB_Busca(raiz, jogador.id, t);
//     if (aux.folha != 2) {
//         ("\nElemento já se encontra na árvore.\n");
//         return;
//     }
    
//     FILE *fp = fopen(raiz, "rb+");
//     if (!fp) exit(1);

//     int nome;
//     fread(&nome, sizeof(int), 1, fp);

//     if (nome == -1){
//         char nome_novo[10];
//         TAB_Cria(nome_novo, t, corrente);

//         TABM aux = leitura(nome_novo, t);
//         aux.nchaves++;
//         aux.chave[0] = jogador;
//         escrita(nome_novo, aux, t);
//         fprintf(fp, sizeof(char), 10, nome_novo);
//         fclose(fp);
//         return;
//     }
//     else{
//         char nome_novo[10];
//         fread(nome_novo, sizeof(char), 10, fp);
//         TABM aux = leitura(nome_novo, t);
//         if (aux.nchaves == ((2 * t) - 1)){
            
//         }
//         else{
//             fclose(fp);
//             insere_nao_completo(nome_novo, jogador, t, corrente);
//         }
//     }

// }



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

