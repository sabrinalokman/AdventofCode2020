#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>
std::ifstream infile ("Day10Data.txt");

using namespace std;
int count3 = 1;
int count1 = 1;
int next = 0;

int main() {
	std::string line;
	int a, b;
	vector<int> jolt;
	
	while(std::getline(infile, line)) {
		std:istringstream iss(line);
		if(!(iss >> a >> b)) {
			jolt.push_back(a);
		}
	}
	std::sort(jolt.begin(), jolt.end());

	for(int i = jolt.size() - 1; i >= 0; i--) {
		if(jolt[i] - jolt[i-1] == 1 && (i - 1) > -1) {
			count1++;
		} else if(jolt[i] - jolt[i-1] == 3 && (i - 1) > -1) {
			count3++;
		}

	}

	cout << "Answer Q1 : "<< count3*count1 << "\n";	
}