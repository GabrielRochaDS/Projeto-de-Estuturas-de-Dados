#include "TAB.h"

char *GeraNome(char *nome, int corrente){
    sprintf(nome, "%d", corrente);
    return nome;
}

TAB *TAB_Inicializa(){
    return NULL;
}


char* TAB_Cria(int t, int corrente){
    char *arq = GeraNome("F", corrente);
    FILE * fp = fopen(arq, "wb");
    if (!fp) exit(1);

    TAB novo;
    novo.nchaves = 0;
    novo.folha = 1;
    TJ jogadores[(2*t -1)];
    novo.lista = jogadores;
    int filhos[2 * t];
    novo.filhos = filhos;
    fwrite(&novo, sizeof(TAB), 1, fp);
    fclose(fp);
    return arq;
}


TAB *TAB_Busca(char *raiz, int id, char *nome_padronizado){
    FILE *fp = fopen(raiz, "rb");
    if (!fp) exit(1);

    TAB *no = (TAB *) malloc (sizeof(TAB));
    fread(no, sizeof(TAB), 1, fp);

    int i = 0;
    while (i < no->nchaves && id < no->lista[i].id) i++;
    if (i < no->nchaves && id == no->lista[i].id){
        fclose(fp);
        return no;
    }
    if (no->folha == 1){
        free(no);
        fclose(fp);
        return NULL;
    }
    fclose(fp);
    char *prox;
    strcpy(prox, nome_padronizado);
    sprintf(prox, "%d", no->filhos[i]);
    free(no);
    return TAB_Busca(prox, id);    
}


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
        fwrite(nome_arq_novo, sizeof(char)); /* INACABADO !!!*/                                     //Escrevendo o nome da nova raíz da árvore no arquivo raíz
    }
}



void TAB_Retira(TAB* arv, int k, int t);


void TAB_Imprime(TAB *a);

