#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linker.h"

#define saveNome_tam 21
#define pokNome_tam 41
#define opNome_tam 21

typedef struct mover{
    char nome[31];
    int status;
}MOVER;

typedef struct pokemon{
    char *pokNome;
    int ataque;
    int vida;
    int velocidade;

    struct pokemon *prox;
    struct pokemon *ant;
}POKEMON;

typedef struct pocao{
    char *nome;
    int status;
    int valor;

    struct pocao *prox_item;
}POCAO;

typedef struct time{
    POKEMON *pk;

    struct time* prox_pok;
}TIME;

typedef struct oponente{
    char nome[opNome_tam];
    TIME;

    struct openente* prox_op;
}OPENENTE;

POKEMON *inicio = NULL;
TIME *inicio_time = NULL;
POCAO *inicio_inv = NULL;
int listaPoks_tam = 0;
int listaItens_tam = 0;
int pokecoins;
FILE *pokecoins_arq;

char* removerItem(int pos){
    if(pos >= 0 && listaItens_tam > 0){
        POCAO *lixo;
        char *itemDescartado;
        if(pos == 0){
            lixo = inicio_inv;
            inicio_inv = inicio_inv->prox_item;
        }else{
            POCAO *aux = inicio_inv;
            int i;
            for(i =0; i < pos -1; i++){
                aux = aux->prox_item;
            }
            lixo = aux->prox_item;
            aux->prox_item = aux->prox_item->prox_item;
        }
        itemDescartado = lixo->nome;
        free(lixo);
        listaPoks_tam--;
        return itemDescartado;
    }
}

void inventarioPessoal(char *itemNome, int itemStatus, int itemValor){
    POCAO *novoItem = malloc(sizeof(POCAO));
    novoItem->nome = itemNome;
    novoItem->status = itemStatus;
    novoItem->valor = itemValor;
    novoItem->prox_item = NULL;

    if(inicio_inv == NULL){
        inicio_inv = novoItem;
    }else{
        novoItem->prox_item = inicio_inv;
        inicio_inv = novoItem;
    }
    listaItens_tam++;
}

void listaPok(char *nome, int vel, int atk, int vida, int pos){
    POKEMON *novo = malloc (sizeof (POKEMON));
    novo->pokNome = nome;
    novo->ataque = atk;
    novo->velocidade = vel;
    novo->vida = vida;
    novo->prox = NULL;
    novo->ant = NULL;

    if(listaPoks_tam == 0 && pos == 0){
        inicio = novo;
        listaPoks_tam++;
    }else if(pos == 0){
        novo->prox = inicio;
        inicio->ant = novo;
        inicio = novo;
        listaPoks_tam++;
    }else if( pos > 0 && pos <= listaPoks_tam){
        if(pos == listaPoks_tam) {
            POKEMON *aux = inicio;
            while(aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novo;
            novo->ant = aux;
            aux = novo;
            listaPoks_tam++;
        }
        else{
            POKEMON *aux = inicio;
            int i;
            for(i = 0; i < pos; i++) {
                aux = aux->prox;
            }
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
            listaPoks_tam++;
        }
    }else{
    printf("insercao invalida! :/");
    }
}

POKEMON* buscaPoks(int esc) {
    POKEMON *aux = inicio;
    while(aux != NULL){
        for(int i = 0; i < esc; i++){
            aux = aux->prox;
        }
        printf("%s, o escolhido é você\n", aux->pokNome);
        return aux;
    }
    printf("Esse pokémon não está na lista!");
    return inicio;
}

POCAO* buscarItem(int esc){
    POCAO *aux = inicio_inv;
    while(aux != NULL){
        for(int i = 0; i < esc; i++){
            aux = aux->prox_item;
        }
        printf("Você utilizou uma %s\n", aux->nome);
        return aux;
    }
    printf("Comando inválido\n");
    return inicio_inv;
}

void formacao_time() {
    int escolha;

    TIME * novoPok = malloc(sizeof(TIME));
    novoPok->prox_pok = NULL;

    listaPok("Charmander", 6, 20, 45, 0);
    listaPok("Squirtle", 9, 16, 43, 1);
    listaPok("Bulbassaur", 5, 28, 56, 2);

    printf("\nDigite o ID do Pokémon que voçê quer no seu time\n");
    scanf("%d", &escolha);

    novoPok->pk = buscaPoks(escolha);

    if(inicio_time == NULL){
        inicio_time = novoPok;
    }else{
        novoPok->prox_pok = inicio_time;
        inicio_time = novoPok;
    }
}

void verTime(){
    TIME *ponteiro = inicio_time;
    printf("| ");
    while(ponteiro != NULL) {
        printf("%s-", ponteiro->pk->pokNome);
        ponteiro = ponteiro->prox_pok;
    }
    printf(" |");
}

int verSaldo(){
    pokecoins_arq = fopen("saldo.bin", "rb");

    fread(&pokecoins, sizeof(int), 1, pokecoins_arq);

    fclose(pokecoins_arq);

    return pokecoins;
}

void comprar(int valor){
    pokecoins_arq = fopen("saldo.bin", "wb+");

    pokecoins = pokecoins - valor;

    fwrite(&pokecoins, sizeof(int), 1, pokecoins_arq);

    fclose(pokecoins_arq);
}

void vender(valor) {
    int escolhaDo_jogador;
    printf("Qual item você quer vender?\n");
    scanf("%d", &escolhaDo_jogador);
    printf("O item %s foi vendido!", removerItem(escolhaDo_jogador));

    pokecoins_arq = fopen("saldo.bin", "wb+");

    pokecoins = pokecoins + valor;

    fwrite(&pokecoins, sizeof(int), 1, pokecoins_arq);

    fclose(pokecoins_arq);
}

void pokemarket(){
    int escolhaDo_jogador;

    printf("Seja bem-vindo aventureiro! O que deseja comprar? \n");

    POCAO smp;
    POCAO sp;
    POCAO hp;

    smp.nome = "SmallPotion";
    smp.status = 30;
    smp.valor = 40;

    sp.nome = "SuperPotion";
    sp.status = 50;
    sp.valor = 60;

    hp.nome = "HyperPotion";
    hp.status = 70;
    hp.valor = 80;

    printf("**NO ESTOQUE**\n"
           "[%s]--Valor(1): %d\n"
           "[%s]--Valor(2): %d\n"
           "[%s]--Valor(3): %d\n"
           "(4) para vender item", smp.nome, smp.valor, sp.nome, sp.valor, hp.nome, hp.valor);
    printf("\nDigite 0, se quiser sair da loja!\n");

    do{
        printf("->:  ");
        scanf("%d", &escolhaDo_jogador);

        switch(escolhaDo_jogador){
        case 1:
            if(pokecoins < smp.valor){
                printf("Você não tem coins suficientes");
            }else{
                comprar(smp.valor);
                inventarioPessoal(smp.nome, smp.status, smp.valor);
            }
            break;
        case 2:
            if(pokecoins < sp.valor){
                printf("Você não tem coins suficientes");
            }else{
                comprar(sp.valor);
                inventarioPessoal(sp.nome, sp.status, sp.valor);
            }
            break;
        case 3:
            if(pokecoins < hp.valor){
                printf("Você não tem coins suficientes");
            }else{
                comprar(hp.valor);
                inventarioPessoal(hp.nome, hp.status, hp.valor);
            }
            break;
        case 4:
            vender();
        }
    }while(escolhaDo_jogador != 0);
}

void verItens(){
    int i = 1;
    POCAO *ponteiro = inicio_inv;
    printf("| ");
    while(ponteiro != NULL) {
        printf("%s(Digite %d para usar)-", ponteiro->nome, i);
        ponteiro = ponteiro->prox_item;
        i++;
    }
    printf(" |");
}

void menu(){
    int respostaDo_jogador;

    printf("\n\t\t MENU \n");

    do{
        printf("\n\n\tDigite '1' para acessar  sua backpack\n"
               "\tDigite '2' para ver a loja\n"
               "\tDigite '3' para ver seu time\n"
               "\tDigite '4' para ver seu saldo\n"
               "\tDigite '5' para batalhar\n"
               "\tDigite '0' para sair\n");
        scanf("%d", &respostaDo_jogador);

        switch(respostaDo_jogador){
        case 1:
            verItens();
            break;
        case 2:
            pokemarket();
            break;
        case 3:
            verTime();
            break;
        case 4:
            printf("Seu saldo atual é de |%d|", verSaldo());
            break;
        case 5:
            break;
        case 0:
            break;
        default:
            printf("Comando inválido\n");
            break;
        }
    }while(respostaDo_jogador != 0);
}



void novoJogo(){
    int pokecoins_iniciais = 200;
    FILE *pont_arq;
    FILE *pont_arq_bd;
    pokecoins_arq = fopen("saldo.bin", "wb+");

    pont_arq = fopen("save.txt", "w");
    char nomeJogador[saveNome_tam];

    printf("Digite seu nome, aventureiro\n");
    fflush(stdin);
    while(1){
        scanf("%sSAVE", nomeJogador);
        int tamanho = strlen(nomeJogador);

        if(tamanho > saveNome_tam){
            printf("O tamanho do nome não pode exceder %d", saveNome_tam);
        }else{
            break;
        }
    }

    printf("...Criando um novo save...\n");

    if(pont_arq == NULL){
        printf("Erro na criação\n");
    }else{
        printf("Criado!\n");
        fprintf(pont_arq, "%s", nomeJogador);
    }

    fclose(pont_arq);

    printf("Criando a base de dados...\n");
    pont_arq_bd = fopen("data.bin", "wb");

    if((pont_arq_bd = fopen("data.bin", "rb")) == NULL){
        printf("Erro na criação de base de dados");
        exit(1);
    }

    printf("BASE DE DADOS CRIADA\n");
    fclose(pont_arq_bd);

    /*
    CHAMAR DENTRO DA BATALHA
    printf("Forme seu time!\n");
    printf("Veja lista de Pokémons disponíveis\n");

    printf("\t\tCharmander (ID=0)\n"
           "\t\tSquirtle (ID=1)\n"
           "\t\tBulbasaur (ID=2)\n");

    printf("Escolha seus companheiros de batalha\n");
    for(int i; i < 3; i++){
        formacao_time();
    }*/

    printf("Bom, é sempre bom uma ajuda para começar...$$$$$TOME 200 POKECOINS!!\n");
    fwrite(&pokecoins_iniciais, sizeof(int), 1, pokecoins_arq);

    fclose(pokecoins_arq);

    menu();
}


void carregarJogo(){
    FILE *pont_arq;
    pont_arq = fopen("save.txt", "r");
    char nomeJogador[saveNome_tam];

    fgets(nomeJogador, saveNome_tam, pont_arq);

    printf("Estado do save '%sSAVE' carregado com sucesso", nomeJogador);
    printf("...");

    fclose(pont_arq);

    menu();
}
