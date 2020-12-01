#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
std::ifstream infile ("Day1Data.txt");
using namespace std;


vector<int> twoNumberSum(vector<int> array, int targetSum) {
  unordered_map <int,int> hashmap {std::make_pair(array[0], 0)};
	for(int i = 0; i < array.size(); ++i) {
		auto search = hashmap.find(targetSum - array[i]);
		if(search != hashmap.end() && search->second != i) {
			return {search->first, array[i]};
		}  hashmap[array[i]] = i;
	} return {};
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

	std::vector<int> solution {twoNumberSum(array, 2020)};
	int multiplied = 1;
	for (auto a : solution) {
		std::cout << a <<" ";
		multiplied *= a;
	}

	std::cout << "\n" << multiplied << "\n";

}