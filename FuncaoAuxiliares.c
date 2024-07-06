#include "TABM.h"

typedef struct Id_Idade{
    int id, idade;
}Id_Idade;


void insertSort(char *nomeArq, Id_Idade *jogador, int i){
    if(i == 1){
        FILE *arq = fopen(nomeArq,"wb+");
        fwrite(jogador, sizeof(Id_Idade), 1, arq);
        fclose(arq);
    }


    FILE *arq = fopen(nomeArq,"rb+");
    fseek(arq, 0, SEEK_END);
    fwrite(jogador, sizeof(Id_Idade), 1, arq);
    int tam = ftell(arq)/sizeof(Id_Idade);
    printf("%i ", tam);

    Id_Idade *comparador = (Id_Idade *)malloc(sizeof(Id_Idade));
    i = tam-1;
    int j = i-1;
    fseek(arq, j*sizeof(Id_Idade), SEEK_SET);

    fread(comparador, sizeof(int), 1, arq);
    while(comparador->idade>jogador->idade){
        fseek(arq, (j+1)*sizeof(int), SEEK_SET);
        fwrite(comparador, sizeof(int), 1, arq);

        j--;
        if(j<0)break;
        fseek(arq, j*sizeof(int), SEEK_SET);
        fread(comparador, sizeof(int), 1, arq);
    }
    fseek(arq, (j+1)*sizeof(int), SEEK_SET);
    fwrite(jogador, sizeof(int), 1, arq);

    free(comparador);
    fclose(arq);
}
    // for(i = 1; i<tam; i++){
    //     fseek(arq, i*sizeof(int), SEEK_SET);
    //     int valor;
    //     fread(&valor, sizeof(int), 1, arq);

    //     int j = i-1;
    //     int comparador;
    //     fseek(arq, j*sizeof(int), SEEK_SET);
    //     fread(&comparador, sizeof(int), 1, arq);
    //     while (comparador>valor){
    //         fseek(arq, (j+1)*sizeof(int), SEEK_SET);
    //         fwrite(&comparador, sizeof(int), 1, arq);

    //         j--;
    //         if(j<0)break;
    //         fseek(arq, j*sizeof(int), SEEK_SET);
    //         fread(&comparador, sizeof(int), 1, arq);
    //     }
    //     fseek(arq, (j+1)*sizeof(int), SEEK_SET);
    //     fwrite(&valor, sizeof(int), 1, arq);
    // }

// void criaVetorBin(int *vet, int elem, char *nome){
//     FILE *arq = fopen(nome, "wb");
//     fwrite(vet, sizeof(int), elem, arq);
//     fclose(arq);
// }

// void leVetorBin(int elem, char *nome){
//     FILE *arq = fopen(nome, "rb");
//     int vetResp[elem];
//     fread(vetResp, sizeof(int), elem, arq);
//     for(int i = 0; i<elem; i++){
//         printf("%i ", *(vetResp + i));
//     }
//     printf("\n");
//     fclose(arq);
// }

int main(void){

}