
# ====================================  #
#       definicao de variaveis          #
# ====================================  #


n = 0                                                   # inicializacao do numero de vertices | ordem da matriz C (nxn) | n >= 2
matrix = [0][0]                                         # inicializacao da matriz de custos C


# ===================================== #
#     funcao inputs: para receber e     #
#     formatar a matriz de custos       #
# ===================================== #


def inputs():
    global n, matrix

    n = int(input())
    matrix = [[0 for i in range(n)] for j in range(n)]  # definindo tamanho da matriz C (nxn)

    i, j = 0, 0                                         # definicao de indices

    # definicao dos pesos das arestas
    for i in range(n):                                  # tratamento linha a linha
        matrix[i] = input().split()                     # array de char

        for x, y in enumerate(matrix[i]):
            matrix[i][x] = int(y)                       # array de char -> array de int


# ===================================== #
#   funcao tem_caminho: retorna true    #
#      se existe caminho entre os       #
#        os vertices entrados,          #
#    retorna false caso contrario       #
# ===================================== #



def tem_caminho(na, nb):
    global matrix

    na, nb = na-1, nb-1                                 # ajusta indices
    return matrix[na][nb] != -1                         # true se != -1


# ===================================== #
#   funcao vertice_isolado: retorna     #
#    true se o vertice nao possui       #
#        aresta que toca em n,          #
#    retorna false caso contrario       #
# ===================================== #


def vertice_isolado(n):
    global matrix

    n = n-1                                             # ajusta indices
    for x in matrix[n]:
        if matrix[n][x] != -1:                          # true se todos valores da linha de n sao -1
            return False
        else:
            return True


# ===================================== #
#   funcao pbgm: retorna o custo da     #
#  bifloresta geradora de custo minimo  #
# ===================================== #


def pbgm():
    global matrix
    v = 0                                               # vertice de inicio
    nv = len(matrix)                                    # numero de vertices
    bifloresta = []                                     # bifloresta sendo gerada
    arestas = []                                        # listas de tuplas de arestas do vertice atual
    visitados = []                                      # lista de vertices visitados
    menor_peso = (float('inf'), None, None)             # tupla para salvar a aresta de menor peso (inf = infinito)
    maior_peso = (0, None, None)                        # tupla para salvar a aresta de maior peso
    custo_total = 0                                     # custo da bifloresta

    while len(bifloresta) != nv-1:                      # loop ate que todos vertices sejam visitados
        visitados.append(v)                             # marca v como visitado

        for i in range(nv):                             # |
            if matrix[v][i] != -1:                      # | salvar todas arestas de v na lista
                arestas.append((matrix[v][i], v, i))    # | (peso, v_saida, v_chegada)

        for i in range(len(arestas)):                   # percorre lista de arestas e guarda a menor em menor_peso
            if arestas[i][0] < menor_peso[0] and arestas[i][2] not in visitados:
                menor_peso = arestas[i]

        arestas.remove(menor_peso)

        bifloresta.append(menor_peso)                   # insere aresta na arvore

        v = menor_peso[2]                               # | prepara para novo laco
        menor_peso = (float('inf'), None, None)         # |

    for i in range(len(bifloresta)):                    # | Encontra a aresta de maior peso
        if bifloresta[i][0] > maior_peso[0]:            # |
            maior_peso = bifloresta[i]                  # |

    bifloresta.remove(maior_peso)                       # Remove a aresta de maior peso da árvore

    for i in range(len(bifloresta)):
        custo_total = custo_total + bifloresta[i][0]    # Calcula custo total, soma dos pesos de todas arestas

    print(custo_total)


inputs()

pbgm()
