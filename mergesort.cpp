#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <fstream>
//using namespace std;

typedef std::vector<int> int_vec;

void print_vec(int_vec A){
	for(int i = 0; i < A.size(); i++){
		std::cout << A.at(i) << ' ';
	}
	std::cout << '\n';
}

int_vec merge(int_vec A, int_vec B){
	int_vec result;
	while (!A.empty() && !B.empty()){
		if (A.front() < B.front()){
			result.push_back(A.front());
			A.erase(A.begin());
		} else {
			result.push_back(B.front());
			B.erase(B.begin());
		}
	}
	std::copy(std::begin(A), std::end(A), std::back_inserter(result));
	std::copy(std::begin(B), std::end(B), std::back_inserter(result));
	return result;
}

int_vec mergesort(int_vec& A){
	if (A.size() <= 1)
		return A;
	int_vec left, right, result;
	std::copy(std::begin(A), std::begin(A) + A.size()/2, std::back_inserter(left));
	std::copy(std::begin(A) + A.size()/2, std::end(A), std::back_inserter(right));
	result = merge(mergesort(left), mergesort(right));
	A = result;
	return result;
}

int main(int argc, char *argv[]) {
	int_vec prueba; /*= {10,9,8,7,6,5,4,3,2,1};*/
	double Time;
	srand(time(NULL));
	/*std::cout << "Prior to mergesort:\n";
	print_vec(prueba);
	std::cout << "Mergesort:\n";
	mergesort(prueba);
	print_vec(prueba);*/
	std::ofstream file;
	file.open("m_random.txt");
	std::ofstream file2;
	file2.open("m_ordered.txt");
	std::ofstream file3;
	file3.open("m_orderedB.txt");
	for(int j = 100000; j <= 1000000; j += 100000){ //random
		prueba.clear();
		for(int i = 0; i < j; i++){ //10k -> 100k, 10k jumps
			prueba.push_back(rand());
		}
		clock_t begin = clock();
		mergesort(prueba);
		clock_t end = clock();
		Time = double(end-begin) / CLOCKS_PER_SEC;
		//std::cout << "Time for " << j << " elements: " << Time << std::endl;
		file << j << ' ' << Time << std::endl;
	}
	for(int j = 100000; j <= 1000000; j += 100000){ //ordered
		prueba.clear();
		for(int i = 0; i < j; i++){ //10k -> 100k, 10k jumps
			prueba.push_back(i);
		}
		clock_t begin = clock();
		mergesort(prueba);
		clock_t end = clock();
		Time = double(end-begin) / CLOCKS_PER_SEC;
		//std::cout << "Time for " << j << " elements: " << Time << std::endl;
		file2 << j << ' ' << Time << std::endl;
	}
	for(int j = 100000; j <= 1000000; j += 100000){ //ordered backwards
		prueba.clear();
		for(int i = j; i > 0; i--){ //10k -> 100k, 10k jumps
			prueba.push_back(i);
		}
		clock_t begin = clock();
		mergesort(prueba);
		clock_t end = clock();
		//std::cout << double(begin) << ' ' << double(end) << '\n';
		Time = double(end-begin) / CLOCKS_PER_SEC;
		//std::cout << "Time for " << j << " elements: " << Time << std::endl;
		file3 << j << ' ' << Time << std::endl;
	}
	file.close();
	file2.close();
	file3.close();
	return 0;
}
