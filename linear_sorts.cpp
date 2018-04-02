#include <iostream>
#include <vector>
#include <tuple>

typedef std::vector<int> int_vec;
typedef std::tuple<int, int> int_key; //key, value
typedef std::vector<int_key> keys_vec;
typedef std::vector<keys_vec> vecs_vec;

void print_vec(int_vec A){ //from mergesort.cpp
	for(int i = 0; i < A.size(); i++){
		std::cout << A.at(i) << ' ';
	}
	std::cout << '\n';
}

int_vec merge(int_vec A, int_vec B){ //modify so that it can sort the pairs
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

int get_bucket(int num, int k, int num_buckets){
	return 0;
}

void counting_sort(int_vec& A, int k){
	int_vec counts (k), result;
	int temp;
	std::fill(A.begin(), A.end(), 0);
	for (int i = 0; i < A.size(); i++){
		counts.at(A.at(i))++;
	}
	A.clear();
	for (int i = 0; i < k; i++){
		temp = counts.at(i);
		for(int j = 0; i < temp; j++){
			A.push_back(i);
		}
	}
}

int_vec bucket_sort(keys_vec A, int k, int num_buckets){
	vecs_vec buckets (num_buckets);
	int_vec result;
	int_key temp;
	for(int i = 0; i < A.size(); i++){
		buckets.at( get_bucket(std::get<0>(A.at(i)) ) ).push_back(A.at(i));;
	}
	if (num_buckets < k){
		for(int i = 0; i < buckets.size(); i++){
			mergesort(buckets.at(i));
		}
	}
	for(int i = 0; i < buckets.size(); i++){
		temp = buckets.at(i);
		for(int j = 0; j < temp.size(); j++){
			result.push_back(std::get<1>(temp.at(j) ) );
		}
	}
	return result;
	
}


int main(int argc, char *argv[]) {
	
	return 0;
}

