#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "abp.h"
#include "arn.h"

int main()
{

    int valor = 0;
    int fator = 0;
    pNodoA *node = NULL;

    pNodoA *arv = NULL;

    arv = InsereArvore(arv, 35);
    arv = InsereArvore(arv, 2);
    arv = InsereArvore(arv, 71);
    arv = InsereArvore(arv, 6);
    arv = InsereArvore(arv, 49);
    arv = InsereArvore(arv, 73);
    arv = InsereArvore(arv, 28);
    arv = InsereArvore(arv, 44);
    arv = InsereArvore(arv, 50);

    Central(arv);
    printf("----\n\n");

    printf("\nValor do nodo para calcular fator: ");
    scanf(" %d", &valor);
    printf("----\n\n");

    node = consultaABP(arv, valor);
    fator = calcula_fator(node);

    printf("Fator no nodo de valor %d: %d\n", valor, fator);
    printf("----\n\n");

    if (verificaAVL(arv))
    {
        printf("A arvore eh AVL.\n");
    }
    else
    {
        printf("A arvore nao eh AVL.\n");
    }
    printf("----\n\n");

    if (verificaARN(arv))
    {
        printf("A arvore eh ARN.\n");
    }
    else
    {
        printf("A arvore nao eh ARN.\n");
    }
    printf("----\n\n");
}
