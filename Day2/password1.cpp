#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
std::ifstream infile ("Day2Data.txt");

using namespace std;

bool isValid(int i, int j, char k, string l) {
	int count = 0;
	for (auto a : l) {
		if (a == k) {
			count++;
		}
	}
	return count >= i && count <= j;
}

int main() {
	std::string line;
	int counter = 0;
	while(std::getline(infile, line)) {
		std::istringstream iss(line);
		int a, b;
		string C;
		char c; //letter but it has colon
		string d; //string
		int e; //endline

		if(!(iss >> a >> b >> C >> d >> e)) {
			c = C[0];
			if(isValid(a, abs(b), c, d)) {
				counter++;
			}
		}	
	}
	std::cout << counter << "\n";
}