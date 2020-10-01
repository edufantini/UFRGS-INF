#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

/*
ENTRADA TESTE:

1

10 6
AACATGAAGG
TTTTGGCCAA
TTTGGCCAAA
GATCAGATTT
CCCGGGGGGA
ATCGATGCAT


SAIDA TESTE:

CCCGGGGGGA
AACATGAAGG
GATCAGATTT
ATCGATGCAT
TTTTGGCCAA
TTTGGCCAAA

 */

int numberInversions(string dna) {

    int count = 0;

    // itera cada letra
    for(int i=0; i<dna.size(); i++) {

        char atual = dna[i];

        // itera cada letra sequente
        for(int j=i+1; j<dna.size(); j++) {

            char compara = dna[j];

            // atual vem antes de compara no alfabeto
            if(atual > compara) {
                count += 1;
            }


        }

    }

    return count;

}


void sortPrint(vector <tuple <int, string>> inversoes_para_cada_dna, vector<string> *resultado){
    
    // Varre todo o vetor começando na segunda posicao
    for(int i=1;i<inversoes_para_cada_dna.size();i++){
        tuple <int, string> key = inversoes_para_cada_dna[i];

        int j = i-1;

        // Varre os elementos adiante do atual e compara para ver se é maior
        while(j>=0 && get<0>(inversoes_para_cada_dna[j]) > get<0>(key)){
            get<0>(inversoes_para_cada_dna[j+1]) = get<0>(inversoes_para_cada_dna[j]);
            get<1>(inversoes_para_cada_dna[j+1]) = get<1>(inversoes_para_cada_dna[j]);

            j = j-1;
        }
        get<0>(inversoes_para_cada_dna[j+1]) = get<0>(key);
        get<1>(inversoes_para_cada_dna[j+1]) = get<1>(key);
    }

    // Printa as string ordenadas
    for(int j=0;j<inversoes_para_cada_dna.size();j++){
        string fullName;
        if(j == inversoes_para_cada_dna.size() - 1){
            fullName = get<1>(inversoes_para_cada_dna[j]) + "\n\n";
            resultado->push_back(fullName);
        }else{
            fullName = get<1>(inversoes_para_cada_dna[j]) + '\n';
            resultado->push_back(fullName);
        }
    }
}
void encontraMenor(vector<int> inversoes, vector<string> dnas, vector<string> *resultado){
    
    // INicializa o vetor de tuplas que conmtem <inversoes, dna>
    tuple <int, string> inversoes_dna;
    vector<tuple <int, string>>  inversoes_para_cada_dna;
    for(int i=0;i<inversoes.size();i++){
        inversoes_para_cada_dna.push_back(make_tuple(inversoes[i], dnas[i]));
    }

    // Ordena o vetor de tuplas de acordo com o numero de inversoes de cada dna
    sortPrint(inversoes_para_cada_dna, resultado);

    
}
void printArray(vector<int> a, int n){
    cout << "[";
    for(int i=0;i<n;i++){
        cout << a[i] << ",";
    }
    cout << "]" << endl;
}

int main() {

    // recebe numero de datasets
    int datasets;
    vector <string> resultado;
    cin >> datasets;

    // itera sobre datasets
    for(int i=1; i<=datasets; i++) {

        // recebe tamanho dna
        int tamanho;
        cin >> tamanho;

        // recebe n de dnas
        int n;
        cin >> n;

        vector<string> lista_de_dnas;

        vector<int> conta_inversoes;

        // itera sobre n de dnas
        for(int j=1; j<=n; j++) {

            // recebe string
            string dna;
            cin >> dna;
            lista_de_dnas.push_back(dna);
            // pupula vetor inversoes
            conta_inversoes.push_back(numberInversions(dna));

        }
        // sorting e print sobre os vetores
        encontraMenor(conta_inversoes, lista_de_dnas, &resultado);
    }

    cout << endl;
    for(int j=0;j<resultado.size();j++){
        cout << resultado[j];
    }

}