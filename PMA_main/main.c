#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linker.h"

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
                printf("\n\t->JÁ EXISTE UM SAVE DO JOGO,DESEJA SOBRESCREVER?LEMBRE,VOCÊ PERDERÁ TODO O SEU PROGRESSO E SEUS DADOS\n");
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
