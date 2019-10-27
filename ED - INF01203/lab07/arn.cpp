#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "abp.h"
#include "arn.h"

int verificaARN(pNodoA *a)
{
    int maior, menor = -1;
    int nivel = 0;
    int alt_esq, alt_dir;

    if (a == NULL)
        return 0;

    if (a != NULL)
    {
        alt_esq = altura(a->esq);
        alt_dir = altura(a->dir);

        if ((alt_dir > 2 * alt_esq) && (alt_esq > 2 * alt_dir))
            return 0;
        return 1;
    }
}