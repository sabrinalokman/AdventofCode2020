#include<algorithm>
#include<vector>
#include<utility>
#include<stack>
#include<queue>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
std::ifstream infile ("Day3Data.txt");

using namespace std;


int main() {
	std::string line;
	int counter = 0;
	int i = 3;
	int tree = 0;

	while(std::getline(infile, line)) {
		std::istringstream iss(line);
		string a, b;
		if(!(iss >> a >> b)) {
			if(counter > 0) {
				while(i > 30) {
					i -= 31;
				}
				if (a[i] == '#') {
					tree++;
				}
				i += 3;
			}
			else counter++;
			
			
		}	
	}
	std::cout << tree << "\n";
}