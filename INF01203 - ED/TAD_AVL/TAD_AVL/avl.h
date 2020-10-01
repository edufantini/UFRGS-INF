typedef int TipoInfo;

typedef struct TNodoA pNodoA;

pNodoA * InsereArvore(pNodoA * a, TipoInfo ch);
int Altura (pNodoA * a);
int Calcula_FB(pNodoA * a);
void Desenha(pNodoA * a , int nivel);
int is_avl(pNodoA * a);
pNodoA * rotacao_direita(pNodoA * pt);
pNodoA * rotacao_esquerda(pNodoA * pt);
pNodoA * rotacao_dupla_direita (pNodoA * pt);
pNodoA * rotacao_dupla_esquerda (pNodoA * pt);
pNodoA * Caso1 (pNodoA * a , int *ok);
pNodoA * Caso2 (pNodoA * a , int *ok);
pNodoA * InsereAVL (pNodoA * a, TipoInfo x, int *ok);

