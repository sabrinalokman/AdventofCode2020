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
vector<tuple<int, string, string>> canContainGold;
int result = 0;
int sum = 1;

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

	return bagGroup;
}

void numOfChild(vector<tuple<int, string, string>> canContainGold, string str) {

	for (auto a : canContainGold) {
		if (get<2>(a) == str) {
			if (!uniqueBag[get<2>(a)]) {
					uniqueBag[get<2>(a)] = get<0>(a);
					numOfChild(canContainGold, get<1>(a));
			}
			else if(uniqueBag[get<2>(a)]) {
				uniqueBag[get<2>(a)] += get<0>(a);
				numOfChild(canContainGold, get<1>(a));
			}
			
		}
	}
}

int recursiveMultip(vector<tuple<int, string, string>> canContainGold, string str; map <string, int> uniqueBag){
	for(auto a : canContainGold) {
		if(get<2>(a) == str) {
			for(auto c : uniqueBag) {
				if(c.first == get<1>(a)) {
					result += c.second * get<0>(a) + get<0>(a);
				}
			}
		}
	}

	return result;
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
	string str("bag");
	string gold = ("shiny gold ");


	while(getline(infile, line)) {
		std:istringstream iss(line);
		vector<string> rule = bagGroup(line, str);

		for(int i = 0; i < rule.size(); i++) {
			std::size_t found = line.find(rule[i+1]);
			int temp = line[found - 2] - '0';

			if(i+1 == rule.size()) {
				break;
			}
			else if (rule[i+1] == " other ") {
				canContainGold.push_back(
					make_tuple(0, "null", rule[0]));
			}
			else {
				canContainGold.push_back(
					make_tuple(temp, rule[i+1], rule[0]));
			}
		}
	}

	for (auto a : canContainGold) {
		cout << "["<< get<0>(a) << "] " << get<1>(a) << "\t : " << get<2>(a)  << "\n";
	} cout << "\n";

	//result1 = numOfParent(canContainGold, gold);
	// for (auto a : uniqueBag) {
	// 	std::cout << a.first << "\n";
	// }

	numOfChild(canContainGold, gold);

	// cout << "\n\n";




	// for(auto c : uniqueBag) {
	// 	if(c.first == "null") {}
	// 	else
	// 		result2 += c.second;
	// }


	//cout << "Answer Q1 : "<< result1 << "\n";	
	cout << "Answer Q2 : "<< result2 + uniqueBag.at(gold) << "\n";
}