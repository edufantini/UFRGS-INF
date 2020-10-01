#include <stdio.h>
#include <stdlib.h>
#include "RN.h"

int main(int argc, char *argv[])
{
  RNtree* arv = NULL;
  arv = Insere(arv,10);
  arv = Insere(arv,20);
  arv = Insere(arv,5);
  arv = Insere(arv,50);
  Desenha(arv,0);
  if(Consulta(40,arv)) printf("O Nodo 40 esta na arvore\n");
  else printf("O Nodo 40 nao esta na arvore\n");
  if(Consulta(10,arv)) printf("O Nodo 10 esta na arvore\n");
  else printf("O Nodo 10 nao esta na arvore\n");
  arv = Remove(arv, 5);
  Desenha(arv,0);
  arv = Remove(arv, 40);
  Desenha(arv,0);
  Destroi(arv);
  system("PAUSE");	
  return 0;
}
