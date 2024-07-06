#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    FILE *arq = fopen("Id_Idade","rb+");
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
        FILE *arq = fopen("Id_Idade","wb+");
        fwrite(jogador, sizeof(Id_Idade), 1, arq);
        fclose(arq);
        return;
    }

    FILE *arq = fopen("Id_Idade","rb+");
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
        fwrite(jogador, sizeof(Id_Jogos), 1, arq);
        fclose(arq);
        return;
    }

    FILE *arq = fopen("Id_Jogos.bin","rb+");
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
        fwrite(jogador, sizeof(Id_Pais), 1, arq);
        fclose(arq);
        return;
    }

    FILE *arq = fopen("Id_Pais.bin","rb+");
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

