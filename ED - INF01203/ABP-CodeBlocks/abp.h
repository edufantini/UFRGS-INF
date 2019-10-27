typedef int tipoinfo;

struct TNodoA{
        tipoinfo info;
        struct TNodoA *esq;
        struct TNodoA *dir;
};

typedef struct TNodoA pNodoA;

pNodoA* InsereArvore(pNodoA *a, tipoinfo ch);
void preFixado(pNodoA *a);
void posFixado(pNodoA *a);
void Central(pNodoA *a);
pNodoA* consultaABP(pNodoA *a, tipoinfo chave);
pNodoA* consultaABP2(pNodoA *a, tipoinfo chave);

