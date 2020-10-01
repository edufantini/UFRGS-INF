#include <stdio.h>
#include <stdlib.h>
#include "jogadores.h"

#define MAX 1

int main()
{
    Jogadores j[MAX];
    int i, k = 1;

    atribui_dados(j, MAX);
    exibe_estatisticas(j, MAX);
    do
    {
        printf("\n\nInsira o numero do jogador que deseja saber se eh o bom (Para sair, entre 99.):");
        scanf("%d", &i);
        if (i == 99)
        {
            k = 0;
        }
        else
        {
            if (eh_o_bom(&j[i]))
            {
                printf("\n\n\tO jogador %s eh o bom!", j[i].nome);
            }
            else
            {
                printf("\n\n\tO jogador %s nao eh o bom!", j[i].nome);
            }
        }

    } while (k);

    return 0;
}