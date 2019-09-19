#include <stdio.h>
#include <stdlib.h>

typedef struct
{

    int numero;
    struct tipoNo *prox;
    struct tipoNo *ant;

} tipoNo;

tipoNo *insere(tipoNo *ptLista, int valor)
{

    tipoNo *novo;

    if (ptLista == NULL)
    {

        // !    Lista vazia
        novo = (tipoNo *)malloc(sizeof(tipoNo));
        novo->numero = valor;

        novo->ant = novo;
        novo->prox = novo;
        ptLista = novo;
    }
    else
    {

        // !    Lista nao vazia

        tipoNo *ptAux;
        ptAux = ptLista;

        while (ptAux->prox != ptLista && ptAux->numero != valor)
        {
            ptAux = ptAux->prox; // Percorre lista
        }

        // ? Ou saiu do loop por encontrar o valor, ou por ter acabado a lista ou ambos

        if (ptAux->numero == valor)
        {
            /* TODO: Achou o valor, insere(v - 1) antes e(v + 1) depois */

            tipoNo *menor;
            menor = (tipoNo *)malloc(sizeof(tipoNo));
            menor->numero = (valor - 1);

            tipoNo *maior;
            maior = (tipoNo *)malloc(sizeof(tipoNo));
            maior->numero = (valor + 1);

            tipoNo *ptAnt;
            tipoNo *ptProx;
            ptAnt = ptAux->ant;
            ptProx = ptAux->prox;

            ptAnt->prox = menor;
            menor->ant = ptAnt;
            menor->prox = ptAux;
            ptAux->ant = menor;
            ptAux->prox = maior;
            maior->ant = ptAux;
            maior->prox = ptProx;
            ptProx->ant = maior;
        }
        else
        {

            /* TODO:    Chegou ao fim da lista e n achou o valor, insere no inicio.
                                - ptAux: ultimo node
                                - ptLista: primeiro node */

            novo = (tipoNo *)malloc(sizeof(tipoNo));
            novo->numero = valor;

            novo->ant = ptAux;
            novo->prox = ptLista;
            ptLista->ant = novo;
            ptAux->prox = novo;
            ptLista = novo;
        }
    }

    return ptLista;
}

void exibeIni(tipoNo *ptLista)
{

    tipoNo *ptAux = ptLista;

    if (ptLista == NULL)
    {
        printf("\n    Nada a exibir.\n");
    }
    else
    {

        printf("\n\n      ");

        do
        {
            printf("%d ", ptAux->numero);
            ptAux = ptAux->prox;
        } while (ptAux != ptLista);
        printf("\n");
    }

    return;
}

void exibeInversoNum(tipoNo *ptLista, int valor)
{

    tipoNo *ptAux = ptLista;

    if (ptLista == NULL)
    {
        printf("\n    Nada a exibir.\n");
    }
    else
    {

        while (ptAux->prox != ptLista && ptAux->numero != valor)
        {
            ptAux = ptAux->prox; // Percorre lista
        }

        if (ptAux->numero == valor)
        {

            tipoNo *ptSucessor = ptAux->prox;

            printf("\n\n      ");

            do
            {
                printf("%d ", ptAux->numero);
                ptAux = ptAux->ant;
            } while (ptAux != ptSucessor->ant);
            printf("\n");
        }
        else
        {
            printf("\n    Valor '%d' nao encontrado na lista.\n", valor);
        }
    }

    return;
}

tipoNo *destroi(tipoNo *ptLista)
{

    if (ptLista != NULL)
    {

        if (ptLista->prox == ptLista)
        {
            free(ptLista);
        }
        else
        {
            tipoNo *ptAux = ptLista;
            tipoNo *ptAnt = ptAux;

            while (ptAux->prox != ptLista)
            {
                ptAux = ptAux->prox; // Percorre lista
            }

            while (ptAux != ptLista)
            {
                ptAnt = ptAux->ant;
                ptAnt->prox = ptLista;
                ptLista->ant = ptAnt;
                free(ptAux);
                ptAux = ptLista->ant;
            }
            free(ptLista);
        }
    }

    return NULL;
}

int main()
{

    tipoNo *ptLista;
    ptLista = NULL;

    int valor = 1;

    while (valor != 0)
    {
        printf("\nInserir valor:");
        scanf("%d", &valor);
        if (valor != 0)
        {
            printf("\n  []  Inserindo valor '%d' ...", valor);
            ptLista = insere(ptLista, valor);
            exibeIni(ptLista);
        }
    }

    printf("\nFINALIZANDO INSERCAO\n=============================\n");

    printf("\n  []  Chamando exibeIni()...");
    exibeIni(ptLista);
    printf("\n  []  Insira um valor para chamar exibeInversoNum():");
    scanf("%d", &valor);
    printf("\n  []  Chamando exibeInversoNum() com valor='%d' ...", valor);
    exibeInversoNum(ptLista, valor);
    printf("\n []  Destruindo lista...");
    ptLista = destroi(ptLista);
    printf("\n  []  Lista destruida.");
}