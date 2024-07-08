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

typedef struct Id_AnoMes{
    int id;
    char ano[10];
    char mes[20];
}Id_AnoMes;


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

//===============Id_AnoMes===============//
void printId_AnoMes(){
    FILE *arq = fopen("Id_AnoMes.bin","rb+");
    if(!arq)exit(1);
    Id_AnoMes id_anomes;
    int aux; 

    while(1){
        aux = fread(&id_anomes, sizeof(Id_AnoMes), 1, arq);
        if(aux != 1)break;
        if(id_anomes.id == -1)continue;
        printf("(%i %s %s) ", id_anomes.id, id_anomes.mes, id_anomes.ano);
    }
    fclose(arq);
    printf("\n");
}

void insertId_AnoMes( Id_AnoMes *jogador, int i){
    if(i == 1){
        FILE *arq = fopen("Id_AnoMes.bin","wb+");
        if(!arq)exit(1);
        fwrite(jogador, sizeof(Id_AnoMes), 1, arq);
        fclose(arq);
        return;
    }

    FILE *arq = fopen("Id_AnoMes.bin","rb+");
    if(!arq)exit(1);
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq)/sizeof(Id_AnoMes);

    Id_AnoMes comparador;
    int j = tam-1;
    fseek(arq, j*sizeof(Id_AnoMes), SEEK_SET);

    fread(&comparador, sizeof(Id_AnoMes), 1, arq);
    while(strcmp(comparador.ano, jogador->ano)>=0){
        fseek(arq, (j+1)*sizeof(Id_AnoMes), SEEK_SET);
        fwrite(&comparador, sizeof(Id_AnoMes), 1, arq);

        j--;
        if(j<0)break;
        fseek(arq, j*sizeof(Id_AnoMes), SEEK_SET);
        fread(&comparador, sizeof(Id_AnoMes), 1, arq);
    }
    fseek(arq, (j+1)*sizeof(Id_AnoMes), SEEK_SET);
    fwrite(jogador, sizeof(Id_AnoMes), 1, arq);
    fclose(arq);
}

void removeId_AnoMes(int id){
    FILE *arq = fopen("Id_AnoMes.bin","rb+");
    if(!arq)exit(1);
    Id_AnoMes comparador;
    int aux;
    while(1){
        aux = fread(&comparador, sizeof(Id_AnoMes), 1, arq);
        if(aux != 1){
            printf("Jogador não encontrado.");
            return;
        }
        if(id == comparador.id)break;
    
    }
    fseek(arq, -sizeof(Id_AnoMes), SEEK_CUR);
    comparador.id = -1;
    strcpy(comparador.ano, "-1");
    strcpy(comparador.mes, "-1");
    fwrite(&comparador, sizeof(Id_AnoMes), 1, arq);
    fclose(arq);
}


//=========================================Funçoes Busca====================================================//
TJ *BuscaPorId(char *raiz, int t, int id);

//===============Mais novo Mais Velho===============// Q1

TLSETJ *HL_Idade(char *raiz, int t){
    FILE *arq = fopen("Id_Idade.bin","rb+");
    if(!arq)exit(1);
    int aux;
    Id_Idade jogador, aux2;
    TLSETJ *resp = NULL;
    while(1){
        aux = fread(&jogador, sizeof(Id_Idade), 1, arq);
        if(aux != 1){ 
            printf("Nao ha jogadores ou leitura nao conseguiu ser feita!");
            return NULL;
        }
        if(jogador.id != -1)break;
    }
    TABM *novo = TABM_Busca(raiz,jogador.id, t);

    int i;
    for(i = 0; i<novo->nchaves; i++){
        if(novo->chave[i]->id == jogador.id)break;
    }
    resp = TLSETJ_insere(resp, novo->chave[i]);

    i = -1;
    while(1){
        aux = fread(&aux2, sizeof(Id_Idade), 1, arq);
        if(aux != 1) break;
        if(aux2.id != -1){
            jogador.id = aux2.id;
        }
    }
    


    fread(&jogador, sizeof(Id_Idade), 1, arq);
    novo = TABM_Busca(raiz,jogador.id, t);

    for(i = 0; i<novo->nchaves; i++){
        if(novo->chave[i]->id == jogador.id)break;
    }
    resp = TLSETJ_insere(resp, novo->chave[i]);

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
        if(jogador.id == -1)continue;

        TABM *novo = TABM_Busca(raiz,jogador.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }

        if(strcmp(posicao, novo->chave[i]->posicao) == 0){
            resp = TLSETJ_insere(resp, novo->chave[i]);
            break;
        }
        TABM_Libera_no(novo, t);
    }

    while (1){
        fseek(arq, pos*sizeof(Id_Idade), SEEK_END);
        aux = fread(&jogador, sizeof(Id_Idade), 1, arq);
        if(aux != 1){
            break;
        }
        if(jogador.id == -1){
            pos --;
            continue;
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
        TABM_Libera_no(novo, t);
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
        if(jogador.id == -1)continue;
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
        TABM_Libera_no(novo, t);
    }

    while (1){
        fseek(arq, pos*sizeof(Id_Idade), SEEK_END);
        
        aux = fread(&jogador, sizeof(Id_Idade), 1, arq);
        if(aux != 1){
            break;
        }
        if(jogador.id == -1){
            pos --;
            continue;
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
        TABM_Libera_no(novo, t);
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

    while(1){
        aux = fread(&jogador, sizeof(Id_Jogos), 1, arq);
        if(aux != 1){
            break;
        }
        if(jogador.id == -1)continue;

        TABM *novo = TABM_Busca(raiz,jogador.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }

        if(strcmp(selecao, novo->chave[i]->pais) == 0){
            resp = TLSETJ_insere(resp, novo->chave[i]);
            break;
            
        }
        TABM_Libera_no(novo, t);
    }

    while (1){
        fseek(arq, pos*sizeof(Id_Jogos), SEEK_END);
        aux = fread(&jogador, sizeof(Id_Jogos), 1, arq);
        if(aux != 1){
            break;
        }
        if(jogador.id == -1){
            pos --;
            continue;
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
        TABM_Libera_no(novo, t);
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
        if(jogador.id == -1)continue;

        TABM *novo = TABM_Busca(raiz,jogador.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }
        resp = TLSETJ_insere(resp, novo->chave[i]);
        break;    
        
        TABM_Libera_no(novo, t);
    }
    atuacao = -1;
    interac = 1;

    while (1){
        fseek(arq, pos*sizeof(Id_Jogos), SEEK_END);
        aux = fread(&jogador, sizeof(Id_Jogos), 1, arq);
        if(aux != 1){
            break;
        }
        if(jogador.id == -1){
            pos --;
            continue;
        }

        TABM *novo = TABM_Busca(raiz,jogador.id, t);

        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == jogador.id)break;
        }
        resp = TLSETJ_insere(resp, novo->chave[i]);
        break;

        pos --;
        TABM_Libera_no(novo, t);
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
        if(jogador.id == -1)continue;
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
        if(id_pais.id == -1)continue;

        TABM *novo = TABM_Busca(raiz, id_pais.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == id_pais.id)break;
        }
        if(strcmp(novo->chave[i]->pais_jogando, id_pais.pais) != 0){
            resp = TLSETJ_insere(resp, novo->chave[i]);
            continue;
        }

        TABM_Libera_no(novo, t);
    }
    fclose(arq);
    return resp;
}


TLSETJ *Jogadores_AtuamNaOrigem(char *raiz, int t){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq)exit(1);
    
    Id_Pais id_pais;
    int aux, i; 
    TLSETJ *resp = NULL;

    while(1){
        aux = fread(&id_pais, sizeof(Id_Pais), 1, arq);
        if(aux != 1)break;
        if(id_pais.id == -1)continue;

        TABM *novo = TABM_Busca(raiz, id_pais.id, t);
        for(i = 0; i<novo->nchaves; i++){
            if(novo->chave[i]->id == id_pais.id)break;
        }
        if(strcmp(novo->chave[i]->pais_jogando, id_pais.pais) == 0){
            resp = TLSETJ_insere(resp, novo->chave[i]);
            continue;
        }

        TABM_Libera_no(novo, t);
    }
    fclose(arq);
    return resp;
}

//===============Busca de jogadores que nasceram no mesmo mes===============// Q7
TLSETJ *JogadoresNasceramMesmoAno(char *raiz, int t, char *ano){
    FILE *fp = fopen("Id_AnoMes.bin", "rb");
    if (!fp) exit(1);

    Id_AnoMes idAnoMes;
    int aux;
    TLSETJ *resp = NULL;

    while(1){
        aux = fread(&idAnoMes, sizeof(Id_AnoMes), 1, fp);
        if (!aux) break;
        if (idAnoMes.id == -1) continue;

        if(strcmp(ano, idAnoMes.ano) == 0){
            TJ *novo = BuscaPorId(raiz, t, idAnoMes.id);
            resp = TLSETJ_insere(resp, novo);
        }
    }
    fclose(fp);
    return resp;
}

//===============Busca de jogadores que nasceram no mesmo mes===============// Q8
TLSETJ *JogadoresNasceramMesmoMes(char *raiz, int t, char *mes){
    FILE *fp = fopen("Id_AnoMes.bin", "rb");
    if (!fp) exit(1);

    Id_AnoMes idAnoMes;
    int aux;
    TLSETJ *resp = NULL;

    while(1){
        aux = fread(&idAnoMes, sizeof(Id_AnoMes), 1, fp);
        if (!aux) break;
        if (idAnoMes.id == -1) continue;

        if(strcmp(mes, idAnoMes.mes) == 0){
            TJ *novo = BuscaPorId(raiz, t, idAnoMes.id);
            resp = TLSETJ_insere(resp, novo);
        }
    }
    fclose(fp);
    return resp;
}

//===============Seleção com mais atuantes dentro/fora origem===============// Q9 e Q10               
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
        if(id_pais.id == -1)continue;

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
            // printf("%s", id_pais.pais);
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
        // printf("%i\n", qtdAtual);
        TABM_Libera_no(novo, t);
    }

    for(i = 0; i < qtdMaiorSelec; i++){
        printf("%s\n", maiorSelec[i]);
    }
    // printf("%d\n", qtdAtual);
    printf("\n");
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
        if(id_pais.id == -1)continue; 

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
            // printf("%s", id_pais.pais);
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
        // printf("%i\n", qtdAtual);
        TABM_Libera_no(novo, t);
    }

    for(i = 0; i < qtdMaiorSelec; i++){
        printf("%s\n", maiorSelec[i]);
    }
    // printf("%d\n", qtdAtual);
    printf("\n");
}

//===============Busca jogador por id===============// Q11

TJ *BuscaPorId(char *raiz, int t, int id){
    int i;
    TABM *no = TABM_Busca(raiz, id, t);
    if(!no){
        printf("Jogador nao encontrado\n");
        TABM_Libera_no(no, t);
        return NULL;
    }
    for(i = 0; i<no->nchaves; i++){
        if(no->chave[i]->id == id)break;
    }

    //Alocando jogador resposta;
    TJ *jogador_resp = (TJ *) malloc (sizeof(TJ));
    jogador_resp->id = no->chave[i]->id;
    jogador_resp->camisa = no->chave[i]->camisa;
    jogador_resp->jogos = no->chave[i]->jogos;
    jogador_resp->gols = no->chave[i]->gols;
    jogador_resp->idade = no->chave[i]->idade;
    strcpy(jogador_resp->data_nasc, no->chave[i]->data_nasc);
    strcpy(jogador_resp->nome, no->chave[i]->nome);
    strcpy(jogador_resp->pais, no->chave[i]->pais);
    strcpy(jogador_resp->pais_jogando, no->chave[i]->pais_jogando);
    strcpy(jogador_resp->posicao, no->chave[i]->posicao);
    strcpy(jogador_resp->time, no->chave[i]->time);

    TABM_Libera_no(no, t);
    return jogador_resp;
}


//===============Funçao auxiliar===============//
int isCaptain(char *nome){
    int len = strlen(nome);
    if(nome[len -1] == ')')return 1;
    return 0;
}


//===============Alteração da Informação de um Jogador===============// Q12
void AlteraJogador(char *raiz, int t){
    int n;
    do{
        printf("Digite o id do jogador que receberá alterações (-1 para sair): ");
        scanf("%d", &n);
        if (n <= 0) break;
        
        TABM *no_buscado = TABM_Busca(raiz, n, t);

        if (!no_buscado){
            printf("Jogador não encontrado!\n");
            continue;
        }

        int i = 0;
        while((i < no_buscado->nchaves) && (n > no_buscado->chave[i]->id)) i++;

        TJ *jogador = no_buscado->chave[i];

        printf("Menu de mudanças:\n");
        printf("Camisa - 1\n");
        printf("Idade - 2\n");
        printf("Jogos - 3\n");
        printf("Gols - 4\n");
        printf("Posição - 5\n");
        printf("País jogando - 6\n");
        printf("Time - 7\n");
        printf("Capitão - 8\n");
        printf("Sair - (-1)\n");

        do{
            int opcao;

            printf("\n");
            printf("Digite a mudança desejada: ");
            scanf("%d", &opcao);
            printf("\n");

            if (opcao == 1){
                int camisa;
                printf("Digite a nova camisa do jogador: ");
                scanf("%d", &camisa);
                
                jogador->camisa = camisa;
            }
            else if(opcao == 2){
                int idade;
                printf("Digite a nova idade do jogador: ");
                scanf("%d", &idade);

                jogador->idade = idade;
            }
            else if(opcao == 3){
                int jogos;
                printf("Digite a nova quantidade de jogos do jogador: ");
                scanf("%d", &jogos);
                
                jogador->jogos = jogos;
            }
            else if(opcao == 4){
                int gols;
                printf("Digite a nova quantidade de gols do jogador: ");
                scanf("%d", &gols);
                
                jogador->gols = gols;
                
            }
            else if(opcao == 5){
                char posicao[3];
                printf("Digite a nova posição do jogador: ");
                scanf("%s", posicao);

                strcpy(jogador->posicao, posicao);
            }
            else if(opcao == 6){
                char paisjogando[40];
                printf("Digite o novo país em que o jogador atua: ");
                scanf(" %[^\n]", paisjogando);

                strcpy(jogador->pais_jogando, paisjogando);
            }
            else if(opcao == 7){
                char time[40];
                printf("Digite o novo time em que o jogador atua: ");
                scanf(" %[^\n]", time);

                strcpy(jogador->time, time);
            }
            else if(opcao == 8){
                int op;
                if (isCaptain(jogador->nome)){
                    printf("O jogador é um capitão, deseja remover este título dele? (1 - SIM, 2 - SAIR)\n");
                    scanf("%d", &op);

                    if (op == 1){
                        int len = strlen(jogador->nome);
                        for(int j = 0; j < len; j++){
                            if (jogador->nome[j] == '('){
                                jogador->nome[j-1] = '\0';
                                break;
                            }
                        }
                    }
                }
                else{
                    printf("O jogador não é um capitão, deseja dar esse título para ele? (1 - SIM, 2 - SAIR)\n");
                    scanf("%d", &op);

                    if (op == 1){
                        char captain[12] = " (captain)";
                        strcat(jogador->nome, captain);
                    }
                }
            }
            else{
                no_buscado->chave[i] = jogador;

                char nome_atual[10];
                GeraNome(nome_atual, no_buscado->nome);

                escrita(nome_atual, no_buscado);
                printf("Alterações salvas!\n");

                printf("\nJogador pós-alterações:\n\n");
                printJogador(jogador);
                printf("\n");

                TABM_Libera_no(no_buscado, t);
                break;
            }
        }while(1);
    }while(1);
}




//===============Busca jogador por selecao===============// Q13

TLSETJ *BuscaPorSelecao(char *raiz, int t){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq) exit(1);

    char nome_selecao[40];
    printf("Digite o nome da seleção a ser buscada: ");
    scanf(" %[^\n]", nome_selecao);
    TLSETJ *resp = NULL;
    Id_Pais id_pais;
    int aux;

    while(1){
        aux = fread(&id_pais, sizeof(Id_Pais), 1, arq);
        if (aux != 1) break;
        if(id_pais.id == -1)continue;

        if (strcmp(nome_selecao, id_pais.pais) == 0){
            TJ *jogador_novo = BuscaPorId(raiz, t, id_pais.id);
            resp = TLSETJ_insere(resp, jogador_novo);
        }
    }
    if(!resp)printf("Seleção nao encontrada\n");
    return resp;
}

//===============Busca e remoção===============// Q14

void RemoveCaptain(char *raiz, int t){
    FILE *arq = fopen("Id_Pais.bin","rb+");
    if(!arq) exit(1);

    Id_Pais id_pais;
    int aux;


    while (1){
        aux = fread(&id_pais, sizeof(Id_Pais), 1, arq);
        if (aux != 1) break;
        if(id_pais.id == -1)continue;
        TJ *jogador = BuscaPorId(raiz, t, id_pais.id);
        if(isCaptain(jogador->nome)) {
            TABM_Retira(raiz, id_pais.id, t);
            removeId_Idade(id_pais.id);
            removeId_Jogo(id_pais.id);
            removeId_Pais(id_pais.id);
            }
    }
    
}

//===============Busca e remoção===============// Q15.1
void RemoveIdadeEspecifica(char *raiz, int t){
    FILE *arq = fopen("Id_Idade.bin","rb+");
    if(!arq) exit(1);

    Id_Idade id_idade;
    int aux, idade;

    printf("Digite a idade especifica a ser removida: \n");
    scanf("%i", &idade);

    while(1){
        aux = fread(&id_idade, sizeof(Id_Idade), 1, arq);
        if(aux != 1)break;;
        if(id_idade.id == -1)continue;
        if(id_idade.idade == idade){
            TABM_Retira(raiz, id_idade.id, t);
            removeId_Idade(id_idade.id);
            removeId_Jogo(id_idade.id);
            removeId_Pais(id_idade.id);
        }
        if(id_idade.idade > idade)return;
    }
    printf("Retirada completa.\n");
}

//===============Busca e remoção===============// Q15.2
void RemoveIdadeAcima(char *raiz, int t){
    FILE *arq = fopen("Id_Idade.bin","rb+");
    if(!arq) exit(1);

    Id_Idade id_idade;
    int aux, idade;

    printf("Digite a idade a ser removida (acima da escolhida): \n");
    scanf("%i", &idade);

    while(1){
        aux = fread(&id_idade, sizeof(Id_Idade), 1, arq);
        if(aux != 1)break;;
        if(id_idade.id == -1)continue;
        if(id_idade.idade >= idade){
            TABM_Retira(raiz, id_idade.id, t);
            removeId_Idade(id_idade.id);
            removeId_Jogo(id_idade.id);
            removeId_Pais(id_idade.id);
        }
    }
    printf("Retirada completa.\n");
    
}

//===============Retirada de jogadores de uma seleção que atuam num determinado país;===============// Q16
void RemoveAtuaEmDeterminadoPais(char *raiz, int t){
    FILE *fp = fopen("Id_Pais.bin", "rb");
    if (!fp) exit(1);
    char selecao[40];
    char pais[40];
    printf("Digite a seleção: ");
    scanf("%s", selecao);

    printf("Digite o determinado pais: ");
    scanf("%s", pais);
    Id_Pais id_pais;
    int r;

    while(1){
        r = fread(&id_pais, sizeof(Id_Pais), 1, fp);
        if (!r) break;
        if(id_pais.id == -1)continue;
        if(strcmp(selecao, id_pais.pais) == 0){
            TJ *jogador = BuscaPorId(raiz, t, id_pais.id);
            if(strcmp(pais, jogador->pais_jogando) == 0){
                TABM_Retira(raiz, id_pais.id, t);
                removeId_Idade(id_pais.id);
                removeId_Jogo(id_pais.id);
                removeId_Pais(id_pais.id);
                printf("Jogador com id %d removido!\n", id_pais.id);
            }
        }
    }
}

//===============Retirada de jogadores de uma seleção que não atuam no país de origem===============// Q17

void RemoveNaoAtuaOrigem(char *raiz, int t){
    FILE *fp = fopen("Id_Pais.bin", "rb");
    if (!fp) exit(1);
    char selecao[40];
    printf("Digite a seleção: ");
    scanf("%s", selecao);
    Id_Pais id_pais;
    int r;

    while(1){
        r = fread(&id_pais, sizeof(Id_Pais), 1, fp);
        if (!r) break;
        if(id_pais.id == -1)continue;
        if(strcmp(selecao, id_pais.pais) == 0){
            TJ *jogador = BuscaPorId(raiz, t, id_pais.id);
            if(strcmp(id_pais.pais, jogador->pais_jogando) != 0){
                TABM_Retira(raiz, id_pais.id, t);
                removeId_Idade(id_pais.id);
                removeId_Jogo(id_pais.id);
                removeId_Pais(id_pais.id);
                printf("Jogador com id %d removido!\n", id_pais.id);
            }
        }
    }
}

//===============Retirada de jogadores de uma seleção atuam no país de origem===============// Q18

void RemoveAtuaOrigem(char *raiz, int t){
    FILE *fp = fopen("Id_Pais.bin", "rb");
    if (!fp) exit(1);
    char selecao[40];
    printf("Digite a seleção: ");
    scanf("%s", selecao);
    Id_Pais id_pais;
    int r;

    while(1){
        r = fread(&id_pais, sizeof(Id_Pais), 1, fp);
        if (!r) break;
        if(id_pais.id == -1)continue;
        if(strcmp(selecao, id_pais.pais) == 0){
            TJ *jogador = BuscaPorId(raiz, t, id_pais.id);
            if(strcmp(id_pais.pais, jogador->pais_jogando) == 0){
                TABM_Retira(raiz, id_pais.id, t);
                removeId_Idade(id_pais.id);
                removeId_Jogo(id_pais.id);
                removeId_Pais(id_pais.id);
                printf("Jogador com id %d removido!\n", id_pais.id);
            }
        }
    }
}


//===============Remoção de todos os jogadores de uma seleção===============// Q19
void RemoveSelecao (char *raiz, int t){
    char nome_selecao[40];
    printf("Digite o nome da seleção a ser removida: ");
    scanf(" %[^\n]", nome_selecao);

    FILE *fp = fopen("Id_Pais.bin", "rb");
    if (!fp) exit(1);

    Id_Pais id_pais;
    int r;

    while(1){
        r = fread(&id_pais, sizeof(Id_Pais), 1, fp);
        if (!r) break;

        if (strcmp(nome_selecao, id_pais.pais) == 0){
            TABM_Retira(raiz, id_pais.id, t);
            removeId_Idade(id_pais.id);
            removeId_Jogo(id_pais.id);
            removeId_Pais(id_pais.id);
            printf("Jogador com id %d removido!\n", id_pais.id);
        }
    }
    printf("\n");
    printf("Seleção %s removida!\n", nome_selecao);    
}




//===============Remoção de Jogadores dado um conjunto contendo suas chaves primárias===============// Q20
void RemoveJogadoresConjunto (char *raiz, int t){
    int n;
    do{
        printf("Digite o id dos jogadores a serem removidos (-1 para sair): ");
        scanf("%d", &n);
        if (n <= 0) break;
        TABM_Retira(raiz, n, t);
        removeId_Idade(n);
        removeId_Jogo(n);
        removeId_Pais(n);
        printf("Jogador com id %d removido!\n", n);
    }while(1);
}



