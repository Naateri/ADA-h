#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <ctime>

typedef std::vector<int> int_vec;
typedef std::pair<int, int> int_key; //key, value
typedef std::vector<int_key> keys_vec;
typedef std::vector<std::vector<int_key> > vecs_vec;
typedef std::stringstream ss;
typedef std::string str;

char endl = '\n';

void print_keysVec(keys_vec A){
	for(int i = 0; i < A.size(); i++){
		std::cout << A.at(i).second << ' ';
	}
	std::cout << endl;
}

bool operator<(const int_key &a, const int_key &b){
	return a.first < b.first;
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

keys_vec merge(keys_vec A, keys_vec B){ //modify so that it can sort the pairs
	keys_vec result;
	while (!A.empty() && !B.empty()){
		if ( (A.front()).first < (B.front()).first){
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

keys_vec mergesort(keys_vec& A){
	if (A.size() <= 1)
		return A;
	keys_vec left, right, result;
	std::copy(std::begin(A), std::begin(A) + A.size()/2, std::back_inserter(left));
	std::copy(std::begin(A) + A.size()/2, std::end(A), std::back_inserter(right));
	result = merge(mergesort(left), mergesort(right));
	A = result;
	return result;
}

int get_bucket(int num, int k, int num_buckets){
	return num/(k / num_buckets);
}

/********************************** 
 COUNTING SORT
   **************************************** */

void counting_sort(int_vec& A, int k){
	int_vec counts (k), result;
	int temp;
	std::fill(counts.begin(), counts.end(), 0);
	for (int i = 0; i < A.size(); i++){
		counts.at(A.at(i))++;
	}
	A.clear();
	for (int i = 0; i < k; i++){
		temp = counts.at(i);
		for(int j = 0; j < temp; j++){
			A.push_back(i);
		}
	}
}

/********************************** 
BUCKET SORT
**************************************** */


keys_vec bucket_sort(keys_vec A, int k, int num_buckets){
	vecs_vec buckets (num_buckets);
	keys_vec result;
	keys_vec temp;
	for(int i = 0; i < A.size(); i++){
		buckets.at( get_bucket( (A.at(i) ).first, k, num_buckets ) ).push_back(A.at(i));;
	}
	if (num_buckets < k){
		for(int i = 0; i < buckets.size(); i++){
			//mergesort(buckets.at(i));
			std::stable_sort(buckets.at(i).begin(), buckets.at(i).end());
		}
	}
	for(int i = 0; i < buckets.size(); i++){
		temp = buckets.at(i);
		for(int j = 0; j < temp.size(); j++){
			result.push_back((temp.at(j) ) );
		}
	}
	return result;
}

/********************************** 
RADIX SORT
**************************************** */


int n_digit(int num, int n, int d){
	str snum;
	snum = intToString(num);
	while (snum.size() < d){
		snum = '0' + snum;
	}
	snum = snum[n];
	snum += '\0';
	return stringToInt(snum);
}

keys_vec int_to_keys(int_vec A){ //transforms a vector of only ints to a vector of pairs (key, val)
	int_key temp;
	keys_vec ret;
	temp.first = 0;
	for(int i = 0; i < A.size(); i++){
		temp.second = A.at(i);
		ret.push_back(temp);
	}
	return ret;
}

keys_vec radix_sort(int_vec A, int d, int k){
	int_key temp;
	keys_vec A_j, result, A_t = int_to_keys(A);
	for (int j = 0; j < d; j++){
		A_j.clear();
		for(int i = 0; i < A_t.size(); i++){
			temp.second = A_t.at(i).second;
			temp.first = n_digit(A_t.at(i).second, d-j-1, d);
			A_j.push_back(temp);
		}
		result = bucket_sort(A_j, k, k);
		A_t = result;
	}
	return result;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	int_vec A0 (8);
	A0 = {0,0,3,1,1,3,1,0};
	counting_sort(A0, 4);
	print_vec(A0);
	int_vec A (8);
	A = {31,5,210,14,95,477,555,125};
	keys_vec test, test2 (10);
	int_key temp;
	int tmp;
	for(int i = 0; i < 10; i++){
		tmp = rand() % 50;
		temp.first = temp.second = tmp;
		test2.at(i) = temp;
	}
	test = bucket_sort(test2, 50, 10);
	print_keysVec(test);
	test = radix_sort(A, 3, 10);
	print_keysVec(test);
	return 0;
}

