#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <vector>
#include <math.h>
#include <climits>
std::ifstream infile ("Day9Data.txt");
using namespace std;

int preambleNum = 25;
vector<long> keepPreamble(preambleNum, 0);

void preambleArr(long a, int i) {
	keepPreamble[i] = a;

	// for(auto e : keepPreamble) {
	// 	cout << e << " ";
	// } cout << "\n";
}

long preambleSumCheck(long k) {
	// cout << "Check " << k << " with previous array\n";
	map<long, long> hashmap;

	for (int i = 0; i < preambleNum; i++) {
		auto search = hashmap.find(k - keepPreamble[i]);

		// for(auto s: hashmap){ cout << s.first << " " << s.second << "\n";}
		// 	cout << endl;
		if(search != hashmap.end() && search->second != i) {
			return -1;
		} 
		hashmap[keepPreamble[i]] = k - keepPreamble[i];
	} 
	// cout << k << endl;
	return k;

}

int main() {
	std::string line;
	long a, b, i = 0;
	long result = INT_MIN;
	
	while(std::getline(infile, line)) {
		std:istringstream iss(line);
		if(!(iss >> a >> b)) {
			if(i < preambleNum) {
				long temp = result;
				result = preambleSumCheck(a);
				result = max(temp, result);
				preambleArr(a, i);
				i++;
			} 
			else {
				i = 0;
				long temp = result;
				result = preambleSumCheck(a);
				result = max(temp, result);
				preambleArr(a, i);
				i++;
			}
		}
	}

	cout << "Answer Q1 : "<< result << "\n";	
}