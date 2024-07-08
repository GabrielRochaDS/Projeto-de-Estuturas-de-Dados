//#include "TABM.c"   
#include "FuncaoAuxiliares.c"

void MenuBusca(){
    printf("\n");
    printf("======================================================================================================================");
    printf("\n");
    printf("Menu da funções de busca da árvore:\n");
    printf("\n");
    printf("Busca de um jogador por ID - 1\n");
    printf("Jogador mais novo e mais velho da competição - 2\n");
    printf("Jogador mais novo e mais velho por seleção - 3\n");
    printf("Jogador mais novo e mais velho por posição - 4\n");
    printf("Jogadores que mais e menos atuaram por equipe - 5\n");
    printf("Jogadores que mais e menos atuaram na competição: - 6\n");
    printf("Menor e maior seleção da competição - 7\n");
    printf("Jogares que atuam fora do seu país de origem - 8\n");
    printf("Jogadores que atuam no seu país de origem - 9\n");
    printf("Jogadores que nasceram no mesmo ano - 10\n");
    printf("Jogadores que nasceram no mesmo mês - 11\n");
    printf("Seleção com mais jogadores que atuam fora do seu país de origem - 12\n");
    printf("Seleção com mais jogadores que atuam no seus país de origem - 13\n");
    printf("Todos os jogadores de uma seleção - 14\n");
    printf("Todos os jogadores que são capitães - 15\n");
    printf("Sair - (-1)\n");
    printf("\n");
    printf("======================================================================================================================\n");
    printf("\n");
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
int preencherJogador(char *arquivo, char *raiz, int t){
    TLSE *linhas = linhasPais(arquivo);
    FILE *fp  = fopen(arquivo, "r");

    //==============Funções Auxiliares iniciando==============//
    Id_Idade *idIdade = (Id_Idade *) malloc (sizeof(Id_Idade));
    Id_Jogos *idJogos = (Id_Jogos *) malloc (sizeof(Id_Jogos));
    Id_Pais *idPais = (Id_Pais *) malloc (sizeof(Id_Pais));
    Id_AnoMes *idAnoMes = (Id_AnoMes *) malloc (sizeof(Id_AnoMes));

    
    
    //==============Alocando TJ==============//
    TJ *jogador_alocado = (TJ *) malloc (sizeof(TJ));
    TJ jogador;
    char pais[30];
    int a = 1, i = 0;
    int corrente = 0;

    //==============Loop le todo EURO.txt==============//
    while(1 && i<1000){
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

            idAnoMes->id = jogador.id;
            int len = strlen(jogador.data_nasc) - 2;

            int h, inicio_mes = -1, fim_mes = 0;
            for(h = 0; h < len ; h++){
                if (jogador.data_nasc[h] == ' '){
                    if (inicio_mes == -1) inicio_mes = h;
                    else fim_mes = h;
                }
                
            }

            strncpy(idAnoMes->mes, jogador.data_nasc+(inicio_mes+1), fim_mes - inicio_mes - 1);
            idAnoMes->mes[fim_mes - inicio_mes - 1] = '\0';
            strcpy(idAnoMes->ano, jogador.data_nasc+(len - 3));
            idAnoMes->ano[4] = '\0';

            insertId_AnoMes(idAnoMes, i);

        }
        i++;
    }
    free(idIdade);
    free(idJogos);
    free(idPais);
    free(idAnoMes);


    printf("\n");
    return corrente;
    
}

int main(void){

    char raiz[9] = "raiz.bin";
    FILE *fp = fopen(raiz, "wb");
    if (!fp) exit(1);
    int num = -1;
    fwrite(&num, sizeof(int), 1, fp);
    fclose(fp);
    int t, n;

    printf("Digite o grau 't' da árvore (grau menor que 2 será setado como 2): ");
    scanf("%d", &t);
    
    if (t < 2) t = 2;

    int corrente = preencherJogador("EURO.txt", raiz, t);

    printf("Folhas:\n");
    TABM_Imprime_ids(raiz, t);

    do{
        printf("\n");
        printf("======================================================================================================================");
        printf("\n");
        printf("Menu da Árvore criada com os jogadores presentes em 'EURO.txt':\n");
        printf("\n");
        printf("Inserção de um novo jogador - 1\n");
        printf("Funções de busca - 2\n");
        printf("Funções de remoção - 3\n");
        printf("Alteração de um jogador - 4\n");
        printf("Sair - (-1)\n");
        printf("\n");
        printf("======================================================================================================================\n");
        printf("\n");

        printf("Digite o número da opção desejada do menu principal: ");
        scanf("%d", &n);
        printf("\n");
        
        if (n == 1){
            TJ *novo = (TJ*) malloc (sizeof(TJ));

            printf("Id do jogador: ");
            int num;
            scanf("%d", &num);
            novo->id = num;

            TABM *verifica = TABM_Busca(raiz, num, t);
            if (verifica){
                printf("\nJogador já se encontra na árvore!\n");
                TABM_Libera_no(verifica, t);
                free(novo);
            }

            printf("Nome do jogador: ");
            char nome[40];
            scanf(" %[^\n]", nome);
            strcpy(novo->nome, nome);

            printf("Camisa do jogador: ");
            int camisa;
            scanf("%d", &camisa);
            novo->camisa = camisa;

            printf("Idade do jogador: ");
            int idade;
            scanf("%d", &idade);
            novo->idade = idade;

            printf("Quantidade de jogos do jogador: ");
            int jogos;
            scanf("%d", &jogos);
            novo->jogos = jogos;

            printf("Quantidade de gols do jogador: ");
            int gols;
            scanf("%d", &gols);
            novo->gols = gols;

            printf("Posição do jogador: ");
            char posicao[3];
            scanf(" %[^\n]", posicao);
            strcpy(novo->posicao, posicao);

            printf("Data de nascimento do jogador (Formato - dia mês por extenso ano): ");
            char data_nasc[40];
            scanf(" %[^\n]", data_nasc);
            strcpy(novo->data_nasc, data_nasc);

            printf("País de origem do jogador: ");
            char pais[40];
            scanf(" %[^\n]", pais);
            strcpy(novo->pais, pais);

            printf("Pais em que o jogador atua: ");
            char pais_jogando[40];
            scanf(" %[^\n]", pais_jogando);
            strcpy(novo->pais_jogando, pais_jogando);

            printf("Time em que o jogador atua: ");
            char time[40];
            scanf(" %[^\n]", time);
            strcpy(novo->time, time);

            printf("\n");
            printJogador(novo);
            printf("\n");

            Id_Idade *jogadoridade = (Id_Idade *) malloc (sizeof(Id_Idade));
            Id_Jogos *jogadorjogos = (Id_Jogos *) malloc (sizeof(Id_Jogos));
            Id_Pais *jogadorpais = (Id_Pais *) malloc (sizeof(Id_Pais));
            Id_AnoMes *jogadoranomes = (Id_AnoMes *) malloc (sizeof(Id_AnoMes));

            jogadoridade->id = novo->id;
            jogadoridade->idade = novo->idade;
            insertId_Idade(jogadoridade, 2);
            
            jogadorjogos->id = novo->id;
            jogadorjogos->jogos = novo->jogos;
            insertId_Jogos(jogadorjogos, 2);
            
            jogadorpais->id = novo->id;
            strcpy(jogadorpais->pais, novo->pais);
            insertId_Pais(jogadorpais, 2);

            jogadoranomes->id = novo->id;
            int len = strlen(novo->data_nasc) - 2;

            int g, inicio_mes = -1, fim_mes = 0;
            for(g = 0; g < len ; g++){
                if (novo->data_nasc[g] == ' '){
                    if (inicio_mes == -1) inicio_mes = g;
                    else fim_mes = g;
                }

            }

            strncpy(jogadoranomes->mes, novo->data_nasc+(inicio_mes+1), fim_mes - inicio_mes - 1);
            jogadoranomes->mes[fim_mes - inicio_mes - 1] = '\0';
            strcpy(jogadoranomes->ano, novo->data_nasc+(len - 2));
            jogadoranomes->ano[4] = '\0';

            insertId_AnoMes(jogadoranomes, 2);

            free(jogadoridade);
            free(jogadorjogos);
            free(jogadorpais);
            free(jogadoranomes);

            TABM_Insere(raiz, novo, t, &corrente);
            
        }
        else if(n == 2){
            int n2;

            MenuBusca();

            do{
                printf("Digite o número da opção desejada do menu de busca (-2 para rever o menu): ");
                scanf("%d", &n2);
                printf("\n");

                if (n2 == 1){
                    printf("Digite o ID do jogador buscado: ");
                    int id;
                    scanf("%d", &id);
                    TJ *jogador = BuscaPorId(raiz, t, id);
                    printf("\n");
                    printf("Informações do jogador buscado:");
                    printf("\n");
                    printJogador(jogador);
                    printf("\n");
                    free(jogador);
                }
                else if(n2 == 2){
                    TLSETJ *hlidade = HL_Idade(raiz, t);
                    printf("\n");
                    printf("Jogadores com maior e menor idade na competição:\n\n");
                    TLSETJ_imprime(hlidade);
                    TLSETJ_libera(hlidade);
                }
                else if(n2 == 3){  //SCANF
                    printf("Digite a seleção dos jogadores a serem buscados: ");
                    char selecao[40];
                    scanf(" %[^\n]", selecao);
                    TLSETJ *hlidadeselecao = HL_IdadeSelecao(raiz, selecao, t);
                    printf("\n");
                    printf("Jogadores com maior e menor idade na seleção %39s:\n\n", selecao);
                    TLSETJ_imprime(hlidadeselecao);
                    TLSETJ_libera(hlidadeselecao);
                }
                else if(n2 == 4){
                    printf("Digite a posição dos jogadores a serem buscados: ");
                    char posicao[3];
                    scanf(" %s", posicao);
                    TLSETJ *hlidadeposicao = HL_IdadePosicao(raiz, posicao, t);
                    printf("\n");
                    printf("Jogadores com maior e menor idade na posição %s:\n\n", posicao);
                    TLSETJ_imprime(hlidadeposicao);
                    TLSETJ_libera(hlidadeposicao);
                }
                else if(n2 == 5){
                    printf("Digite a seleção dos jogadores que mais atuaram a serem buscados: ");
                    char selecao[40];
                    scanf(" %[^\n]", selecao);
                    printf("Passou");
                    TLSETJ *hlatuacaoselecao = HL_AtuacaoSelecao(raiz, selecao, t);
                    printf("\n");
                    printf("Jogadores que mais atuaram na seleção %s:\n\n", selecao);
                    TLSETJ_imprime(hlatuacaoselecao);
                    TLSETJ_libera(hlatuacaoselecao);
                }
                else if(n2 == 6){
                    TLSETJ *hlatuacao = HL_Atuacao(raiz, t);
                    printf("\n");
                    printf("Jogadores que mais e menos atuaram na competição:\n\n");
                    TLSETJ_imprime(hlatuacao);
                    TLSETJ_libera(hlatuacao);
                }
                else if(n2 == 7){
                    HL_QtdSelecao();
                }
                else if(n2 == 8){
                    TLSETJ *jogadoresfora = Jogadores_AtuamFora(raiz, t);
                    printf("\n");
                    printf("Jogadores que atuam fora do seu país de origem:\n\n");
                    TLSETJ_imprime(jogadoresfora);
                    TLSETJ_libera(jogadoresfora);
                }
                else if(n2 == 9){
                    TLSETJ *jogadoresdentro = Jogadores_AtuamNaOrigem(raiz, t);
                    printf("\n");
                    printf("Jogadores que atuam no seu país de origem:\n\n");
                    TLSETJ_imprime(jogadoresdentro);
                    TLSETJ_libera(jogadoresdentro);
                }
                else if(n2 == 10){
                    printf("Digite o ano de nascimento dos jogadores a serem buscados: ");
                    char ano[5];
                    scanf(" %s", ano);
                    TLSETJ *jogadoresano = JogadoresNasceramMesmoAno(raiz, t, ano);
                    printf("\n");
                    printf("Jogadores que nasceram no ano de %s:\n\n", ano);
                    TLSETJ_imprime(jogadoresano);
                    //TLSETJ_libera(jogadoresano);
                }
                else if(n2 == 11){ //LIBERANDO ERRADO
                    printf("Digite o mês de nascimento dos jogadores a serem buscados: ");
                    char mes[15];
                    scanf(" %s", mes);
                    TLSETJ *jogadoresmes = JogadoresNasceramMesmoMes(raiz, t, mes);
                    printf("\n");
                    printf("Jogadores que nasceram no mês de %s:\n\n", mes);
                    TLSETJ_imprime(jogadoresmes);
                    //TLSETJ_libera(jogadoresmes);
                }
                else if(n2 == 12){
                    //VERIFICAR SE IMPRIME MENOR TAMBÉM
                    printf("\n");
                    printf("Seleção com mais jogadores jogando fora do país de origem:\n\n");
                    PrintSelecoesComMaisFora(raiz, t);
                }
                else if(n2 == 13){
                    //VERIFICAR SE IMPRIME MENOR TAMBÉM
                    printf("\n");
                    printf("Seleção com mais jogadores jogando em seu país de origem:\n\n");
                    PrintSelecoesComMaisDentro(raiz, t);
                }
                else if(n2 == 14){
                    TLSETJ *jogadoresselecao = BuscaPorSelecao(raiz, t);
                    printf("\n");
                    printf("Jogadores da seleção escolhida:\n\n");
                    TLSETJ_imprime(jogadoresselecao);
                    //TLSETJ_libera(jogadoresselecao);
                }
                else if(n2 == 15){
                    
                }
                else if(n2 == -2){
                    MenuBusca();
                }
                else break;
            }while(1);
        }
        else if(n == 3){
            int n3;
            do{
                printf("\n");
                printf("======================================================================================================================");
                printf("\n");
                printf("Menu da funções de remoção da árvore:\n");
                printf("\n");
                printf("Remoção de jogadores por ID - 1\n");
                printf("Remoção de jogadores de uma determinada idade - 2\n");
                printf("Remoção de jogadores a partir de uma determinada idade para acima dela - 3\n");
                printf("Retirada de todos os jogadores de uma seleção que atuam num determinado país - 4\n");
                printf("Retirada de todos os os jogadores de uma seleção que não atuam no país de origem - 5\n");
                printf("Retirada de todos os os jogadores de uma seleção atuam no país de origem - 6\n");
                printf("Retirada de todos os os jogadores de uma seleção - 7\n");
                printf("Remoção de todos os capitães - 8\n");
                printf("Sair - (-1)\n");
                printf("\n");
                printf("======================================================================================================================\n");
                printf("\n");

                printf("Digite o número da opção desejada do menu de remoção: ");
                scanf("%d", &n3);
                printf("\n");

                if (n3 == 1){
                    RemoveJogadoresConjunto(raiz, t);
                }
                else if (n3 == 2){
                    RemoveIdadeEspecifica(raiz, t);
                    printf("\n");
                    printf("Idades Atualizadas:\n\n");
                    printId_Idade();
                }
                else if (n3 == 3){  //PROBLEMA REMOÇÃO
                    RemoveIdadeAcima(raiz, t);
                    printf("\n");
                    printf("Idades Atualizadas:\n\n");
                    printId_Idade();
                }
                else if (n3 == 4){
                    RemoveAtuaEmDeterminadoPais(raiz, t);
                    printf("Id e Países após remoção:\n\n");
                    printId_Pais();
                }
                else if (n3 == 5){
                    RemoveNaoAtuaOrigem(raiz, t);
                    printf("Id e Países após remoção:\n\n");
                    printId_Pais();
                }
                else if (n3 == 6){
                    RemoveAtuaOrigem(raiz, t);
                    printf("Id e Países após remoção:\n\n");
                    printId_Pais();
                }
                else if (n3 == 7){  //PROBLEMA SCANF
                    RemoveSelecao(raiz, t);
                    printf("Id e Países após remoção:\n\n");
                    printId_Pais();
                }
                else if (n3 == 8){  //
                    RemoveCaptain(raiz, t);
                }
                else break;
            }while(1);
        }
        else if(n == 4){
            AlteraJogador(raiz, t);
        }
        else break;
    }while(1);


    return 0;
}