#include <vector>
#include <iostream>

#include "quick-sort.h"

using namespace std;

void swap(vector<int> &A, int i, int j){ // swaps A[i] and A[j]
    int aux = A[i];
    A[i] = A[j];
    A[j] = aux;
}

int chose_median(vector<int> &A, int lo, int hi){
    int mid = (lo+hi)/2;
    int val = max(min(A[lo],A[mid]),min(A[mid],A[hi]));
    if (val == A[lo])  return lo;
    if (val == A[mid]) return mid;
                       return hi;
}

int hoare_partition(vector<int> &A, int lo, int hi){
    int p, p_idx;
    p_idx = chose_median(A,lo,hi);
    p = A[p_idx];
    swap(A,lo,p_idx);
    bool esq = true;
    int i = lo, f=hi;
    while(i<f){
        if(esq){
            if(p >= A[f]){
                swap(A,i,f);
                i++;
                esq = false;
            } else 
                f--;
        } else {
            if(p < A[i]){
                swap(A,i,f); 
                f--;
                esq = true;
            } else
                i++;
        }
    }
    return i;   
}

void quicksort_hoare(vector<int> &A, int lo, int hi){
    if(lo < hi){
        int p  = hoare_partition(A,lo,hi);
        quicksort_hoare (A, lo, p-1);
        quicksort_hoare (A, p+1, hi);
    }
}


void swap(vector<MovieHash*> &A, int i, int j){ // swaps A[i] and A[j]
    MovieHash* aux = A[i];
    A[i] = A[j];
    A[j] = aux;
}

int chose_median(vector<MovieHash*> &A, int lo, int hi){
    int mid = (lo+hi)/2;
    float val = max(min(A[lo]->avg_ratings,A[mid]->avg_ratings),min(A[mid]->avg_ratings,A[hi]->avg_ratings));
    if (val == A[lo]->avg_ratings)  return lo;
    if (val == A[mid]->avg_ratings) return mid;
                                    return hi;
}

int hoare_partition(vector<MovieHash*> &A, int lo, int hi){
    int p_idx;
    float p;
    p_idx = chose_median(A,lo,hi);
    p = A[p_idx]->avg_ratings;
    swap(A,lo,p_idx);
    bool esq = true;
    int i = lo, f=hi;
    while(i<f){
        if(esq){
            if(p >= A[f]->avg_ratings){
                swap(A,i,f);
                i++;
                esq = false;
            } else 
                f--;
        } else {
            if(p < A[i]->avg_ratings){
                swap(A,i,f); 
                f--;
                esq = true;
            } else
                i++;
        }
    }
    return i;   
}

void quicksort_hoare(vector<MovieHash*> &A, int lo, int hi){
    if(lo < hi){
        int p  = hoare_partition(A,lo,hi);
        quicksort_hoare (A, lo, p-1);
        quicksort_hoare (A, p+1, hi);
    }
}