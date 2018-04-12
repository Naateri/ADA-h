#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

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
		if (p >= 99000) std::cout << p << ' ' << q << ' ' << r << '\n';
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
	int_vec A, copy;
	double time, time2;
	std::ofstream file;
	file.open("times.txt");
	/*file << "Random elements: " << std::endl;
	for (int i = 100000; i <= 1000000; i += 100000){
		for(int j = 0; j < i; j++){
			A.push_back(int(rand()) );
		}
		copy = A;
		clock_t begin = clock();
		quicksort_H(copy, 0, copy.size() - 1);
		clock_t end = clock();
		time = double(end-begin) / CLOCKS_PER_SEC;
		
		copy = A;
		clock_t begin1 = clock();
		quicksort_L(copy, 0, copy.size() - 1);
		clock_t end1 = clock();
		time2 = double(end1-begin1) / CLOCKS_PER_SEC;
		
		file << i << " HOARE " << time << " N.LOMUTO " << time2 << std::endl;
		A.clear();
	}*/
	
	file << "Ordered elements: " << std::endl;
	for (int i = 100000; i <= 1000000; i += 100000){
		for(int j = 0; j < i; j++){
			A.push_back(j+1);
		}
		copy = A;
		clock_t begin = clock();
		std::cout << "beginning quicksort\n";
		quicksort_H(copy, 0, copy.size() - 1);
		std::cout << "ending quicksort\n";
		clock_t end = clock();
		time = double(end-begin) / CLOCKS_PER_SEC;
		
		copy = A;
		clock_t begin1 = clock();
		quicksort_L(copy, 0, copy.size() - 1);
		clock_t end1 = clock();
		time2 = double(end1-begin1) / CLOCKS_PER_SEC;
		
		file << i << " HOARE " << time << " N.LOMUTO " << time2 << std::endl;
		
		A.clear();
	}
	
	file << "Inversely Ordered elements: " << std::endl;
	for (int i = 100000; i <= 1000000; i += 100000){
		for(int j = i; j > 0; j--){
			A.push_back(j);
		}
		copy = A;
		clock_t begin = clock();
		quicksort_H(copy, 0, copy.size() - 1);
		clock_t end = clock();
		time = double(end-begin) / CLOCKS_PER_SEC;
		
		copy = A;
		clock_t begin1 = clock();
		quicksort_L(copy, 0, copy.size() - 1);
		clock_t end1 = clock();
		time2 = double(end1-begin1) / CLOCKS_PER_SEC;
		
		file << i << " HOARE " << time << " N.LOMUTO " << time2 << std::endl;
		A.clear();
	}
	
	return 0;
}

