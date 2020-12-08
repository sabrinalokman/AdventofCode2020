#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <utility>
std::ifstream infile ("Day7Data1.txt");

using namespace std;
map <string, int> uniqueBag;
pair<string, string> dependency;
vector<pair<string,string>> canContainGold;
int counter = 0;

int countOccurence(string line, string str) {
	string l;
	int count;
	std:istringstream iss(line);
	while(getline(iss, l, ' ')) {
		int charCount = 0;
		for(int i = 0; i < str.size(); i++) {
			if( l[i] == str[i] ) charCount++; //check for 'b' 'a' 'g' in the word
			if (charCount == str.size()) count++;
		}
	} return count;
}

vector<string> bagGroup(string line, string str) {
	int afterFirst = 11;
	int subsequent = 4;

	vector<string> bagGroup;

	std::size_t found = line.find(str);
	int count = countOccurence(line, str);
	int prevLength = 0;

	bagGroup.push_back(line.substr(0, found)); //for the first item

	for(int i = 1; i < count; i++) {
		found = line.find(str, found+i);

		if(i == 1) { //take care of "first item contains"
			prevLength = bagGroup[i-1].length() + str.length() + 1 + afterFirst;
			bagGroup.push_back(line.substr(prevLength, found - prevLength));
		}

		else if (i > 1) { //take care of subsequent item 
			if(line[prevLength + bagGroup[i-1].length() + str.length() + 1] == 's') {
				prevLength += bagGroup[i-1].length() + str.length() + subsequent;
			} 
			else if(line[prevLength + bagGroup[i-1].length() + str.length() + 1] == ',') {
				prevLength += bagGroup[i-1].length() + str.length() + 1 + subsequent;
			} 
			else 
				prevLength += bagGroup[i-1].length() + str.length() + subsequent;


			bagGroup.push_back(line.substr(prevLength, found - prevLength));
		}

	}

	// for(auto a : bagGroup) {
	// 	cout << a << endl;
	// }
	
	return bagGroup;
}

int numOfBags(map<string, vector<string>> dependencies, string str) {

	for (auto a : dependencies) {
		if (a.first == str) {
			for(auto b : a.second) {
				if(!uniqueBag[b]) {
					uniqueBag[b]++;
					counter++;
					numOfBags(dependencies, b);
				}
			}
		}
		
	}
	return uniqueBag.size();
}

int numOfParent(vector<pair<string,string>> canContainGold, string str) {
	
	for(auto a : canContainGold) {
		if (a.first == str) {
			if(!uniqueBag[a.second]) {
				uniqueBag[a.second]++;
				numOfParent(canContainGold, a.second);
			}
		}
	}

	return uniqueBag.size();

}

int main() {
	std::string line;
	int result1 = 0, result2 = 0;
	map<string, vector<string>> dependencies;
	string str("bag");
	string gold = ("shiny gold ");


	while(getline(infile, line)) {
		std:istringstream iss(line);
		vector<string> rule = bagGroup(line, str);

		for(int i = 0; i < rule.size(); i++) {
			if(i+1 == rule.size()) {
				canContainGold.push_back(make_pair("null", rule[i]));
			} else {
				canContainGold.push_back(make_pair(rule[i+1], rule[0]));
			}
		}
	}

		// for (auto a : canContainGold) {
		// 	cout << a.first << "\t :" << a.second << "\n";
		// } cout << "\n";



	// for(auto a : dependencies) {

	// 	cout << a.first << " : ";
	// 	for(auto b : a.second) {
	// 		cout << b << " ";
	// 	}
	// 	cout << "\n";
	// }

	result1 = numOfParent(canContainGold, gold);
	// for (auto a : uniqueBag) {
	// 	std::cout << a.first << "\n";
	// }



	//result1 = numOfBags(dependencies, gold); 

	cout << "Answer Q1 : "<< result1 << "\n";	
	//cout << "Answer Q2 : "<<result2 << "\n";
}