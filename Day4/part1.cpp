#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>
std::ifstream infile ("Day4Data1.txt");

using namespace std;

bool isValid(map<string,string> mp) 
{
	if (mp.size() == 8) return true;

	else if(mp.size() == 7) 
	{
		auto it = mp.find("cid");
		if (it != mp.end()) // means i found cid part of this
		{
			return false;
		} 
		return true;
	} 

	else return false;
}

bool parseData(vector<string> eachPassport) {
	
	map<string, string> passportMap;

	for (int i = 0; i < eachPassport.size(); i++) 
	{
		string key = eachPassport[i].substr(0, eachPassport[i].find(':'));
		string data = eachPassport[i].substr(eachPassport[i].find(':')+1);
		passportMap[key] = data;
	}

	// for(auto a: passportMap) std::cout << a.first << " " << a.second << "\n";

	return isValid(passportMap);
}

int main() {
	std::string line, l;
	vector<string> data , passportData;
	int counter = 0;
	int passport = 0;

	while(std::getline(infile, line)) {
		std:istringstream iss(line);
		if(line.empty()) {
			data.push_back(" ");
			passport++;
		}
		while(std::getline(iss, l, ' ')) {
			data.push_back(l);
		} 	
	}

	// for (auto a : data) std::cout << a << " " << a.length() << " \n";

	for (auto a : data) 
	{
		if (a.length() != 1) 
		{
			passportData.push_back(a);
		} 
		else 
		{	
			// for (auto b : passportData) std::cout << b << "\n";
			if(parseData(passportData)) counter++;
			passportData.clear();
		}
	}
			
	std::cout << "Counter is " << counter <<" and passport is " << passport << "\n";
}