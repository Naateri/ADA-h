#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
//using namespace std;

typedef std::vector<int> int_vec;
typedef std::vector< std::vector<int> > vec_of_vecs;

///HELPFUL FUNCTIONS///

int find_elem(int_vec A, int val){
	for(int i = 0; i < A.size(); i++){
		if (A.at(i) == val) return i;
	}
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

void print_vec(int_vec A){
	for(int i = 0; i < A.size(); i++){
		std::cout << A.at(i) << ' ';
	}
	std::cout << '\n';
}

///ACTUAL FUNCTIONS///

int select_k(int_vec A, int k);

int actual_naive_select_k(int_vec A, int k){
	return mergesort(A).at(k);
}

int random_choose_pivot(int_vec A){
	srand(time(NULL));
	return rand() % int(A.size());
}

int median(int_vec A){
	//return mergesort(A).at(A.size()/2);
	return mergesort(A)[A.size()/2];
}

int smartly_choose_pivot(int_vec A){
	int m, j, p, p_i, tempi;
	m = ceil(A.size() / float(5));
	int_vec candidate_pivots, temp;
	int_vec cop(A); ///cop = copy of A
	vec_of_vecs groups (m);
	for(int i = 0; i < m; i++){
		j = 5;
		temp.clear();
		while (j > 0 && !cop.empty() ){
			temp.push_back(cop.front() ); ///adding to temp first element of A's copy
			cop.erase(cop.begin() ); ///then deleting that number
			j--;
		}
		groups.at(i) = temp;
	}
	for(int i = 0; i < m-1; i++){
		p_i = median(groups.at(i));
		candidate_pivots.push_back(p_i);
	}
	tempi = select_k(candidate_pivots, m/2);
	p = find_elem(A, tempi);
	return p;
}

int smartly_choose_pivot_3(int_vec A){
	int m, j, p, p_i, tempi;
	m = ceil(A.size() / float(3));
	int_vec candidate_pivots, temp;
	int_vec cop(A); ///cop = copy of A
	vec_of_vecs groups (m);
	for(int i = 0; i < m; i++){
		j = 3;
		temp.clear();
		while (j > 0 && !cop.empty() ){
			temp.push_back(cop.front() ); ///adding to temp first element of A's copy
			cop.erase(cop.begin() ); ///then deleting that number
			j--;
		}
		groups.at(i) = temp;
	}
	for(int i = 0; i < m-1; i++){
		p_i = median(groups.at(i));
		candidate_pivots.push_back(p_i);
	}
	tempi = select_k(candidate_pivots, m/2);
	p = find_elem(A, tempi);
	return p;
}

int partition(int_vec A, int p, int_vec& L, int_vec& R){
	//int_vec L, R;
	L.clear();
	R.clear();
	for (int i= 0; i < A.size(); i++){
		if (i == p) continue;
		else if (A.at(i) <= A.at(p) ) L.push_back(A.at(i));
		else if (A.at(i) > A.at(p) ) R.push_back(A.at(i) );
	}
	return A.at(p);
}

int naive_select_k(int_vec A, int k){
	if (A.size() == 1) return A.at(0);
	int_vec L, R;
	int p = random_choose_pivot(A);
	A.at(p) = partition(A, p, L, R);
	if (L.size() == k) return A.at(p);
	else if (L.size() > k) return naive_select_k(L, k);
	else if (L.size() < k) return naive_select_k(R, k-L.size()-1);
}

int select_k(int_vec A, int k){
	if (A.size() <= 100) return actual_naive_select_k(A, k);
	int p = smartly_choose_pivot(A);
	int_vec L, R;
	A.at(p) = partition(A, p, L, R);
	if (L.size() == k) return A.at(p);
	else if (L.size() > k) return select_k(L, k);
	else if (L.size() < k) return select_k(R, k-L.size()-1);
}

int select_k_3(int_vec A, int k){
	if (A.size() <= 100) return actual_naive_select_k(A, k);
	int p = smartly_choose_pivot_3(A);
	int_vec L, R;
	A.at(p) = partition(A, p, L, R);
	if (L.size() == k) return A.at(p);
	else if (L.size() > k) return select_k(L, k);
	else if (L.size() < k) return select_k(R, k-L.size()-1);
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	/*int_vec test (10);
	test = {4,8,2,1,3,5,15,18,20,10};*/
	int_vec test2;
	for(int i = 0; i < 1000; i++){
		test2.push_back( int( rand() ) );
	}
	std::cout << actual_naive_select_k(test2, 150) << std::endl;
	std::cout << naive_select_k(test2, 150) << std::endl;
	std::cout << select_k(test2, 150) << std::endl;
	std::cout << select_k_3(test2, 150) << std::endl;
	/*double Time1, Time2, Time3, Time4;
	for(int i = 100000; i <= 1000000; i += 100000){ //random
	test2.clear();
	for(int j = 0; j < i; j++){ //10k -> 100k, 10k jumps
	test2.push_back(rand());
	}
	clock_t begin = clock();
	for(int k = 0; k < 10; k++){
	actual_naive_select_k(test2, rand()%i);
	}
	clock_t end = clock();
	Time1 = double(end-begin) / CLOCKS_PER_SEC;
	Time1 /= 10;
	clock_t begin3 = clock();
	for(int k = 0; k < 10; k++){
	naive_select_k(test2, rand()%i);
	
	}
	clock_t end3 = clock();
	Time2 = double(end3-begin3) / CLOCKS_PER_SEC;
	Time2 /= 10;
	clock_t begin1 = clock();
	select_k(test2, rand()%i);
	clock_t end1 = clock();
	Time3 = double(end1-begin1) / CLOCKS_PER_SEC;
	clock_t begin2 = clock();
	select_k_3(test2, rand()%i);
	clock_t end2 = clock();
	Time4 = double(end2-begin2) / CLOCKS_PER_SEC;
	std::cout << i << " elements: " << Time1 << ' ' << Time2 << ' ' << Time3 << ' ' << Time4 << std::endl;
	}*/
	return 0;
}
