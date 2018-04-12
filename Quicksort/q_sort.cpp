#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <ctime>

typedef std::vector<int> int_vec;

void swap(int_vec& A, int i, int j){
	int temp = A.at(i);
	A.at(i) = A.at(j);
	A.at(j) = temp;
}

void print_vec(int_vec A){
	for(int i = 0; i < A.size(); i++){
		std::cout << A.at(i) << ' ';
	}
	std::cout << std::endl;
}

//////////////////////////////////HOARE/////////////////////////////

int HOARE_partition(int_vec& A, int p, int r){
	int x, i, j;
	x = A.at(p);
	i = p - 1;
	j = r + 1;
	while (true){
		do{
			j--;
		} while( A.at(j) > x );
		do{
			i++;
		} while( A.at(i) < x );
		if (i < j) swap(A, i, j);
		else return j;
	}
}

void quicksort_H(int_vec& A, int p, int r){
	int q;
	if (p < r){
		q = HOARE_partition(A, p, r);
		quicksort_H(A, p, q);
		quicksort_H(A,q + 1, r);
	}
}

/////////////////////////N.LOMUTO/////////////////////

int LomutoPartition(int_vec& A, int p, int r){
	int x, i;
	x = A.at(r);
	i = p-1;
	for (int j = p; j < r; j++){
		if (A.at(j) <= x){
			i++;
			swap(A, i, j);
		}
	}
	swap(A, i+1, r);
	return i;
}

void quicksort_L(int_vec& A, int p, int r){
	int q;
	if (p < r){
		q = LomutoPartition(A, p, r);
		quicksort_L(A, p, q);
		quicksort_L(A,q + 1, r);
	} else return;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	/*int_vec A (100); //Testing to see if algorithms are ok
	int_vec A1;
	for(int i = 0; i < 100; i++){
		A.at(i) = rand()%1000000;
	}
	A1 = A;
	quicksort_L(A, 0, A.size()-1);
	quicksort_H(A1, 0, A1.size()-1);
	print_vec(A);
	print_vec(A1);*/
	return 0;
}

