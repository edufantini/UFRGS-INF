#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogadores.h"

/*
        Atribui Dados
        -------------    
    Funcao para insercao de dados no array.
*/

void atribui_dados(Jogadores *j, int k)
{
    int i;
    for (i = 0; i <= k; i++)
    {
        printf("\n\n[*]Dados do jogador (%d)", i);
        printf("\n\tInsira o nome:");
        scanf("%s", j[i].nome);
        printf("\n\tInsira a idade:");
        scanf("%d", &j[i].idade);
        printf("\n\tInsira o numero de gols:");
        scanf("%d", &j[i].num_gols);
        printf("\n\tInsira o numero de faltas:");
        scanf("%d", &j[i].num_faltas);
        printf("\n\tInsira o numero de passes errados:");
        scanf("%d", &j[i].num_passes_errados);
        printf("\n\tInsira o numero de passes corretos:");
        scanf("%d", &j[i].num_passes_corretos);
    }
    printf("\n\n");
    for (i = 0; i <= 60; i++)
    {
        printf("=");
    }
}

/* 
        Exibe Estatisticas
        ------------------
    Funcao para exibir as estatisticas de
    todos os jogadores do array.

 */

void exibe_estatisticas(Jogadores *j, int k)
{
    int i;
    for (i = 0; i <= k; i++)
    {
        printf("\n\n\n[*]Estatísticas do Jogador %s (%d):", j[i].nome, i);
        printf("\n\tNumero de gols: %d", j[i].num_gols);
        printf("\n\tNumero de faltas: %d", j[i].num_faltas);
        printf("\n\tNumero de passes errados: %d", j[i].num_passes_errados);
        printf("\n\tNumero de passes corretos: %d", j[i].num_passes_corretos);
    }
    printf("\n\n");
    for (i = 0; i <= 60; i++)
    {
        printf("=");
    }
}

/* 
        Eh O Bom
        --------
    Funcao que calcula o indice de qualidade do jogador
    e define se ele eh o bom ou nao.
    O indice eh dado pela formula:

    ((3*(Pc - Pe) + 2*G - F)/5) * (Id/25), onde:

        - Pc: Passes corretos
        - Pe: Passes errados
        - G: Gols
        - F: Faltas
        - Id: Idade

    Caso o indice do jogadores seja maior 
    ou igual a 10, ele eh o bom.

 */

int eh_o_bom(Jogadores *j)
{
    int i;
    float indice = (3 * (j->num_passes_corretos - j->num_passes_errados) + 2 * j->num_gols - j->num_faltas) / 5;
    float fator_idade = j->idade / 25;
    float val = indice * fator_idade;

    printf("\n\n");
    for (i = 0; i <= 60; i++)
    {
        printf("=");
    }

    if (val >= 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}