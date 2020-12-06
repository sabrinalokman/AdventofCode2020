#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
std::ifstream infile ("Day6Data.txt");

using namespace std;

int main() {
	std::string line;
	int result1 = 0, result2 = 0, people = 0;
	map<char,int> uniqQ;
	
	while(std::getline(infile, line)) {
		std:istringstream iss(line);
		if(!line.empty()) {
			people++;
			if(line.length() > 1) {
				for(auto a : line) {
					uniqQ[a]++;
				}
			}
			else if (line.length() == 1) {
				uniqQ[line[0]]++;
			}
		} else {
			result1 += uniqQ.size();
			//std::cout << uniqQ.size() << "\n";
			for (auto i : uniqQ) {
				if(i.second == people) {
					result2++;
				}
				// cout << i.first << " " << i.second << " " << count << "\n";
			}
			uniqQ.clear();
			people = 0; 
		}
	}
	cout << "Answer Q1 : "<<result1 << "\n";	
	cout << "Answer Q2 : "<<result2 << "\n";
}