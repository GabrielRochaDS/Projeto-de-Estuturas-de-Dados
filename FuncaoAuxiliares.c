#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TLSETJ.c"

//=========================================Structs====================================================
//(01)
typedef struct Id_Idade{ 
    int id, idade;
}Id_Idade;

//(02, 03)
typedef struct Id_Jogos{
    int id, jogos;
}Id_Jogos;

//(04, 05, 06, 09, 10)
typedef struct Id_Pais{
    int id;
    char pais[40];
}Id_Pais;


//=========================================Funçoes Inserção====================================================//

//===============Id_Idade===============//
void printId_Idade(){
    FILE *arq = fopen("Id_Idade.bin","rb+");
    if(!arq)exit(1);
    Id_Idade id_idade;
    int aux; 

    while(1){
        aux = fread(&id_idade, sizeof(Id_Idade), 1, arq);
        if(aux != 1)break;
        printf("(%i %i) ", id_idade.id, id_idade.idade);
    }
    fclose(arq);
}
void insertId_Idade(Id_Idade *jogador, int i){
    if(i == 1){
        FILE *arq = fopen("Id_Idade.bin","wb+");
        if(!arq)exit(1);
        fwrite(jogador, sizeof(Id_Idade), 1, arq);
        fclose(arq);
        return;
    }

    FILE *arq = fopen("Id_Idade.bin","rb+");
    if(!arq)exit(1);
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq)/sizeof(Id_Idade);

    Id_Idade comparador;
    int j = tam-1;
    fseek(arq, j*sizeof(Id_Idade), SEEK_SET);

    fread(&comparador, sizeof(Id_Idade), 1, arq);
    while(comparador.idade > jogador->idade){
        fseek(arq, (j+1)*sizeof(Id_Idade), SEEK_SET);
        fwrite(&comparador, sizeof(Id_Idade), 1, arq);

        j--;
        if(j<0)break;
        fseek(arq, j*sizeof(Id_Idade), SEEK_SET);
        fread(&comparador, sizeof(Id_Idade), 1, arq);
    }
    fseek(arq, (j+1)*sizeof(Id_Idade), SEEK_SET);
    fwrite(jogador, sizeof(Id_Idade), 1, arq);
    fclose(arq);
}

//===============Id_Jogos===============//

void printId_Jogos(){
    FILE *arq = fopen("Id_Jogos.bin","rb+");
    if(!arq)exit(1);
    Id_Jogos id_jogos;
    int aux; 

    while(1){
        aux = fread(&id_jogos, sizeof(Id_Idade), 1, arq);
        if(aux != 1)break;
        printf("(%i %i) ", id_jogos.id, id_jogos.jogos);
    }
    fclose(arq);
}
void insertId_Jogos(Id_Jogos *jogador, int i){
    if(i == 1){
        FILE *arq = fopen("Id_Jogos.bin","wb+");
        if(!arq)exit(1);
        fwrite(jogador, sizeof(Id_Jogos), 1, arq);
        fclose(arq);
        return;
    }

    FILE *arq = fopen("Id_Jogos.bin","rb+");
    if(!arq)exit(1);
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq)/sizeof(Id_Jogos);

    Id_Jogos comparador;
    int j = tam-1;
    fseek(arq, j*sizeof(Id_Jogos), SEEK_SET);

    fread(&comparador, sizeof(Id_Jogos), 1, arq);
    while(comparador.jogos > jogador->jogos){
        fseek(arq, (j+1)*sizeof(Id_Jogos), SEEK_SET);
        fwrite(&comparador, sizeof(Id_Jogos), 1, arq);

        j--;
        if(j<0)break;
        fseek(arq, j*sizeof(Id_Jogos), SEEK_SET);
        fread(&comparador, sizeof(Id_Jogos), 1, arq);
    }
    fseek(arq, (j+1)*sizeof(Id_Jogos), SEEK_SET);
    fwrite(jogador, sizeof(Id_Jogos), 1, arq);
    fclose(arq);
}


//===============Id_Pais===============//
void printId_Pais(){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq)exit(1);
    Id_Pais id_pais;
    int aux; 

    while(1){
        aux = fread(&id_pais, sizeof(Id_Pais), 1, arq);
        if(aux != 1)break;
        printf("(%i %s) ", id_pais.id, id_pais.pais);
    }
    fclose(arq);
}

void insertId_Pais( Id_Pais *jogador, int i){
    if(i == 1){
        FILE *arq = fopen("Id_Pais.bin","wb+");
        if(!arq)exit(1);
        fwrite(jogador, sizeof(Id_Pais), 1, arq);
        fclose(arq);
        return;
    }

    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq)exit(1);
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq)/sizeof(Id_Pais);

    Id_Pais comparador;
    int j = tam-1;
    fseek(arq, j*sizeof(Id_Pais), SEEK_SET);

    fread(&comparador, sizeof(Id_Pais), 1, arq);
    while(strcmp(comparador.pais, jogador->pais)>=0){
        fseek(arq, (j+1)*sizeof(Id_Pais), SEEK_SET);
        fwrite(&comparador, sizeof(Id_Pais), 1, arq);

        j--;
        if(j<0)break;
        fseek(arq, j*sizeof(Id_Pais), SEEK_SET);
        fread(&comparador, sizeof(Id_Pais), 1, arq);
    }
    fseek(arq, (j+1)*sizeof(Id_Pais), SEEK_SET);
    fwrite(jogador, sizeof(Id_Pais), 1, arq);
    fclose(arq);
}


//=========================================Funçoes Busca====================================================//

//===============Mais novo Mais Velho===============//

TLSETJ *maisNovo_maisVelho(char *raiz, int t){
    FILE *arq = fopen("Id_Idade.bin","rb+");
    if(!arq)exit(1);
    
    Id_Idade jogador;
    TLSETJ *resp = NULL;

    fread(&jogador, sizeof(Id_Idade), 1, arq);
    TABM *novo = TABM_Busca(raiz,jogador.id, t);

    int i;
    for(i = 0; i<novo->nchaves; i++){
        if(novo->chave[i]->id == jogador.id)break;
    }
    resp = TLSETJ_insere(resp, novo->chave[i]);

    //TABM_Libera_no(novo, t);

    fseek(arq, -sizeof(Id_Idade), SEEK_END);


    fread(&jogador, sizeof(Id_Idade), 1, arq);
    novo = TABM_Busca(raiz,jogador.id, t);

    for(i = 0; i<novo->nchaves; i++){
        if(novo->chave[i]->id == jogador.id)break;
    }
    resp = TLSETJ_insere(resp, novo->chave[i]);

    //TABM_Libera_no(novo, t);
    return resp;
}

TLSETJ *maisNovo_maisVelhoPosicao(char *raiz, char *posicao, int t){
    FILE *arq = fopen("Id_Idade.bin","rb+");
    if(!arq)exit(1);
    
    int aux, i, pos = -1;
    Id_Idade jogador;
    TLSETJ *resp = NULL;

    while(1){
        aux = fread(&jogador, sizeof(Id_Idade), 1, arq);
        if(aux != 1){
            break;
        }

        TABM *novo = TABM_Busca(raiz,jogador.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }

        if(strcmp(posicao, novo->chave[i]->posicao) == 0){
            resp = TLSETJ_insere(resp, novo->chave[i]);
            break;
        }
        //TABM_Libera_no(novo, t);
    }

    while (1){
        fseek(arq, pos*sizeof(Id_Idade), SEEK_END);
        aux = fread(&jogador, sizeof(Id_Idade), 1, arq);
        if(aux != 1){
            break;
        }

        TABM *novo = TABM_Busca(raiz,jogador.id, t);

        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }

        if(strcmp(posicao, novo->chave[i]->posicao) == 0){
            resp = TLSETJ_insere(resp, novo->chave[i]);
            break;
        }
        pos --;
        //TABM_Libera_no(novo, t);
    }
    return resp;
}

TLSETJ *maisNovo_maisVelhoSelecao(char *raiz, char *selecao, int t){

}