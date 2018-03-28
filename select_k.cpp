#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
//using namespace std;

typedef std::vector<int> int_vec;
typedef std::vector< std::vector<int> > vec_of_vecs;

int select_k(int_vec A, int k);

void print_vec(int_vec A){
	for(int i = 0; i < A.size(); i++){
		std::cout << A.at(i) << ' ';
	}
	std::cout << '\n';
}

int random_choose_pivot(int_vec A){
	srand(time(NULL));
	return rand() % int(A.size());
}

int smartly_choose_pivot(int_vec A){
	int m = A.size() / 5, j, p, p_i;
	int_vec candidate_pivots, temp, cop = A;
	vec_of_vecs groups;
	for(int i = 0; i < m; i++){
		j = 5;
		temp.clear();
		while (j > 0 && !cop.empty() ){
			temp.push_back(cop.front() );
			cop.erase(cop.begin() );
			j--;
		}
		groups.push_back(temp);
	}
	for(int i = 0; i < m-1; i++){
		;//p_i = median(groups[i]);
		//candidate_pivots.push_back(p_i);
	}
	A.at(p) = select_k(candidate_pivots, m/2);
	return p;
}

int partition(int_vec A, int p, int_vec& L, int_vec& R){
	//int_vec L, R;
	L.clear();
	R.clear();
	for (int i= 0; i < A.size() - 1; i++){
		if (i == p) continue;
		else if (A.at(i) <= A.at(p) ) L.push_back(A.at(i));
		else if (A.at(i) > A.at(p) ) R.push_back(A.at(i) );
	}
	std::cout << "L: ";
	print_vec(L);
	std::cout << "R: ";
	print_vec(R);
	return A.at(p);
}

int select_k(int_vec A, int k){
	if (A.size() == 1) return A.at(0);
	int_vec L, R;
	int p = random_choose_pivot(A);
	A[p] = partition(A, p, L, R);
	if (L.size() == k) return A.at(p);
	else if (L.size() > k) return select_k(L, k);
	else if (L.size() < k) return select_k(R, k-L.size()-1);
}

int main(int argc, char *argv[]) {
	int_vec test (6);
	test = {4,8,2,1,3,5};
	std::cout << select_k(test, 4);
	return 0;
}

