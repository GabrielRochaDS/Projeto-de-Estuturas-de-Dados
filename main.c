#include "Funcoes/TLSE.c"
//#include "TABM.c"   
#include "FuncaoAuxiliares.c"



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

    //==============Funções Auxiliares iniciando==============//
    Id_Idade *idIdade = (Id_Idade *) malloc (sizeof(Id_Idade));
    Id_Jogos *idJogos = (Id_Jogos *) malloc (sizeof(Id_Jogos));
    Id_Pais *idPais = (Id_Pais *) malloc (sizeof(Id_Pais));

    
    
    //==============Alocando TJ==============//
    TJ *jogador_alocado = (TJ *) malloc (sizeof(TJ));
    TJ jogador;
    char pais[30];
    int a = 1, i = 0;
    int corrente = 0;

    //==============Loop le todo EURO.txt==============//
    while(1 && i<5){
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

            //==============================Jogador Lido E inserindo==============================//
            TABM_Insere(raiz, jogador_alocado, t, &corrente);
            
            //==============Funções Auxiliares inserindo==============//
            idIdade->id = jogador.id;
            idIdade->idade = jogador.idade;
            insertId_Idade(idIdade, i);

            idJogos->id = jogador.id;
            idJogos->jogos = jogador.jogos;
            insertId_Jogos(idJogos, i);

            idPais->id = jogador.id;
            strcpy(idPais->pais, jogador.pais);
            insertId_Pais(idPais, i);

        }
        i++;
    }
    free(idIdade);
    free(idJogos);
    free(idPais);


    printf("\n");
    
}

int main(void){
    
    //==============Criando a raiz==============//
    char raiz[10] = "raiz.bin";
    FILE *fp = fopen(raiz, "wb");
    int num = -1;
    fwrite(&num, sizeof(int), 1, fp);
    fclose(fp);
    int t = 2;

    //==============Preenchendo os jogadores==============//
    preencherJogador("EURO.txt", raiz, t);

    //==============Print Funcoes auxiliares==============//
    // printId_Idade();
    // printf("\n\n");
    // printId_Jogos();
    // printf("\n\n");
    // printId_Pais();
    // printf("\n\n");

    //==============TLSETJ funcoes auxiliares Idade==============//
    // TLSETJ *lista = HL_Idade(raiz,t);
    // TLSETJ *lista = HL_IdadePosicao(raiz,"MF",t);
    // TLSETJ *lista = HL_IdadeSelecao(raiz,"Germany",t);
    // TLSETJ_imprime(lista);

    //==============TLSETJ funcoes auxiliares Jogos==============//
    // TLSETJ *lista = HL_AtuacaoSelecao(raiz, "Germany", t);
    // TLSETJ *lista = HL_Atuacao(raiz, t);
    // TLSETJ_imprime(lista);

    //==============TLSETJ funcoes auxiliares Seleções==============//
    // printId_Pais();
    // HL_QtdSelecao();
    // TLSETJ *lista = Jogadores_AtuamFora(raiz, t);
    // TLSETJ *lista = Jogadores_AtuamNaOritem(raiz, t);
    // TLSETJ_imprime(lista);

    //==============Imprimindo ids==============//
    TABM_Imprime_ids(raiz, t);



    //==============Testes Retira==============//
    FILE *teste = fopen(raiz, "rb");
    if (!fp) exit(1);

    fread(&num, sizeof(int), 1, teste);
    fclose(fp);
    
    char nome_n[10];
    GeraNome(nome_n, num);
    TABM *no = leitura(nome_n, t);

    TABM_Imprime_no(no->nome, t);

    TABM_Retira(raiz, 38, t);
    // // TABM_Retira(raiz, 152, t);
    TABM_Retira(raiz, 131, t);
    TABM_Retira(raiz, 216, t);

    FILE *teste2 = fopen(raiz, "rb");
    if (!fp) exit(1);

    fread(&num, sizeof(int), 1, teste2);
    fclose(fp);
    
    char nome_n2[10];
    GeraNome(nome_n2, num);
    TABM *no2 = leitura(nome_n2, t);

    TABM_Imprime_no(no2->nome, t);



    //==============Imprime Ids e libera==============//
    TABM_Imprime_ids(raiz, t);
    // TABM_Libera_no(resp, t);



    return 0;
}