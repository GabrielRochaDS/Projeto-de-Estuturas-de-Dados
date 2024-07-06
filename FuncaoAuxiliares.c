#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcoes/TLSE.c"
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
    printf("\n");
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
    int aux;
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
        aux = fread(&comparador, sizeof(Id_Idade), 1, arq);
        if(aux != 1)break;
    }
    fseek(arq, (j+1)*sizeof(Id_Idade), SEEK_SET);
    fwrite(jogador, sizeof(Id_Idade), 1, arq);
    fclose(arq);
}

void removeId_Idade(int id){
    FILE *arq = fopen("Id_Idade.bin","rb+");
    if(!arq)exit(1);
    Id_Idade comparador;
    int aux;
    while(1){
        aux = fread(&comparador, sizeof(Id_Idade), 1, arq);
        if(aux != 1){
            printf("Jogador nao encontrado.");
            return;
        }
        if(id == comparador.id)break;
    
    }
    fseek(arq, -sizeof(Id_Idade), SEEK_CUR);
    comparador.id = -1;
    comparador.idade = -1;
    fwrite(&comparador, sizeof(Id_Idade), 1, arq);
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
    printf("\n");
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

void removeId_Jogo(int id){
    FILE *arq = fopen("Id_Jogos.bin","rb+");
    if(!arq)exit(1);
    Id_Jogos comparador;
    int aux;
    while(1){
        aux = fread(&comparador, sizeof(Id_Jogos), 1, arq);
        if(aux != 1){
            printf("Jogador nao encontrado.");
            return;
        }
        if(id == comparador.id)break;
    
    }
    fseek(arq, -sizeof(Id_Jogos), SEEK_CUR);
    comparador.id = -1;
    comparador.jogos = -1;
    fwrite(&comparador, sizeof(Id_Jogos), 1, arq);
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
    printf("\n");
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

void removeId_Pais(int id){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq)exit(1);
    Id_Pais comparador;
    int aux;
    while(1){
        aux = fread(&comparador, sizeof(Id_Pais), 1, arq);
        if(aux != 1){
            printf("Jogador nao encontrado.");
            return;
        }
        if(id == comparador.id)break;
    
    }
    fseek(arq, -sizeof(Id_Pais), SEEK_CUR);
    comparador.id = -1;
    strcpy(comparador.pais, "-1");
    fwrite(&comparador, sizeof(Id_Pais), 1, arq);
    fclose(arq);
}


//=========================================Funçoes Busca====================================================//

//===============Mais novo Mais Velho===============// Q1

TLSETJ *HL_Idade(char *raiz, int t){
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

TLSETJ *HL_IdadePosicao(char *raiz, char *posicao, int t){
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

TLSETJ *HL_IdadeSelecao(char *raiz, char *selecao, int t){
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

        if(strcmp(selecao, novo->chave[i]->pais) == 0){
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

        if(strcmp(selecao, novo->chave[i]->pais) == 0){
            resp = TLSETJ_insere(resp, novo->chave[i]);
            break;
        }
        pos --;
        //TABM_Libera_no(novo, t);
    }
    return resp;
}


//===============Mais e menos atuação===============// Q2 e Q3

TLSETJ *HL_AtuacaoSelecao(char *raiz, char *selecao, int t){
    FILE *arq = fopen("Id_Jogos.bin","rb+");
    if(!arq)exit(1);
    
    int aux, i, pos = -1;
    Id_Jogos jogador;
    TLSETJ *resp = NULL;
    int atuacao = -1, interac = 1;

    while(1){
        aux = fread(&jogador, sizeof(Id_Jogos), 1, arq);
        if(aux != 1){
            break;
        }

        TABM *novo = TABM_Busca(raiz,jogador.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }

        if(strcmp(selecao, novo->chave[i]->pais) == 0){
            if(interac == 1){
                interac = -1;
                atuacao = novo->chave[i]->jogos;
            }
            if(interac != 1 && novo->chave[i]->jogos != atuacao){   
                break;
            }
            resp = TLSETJ_insere(resp, novo->chave[i]);
            
        }
        //TABM_Libera_no(novo, t);
    }
    atuacao = -1;
    interac = 1;

    while (1){
        fseek(arq, pos*sizeof(Id_Jogos), SEEK_END);
        aux = fread(&jogador, sizeof(Id_Jogos), 1, arq);
        if(aux != 1){
            break;
        }

        TABM *novo = TABM_Busca(raiz,jogador.id, t);

        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }

        if(strcmp(selecao, novo->chave[i]->pais) == 0){
            if(interac == 1){
                interac = -1;
                atuacao = novo->chave[i]->jogos;
            }
            if(interac != 1 && novo->chave[i]->jogos != atuacao){   
                break;
            }
            resp = TLSETJ_insere(resp, novo->chave[i]);
        }
        pos --;
        //TABM_Libera_no(novo, t);
    }
    return resp;
}

TLSETJ *HL_Atuacao(char *raiz, int t){
    FILE *arq = fopen("Id_Jogos.bin","rb+");
    if(!arq)exit(1);
    
    int aux, i, pos = -1;
    Id_Jogos jogador;
    TLSETJ *resp = NULL;
    int atuacao = -1, interac = 1;

    while(1){
        aux = fread(&jogador, sizeof(Id_Jogos), 1, arq);
        if(aux != 1){
            break;
        }

        TABM *novo = TABM_Busca(raiz,jogador.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }
        if(interac == 1){
            interac = -1;
            atuacao = novo->chave[i]->jogos;
        }
        if(interac != 1 && novo->chave[i]->jogos != atuacao){   
            break;
        }
        resp = TLSETJ_insere(resp, novo->chave[i]);
            
        
        //TABM_Libera_no(novo, t);
    }
    atuacao = -1;
    interac = 1;

    while (1){
        fseek(arq, pos*sizeof(Id_Jogos), SEEK_END);
        aux = fread(&jogador, sizeof(Id_Jogos), 1, arq);
        if(aux != 1){
            break;
        }

        TABM *novo = TABM_Busca(raiz,jogador.id, t);

        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }
        
        if(interac == 1){
            interac = -1;
            atuacao = novo->chave[i]->jogos;
        }
        if(interac != 1 && novo->chave[i]->jogos != atuacao){   
            break;
        }
        resp = TLSETJ_insere(resp, novo->chave[i]);
        
        pos --;
        //TABM_Libera_no(novo, t);
    }
    return resp;
}

//===============Maior e menor selecao===============// Q4

void HL_QtdSelecao(){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq) exit(1);

    Id_Pais jogador;
    char maiorSel[40], menorSel[40], atualSel[40];
    int qtdMaior, qtdMenor, qtdatual;
    int interac = 1, aux;

    while(1){
        aux = fread(&jogador, sizeof(Id_Pais), 1, arq);
        if(aux != 1) break;
        if(interac == 1){
            strcpy(maiorSel, jogador.pais);
            strcpy(menorSel, jogador.pais);
            strcpy(atualSel, jogador.pais);
            qtdMaior = 1;
            qtdMenor = 1000000;
            qtdatual = 1;
            interac ++;
        }else{
            if(strcmp(atualSel, jogador.pais) == 0){
                qtdatual ++;
            }
            else{ 
                if(qtdatual <= qtdMenor){
                    qtdMenor = qtdatual;
                    strcpy(menorSel, atualSel);
                }
                strcpy(atualSel, jogador.pais);
                qtdatual = 1;
            }
        }
        if(qtdatual > qtdMaior){
            qtdMaior = qtdatual;
            strcpy(maiorSel, atualSel);
        }

    }
    printf("Menor seleção: %s com %i jogadores\n", menorSel, qtdMenor);
    printf("Maior seleção: %s com %i jogadores\n", maiorSel, qtdMaior);
}

//===============Jogadores que atuam dentro/fora da origem===============// Q5 e Q6


TLSETJ *Jogadores_AtuamFora(char *raiz, int t){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq)exit(1);

    Id_Pais id_pais;
    int aux, i; 
    TLSETJ *resp = NULL;

    while(1){
        aux = fread(&id_pais, sizeof(Id_Pais), 1, arq);
        if(aux != 1)break;

        TABM *novo = TABM_Busca(raiz, id_pais.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == id_pais.id)break;
        }
        if(strcmp(novo->chave[i]->pais_jogando, id_pais.pais) != 0){
            resp = TLSETJ_insere(resp, novo->chave[i]);
        }

        //TABM_Libera_no(novo, t);
    }
    return resp;
    fclose(arq);
}


TLSETJ *Jogadores_AtuamNaOritem(char *raiz, int t){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq)exit(1);
    
    Id_Pais id_pais;
    int aux, i; 
    TLSETJ *resp = NULL;

    while(1){
        aux = fread(&id_pais, sizeof(Id_Pais), 1, arq);
        if(aux != 1)break;

        TABM *novo = TABM_Busca(raiz, id_pais.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == id_pais.id)break;
        }
        if(strcmp(novo->chave[i]->pais_jogando, id_pais.pais) == 0){
            resp = TLSETJ_insere(resp, novo->chave[i]);
        }

        //TABM_Libera_no(novo, t);
    }
    return resp;
    fclose(arq);
}

//===============Seleção com mais atuantes dentro/fora origem===============// Q5 e Q6               
//====================================================================================================================================================//
//Dando erro, alguns dao um a mais e outros um a menos


void PrintSelecoesComMaisFora(char *raiz, int t){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq)exit(1);
    Id_Pais id_pais;
    int aux, i, interac = 1; 
    char maiorSelec[10][40], atual[40];
    int qtdAtual = 0, maior = 0, qtdMaiorSelec = 0;

    while(1){
        
        aux = fread(&id_pais, sizeof(Id_Pais), 1, arq);
        if(aux != 1)break;

        TABM *novo = TABM_Busca(raiz, id_pais.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == id_pais.id)break;
        }

        if(interac == 1){
            qtdMaiorSelec = 1;
            qtdAtual = 0;
            maior = qtdAtual;
            strcpy(maiorSelec[0], id_pais.pais);
            interac = -1;
        }
        if(strcmp(id_pais.pais, atual) != 0){
            qtdAtual = 1;
            printf("%s", id_pais.pais);
            strcpy(atual, id_pais.pais);
        }else if(strcmp(novo->chave[i]->pais_jogando, id_pais.pais) != 0){
            qtdAtual += 1;
            
            if(qtdAtual > maior){
                qtdMaiorSelec = 1;
                maior = qtdAtual;
                strcpy(maiorSelec[0], id_pais.pais);
            }else if(qtdAtual == maior){
                strcpy(maiorSelec[qtdMaiorSelec], id_pais.pais);
                qtdMaiorSelec++;
            }
        } 
        printf("%i\n", qtdAtual);
        //TABM_Libera_no(novo, t);
    }

    for(i = 0; i < qtdMaiorSelec; i++){
        printf("%s\n", maiorSelec[i]);
    }
    printf("%d\n", qtdAtual);
}

void PrintSelecoesComMaisDentro(char *raiz, int t){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq)exit(1);
    Id_Pais id_pais;
    int aux, i, interac = 1; 
    char maiorSelec[10][40], atual[40];
    int qtdAtual = 0, maior = 0, qtdMaiorSelec = 0;

    while(1){
        
        aux = fread(&id_pais, sizeof(Id_Pais), 1, arq);
        if(aux != 1)break;

        TABM *novo = TABM_Busca(raiz, id_pais.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == id_pais.id)break;
        }

        if(interac == 1){
            qtdMaiorSelec = 1;
            qtdAtual = 0;
            maior = qtdAtual;
            strcpy(maiorSelec[0], id_pais.pais);
            interac = -1;
        }
        if(strcmp(id_pais.pais, atual) != 0){
            qtdAtual = 1;
            printf("%s", id_pais.pais);
            strcpy(atual, id_pais.pais);
        }else if(strcmp(novo->chave[i]->pais_jogando, id_pais.pais) == 0){
            qtdAtual += 1;
            
            if(qtdAtual > maior){
                qtdMaiorSelec = 1;
                maior = qtdAtual;
                strcpy(maiorSelec[0], id_pais.pais);
            }else if(qtdAtual == maior){
                strcpy(maiorSelec[qtdMaiorSelec], id_pais.pais);
                qtdMaiorSelec++;
            }
        } 
        printf("%i\n", qtdAtual);
        //TABM_Libera_no(novo, t);
    }

    for(i = 0; i < qtdMaiorSelec; i++){
        printf("%s\n", maiorSelec[i]);
    }
    printf("%d\n", qtdAtual);
}




//===============Remoção de Jogadores dado um conjunto contendo suas chaves primárias===============//
// void RemoveJogadoresConjunto (char *raiz, int t){
//     int n;
//     do{
//         scanf("%")

//     }while(n > 0);
// }



