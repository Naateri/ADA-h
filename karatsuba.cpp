#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <math.h>
//using namespace std;

typedef std::string str;
typedef std::stringstream ss;

str intToString(const int &z) {
	ss leString;
	leString << z;
	return leString.str();
}

int karatsuba_multiply(int j, int k){
	str sj, sk;
	int n, a, b, c, d, pot;
	sj = intToString(j);
	sk = intToString(k);
	n = std::max(sj.size(), sk.size());
	pot = pow(10, int(n/2));
	//j = a*pot + b, b = j - a * pot
	a = j / pot;
	b = j - a * pot; 
	c = k / pot;
	d = k - a * pot;
	
}

int main(int argc, char *argv[]) {
	
	return 0;
}

