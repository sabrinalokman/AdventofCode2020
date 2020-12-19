#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <math.h>
#include <climits>
#include <numeric>
#include <queue>
#include <algorithm>
std::ifstream infile ("Day9Data.txt");
std::ifstream infile2 ("Day9Data.txt");
using namespace std;

int preambleNum = 25;
vector<long> keepPreamble(preambleNum, 0);
long result = INT_MIN;
long solution = 0;

void preambleArr(long a, int i) { keepPreamble[i] = a; }

long preambleTwoSum(long k) {
	map<long, long> hashmap;

	for (int i = 0; i < preambleNum; i++) {
		auto search = hashmap.find(k - keepPreamble[i]);
		if(search != hashmap.end() && search->second != i) {
			return -1;
		} 
		hashmap[keepPreamble[i]] = k - keepPreamble[i];
	} 
	return k;
}

void solution1(long a, int i) {
	long temp = result;
	result = preambleTwoSum(a);
	result = max(temp, result);
	preambleArr(a, i);
}

long long solution2(queue<long long> q) {
	
	vector<long long> v;
	while(!q.empty()) {
		v.push_back(q.front());
		q.pop();
	}

	return solution = *std::max_element(v.begin(), v.end()) + *std::min_element(v.begin(), v.end());
}

int main() {
	std::string line;
	long a, b, i = 0;
	
	while(std::getline(infile, line)) {
		std:istringstream iss(line);
		if(!(iss >> a >> b)) {
			if(i < preambleNum) {
				solution1(a, i);
				i++;
			} 
			else {
				i = 0;
				solution1(a, i);
				i++;
			}
		}
	}

	cout << "Answer Q1 : "<< result << "\n";

	long long sumPreamble = 0;
	queue<long long> q;

	while(std::getline(infile2, line)) {
		istringstream iss(line);
		if(!(iss >> a >> b)) {
			if (a == result) return 0;

			if(sumPreamble < result) {
				sumPreamble += a;
				q.push(a);
				//cout << "PUSH : " << a << endl;
			}
			else {
				sumPreamble += a;
				q.push(a);
				//cout << "PUSH : " << a << endl;
				//cout << "Before: " << sumPreamble << endl;
				while (sumPreamble > result) {
					sumPreamble -= q.front();
					//cout << "POP : " << q.front() << endl;
					q.pop();
				} 
				//cout << "After: " << sumPreamble << endl;

				if(sumPreamble == result) {
					cout << "Answer Q2 : " << solution2(q) << endl;
					return 0;
				}
			}
		}
	}

}