#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
vector<int> example {0, 3, 6};
vector<int> numbers {8, 0, 17, 4, 1, 12};
int turn = 10;
unordered_map<int,int> age;

void playMemoryGame(vector<int> v) {
	int counter = v.size();
	int i = 0;
	int recent;

	while(counter--) {
		cout << example[i] << " ";
		recent = example[i];
		i++;
		age[example[i]]++;
	}
	cout <<endl << recent << endl;

	for(auto a : age) {
		cout << a.first << " " << a.second << endl;
	}

}
	
int main() {
	playMemoryGame(example);
}