#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
//using namespace std;

void insert_sort(std::vector<int>& vec){
	int cur_value, j;
	for(int i = 0; i < vec.size(); i++){
		cur_value = vec[i];
		j = i-1;
		while (j >= 0 && vec[j] > cur_value){
			vec[j+1] = vec[j];
			j--;
		}
		vec[j+1] = cur_value;
	}
}

int main(int argc, char *argv[]) {
	std::vector<int> prueba;
	double Time;
	srand(time(NULL));
	std::ofstream file;
	file.open("i_random.txt");
	std::ofstream file2;
	file2.open("i_ordered.txt");
	std::ofstream file3;
	file3.open("i_orderedB.txt");
	for(int j = 100000; j <= 1000000; j += 100000){ //random
		prueba.clear();
		for(int i = 0; i < j; i++){ //10k -> 100k, 10k jumps
			prueba.push_back(rand());
		}
		clock_t begin = clock();
		insert_sort(prueba);
		clock_t end = clock();
		//std::cout << double(begin) << ' ' << double(end) << '\n';
		Time = double(end-begin) / CLOCKS_PER_SEC;
		file << j << ' ' << Time << std::endl;
		//std::cout << "Time for " << j << " elements: " << Time << std::endl;
	}
	for(int j = 100000; j <= 1000000; j += 100000){ //ordered
		prueba.clear();
		for(int i = 0; i < j; i++){ //10k -> 100k, 10k jumps
			prueba.push_back(i);
		}
		clock_t begin = clock();
		insert_sort(prueba);
		clock_t end = clock();
		//std::cout << double(begin) << ' ' << double(end) << '\n';
		Time = double(end-begin) / CLOCKS_PER_SEC;
		file2 << j << ' ' << Time << std::endl;
		//std::cout << "Time for " << j << " elements (ordered): " << Time << std::endl;
	}
	for(int j = 100000; j <= 1000000; j += 100000){ //ordered
		prueba.clear();
		for(int i = j; i > 0; i--){ //10k -> 100k, 10k jumps
			prueba.push_back(i);
		}
		clock_t begin = clock();
		insert_sort(prueba);
		clock_t end = clock();
		//std::cout << double(begin) << ' ' << double(end) << '\n';
		Time = double(end-begin) / CLOCKS_PER_SEC;
		//cout << "Time for " << j << " elements (reverse ordered): " << Time << std::endl;
		file3 << j << ' ' << Time << std::endl;
	}
	/*clock_t begin = clock();
	insert_sort(prueba);
	clock_t end = clock();
	//std::cout << double(begin) << ' ' << double(end) << '\n';
	Time = double(end-begin) / CLOCKS_PER_SEC;
	std::cout << "Time: " << Time << std::endl;
	for(int i = 0; i < prueba.size(); i++){
		//std::cout << prueba.at(i) << ' ';
	}
	std::cout << '\n';*/
	file.close();
	file2.close();
	file3.close();
	return 0;
}

