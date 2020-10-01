#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#define SIZE1 100
#define SIZE2 1000
#define SIZE3 10000
#define SIZE4 100000
#define NSIZES 4

void printArray(int C[], int tam);
void printVector(vector<int> C);
void generateRandomArray(int a[], int size);
void insertionSort(int a[], int n, int f, int h);
void shellSort(int a[], int n, vector<int> ciura);

void printArray(int C[], int tam) {
	printf("[");
	for (int i=0; i<tam-1; i++) {
		printf("%d, ", C[i]);
	}
	printf("%d]\n", C[tam-1]);
}

void printVector(vector<int> C) {
	printf("[");
	for (int i=0; i < C.size(); i++) {
		printf("%d, ", C.at(i));
	}
	printf("]\n");
}

void generateRandomArray(int a[], int size){
    for(int i=0;i<size;i++){
        a[i] = rand()%size+1;
    }
}

void verify_correctness(int a[], int size){
    for(int i=0;i<size-1;i++){
        if(a[i] > a[i+1]){
            cout << "The array did not ordered correctly" << endl;
            break;
        }
    }
}

vector<int> initializeCiura(int size){
    int i=0;
    int flag = 0;
    vector<int> ciura = {1};
    
    while(flag != 1){
        //printVector(ciura);
        //cin.get();
        if(ciura[i] < 701){
            switch(ciura[i]){
                case(1):
                    if(4 <= size)
                        ciura.push_back(4);
                    else
                        flag = 1;
                    break;
                case(4):
                    if(10 <= size)
                        ciura.push_back(10);
                    else
                        flag = 1;
                    break;
                case(10):
                    if(23 <= size)
                        ciura.push_back(23);
                    else
                        flag = 1;
                    break;
                case(23):
                    if(57 <= size)
                        ciura.push_back(57);
                    break;
                case(57):
                    if(132 <= size)
                        ciura.push_back(132);
                    else
                        flag = 1;
                    break;
                case(132):
                    if(301 <= size)
                        ciura.push_back(301);
                    else
                        flag = 1;
                    break;
                case(301):
                    if(701 <= size)
                        ciura.push_back(701);
                    else
                        flag = 1;
            }
        }else{
            if(floor(2.25*ciura[i]) <= size)
                ciura.push_back(floor(2.25*ciura[i]));
            else
                flag = 1;
        }
        i++;
    }

    return ciura;
}

void insertionSort(int a[], int n, int f, int h){
    // j = posicao do segundo elemento do gap 
    for(int j= f+h; j < n; j += h){
        int temp = a[j]; // temp guarda o segundo elemento do gap

        //inserir chave na seq ordenada a[i+h ... j+h-1]
        int k = j-h; // k = primeiro elemento do gap

        while(k>= 0 && a[k] > temp){
            a[k+h] = a[k];
            k = k-h;
        }
            a[k+h] = temp;
    }
}


// Shellsort function
// a: array of int
// n: size of a
void shellSort(int a[], int n, vector<int> ciura) {
    int t = 1; //inc

    //printArray(a, n);

    // Starts witha  big gap then reduce it
    // Calculates the gap every iteration
	for(int i = ciura.size() - 1; i >=0; i--){
        //cout << "h = " << ciura.at(i) << endl;
        //cin.get();
        int h = ciura.at(i);
        // i: crosses the gap
        for(int i=0; i<h;i++){
            insertionSort(a, n, i, h);
            
        } 
        //cout << "After increments of size " << h << " the list is: ";
        //printArray(a, n);
        //cout << endl;
        t++;
    }
}
int main(){

    vector<int> ciura;

    // Generates a random array based on SIZE
    //-------------------------------
    int a[SIZE1];
    generateRandomArray(a, SIZE1);
    //printArray(a, SIZE1);
    //-------------------------------
    int b[SIZE2];
    generateRandomArray(b, SIZE2);
    //printArray(b, SIZE2);
    //-------------------------------
    int c[SIZE3];
    generateRandomArray(c, SIZE3);
    //printArray(c, SIZE3);
    //-------------------------------
    int d[SIZE4];
    generateRandomArray(d, SIZE4);
    //printArray(d, SIZE4);
    //-------------------------------

    clock_t begin = clock();
    // Initialize an array based on the ciura sequence
    // While the last number of the array is < SIZE
    //------------------------------------
    ciura = initializeCiura(SIZE1);
    shellSort(a, SIZE1, ciura);
    verify_correctness(a, SIZE1);
    float full_t = float( clock () - begin ) /  CLOCKS_PER_SEC;
    cout << "Time size 1 (s): " << full_t << endl;
    //------------------------------------
    begin = clock();
    ciura = initializeCiura(SIZE2);
    shellSort(b, SIZE2, ciura);
    verify_correctness(b, SIZE2);
    full_t = float( clock () - begin ) /  CLOCKS_PER_SEC;
    cout << "Time size 2 (s): " << full_t << endl;
    //------------------------------------
    begin = clock();
    ciura = initializeCiura(SIZE3);
    shellSort(c, SIZE3, ciura);
    verify_correctness(c, SIZE3);
    full_t = float( clock () - begin ) /  CLOCKS_PER_SEC;
    cout << "Time size 3 (s): " << full_t << endl;
    //------------------------------------
    begin = clock();
    ciura = initializeCiura(SIZE4);
    shellSort(d, SIZE4, ciura);
    verify_correctness(d, SIZE4);
    full_t = float( clock () - begin ) /  CLOCKS_PER_SEC;
    //------------------------------------
    //printVector(ciura);
    return 0;
}