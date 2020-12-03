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
	int i = 1, j = 3, k = 5, l = 7, m = 1;
	int p = 0, q = 0, r = 0, s = 0, t = 0;

	while(std::getline(infile, line)) {
		std::istringstream iss(line);
		string a, b;
		if(!(iss >> a >> b)) {
			//std::cout << counter << "\n";
			if(counter > 0) {

				//Right 1, down 1
				while(i > 30) {
					i -= 31;
				} 
				if (a[i] == '#') {
					p++;
				}
				i += 1;

				//Right 3, down 1
				while(j > 30) {
					j -= 31;
				} 
				if (a[j] == '#') {
					q++;
				}
				j += 3;


				//Right 5, down 1
				while(k > 30) {
					k -= 31;
				} 
				if (a[k] == '#') {
					r++;
				}
				k += 5;

				//Right 7, down 1
				while(l > 30) {
					l -= 31;
				} 
				if (a[l] == '#') {
					s++;
				}
				l += 7;

				//Right 1, down 2
				if(counter == 2) {
					while(m > 30) {
						m -= 31;
					} 
					if (a[m] == '#') {
						t++;
					}
					m += 1;
					counter = 1;
				} 
				else counter++;
			} 
			else counter++;
		}	
	}
	std::cout << p << ' ';
	std::cout << q << ' ';
	std::cout << r << ' ';
	std::cout << s << ' ';
	std::cout << t << std::endl;

	std::cout << "The answer: "<<p * q * r * s * t << "\n";
}