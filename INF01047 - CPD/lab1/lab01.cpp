#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

void printArray(int C[], int tam) {
	printf("[");
	for (int i=0; i<tam-1; i++) {
		printf("%d, ", C[i]);
	}
	printf("%d]\n", C[tam-1]);
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
void shellSort(int a[], int n) {
    int t = 1; //inc

    printArray(a, n);

    // Starts witha  big gap then reduce it
    // Calculates the gap every iteration
	for(int h = floor(n/2); h > 0; h = floor(n/pow(2, t))){
        // i: crosses the gap
        for(int i=0; i<h;i++){
            insertionSort(a, n, i, h);
            
        } 
        cout << "After increments of size " << h << " the list is: ";
        printArray(a, n);
        cout << endl;
        t++;
    }
}




int main(){
    int arr_teste[9]={54, 26, 93, 17, 77, 31, 44, 55, 20};
    int arr_1a[15] = {733, 77, 611, 51, 496, 990, 61, 175, 127, 794, 794, 76, 197, 141, 863};
    int arr_1b[20] = {872, 424, 729, 573, 877, 696, 321, 758, 949, 217, 767, 238, 562, 175, 999, 12, 380, 406, 225, 995};

    /*EXERCICIO 1*/
    //shellSort(arr_teste, 9);
    // A
    //shellSort(arr_1a, 15);
    // B
    shellSort(arr_1b, 20);

}