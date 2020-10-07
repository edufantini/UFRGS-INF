/*
    Radix Sort MSD String Sort
    Authors:    Eduardo Fantini
                Thiago Lermen
    Input: 1 text file
    Output:
        - 1 file containing the words of the input file in lexicographic order
		- 1 file containing a list of all the unique words in the input file, in
		  lexicographic order, followed by their respective repetition numbers

 
    g++ RadixSortMSD.cpp -o radix
 
 
*/

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include "rang.h"


using namespace std;

// alphabet size
const int ALPH_SZ = 26;

// prints a single vector
void printVector(vector<string> words){
    int size = words.size();
    for (int i = 0 ; i < size ; i++){
        cout << words[i] << " ";
    }
    cout << endl;
}

// open and reads from a file, pushing the data to the 'words' vector
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
    if(d < word.size())
        return toascii(word[d]);
    else
        return -1;
}

// driver code for the sorting algorithm
void radixSortMSD(vector<string> &input, vector<string> &output, int lo, int hi, int d){
 
	if (hi <= lo)
        return;

    // max word size
    int R = 256;
    
    // vetor de acumulação
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

// save both output files
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
	return 1;
}


// generate output file name
string outputFilename(string file) {
	// removendo extensao
	size_t i = file.find_last_of(".");
	string semext = file.substr(0, i);
	string outName = semext + "_ordenado.txt";
	return outName;
}

// generate output file name for the counting file
string outputCountFilename(string file) {
	// removendo extensao
	size_t i = file.find_last_of(".");
	string semext = file.substr(0, i);
	string outName = semext + "_contagem.txt";
	return outName;
}

// get the number of repetitions of each word
int countWords(vector<string> &words, vector<string> &count) {
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
		} else{
			// lendo 2+ ocorrencia da palavra
			currWordCount++;
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
	int n = countWords(words, count);
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