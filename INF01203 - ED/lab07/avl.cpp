#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "abp.h"
#include "arn.h"

int altura(pNodoA *a)
{
    int alt_esq, alt_dir;
    if (a == NULL)
        return 0;
    else
    {
        alt_esq = altura(a->esq);
        alt_dir = altura(a->dir);
        if (alt_esq > alt_dir)
            return (1 + alt_esq);
        else
            return (1 + alt_dir);
    }
}

int calcula_fator(pNodoA *a)
{
    return (altura(a->esq) - altura(a->dir));
}

int verificaAVL(pNodoA *a)
{
    int alt_esq, alt_dir;

    if (a != NULL)
    {
        alt_esq = altura(a->esq);
        alt_dir = altura(a->dir);
        return ((alt_esq - alt_dir < 2) && (alt_dir - alt_esq < 2) && (verificaAVL(a->esq)) && (verificaAVL(a->dir)));
    }
    else
        return 1;
}