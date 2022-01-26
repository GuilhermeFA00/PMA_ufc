#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define saveNome_tam 21

/*
typedef struct{

}pokemon_corpo;

typedef struct{

}time;

typedef struct{

}inventario;

typedef struct{

}oponente;

typedef struct{

}mover;

typedef struct{

}pocao;
*/

void novoJogo(){
    FILE *pont_arq;
    pont_arq = fopen("save.txt", "a");
    char nomeDo_save[saveNome_tam];

    printf("Digite o nome do novo save\n");
    fflush(stdin);
    while(1){
        scanf("%s", nomeDo_save);
        int tamanho = strlen(nomeDo_save);

        if(tamanho > saveNome_tam){
            printf("O tamanho do nome do save não pode exceder %d", saveNome_tam);
        }else{
            break;
        }
    }

    printf("...Criando um novo save...\n");

    if(pont_arq == NULL){
        printf("Erro na criação");
    }else{
        printf("Criado!");
        fprintf(pont_arq, "%s", nomeDo_save);
    }

    fclose(pont_arq);
}

void carregarJogo(){
    FILE *pont_arq;
    pont_arq = fopen("save.txt", "r");
    char nomeDo_save[saveNome_tam];

    while(fgets(nomeDo_save, saveNome_tam, pont_arq) != NULL)printf("%s", nomeDo_save);

    fclose(pont_arq);
}

int main(){
    int resposta_do_jogador;
    FILE *pont_arq;
    pont_arq = fopen("save.txt", "r");

    printf("\nBem-vindo ao Pokémon Master Academy!!\n");
    printf("\t\t-----\n");
    printf("\t\t-----\n");
    printf("\t\tPMA\n");
    printf("\n\t\tMENU\n\n");

    printf("\t\tNOVO JOGO(1)\n");
    printf("\t\tCARREFAR JOGO(2)\n");
    //printf("\t\tCRÉDITOS(3)\n");//Função não confirmada pela a equipe
    printf("\t\tSAIR(0)\n");

    fflush(stdin);
    scanf("%d", &resposta_do_jogador);

    switch(resposta_do_jogador){
        case 1:
            printf("\n...");
            if(pont_arq = fopen("save.txt", "r")){
                int novo_jogo;

                fclose(pont_arq);
                printf("\n\t->JÁ EXISTE UM SAVE DO JOGO,DESEJA SOBRESCREVER?LEMBRE,VOCÊ PERDERÁ TODO O SEU PROGRESSO\n");
                printf("\tDigite '1' para sobrescrever e começar um novo jogo\n");
                printf("\tDigite qualquer tecla para cancelar\n");
                fflush(stdin);
                scanf("%d", &novo_jogo);

                novo_jogo == 1 ? novoJogo() : printf("Cancelar\n");
                break;
            }else{
                printf("...A aventura começa\n\n");
                novoJogo();
            }
            break;
        case 2:
            printf("\n...");
            if(pont_arq = fopen("save.txt", "r")){
                printf("...carregando\n");
                carregarJogo();
            }else{
                printf("___Não há nenhum jogo salvo___\n");
            }
            break;
        case 0:
            printf("...   ...");
            break;
        default:
            printf("Erro");
    }
    return 0;
}
