#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
std::ifstream infile ("Day1Data.txt");
using namespace std;

vector<int> threeNumberSum(vector<int> array, int targetSum) {
	vector<int> result;
	std::sort(array.begin(), array.end());
	for (int i = 0; i < array.size() - 2; i++) {
		int l = i + 1, r = array.size()-1;
		while (l < r) {
			if (array[i] + array[l] + array[r] == targetSum) {
				result.push_back(array[i]);
				result.push_back(array[l]);
				result.push_back(array[r]);
				r--;
				l++;
			}
			else if (array[i] + array[l] + array[r] < targetSum) {
				l++;
			} 
			else if (array[i] + array[l] + array[r] > targetSum) {
				r--;
			} 
		}	
	}
  return result;
}

int main() {
	std::string line;
	std::vector<int> array;

	while(std::getline(infile, line)) {
		std::istringstream iss(line);
		int a, b;
		if(!(iss >> a >> b)) {
			array.push_back(a);
		}
	}

	std::vector<int> solution {threeNumberSum(array, 2020)};
	int multiplied = 1;
	for (auto a : solution) {
		std::cout << a <<" ";
		multiplied *= a;
	}

	std::cout << "\n" << multiplied << "\n";

}