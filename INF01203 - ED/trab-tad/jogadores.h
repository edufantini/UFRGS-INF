
/* Tipos Exportados */

typedef struct Jogadores
{
    char nome[40];
    int idade;
    int num_gols;
    int num_faltas;
    int num_passes_errados;
    int num_passes_corretos;
} Jogadores;

/* Funções Exportadas */

/* Atribui Dados */
void atribui_dados(Jogadores *j, int k);
/* Exibe Estatísticas */
void exibe_estatisticas(Jogadores *j, int k);
/* Eh o bom */
int eh_o_bom(Jogadores *j);