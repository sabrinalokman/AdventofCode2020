#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
std::ifstream infile ("Day8Data.txt");

using namespace std;
int accumulator = 0;
map<pair<int, bool>, pair<string, int>> data;
int counter = 0;
bool accInstBool = 1;
bool jmpInstBool = 1;

bool accInst(int acc, map<pair<int, bool>, pair<string, int>> &data) {
	accumulator += acc;
	//cout << "\nAdd " << acc << "\n";

	auto entry = data.find(make_pair(counter, 0));
	if (entry != end(data))
	{
	    auto const value = std::move(entry->second);
	    data.erase(entry);
	    data.insert({make_pair(counter, 1), std::move(value)});
	    counter++;
	    return true;
	}
	else {
		accInstBool = 0;
		return false;
	}
}

bool jmpInst(int jmp, map<pair<int, bool>, pair<string, int>> &data) {
	//cout << "\nJump " << jmp << "\n";
	auto entry = data.find(make_pair(counter + jmp , 0));
	if (entry != end(data)) 
	{	counter = counter + jmp;
		if(entry->second.first == "acc") {
			accInst(entry->second.second, data);
		}
		else if (entry->second.first == "jmp") {
			jmpInst(entry->second.second, data);
		}
		auto const value = std::move(entry->second);
		data.erase(entry);
		data.insert({make_pair(counter, 1), std::move(value)});
		return true;
	}
	else {
		jmpInstBool = 0;
		return false;
	}
}

void print(map<pair<int, bool>, pair<string, int>> &data) {
	for (auto a : data) {

		cout << a.first.first << " " << a.first.second << " "
		<< a.second.first << " " << a.second.second;

		cout << "\n";
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
	// print(data);

	while(accInstBool && jmpInstBool) {
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
	}

	// print(data);


	cout << "Answer Q1 : "<< accumulator << "\n";	
}