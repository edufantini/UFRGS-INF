#include <stdio.h>
#include <stdlib.h>
#include "abp.h"



pNodoA* InsereArvore(pNodoA *a, tipoinfo ch)
{
     if (a == NULL)
     {
         a =  (pNodoA*) malloc(sizeof(pNodoA));
         a->info = ch;
         a->esq = NULL;
         a->dir = NULL;
         return a;
     }
     else
          if (ch < a->info)
              a->esq = InsereArvore(a->esq,ch);
          else if (ch > a->info)
              a->dir = InsereArvore(a->dir,ch);
     return a;
}

void preFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          printf("%d\n",a->info);
          preFixado(a->esq);
          preFixado(a->dir);
      }
}

void Central(pNodoA *a)
{
     if (a!= NULL)
     {
          Central(a->esq);
          printf("%d\n",a->info);
          Central(a->dir);
      }
}

void posFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          posFixado(a->esq);
          posFixado(a->dir);
          printf("%d\n",a->info);
      }
}

pNodoA* consultaABP(pNodoA *a, tipoinfo chave) {

    while (a!=NULL){
          if (a->info == chave )
             return a; //achou então retorna o ponteiro para o nodo
          else
            if (a->info > chave)
               a = a->esq;
            else
               a = a->dir;
            }
            return NULL; //se não achou
}

pNodoA* consultaABP2(pNodoA *a, tipoinfo chave) {
    if (a!=NULL) {


       if (a->info == chave)
         return a;
       else
           if (a->info > chave)
                return consultaABP2(a->esq,chave);
            if (a->info < chave)
                return consultaABP2(a->dir,chave);

            else return a;
       }
       else return NULL;
}

