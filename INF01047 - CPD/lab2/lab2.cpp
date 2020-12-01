
// UNCOMMENT FOR WINDOWS
//#define WINDOWS
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

//==============================

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

const string INPUT = "entrada.txt";

//==================================

// 0 -> mediana de 3 e Lomuto part
// 1 -> mediana de 3 e Hoare part
// 2 -> random e Lomuto part
// 3 -> random e Hoare part

// Particionador MEDIANA DE 3: particionador = mediana entre o 1o, ultimo e elemento médio
// Particionador RANDOMIZADO: particionador = aleatório


/*  *   *   *   *   *   *   *   *   *
 *
 *
 *  FUNCOES AUXILIARES/ORGANIZAÇÃO
 *
 *
 *  *   *   *   *   *   *   *   *   */

// retorna string com diretorio atual
string GetCurrentWorkingDir( void ) {
	char buff[FILENAME_MAX];
	GetCurrentDir( buff, FILENAME_MAX );
	string current_working_dir(buff);
	return current_working_dir;
}

// printa um vetor individual
void printVector(vector<int> v) {
    int size = v.size();
    printf("[");
    for (int i=0; i<size-1; i++) {
        printf("%d, ", v[i]);
    }
    printf("%d]\n", v[size-1]);
}

// printa vetores do vetor de armazenamento
void printAllVectors(vector<vector<int>> &v) {

    for(int i = 0; i < v.size(); i++) {
        printVector(v[i]);
    }

}

// preenche o vetor de armazenamento com os valores da linha recebida
void populateVector(string line, vector<vector<int>> &v) {

    vector<int> aux;
    string word = "";

    // iterando sobre linha e separando por espaços
    for (auto x : line) {
        if (x == ' ') {
            aux.push_back(stoi(word));
            word = "";
        } else {
            word = word + x;
        }
    }
    // adicionar valores em um vetor
    aux.push_back(stoi(word));
    // e entao adicionar este vetor ao vetor principal
    v.push_back(aux);
}

// transfere dados da entrada para o vetor de armazenamento
int readData(string filename, vector<vector<int>> &v) {

    string line;
    ifstream file (filename);
    int n = 0;

    // comeco da leitura
    if (file.is_open()) {

        while (getline(file,line)) {

            // se já leu a primeira linha começa a popular vetor com arrays recebidos
            if(n) {

                string ssize = "";
                string str;
                int asize;

                // ler tamanho do array
                for (auto x : line) {
                    if (x == ' ') {
                        // acabou de ler primeiro numero, corta string
                        str = line.substr(ssize.size()+1);
                        break;
                    }else{
                        // lendo primeiro numero
                        ssize =  ssize + x;
                    }
                }

                asize = stoi(ssize);
                // chama funcao para popular vetor com valores da linha
                populateVector(str, v);

            }else{
                // 1a linha, recebe numero de vetores
                n = stoi(line);
            }

        }
        file.close();
        // sem erros, retorna numero de vetores
        return n;
    }
    // erro ao ler arquivo, retorna 0 indicando erro
    return 0;
}


/*  *   *   *   *   *   *   *   *   *
 *
 *
 *  FUNCOES PARTICIONADOR/PARTICIONAMENTO
 *
 *
 *  *   *   *   *   *   *   *   *   */

int lomutoPartMed3(vector<int> &v, int lo, int hi, int &s) {
	
	int middle = lo + (hi - lo) / 2;
	
	if((v.at(middle) >= v.at(lo) && v.at(middle) <= v.at(hi))
	   || (v.at(middle) <= v.at(lo) && v.at(middle) >= v.at(hi))) {
		std::swap(v.at(hi), v.at(middle));
		s++;
	}
	
	if((v.at(hi) >= v.at(lo) && v.at(hi) <= v.at(middle))
	   || (v.at(hi) <= v.at(lo) && v.at(hi) >= v.at(middle))) {
		std::swap(v.at(lo), v.at(hi));
		s++;
	}
	
	int i = lo-1;
	int p = v[hi];
	int j;
	
	for (j = lo; j <= hi -1; j++) {
		if(v[j] < p) {
			s++;
			i++;
			swap(v[i], v[j]);
		}
	}
	s++;
	swap(v[i+1], v[hi]);
	
	return i+1;
}

int lomutoPartRand(vector<int> &v, int lo, int hi, int &s) {
	// randomizacao
	srand(time(NULL));
	int ran = lo + rand() % (hi - lo);
	swap(v[ran], v[hi]);
	
	int i = lo-1;
	int p = v[hi];
	int j;
	
    for (j = lo; j <= hi -1; j++) {
        if(v[j] <= p) {
            s++;
	        i++;
            swap(v[i], v[j]);
        }
    }
    s++;
    swap(v[i+1], v[hi]);
    
    return i+1;
}

int hoarePartMed3(vector<int> &vec, int low, int high, int &s)
{
	int middle = low + (high - low) / 2;
	
	if((vec.at(middle) >= vec.at(low) && vec.at(middle) <= vec.at(high))
	   || (vec.at(middle) <= vec.at(low) && vec.at(middle) >= vec.at(high))) {
		std::swap(vec.at(high), vec.at(middle));
		s++;
	}
	
	if((vec.at(high) >= vec.at(low) && vec.at(high) <= vec.at(middle))
	   || (vec.at(high) <= vec.at(low) && vec.at(high) >= vec.at(middle))) {
		std::swap(vec.at(low), vec.at(high));
		s++;
	}
	
	
	int pivot = vec.at(low);
	int i = low - 1, j = high + 1;
	
	while(true)
	{
		do
		{
			i++;
		} while(vec.at(i) < pivot);
		
		do
		{
			j--;
		} while(vec.at(j) > pivot);
		
		if(i >= j)
			return j;
		
		std::swap(vec.at(i), vec.at(j));
		s++;
	}
}

int hoarePartRand(vector<int> &vec, int low, int high, int &s) {
	
	// randomizacao
	srand(time(NULL));
	int ran = low + rand() % (high - low);
	swap(vec[ran], vec[high]);
	
	int pivot = vec.at(low);
	int i = low - 1, j = high + 1;
	
	while(true)
	{
		do
		{
			i++;
		} while(vec.at(i) < pivot);
		
		do
		{
			j--;
		} while(vec.at(j) > pivot);
		
		if(i >= j)
			return j;
		
		std::swap(vec.at(i), vec.at(j));
		s++;
	}

}

/*  *   *   *   *   *   *   *   *   *
 *
 *
 *  FUNCOES EXECUÇÃO DE SORTING
 *
 *
 *  *   *   *   *   *   *   *   *   */

void qsortLomutoRand(vector<int> &v, int lo, int hi, int &s, int &r) {
	if(hi > lo) {
		int q = lomutoPartRand(v, lo, hi, s);
		r += 2;
		// particonador é o  elemento q divide??
		qsortLomutoRand(v, lo, q-1, s, r); // recursao no 1o sub-array
		qsortLomutoRand(v, q+1, hi, s, r); // recursao no 2o sub-array
	}
}

void qsortLomutoMed3(vector<int> &v, int lo, int hi, int &s, int &r) {
	if(hi > lo) {
		int q = lomutoPartMed3(v, lo, hi, s);
		r += 2;
		// particonador é o  elemento q divide??
		qsortLomutoMed3(v, lo, q-1, s, r); // recursao no 1o sub-array
		qsortLomutoMed3(v, q+1, hi, s, r); // recursao no 2o sub-array
	}
}

// void qsortHoareMed3(vector<int> &v, int lo, int hi, int &s, int &r) {
// 	if(hi > lo) {
// 		int q = hoarePartMed3(v, lo, hi, s);
// 		r += 2;
// 		// particonador é o  elemento q divide??
// 		qsortHoareMed3(v, lo, q-1, s, r); // recursao no 1o sub-array
// 		qsortHoareMed3(v, q+1, hi, s, r); // recursao no 2o sub-array
// 	}
// }

void qsortHoareRand(vector<int> &v, int lo, int hi, int &s, int &r) {
	if(hi > lo) {
		int q = hoarePartRand(v, lo, hi, s);
		r += 2;
		// particonador é o  elemento q divide??
		qsortHoareRand(v, lo, q-1, s, r); // recursao no 1o sub-array
		qsortHoareRand(v, q+1, hi, s, r); // recursao no 2o sub-array
	}
}

/*  *   *   *   *   *   *   *   *   *
 *
 *
 *  FUNCOES OUTPUT DOS RESULTADOS
 *
 *
 *  *   *   *   *   *   *   *   *   */

void saveResultsLomutoRand(tuple<int, int, float> stats, vector<vector<int>> &v) {
	
	string f = GetCurrentWorkingDir() + "/saida-aleatorio-lomuto.txt" ;
	ofstream file(f);
	for(int i=0; i < v.size(); i++) {
		vector<int> aux = v[i];
		file << aux.size();
		for (int j=0; j<aux.size(); j++) {
			file << " " << aux[j];
		}
		file << endl;
		
	}
	file.close();
	
	string fs = GetCurrentWorkingDir() + "/stats-aleatorio-lomuto.txt" ;
	ofstream files(fs);
	files << "Swaps: " << get<0>(stats) << endl;
	files << "Recursões: " << get<1>(stats) << endl;
	files << "Tempo: " << get<2>(stats) << endl;
	files.close();
}

void saveResultsLomutoMed3(tuple<int, int, float> stats, vector<vector<int>> &v) {
	
	string f = GetCurrentWorkingDir() + "/saida-mediana-3-lomuto.txt" ;
	ofstream file(f);
	
	for(int i=0; i < v.size(); i++) {
		vector<int> aux = v[i];
		file << aux.size();
		for (int j=0; j<aux.size(); j++) {
			file << " " << aux[j];
		}
		file << endl;
		
	}
	file.close();
	
	string fs = GetCurrentWorkingDir() + "/stats-mediana-3-lomuto.txt" ;
	ofstream files(fs);
	files << "Swaps: " << get<0>(stats) << endl;
	files << "Recursões: " << get<1>(stats) << endl;
	files << "Tempo: " << get<2>(stats) << endl;
	files.close();
}

void saveResultsHoareMed3(tuple<int, int, float> stats, vector<vector<int>> &v) {
	
	string f = GetCurrentWorkingDir() + "/saida-mediana-3-hoare.txt";
	ofstream file(f);
	for(int i=0; i < v.size(); i++) {
		vector<int> aux = v[i];
		file << aux.size();
		for (int j=0; j<aux.size(); j++) {
			file << " " << aux[j];
		}
		file << endl;
		
	}
	file.close();
	
	string fs = GetCurrentWorkingDir() + "/stats-mediana-3-hoare.txt";
	ofstream files(fs);
	files << "Swaps: " << get<0>(stats) << endl;
	files << "Recursões: " << get<1>(stats) << endl;
	files << "Tempo: " << get<2>(stats) << endl;
	files.close();
}

void saveResultsHoareRand(tuple<int, int, float> stats, vector<vector<int>> &v) {
	
	string f = GetCurrentWorkingDir() + "/saida-aleatorio-hoare.txt";
	ofstream file(f);
	for(int i=0; i < v.size(); i++) {
		vector<int> aux = v[i];
		file << aux.size();
		for (int j=0; j<aux.size(); j++) {
			file << " " << aux[j];
		}
		file << endl;
		
	}
	file.close();
	
	string fs = GetCurrentWorkingDir() + "/stats-aleatorio-hoare.txt";
	ofstream files(fs);
	files << "Swaps: " << get<0>(stats) << endl;
	files << "Recursões: " << get<1>(stats) << endl;
	files << "Tempo: " << get<2>(stats) << endl;
	files.close();
}

/*  *   *   *   *   *   *   *   *   *
 *
 *
 *  FUNCOES DRIVER DE CADA ALGORITMO
 *
 *
 *  *   *   *   *   *   *   *   *   */

tuple<int, int, float> execLomutoRand(int n, vector<vector<int>> &v) {
	
	int s = 0;
	int r = 0;
	const clock_t a = clock(); // conta tempo
	for(int i = 0; i < n; i++) {
		qsortLomutoRand(v[i], 0, v[i].size() - 1, s, r);
//		printVector(v[i]);
	}
	float t = float(clock() - a)/CLOCKS_PER_SEC;
	tuple<int, int, float>ret = make_tuple(s, r, t);
	saveResultsLomutoRand(ret, v);
	return ret;
}

tuple<int, int, float> execLomutoMed3(int n, vector<vector<int>> &v) {
	
	int s = 0;
	int r = 0;
	const clock_t a = clock(); // conta tempo
	for(int i = 0; i < n; i++) {
		qsortLomutoMed3(v[i], 0, v[i].size() - 1, s, r);
//		printVector(v[i]);
	}
	float t = float(clock() - a)/CLOCKS_PER_SEC;
	tuple<int, int, float>ret = make_tuple(s, r, t);
	saveResultsLomutoMed3(ret, v);
	return ret;
}

tuple<int, int, float> execHoareMed3(int n, vector<vector<int>> &v) {
	
	int s = 0;
	int r = 0;
	const clock_t a = clock(); // conta tempo
	for(int i = 0; i < n; i++) {
		qsortHoareMed3(v[i], 0, v[i].size() - 1, s, r);
//		printVector(v[i]);
	}
	float t = float(clock() - a)/CLOCKS_PER_SEC;
	tuple<int, int, float>ret = make_tuple(s, r, t);
	saveResultsHoareMed3(ret, v);
	return ret;
}

tuple<int, int, float> execHoareRand(int n, vector<vector<int>> &v) {
	
	int s = 0;
	int r = 0;
	const clock_t a = clock(); // conta tempo
	for(int i = 0; i < n; i++) {
		qsortHoareRand(v[i], 0, v[i].size() - 1, s, r);
//		printVector(v[i]);
	}
	float t = float(clock() - a)/CLOCKS_PER_SEC;
	tuple<int, int, float>ret = make_tuple(s, r, t);
	saveResultsHoareRand(ret, v);
	return ret;
}

void copyVector(vector<vector<int>> &v, vector<vector<int>> &vcopy) {
	vcopy.clear();
	for(int k=0; k < v.size(); k++) {
		vcopy.push_back(v[k]);
	}
}

int main(int argc, char** argv) {

    // validação de args
    if(argc != 2) {
        cout << "Argumentos inválidos! Use " << argv[0]
             << " (arq entrada TXT)" << endl;
        exit(1);
    }
    
    vector<vector<int>> v; // vetor de armazenamento
    // tenta ler dados
    int n = readData(argv[1], v);
    if(!n) {
        // erro ao ler dados
        cout << "Não foi possível abrir o arquivo de entrada." << endl;
    }
	
    // cria uma cópia de v
	vector<vector<int>> vcopy;
 
	copyVector(v, vcopy);
	tuple<int, int, float> rLomutoRand = execLomutoRand(n, vcopy);
	
	copyVector(v, vcopy); // restaura valores originais
	tuple<int, int, float> rLomutoMed3 = execLomutoMed3(n, vcopy);
	
	copyVector(v, vcopy);
	tuple<int, int, float> rHoareRand = execHoareRand(n, vcopy);
	
	copyVector(v, vcopy);
	tuple<int, int, float> rHoareMed3 = execHoareMed3(n, vcopy);

    cout << "SWAPS | RECURS | TIME" << endl;
    cout <<  get<0>(rLomutoRand) << "\t| " << get<1>(rLomutoRand) << "\t| " << get<2>(rLomutoRand) << endl;
    cout <<  get<0>(rLomutoMed3) << "\t| " << get<1>(rLomutoMed3) << "\t| " << get<2>(rLomutoMed3) << endl;
    cout <<  get<0>(rHoareRand) << "\t| " << get<1>(rHoareRand) << "\t| " << get<2>(rHoareRand) << endl;
    cout <<  get<0>(rHoareMed3) << "\t| " << get<1>(rHoareMed3) << "\t| " << get<2>(rHoareMed3) << endl;

}
