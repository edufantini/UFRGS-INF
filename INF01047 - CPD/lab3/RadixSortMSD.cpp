/*
    Radix Sort MSD String Sort
    Autores:    Eduardo Fantini
                Thiago Lermen
    Input: 2 text files
    Output:
        - 1 file including the sorting of the words int he book
        - 1 file containing the accumulated number of each word in the book
    

*/

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include "rang.h"



using namespace std;

const int ALPH_SZ = 26;

void printVector(vector<string> words){
    int size = words.size();
    for (int i = 0 ; i < size ; i++){
        cout << words[i] << " ";
    }
    cout << endl;
}

void printArray(int a[], int size){
    cout << "[";
    for (int i=0;i<size;i++){
        cout << a[i] << " ";
    }
    cout << "]" << endl;
}


int readFile(string file_name, vector<string> *words){
    fstream file;
    string line, word;
    int out = 0;
    file.open (file_name);

    while(file >> word){
        words->push_back(word);
    }
    out = words->size();
    file.close();

    return out;
}

// retorna o caractere na posição 'd'
int charAt(string word, int d){
    if (d < word.size()){

//        cout << "Palavra: "<< word << endl;
//        cout << "Char na posicao " << d+1 << ": "<< word[d] << endl;
//        int e = toascii(word[d]);
//        cout << "Valor ascii do caractere e:" << e << endl;
//        cout << "Posicao do alfabeto do caractere:" << e-64 << endl;

        return toascii(word[d]);
    }else{
        return -1;
    }
}

void radixSortMSD(vector<string> &input, vector<string> &output, int lo, int hi, int d){
    if (hi <= lo)
        return;

    int R = 256;
    int count[R+2] = {0};

    // contando numero de caracteres em count
    for (int i = lo ; i <= hi ; i++){
        count[charAt(input[i], d) + 2]++;
    }
    // acumulando numero de caracteres em count
    for (int r = 0; r < R + 1 ; r++){
        count[r+1] += count[r];
    }
    // colocando palavras nas posições corretas no vetor out
    for (int i = lo ; i <= hi ; i++){
        output[count[charAt(input[i], d)+1]++] = input[i];
    }
    // salvando resultado no vetor principal
    for (int i = lo ; i <= hi ; i++){
        input[i] = output[i - lo];
    }
	// chamando função recursivamente
    for (int r = 0 ; r < R ; r++){
        radixSortMSD(input, output, lo + count[r], lo + count[r+1] - 1, d+1);
    }
}

int saveResults(vector<string> &words, vector<string> &count, string fout, string fcount) {
	
	ofstream file(fout);
	for(int i=0; i < words.size(); i++) {
		file << words[i] << endl;
	}
	file.close();
	
	ofstream filec(fcount);
	for(int i=0; i < count.size(); i+=2) {
		filec << count[i]  << " => " << count[i+1] << endl;
	}
	filec.close();
}

string outputFilename(string file) {
	// removendo extensao
	size_t i = file.find_last_of(".");
	string semext = file.substr(0, i);
	string outName = semext + "_ordenado.txt";
	return outName;
}

string outputCountFilename(string file) {
	// removendo extensao
	size_t i = file.find_last_of(".");
	string semext = file.substr(0, i);
	string outName = semext + "_contagem.txt";
	return outName;
}

int contaPalavras(vector<string> &words, vector<string> &count) {
	string curWord = "";
	int singleWords = 0;
	int currWordCount = 0;
	for(int i=0; i<words.size(); i++) {
		if(words[i] != curWord) {
			// lendo 1a ocorrencia da palavra
			singleWords++;
			// salva contagem da palavra anterior, se a contagem é != 0
			if(currWordCount)
				count.push_back(to_string(currWordCount));
			
			curWord = words[i];
			currWordCount = 1;
			count.push_back(words[i]);
//			printVector(wordCount);
		} else{
			// lendo 2+ ocorrencia da palavra
			currWordCount++;
			
//			cout << "Palavra igual" << endl;
//			cout << curWord << " | " << currWordCount << endl;
		}
	}
	count.push_back(to_string(currWordCount));
	return singleWords;
}

int main(int argc, char** argv){
	
	// validação de args
	if(argc != 2) {
		cout << "Argumentos inválidos! Use " << argv[0]
		     << " (arq entrada TXT)" << endl;
		exit(1);
	}
	
	string file = argv[1];
	string out = outputFilename(file);
	string out_count = outputCountFilename(file);
    vector<string> words;
    vector<string> count;
	cout << "\n========================================================\n" << endl;
	cout << rang::fg::yellow << "Iniciando leitura do arquivo de entrada..." << rang::fg::reset << endl;
    if (!readFile(file, &words)){
        cout << rang::bg::red << "Erro na leitura do arquivo!" << rang::bg::reset << endl;
	    cout << "\n========================================================\n" << endl;
        exit(1);
    }
	cout << rang::fg::green << "Arquivo " << file << " lido com sucesso." << rang::fg::yellow << "\nIniciando ordenamento..." << rang::fg::reset << endl;
    
    // arquivo lido com sucesso
    vector <string> aux (words.size());
    
    // executa ordenamento e conta tempo
	const clock_t a = clock();
    radixSortMSD(words, aux, 0, words.size()-1, 0);
	float t = float(clock() - a)/CLOCKS_PER_SEC;

    cout << "\n========================================================\n" << endl;
	cout << rang::fg::green << "Lista de " << words.size() << " palavras ordenada em " << t << " segundos." << rang::fg::reset << endl;
	cout << "\n========================================================\n" << endl;
	
	cout << rang::fg::yellow << "Iniciando contagem de repetições de palavras..." << rang::fg::reset << endl;
	const clock_t b = clock();
	int n = contaPalavras(words, count);
	t = float(clock() - b)/CLOCKS_PER_SEC;
	
	if(!n) {
		cout << rang::bg::red << "Erro na contagem de palavras!" << rang::bg::reset << endl;
		cout << "\n========================================================\n" << endl;
		exit(1);
	}
	cout << rang::fg::green << "Contagem de " << n << " palavras únicas realizada em " << t << " segundos." << rang::fg::reset << endl;
	cout << "\n========================================================\n" << endl;
	cout << rang::fg::yellow << "Escrevendo resultados em arquivos de saida..." << rang::fg::reset << endl;
	
	if(!saveResults(words, count, out, out_count)) {
		cout << rang::bg::red << "Erro ao salvar arquivos de saída!" << rang::bg::reset << endl;
		cout << "\n========================================================\n" << endl;
		exit(1);
	}
	
	cout << "\n========================================================\n" << endl;
	cout << rang::fg::green << "Arquivo ordenado salvo como " << out << "." << rang::fg::reset << endl;
	cout << rang::fg::green << "Arquivo de contagem salvo como " << out_count << "." << rang::fg::reset << endl;
	cout << "\n========================================================\n" << endl;
	
	
    return 0;
}