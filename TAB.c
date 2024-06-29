#include "TAB.h"

TAB *leitura(char *nome, int t){
    TAB *no = (TAB*) malloc (sizeof(TAB));

    FILE *fp = fopen(nome, "rb");
    if (!fp) exit(1);

    fread(no->nchaves, 1, sizeof(int), fp);
    fread(no->folha, 1, sizeof(int), fp);
    fread(no->prox, 1, sizeof(int), fp);
    fread(no->ids, ((2 * t) - 1), sizeof(int), fp);
    fread(no->chave, ((2 * t) - 1), sizeof(TJ), fp);
    fread(no->filhos, (2 * t), sizeof(int), fp);

    fclose(fp);

    return no;
}

void escrita(char *nome, TAB no, int t){
    FILE *fp = fopen(nome, "wb");
    if(!fp) exit(1);

    fwrite(&no.nchaves, sizeof(int), 1, fp);
    fwrite(&no.folha, sizeof(int), 1, fp);
    fwrite(&no.prox, sizeof(int), 1, fp);
    fwrite(&no.ids, sizeof(int), ((2 * t) - 1), fp);
    fwrite(&no.chave, sizeof(TJ), ((2 * t) - 1), fp);
    fwrite(&no.filhos, sizeof(int), (2 * t), fp);

    fclose(fp);
}

void GeraNome(char *nome, int corrente){
    sprintf(nome, "%d", corrente);
}

TAB *TAB_Inicializa(){
    return NULL;
}


void TAB_Cria(char *arq, int t, int corrente){
    GeraNome(arq, corrente);

    TAB novo;
    novo.nchaves = 0;
    novo.folha = 1;
    novo.prox = -1;
    escrita(arq, novo, t);
}

TAB *TAB_Busca(char *raiz, int id, int t){
    FILE *fp = fopen(raiz, "rb");
    if (!fp) exit(1);

    TAB *no = leitura(raiz, t);

    int i = 0;
    while (i < no->nchaves && id > no->chave[i].id) i++;
    if ((i < no->nchaves) && (id == no->chave[i].id) && (no->folha)){
        fclose(fp);
        return no;
    }
    if (no->folha == 1){
        free(no);
        fclose(fp);
        return NULL;
    }
    fclose(fp);
    char prox[10];
    GeraNome(prox, no->filhos[i]);
    free(no);
    return TAB_Busca(prox, id, t);  
}

/*
void TAB_Insere(char *raiz, TJ *jogador, int t, int *corrente){
    FILE *fp = fopen(raiz, "r+");
    if (!fp) exit(1);

    char nome_no[6];
    fread(&nome_no, sizeof(char), 6, fp);
    if (!strcmp(nome_no[6], "-1")){                                 //Raíz vazia, árvore não iniciada
        char *nome_arq_novo = TAB_cria(t, corrente++);              //Criando um novo arquivo nó
        FILE *fpnovo = fopen(nome_arq_novo, "rb+");                  //Abrindo o arquivo
        TAB atual;                
        fread(&atual, sizeof(TAB), 1, fpnovo);                      //Lendo o nó
        atual.nchaves = 1;                                          //Modificando o novo jogador na árvore recem-criada
        atual.lista[0] = jogador;                                   //Adicionando o jogador nas chaves do nó
        fwrite(nome_arq_novo, sizeof(char)); /* INACABADO !!!                                    //Escrevendo o nome da nova raíz da árvore no arquivo raíz
    }
}



void TAB_Retira(TAB* arv, int k, int t);


void TAB_Imprime(TAB *a);
*/

