#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"

// tipo para a LSE


struct TX{
        tipoinfo info;
        struct TX *p1;        
};

typedef struct TX X;


void OqueSera (pNodoA *a,  X **y){
  X *p;

  if (a != NULL)
    { 
          p = (X*) malloc(sizeof(X));
          p->info =  a->info;
          p->p1 = *y;
          *y = p;
          OqueSera (a->esq, y);
          OqueSera (a->dir, y);
    }
}



int main()
{
   pNodoA *arv = NULL, *procurado=NULL;

   arv = InsereArvore(arv,30);
   arv = InsereArvore(arv,45);
   arv = InsereArvore(arv,25);
   arv = InsereArvore(arv,90);
   arv = InsereArvore(arv,80);
   arv = InsereArvore(arv,95);

   
   
   Central(arv);
   printf("----\n\n");

  
   preFixado(arv);
   
   
   //testando o que sera;

   X *l=NULL, *aux=l;
  
   OqueSera (arv,&l);
   if (l==NULL) puts ("nulo");
   for (aux = l; aux!=NULL; aux=aux->p1)
     printf("%d ",aux->info);
   system("pause");

}


