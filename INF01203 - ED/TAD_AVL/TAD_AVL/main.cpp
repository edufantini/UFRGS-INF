#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int main()
{

   pNodoA *arv = NULL;
   int i, ok;



  arv = InsereAVL(arv, 42,&ok);
  arv = InsereAVL(arv, 15,&ok);
  arv = InsereAVL(arv, 88,&ok);
  arv = InsereAVL(arv, 6,&ok);
  arv = InsereAVL(arv, 27,&ok);
  arv = InsereAVL(arv, 4,&ok);



  Desenha(arv,1);



  if (is_avl(arv)) puts("Eh AVL");
  else puts("Nao eh AVL");

  system("pause");

}

