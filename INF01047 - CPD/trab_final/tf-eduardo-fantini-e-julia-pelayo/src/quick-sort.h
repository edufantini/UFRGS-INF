#include <vector>
#include "hash.h"

void swap(std::vector<int> &A, int i, int j);

int chose_median(std::vector<int> &A, int lo, int hi);

int hoare_partition(std::vector<int> &A, int lo, int hi);

void quicksort_hoare(std::vector<int> &A, int lo, int hi);

// movie hash
void swap(std::vector<MovieHash*> &A, int i, int j);

int chose_median(std::vector<MovieHash*> &A, int lo, int hi);

int hoare_partition(std::vector<MovieHash*> &A, int lo, int hi);

void quicksort_hoare(std::vector<MovieHash*> &A, int lo, int hi);
