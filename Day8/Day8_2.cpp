#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
std::ifstream infile ("Day8Data1.txt");

using namespace std;
int accumulator = 0;
map<pair<int, bool>, pair<string, int>> data;
int counter = 0;
bool isChanged = 0;
int oldIdx = -1;
string oldStr;
int oldVal;
map<int, int> tracker;



void accInst(int acc, map<pair<int, bool>, pair<string,int>> &data) {
	accumulator += acc;
	tracker[counter] = accumulator;
	//cout << "\nAdd " << acc << "\n";
	counter++;
	//cout << "current counter " << counter << endl;
}

void jmpInst(int jmp, map<pair<int, bool>, pair<string,int>> &data) {
	//cout << "\nJump " << jmp << "\n";
	counter = counter + jmp;
	//cout << "Current counter " << counter << endl;
}

void print() {
	for (auto a : data) {
		cout << a.first.first << " " << a.first.second << " "
		<< a.second.first << " " << a.second.second;
		
		cout << "\t "<<tracker[a.first.first];
		cout<< "\n";
	}cout << "\n";


}

void overwrite(string str, int idx, int val, map<pair<int, bool>, pair<string,int>> &data) {

	//cout<< "\nOverwriting to " << str << " with idx " << idx << endl;

	auto entryOld = data.find(make_pair(oldIdx, 1));
	if (entryOld != end(data) && !isChanged) 
	{	//cout << "inside old entry\n" << endl;
	    data.erase(entryOld);
	    data.insert({make_pair(oldIdx, 1), make_pair(oldStr,oldVal)});
		isChanged = 1;

	}
	
	auto entryNew = data.find(make_pair(idx, 0));
	if (entryNew != end(data)) 
	{	//cout << "inside new entry\n";
		oldStr = entryNew->second.first;
		oldVal = entryNew->second.second;
	    data.erase(entryNew);
	    data.insert({make_pair(idx, 1), make_pair(str, val)});
		counter = idx;
		oldIdx = idx;
		//accumulator = tracker[idx];
		while(tracker[idx] == 0) {
			idx--;
		}

		accumulator = tracker[idx];
		cout << counter << " " << accumulator << endl;
		isChanged = 0;
		
	}
}



int main() {
	std::string line;
	string a;
	int b, c;
	
	while(std::getline(infile, line)) {
		std:istringstream iss(line);
		if(!(iss >> a >> b >> c)) {
			data[make_pair(counter, 0)] = make_pair(a,b);
			counter++;
		}
	}
	counter = 0;
	int tmp = 0;

	int N = data.size();

	while (counter < N) {
		if(counter < tmp) {		
		tmp = 0;
			for (auto a : data) {
				if(a.second.first == "jmp" &&
				 a.second.second != 0 && a.first.second == 0) {
					overwrite("nop", a.first.first, a.second.second, data);
					break;
				}
				else if(a.second.first == "nop" &&
					a.second.second != 0 && a.first.second == 0) {
					overwrite("jmp", a.first.first, a.second.second, data);
					break;
				}
			}
		} 
		else
		{	print();
			tmp = counter;

			auto check = data.find(make_pair(counter,0));
			if(check != end(data)) {
				auto a = data[make_pair(counter, 0)];
				if(a.first == "acc") {
					accInst(a.second, data);
				}

				else if (a.first == "jmp") {
					jmpInst(a.second, data);
				} 

				else {
					counter++;
				}
			} else {
				auto a = data[make_pair(counter, 1)];
				if(a.first == "acc") {
					accInst(a.second, data);
				}

				else if (a.first == "jmp") {
					jmpInst(a.second, data);
				} 

				else {
					counter++;
				}
			}			
		}	
	}

	// for(auto j : tracker) {
	// 	cout << j.first << " " << j.second << endl;
	// }



	cout << "Answer Q2 : "<< accumulator << "\n";		
}