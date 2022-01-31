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
    char nome[31];
    int status;
    int valor;
}POCAO;

typedef struct time{
    POKEMON;

    struct time* prox_pok;
}TIME;

typedef struct inventario{
    POCAO;

    struct inventario* prox_item;
}INVENTARIO;

typedef struct oponente{
    char nome[opNome_tam];
    TIME;

    struct openente* prox_op;
}OPENENTE;

POKEMON *inicio = NULL;
int tam = 0;

void listaPok(char *nome, int vel, int atk, int vida, int pos){
    POKEMON *novo = malloc (sizeof (POKEMON));
    novo->pokNome = nome;
    novo->ataque = atk;
    novo->velocidade = vel;
    novo->vida = vida;
    novo->prox = NULL;
    novo->ant = NULL;

    if(tam == 0 && pos == 0){
        inicio = novo;
        tam++;
    }else if(pos == 0){
        novo->prox = inicio;
        inicio->ant = novo;
        inicio = novo;
        tam++;
    }else if( pos > 0 && pos <= tam){
        if(pos == tam) {
            POKEMON *aux = inicio;
            while(aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novo;
            novo->ant = aux;
            aux = novo;
            tam++;
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
            tam++;
        }
    }else{
    printf("insercao invalida! :/");
    }
}

void imprimir(POKEMON *inicio){
    POKEMON *ponteiro = inicio;
    printf("[ ");
    while(ponteiro != NULL) {
        printf("(%s),", ponteiro->pokNome);
        ponteiro = ponteiro->prox;
    }
    printf(" ]");
}

void formacao_time() {

    listaPok("Charmander", 6, 20, 45, 0);
    listaPok("Squirtle", 9, 16, 43, 1);
    listaPok("Bulbassaur", 5, 28, 56, 2);

    printf("Forme seu time!\n");

    printf("Veja lista de Pokémons disponíveis\n");

    imprimir(inicio);
}

/*
int saldo() {
    FILE* pont_arq;
    int pokekoins = pokekoins + comprar();

    if((pont_arq = fopen("data.bin", "rb+")) == NULL){
        printf("Erro na leitura!\n");
        exit(1);
    }

    fwrite(&pokekoins, sizeof(int), 1, pont_arq);

    rewind(pont_arq);

    fread(&pokekoins, sizeof(int), 1, pont_arq);

    fclose(pont_arq);

    return pokekoins;
}

void verItens();

int comprar(int valor){
    return valor;
}

int vender(int valor);

void loja(){
    int escolhaDo_jogador;

    POCAO smallPotion;
    POCAO superPotion;
    POCAO hyperPotion;

    smallPotion.status = 20;
    smallPotion.valor = 30;

    superPotion.status = 50;
    superPotion.valor = 50;

    hyperPotion.status = 100;
    hyperPotion.valor = 70;

    do{
        printf("SP('1')-%d\n"
               "SUP('2')-%d\n"
               "HP('3')-%d\n"
               "'0' para sair da loja", smallPotion.valor,
                                        superPotion.valor,
                                        hyperPotion.valor);
        scanf("%d", &escolhaDo_jogador);

        switch(escolhaDo_jogador){
        case 1:
            comprar(smallPotion.valor);
            break;
        case 2:
            comprar(superPotion.valor);
            break;
        case 3:
            comprar(hyperPotion.valor);
            break;
        case 0:
            break;
        default:
            printf("Digite algo válido\n");
            break;
        }
    }while(escolhaDo_jogador != 0);
}
*/



void menu(){
    int respostaDo_jogador;

    printf("\n\t\t MENU \n");

    do{
        printf("\tDigite '1' para acessar  sua backpack\n"
               "\tDigite '2' para ver a loja\n"
               "\tDigite '3' para ver seu time\n"
               "\tDigite '4' para ver seu saldo\n"
               "\tDigite '5' para batalhar\n"
               "\tDigite '0' para sair\n");
        scanf("%d", &respostaDo_jogador);

        switch(respostaDo_jogador){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
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
    FILE *pont_arq;
    FILE *pont_arq_bd;
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

    formacao_time();

    menu();
}
