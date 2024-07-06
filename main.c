#include "Funcoes/TLSE.c"
#include "TABM.c"   
//#include "FuncaoAuxiliares.c"


//=============================================================================================
typedef struct Id_Idade{
    int id, idade;
}Id_Idade;

void printId_Idade(char *nomeArq){
    FILE *arq = fopen(nomeArq,"rb+");
    Id_Idade id_idade;
    int aux; 

    while(1){
        aux = fread(&id_idade, sizeof(Id_Idade), 1, arq);
        if(aux != 1)break;
        printf("(%i %i) ", id_idade.id, id_idade.idade);
    }
    fclose(arq);
}
void insertSort(char *nomeArq, Id_Idade *jogador, int i){
    if(i == 1){
        FILE *arq = fopen(nomeArq,"wb+");
        fwrite(jogador, sizeof(Id_Idade), 1, arq);
        fclose(arq);
    }


    FILE *arq = fopen(nomeArq,"rb+");
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq)/sizeof(Id_Idade);

    Id_Idade *comparador = (Id_Idade *)malloc(sizeof(Id_Idade));
    int j = tam-1;
    fseek(arq, j*sizeof(Id_Idade), SEEK_SET);

    fread(comparador, sizeof(Id_Idade), 1, arq);
    while(comparador->idade > jogador->idade){
        fseek(arq, (j+1)*sizeof(Id_Idade), SEEK_SET);
        fwrite(comparador, sizeof(Id_Idade), 1, arq);

        j--;
        if(j<0)break;
        fseek(arq, j*sizeof(Id_Idade), SEEK_SET);
        fread(comparador, sizeof(Id_Idade), 1, arq);
    }
    fseek(arq, (j+1)*sizeof(Id_Idade), SEEK_SET);
    fwrite(jogador, sizeof(Id_Idade), 1, arq);

    free(comparador);
    fclose(arq);
}



//===================================Boolean para ver se uma string é pais===================================
int pais(char *nome){
    size_t i = 0;
    while(i < strlen(nome)){
        if(nome[i] == '/')return 0;
        i ++;
    }
    return 1;
} 

//===================================retorna TLSE de quais linhas são paises===================================
TLSE *linhasPais(char *arquivo){
    FILE *fp  = fopen(arquivo, "r");
    if(!fp)exit(1);

    TLSE *linhas = NULL;

    int a = 1, i = 0;
    char leitura[1000];    
    while (1){
        a = fscanf(fp, "%[^\n]\n", leitura);
        if(a!=1)break;
        if(pais(leitura)){
            linhas = TLSE_insere(linhas, i);
        }
        i++;
    }
    fclose(fp);
    return linhas;
}

//===================================Le o arquivo e gera a struct Jogador===================================
void preencherJogador(char *arquivo, char *raiz, int t){
    TLSE *linhas = linhasPais(arquivo);
    FILE *fp  = fopen(arquivo, "r");

    Id_Idade *idIdade = (Id_Idade *)malloc(sizeof(Id_Idade));
    
    int corrente = 0;

    TJ *jogador_alocado = (TJ *) malloc (sizeof(TJ));
    TJ jogador;
    char pais[30];
    int a = 1, i = 0;

    while(1 && i < 7){
        if(TLSE_busca(linhas, i)){
            a = fscanf(fp, "%[^\n]\n", pais);
            if(a!=1)break;
        }
        else{
            a = fscanf(fp, "%i/", &jogador.id);
            if(a!=1)break;

            a = fscanf(fp, "%i/", &jogador.camisa);
            if(a!=1)break;

            a = fscanf(fp, "%[^/]/", jogador.posicao);

            a = fscanf(fp, "%[^/]/", jogador.nome);
            if(a!=1)break;

            a = fscanf(fp, "%[^(](aged", jogador.data_nasc);
            if(a!=1)break;

            a = fscanf(fp, "%i)/", &jogador.idade);
            if(a!=1)break;

            a = fscanf(fp, "%i/", &jogador.jogos);
            if(a!=1)break;

            a = fscanf(fp, "%i/", &jogador.gols);
            if(a!=1)break;

            a = fscanf(fp, "%[^/]/", jogador.pais_jogando);
            if(a!=1)break;

            a = fscanf(fp, "%[^\n]\n", jogador.time);
            if(a!=1)break;

            strcpy(jogador.pais, pais);

            jogador_alocado->id = jogador.id;
            jogador_alocado->camisa = jogador.camisa;
            strcpy(jogador_alocado->posicao, jogador.posicao);
            strcpy(jogador_alocado->nome , jogador.nome);
            strcpy(jogador_alocado->data_nasc, jogador.data_nasc);
            jogador_alocado->idade = jogador.idade;
            jogador_alocado->jogos = jogador.jogos;
            jogador_alocado->gols = jogador.gols;
            strcpy(jogador_alocado->pais_jogando, jogador.pais_jogando);
            strcpy(jogador_alocado->pais, jogador.pais);
            strcpy(jogador_alocado->time, jogador.time);

            //==============================Jogador Lido || Falta inserir==============================//
            TABM_Insere(raiz, jogador_alocado, t, &corrente);
            //printJogador(jogador_alocado);
            //printf("\n\n");
            idIdade->id = jogador.id;
            idIdade->idade = jogador.idade;
            // printf("(%d -- %d) ", idIdade->id, idIdade->idade);
            insertSort("Id_Idade", idIdade, i);
            
            //==============================Jogador Lido || Falta inserir==============================//s


        }
        i++;
    }
    printf("\n");
    
}

int main(void){
    
    //Criando a raiz
    char raiz[10] = "raiz.bin";
    FILE *fp = fopen(raiz, "wb");
    int num = -1;
    fwrite(&num, sizeof(int), 1, fp);
    fclose(fp);
    int t = 2;

    //Preenchendo os jogadores
    preencherJogador("EURO.txt", raiz, t);

    printId_Idade("Id_Idade");
    printf("\n\n");

    // //Imprimindo ids
    // TABM_Imprime_ids(raiz, t);

    // //Restringi o preenche jogador para 3 pra testar o caso 1 da retira!!

    // TABM_Retira(raiz, 152, t);
    // TABM_Retira(raiz, 131, t);
    // TABM_Retira(raiz, 216, t);

    
    // printf("\n");
    // printf("\n");

    TABM_Imprime_ids(raiz, t);

    // TABM_Libera_no(resp, t);

    return 0;
}