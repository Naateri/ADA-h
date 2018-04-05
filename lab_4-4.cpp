/*
File: sorting.cpp
Authors: Eric and Duncan
Date:

c++ command to compile: -Wall -pedantic-errors -O0 -finput-charset=iso-8859-1 -fexec-charset=cp437 -std=c++11

*/

#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <cstdlib>

typedef std::vector<int> int_vec;
typedef std::pair<int, int> int_key; //key, value
typedef std::vector<int_key> keys_vec;
typedef std::vector<std::vector<int_key> > vecs_vec;
typedef std::stringstream ss;
typedef std::string str;

//char endl = '\n';

bool operator<(const int_key &a, const int_key &b){
	return a.first < b.first;
}

int get_bucket(int num, int k, int num_buckets){
	return num/(k / num_buckets);
}

keys_vec int_to_keys(int_vec A){ //transforms a vector of only ints to a vector of pairs (key, val)
	int_key temp;
	keys_vec ret;
	//temp.first = 0;
	for(int i = 0; i < A.size(); i++){
		temp.first = temp.second = A.at(i);
		ret.push_back(temp);
	}
	return ret;
}

int_vec keys_to_int(keys_vec A){ //transforms a vector of only ints to a vector of pairs (key, val)
	int_vec temp;
	keys_vec ret;
	for(int i = 0; i < A.size(); i++){
		temp.push_back(A.at(i).second);
	}
	return temp;
}

void print_keysVec(keys_vec A){
	int j;
	for(int i = 0; i < A.size(); i++){
		std::cout << A.at(i).second << ' ';
		//std::cin >> j;
	}
	std::cout << std::endl;
}

str intToString(const int &z) {
	ss leString;
	leString << z;
	return leString.str();
}

int stringToInt(str a){
	int ret;
	ss convi(a);
	convi >> ret;
	return ret;
}

void print_vec(int_vec A){ //from mergesort.cpp
	for(int i = 0; i < A.size(); i++){
		std::cout << A.at(i) << ' ';
	}
	std::cout << '\n';
}

int n_digit(int num, int n, int d){
	str snum;
	snum = intToString(num);
	while (snum.size() < d){
		snum = "0" + snum;
	}
	snum = snum[n];
	snum += '\0';
	return stringToInt(snum);
}

//countingsort
//sorted result is returned as a new array
//assume array is populated with data prior to this call
template<class RandomAccessIterator>
void countingsort(RandomAccessIterator first, RandomAccessIterator last, int k){
	int_vec counts (k), result;
	int temp;
	RandomAccessIterator ind;
	std::fill(counts.begin(), counts.end(), 0);
	for(ind = first; ind != last; ind++){
		counts.at(*ind)++;
	}
	ind = first;
	for (int i = 0; i < k; i++){
		temp = counts.at(i);
		for (int j = 0; j < temp; j++, ind++){
			*ind = i;
		}
	}
}

//countingsort
//sorted result is returned as a new array
//assume array is populated with data prior to this call
template<class RandomAccessIterator>
void bucketsort(RandomAccessIterator first, RandomAccessIterator last, int k, int num_buckets){
	RandomAccessIterator Index;
	vecs_vec buckets (num_buckets);
	keys_vec result, temp;
	for(Index = first; Index != last; Index++){
		buckets.at( get_bucket( (*Index).first, k, num_buckets ) ).push_back(*Index);
	}
	if (num_buckets < k){
		for(int i = 0; i < buckets.size(); i++){
			std::stable_sort(buckets.at(i).begin(), buckets.at(i).end());
		}
	}
	for(int i = 0; i < buckets.size(); i++){
		temp = buckets.at(i);
		for(int j = 0; j < temp.size(); j++){
			result.push_back((temp.at(j) ) );
		}
	}
	keys_vec::iterator it = result.begin();
	for(Index = first; Index != last; Index++, it++){
		*Index = *(it);
	}
}

//countingsort
//sorted result is returned as a new array
//assume array is populated with data prior to this call
template<class RandomAccessIterator>
void radixsort(RandomAccessIterator first, RandomAccessIterator last, int d, int k){
	int_key temp;
	keys_vec A_j, result, A_t;
	int_vec conv;
	RandomAccessIterator index;
	for(index = first; index != last; index++){
		conv.push_back(*index);
	}
	A_t = int_to_keys(conv); //transforming the vector to a pair(int, int) vector
	for (int j = 0; j < d; j++){ //radix_sort pseudocode
		A_j.clear();
		for(int i = 0; i < A_t.size(); i++){
			temp.second = A_t.at(i).second;
			temp.first = n_digit(A_t.at(i).second, d-j-1, d);
			A_j.push_back(temp);
		}
		bucketsort(A_j.begin(), A_j.end(), k, k);
		A_t = A_j;
		result = A_t;
	}
	keys_vec::iterator it = result.begin();
	for(index = first; index != last; index++, it++){
		*index = (*it).second;
	}
}


//return 1 if a is sorted (in non-decreasing order);
//return 0 otherwise
//assume array is allocated and populated with data prior to this call
template<class RandomAccessIterator>
bool issorted(RandomAccessIterator first, RandomAccessIterator last){
	RandomAccessIterator it;
	for(it = first; it != last-1; it++){
		if (*it <= (*(it+1))){
			continue;
		} else return false;
	}
	return true;
}

template <class v>
bool issorted(v Array){
	for(int i = 0; i < Array.size()-1; i++){
		if (Array.at(i) < Array.at(i+1) ) continue;
		else return false;
	}
	return true;
}


int ns[] = {1000, 10000, 100000, 1000000, 10000000, 100000000};
int ks[] = {1000, 100000, 100000000};

int main(int argc, char *argv[]) {
	srand(time(NULL));
	double t1, t2, t3;
	int size;
	for (auto n: ns) {
		for (auto k: ks) {
			//declare an array a
			int_vec a, aa;
			keys_vec A, AA;
			//populate the array with random data
			for(int i = 0; i < n; i++){
				a.push_back(rand() % k);
			}
			// crear una copia de a llamada aa
			A = int_to_keys(a);
			aa = a;
			clock_t begin = clock();
			countingsort(aa.begin(), aa.end(), k);
			clock_t end = clock();
			t1 = double(end-begin)/CLOCKS_PER_SEC;
			if (!issorted(aa.begin(), aa.end())) {
				throw "countingsort not working";
			}
			// crear una copia de a llamada aa
			AA = A;
			clock_t begin1 = clock();
			bucketsort(AA.begin(), AA.end(), k, k/2);
			clock_t end1 = clock();
			t2 = double(end1-begin1)/CLOCKS_PER_SEC;
			if (!issorted(AA.begin(), AA.end())) {
				throw "bucketsort not working";
			}
			// crear una copia de a llamada aa
			aa = a;
			size = intToString(k).size();
			clock_t begin2 = clock();
			radixsort(aa.begin(), aa.end(), size-1, 10);
			clock_t end2 = clock();
			t3 = double(end2-begin2)/CLOCKS_PER_SEC;
			if (!issorted(aa.begin(), aa.end())) {
				throw "radixsort not working";
			}
			std::cout << n << " " << k << " " << t1 << " " << t2 << " " << t3 << std::endl;
		}
	}
	
	return 0;
}

/*
JUST SOME TESTING
int_vec A, aa;
keys_vec a, AA;
A = {5,8,9,3,2,1,1,5,7};
aa = A;
a = int_to_keys(A);
countingsort(A.begin(), A.end(), 10);
print_vec(A);
bucketsort(a.begin(), a.end(),10, 10);
print_keysVec(a);
radixsort(aa.begin(), aa.end(), 1, 10);
print_vec(aa);*/
