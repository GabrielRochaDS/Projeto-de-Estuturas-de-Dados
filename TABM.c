#include "TABM.h"

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

TABM *busca_aux(TABM *no, int id, int t){
    int i = 0;
    if (no->folha){
        while (i < no->nchaves && id > no->chave[i]->id) i++;
        if ((i < no->nchaves) && (id == no->chave[i]->id)) return no;
        //TABM_Libera_no(no, t);
        return NULL;
    }
    else while (i < no->nchaves && id >= no->ids[i]) i++;
    
    char nome_filhoi[10];
    GeraNome(nome_filhoi, no->filhos[i]);

    //TABM_Libera_no(no, t);

    TABM *no_filhoi = leitura(nome_filhoi, t);
    
    return busca_aux(no_filhoi, id, t);
}

TABM *TABM_Busca(char *raiz, int id, int t){
    FILE *fp = fopen(raiz, "rb");
    if (!fp) exit(1);

    int num;
    fread(&num, sizeof(int), 1, fp);
    fclose(fp);

    if (num == -1) return NULL;                      //Se a raíz se encontra vazia, retorna

    char novo_nome[10];
    GeraNome(novo_nome, num);

    TABM *no = leitura(novo_nome, t);

    return busca_aux(no, id, t);
}

void divisao(TABM *x, int i, TABM *y, int t, int *corrente){
    TABM *z = TABM_Cria(t);
    z->folha = y->folha;
    z->nome = (*corrente);
    (*corrente) = (*corrente) + 1;
    int j;
    if(!y->folha){
        z->nchaves = t-1;
        for(j=0;j<t-1;j++) z->ids[j] = y->ids[j+t];
        for(j=0;j<t;j++){
            z->filhos[j] = y->filhos[j+t];
            // y->filhos[j+t] = NULL; Não necessário pois quando escrevermos os nós os filhos excedentes não serão escritos
            //devido a modificação do y->nchaves;
        }
    }
    else {
        z->nchaves = t; //z possuir� uma chave a mais que y se for folha
        for(j = 0; j < t; j++) z->chave[j] = y->chave[j+t-1];//Caso em que y � folha, temos q passar a info para o n� da direita
        z->prox = y->prox; //ultima revisao: 04/2020
        y->prox = z->nome;
    }
    y->nchaves = t-1;
    for(j = x->nchaves; j >= i; j--) x->filhos[j+1] = x->filhos[j];
    x->filhos[i] = z->nome;
    for(j = x->nchaves; j >= i; j--) x->ids[j] = x->ids[j-1];
    if (y->folha) x->ids[i-1] = y->chave[t-1]->id;
    else x->ids[i-1] = y->ids[t-1];
    x->nchaves++;

    char novo_nomex[10];
    char novo_nomey[10];
    char novo_nomez[10];
    
    GeraNome(novo_nomex, x->nome);
    GeraNome(novo_nomey, y->nome);
    GeraNome(novo_nomez, z->nome);

    escrita(novo_nomex, x);
    escrita(novo_nomey, y);
    escrita(novo_nomez, z);

    // TABM_Libera_no(z, t);
    // TABM_Libera_no(x, t);
    // TABM_Libera_no(y, t);
}

void insere_nao_completo(TABM *x, TJ *jogador, int t, int *corrente){
    int i = x->nchaves - 1;
    if (x->folha){
        while((i>=0) && (jogador->id < x->chave[i]->id)){
            x->chave[i+1] = x->chave[i];
            i--;
        }
        x->chave[i+1] = jogador;
        x->nchaves += 1;
        char novo_nome[10];
        GeraNome(novo_nome, x->nome);
        escrita(novo_nome, x);
        // TABM_Libera_no(x, t);
        return;
    }

    while((i >= 0) && (jogador->id < x->ids[i])) i--;
    i++;

    char novo_nome[10];
    GeraNome(novo_nome, x->filhos[i]);
    TABM *no_filho = leitura(novo_nome, t);

    if(no_filho->nchaves == ((2*t)-1)){         //MODIFICAÇÃO: LER NÓ ATUALIZADO PÓS DIVISÃO

        int nome_x = x->nome;

        divisao(x, (i+1), no_filho, t, corrente);
        
        char novo_nomex[10];
        GeraNome(novo_nomex, nome_x);

        x = leitura(novo_nomex, t);

        if(jogador->id > x->ids[i]){
            char novo_nome_filho[10];
            GeraNome(novo_nome_filho, x->filhos[i + 1]);
            no_filho = leitura(novo_nome_filho, t);
        }
        else no_filho = leitura(novo_nome, t);
    }
    // TABM_Libera_no(x, t);
    insere_nao_completo(no_filho, jogador, t, corrente);
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

        (*corrente) = 1;
    
        rewind(fp);
        fwrite(&novo->nome, sizeof(int), 1, fp);
        
        escrita(nome_novo, novo);
        // TABM_Libera_no(novo, t);
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


    if (no->nchaves == ((2 * t) - 1)){
        TABM *S = TABM_Cria(t);
        S->nchaves = 0;
        S->folha = 0;
        S->filhos[0] = prim_arq;
        S->nome = (*corrente);

        char novo_nome2[10];
        GeraNome(novo_nome2, (*corrente));
        rewind(fp);
        fwrite(corrente, sizeof(int), 1, fp);
        (*corrente) = (*corrente) + 1;

        int nome_S = S->nome;

        divisao(S, 1, no, t, corrente);       //MODIFICAÇÃO: LER NÓ ATUALIZADO PÓS DIVISÃO

        char novo_nomeS[10];
        GeraNome(novo_nomeS, nome_S);
        S = leitura(novo_nomeS, t);

        insere_nao_completo(S, jogador, t, corrente);
        fclose(fp);
        return;
    }

    insere_nao_completo(no, jogador, t, corrente);
    fclose(fp);
}

void remover(TABM *a, int id, int t){
    if(!a) return;
    int i;
    if (a->folha){  //CASO 1 somente ocorre se estivermos na folha;
        for(i = 0; i < a->nchaves && a->chave[i]->id < id; i++);
        if((i < a->nchaves) && (id == a->chave[i]->id)){ //CASO 1
            printf("\nCASO 1\n");
            int j;
            for(j = i; j < a->nchaves-1;j++) a->chave[j] = a->chave[j+1];
            a->nchaves -= 1;
            char novo_nome[10];
            GeraNome(novo_nome, a->nome);
            escrita(novo_nome, a);
            //TABM_Libera_no(a, t);                         //Liberação do nó não feita
        }
        return;
    }

    else{
        for(i = 0; i < a->nchaves && a->ids[i] < id; i++);

        if((i < a->nchaves) && (id == a->ids[i])) i++;

        char nome_filhoy[10];
        GeraNome(nome_filhoy, a->filhos[i]);
        TABM *y = leitura(nome_filhoy, t);

        if (y->nchaves == t - 1){
            if (i < a->nchaves - 1){
                char nome_irmaofrente[10];
                GeraNome(nome_irmaofrente, a->filhos[i + 1]);
                TABM *zf = leitura(nome_irmaofrente, t);        //Lendo o irmão da direita primeiramente

                if((i < a->nchaves) && (zf->nchaves >= t)){
                    printf("\nCASO 3A: i menor que nchaves\n"); //Irmão da direita possui chave, caso restritos para nós com i != a->nchaves (filho da borda direita);
                    if (!y->folha){
                        y->ids[t-1] = a->ids[i];                //dar a y a chave i da arv
                        a->ids[i] = zf->ids[0];                 //dar a arv uma chave de z

                        y->nchaves += 1;

                        int j;
                        for(j = 0; j < zf->nchaves - 1; j++)    //ajustar chaves de z
                            zf->ids[j] = zf->ids[j+1];
                        y->filhos[y->nchaves] = zf->filhos[0];  //enviar ponteiro menor de z para o novo elemento em y
                        for(j = 0; j < zf->nchaves; j++)        //ajustar filhos de z
                            zf->filhos[j] = zf->filhos[j + 1];
                        zf->nchaves -= 1;
                        printf("Pass2");

                        char nome_pai[10];
                        GeraNome(nome_pai, a->nome);

                        escrita(nome_pai, a);
                        escrita(nome_filhoy, y);
                        escrita(nome_irmaofrente, zf);

                        //TABM_Libera_no(zf, t);
                        remover(y, id, t);
                        return;
                    }
                    else{
                        a->ids[i] = zf->chave[0]->id + 1;
                        y->chave[t-1] = zf->chave[0];

                        y->nchaves += 1;

                        int j;
                        for(j = 0; j < zf->nchaves - 1; j++)    //ajustar chaves de z
                            zf->chave[j] = zf->chave[j+1];
                        zf->nchaves -= 1;

                        char nome_pai[10];
                        GeraNome(nome_pai, a->nome);

                        escrita(nome_pai, a);
                        escrita(nome_filhoy, y);
                        escrita(nome_irmaofrente, zf);

                        //TABM_Libera_no(zf, t);
                        remover(y, id, t);
                        return;
                    }
                }
            }

            //TABM_Libera_no(zf, t);  //Liberando o nó do irmão da frente que não vingou
            if (i > 0){
                char nome_irmaotras[10];
                GeraNome(nome_irmaotras, a->filhos[i - 1]);
                TABM *zt = leitura(nome_irmaotras, t);

                if((i > 0) && (zt->nchaves >=t)){ //CASO 3A   OLHA IRMÃO ESQUERDA
                    printf("\n");
                    printf("\nCASO 3A: i igual a nchaves\n");
                    printf("\n");

                    if (!y->folha){
                        int j;
                        for(j = y->nchaves; j > 0; j--)         //encaixar lugar da nova chave
                            y->ids[j] = y->ids[j-1];
                        for(j = y->nchaves + 1; j > 0; j--)     //encaixar lugar dos filhos da nova chave
                            y->filhos[j] = y->filhos[j-1];

                        y->ids[0] = a->ids[i-1];                //dar a y a chave i da arv
                        a->ids[i-1] = zt->ids[zt->nchaves - 1]; //dar a arv uma chave de z

                        y->nchaves += 1;

                        y->filhos[0] = zt->filhos[zt->nchaves]; //enviar ponteiro de z para o novo elemento em y
                        zt->nchaves -= 1;
                        
                    }
                    else{
                        int j;
                        for(j = y->nchaves; j > 0; j--)         //encaixar lugar da nova chave
                            y->chave[j] = y->chave[j-1];
                        a->ids[i-1] = zt->chave[zt->nchaves - 1]->id;
                        y->chave[0] = zt->chave[zt->nchaves-1];

                        y->nchaves += 1;
                        zt->nchaves -= 1;
                    }
                    
                    char nome_pai[10];
                    GeraNome(nome_pai, a->nome);

                    escrita(nome_pai, a);
                    escrita(nome_filhoy, y);
                    escrita(nome_irmaotras, zt);

                    //TABM_Libera_no(zt, t);
                    
                    remover(y, id, t);
                    return;
                }
            }

            //CASO 3B
        }
    }

    char nome_prox_filho[10];
    GeraNome(nome_prox_filho, a->filhos[i]);
    TABM *no_prox_filho = leitura(nome_prox_filho, t);

    // TABM_Libera_no(a, t);

    remover(no_prox_filho, id, t);
}

void TABM_Retira(char *raiz, int id, int t){
    FILE *fp = fopen(raiz, "rb");
    int num;
    fread(&num, sizeof(int), 1, fp);
    fclose(fp);

    if (num == -1){
        printf("-----------------ERRO-NA-REMOÇÃO-----------------\nÁrvore Vazia.\n"); 
        return;
    }
    
    // TABM *a = TABM_Busca(raiz, id, t);
    // if(!a){
    //     printf("-----------------ERRO-NA-REMOÇÃO-----------------\nJogador não se encontra na árvore.\n");
    //     return;
    // }
    //TABM_Libera_no(a, t);

    char nome_primeiro_no[10];
    GeraNome(nome_primeiro_no, num);
    TABM *no = leitura(nome_primeiro_no, t);
    remover(no, id, t);
    //TABM_Libera_no(a, t);
}



void TABM_Imprime_ids(char *raiz, int t){
    FILE *fp = fopen(raiz, "rb");
    if(!fp) exit(1);
    int num, i;
    fread(&num, sizeof(int), 1, fp);
    fclose(fp);

    if (num == -1){
        printf("Árvore Vazia.\n"); 
        return;
    }

    char novo_nome[10];
    GeraNome(novo_nome, num);
    TABM *resp = leitura(novo_nome, t);

    while(!resp->folha){
        novo_nome[0] = '\0';
        GeraNome(novo_nome, resp->filhos[0]);
        resp = leitura(novo_nome, t);
    }
    while(1){
        printf("( ");
        for(i = 0; i<resp->nchaves; i++){
            if (i  < resp->nchaves-1){
                printf("%i | ", resp->chave[i]->id);
            }
            else {printf("%i ", resp->chave[i]->id);
            }
        }
        printf(")-->");   
        if(resp->prox == -1)break;

        novo_nome[0] = '\0';
        GeraNome(novo_nome, resp->prox);
        resp = leitura(novo_nome, t);
    }
    printf("\n");

}

void TABM_Imprime_no(int num, int t){

    char novo_nome2[10];
    GeraNome(novo_nome2, num);
    TABM *a = leitura(novo_nome2, t);

    int i;
    
    if (a->folha){
        printf("=====Nó da árvore=====\n");
        printf("Número do árquivo: %d\n", a->nome);
        printf("Número de chaves: %d\n", a->nchaves);
        printf("Folha: %d\n", a->folha);
        printf("Id do próximo: %d\n", a->prox);
        printf("\n");
        printf("=====Jogadores=====\n");
        for (i = 0; i < a->nchaves; i++){
            printJogador(a->chave[i]);
            printf("\n");
        }
    }
    else{
        printf("=====Nó da árvore=====\n");
        printf("Número do árquivo: %d\n", a->nome);
        printf("Número de chaves: %d\n", a->nchaves);
        printf("Folha: %d\n", a->folha);
        for (i = 0; i < a->nchaves; i++) printf("ID Jogador[%d] = %d\n", i, a->ids[i]);
        for(i = 0; i < (a->nchaves+1); i++) printf("Nome do filho[%d] = %d\n", i, a->filhos[i]);
        printf("\n");
    }
}

// void TABM_Libera_no(TABM *no, int t){
//     if (!no) return;
//     for (int i = 0; i < ((2 * t)); i++) free(no->chave[i]);
//     free(no->chave);
//     //free(no->ids);
//     free(no->filhos);
//     free(no);
// }