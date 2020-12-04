#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>
std::ifstream infile ("Day4Data.txt");

using namespace std;

bool isFieldValid(const std::__cxx11::basic_string<char> key, const std::__cxx11::basic_string<char> value)
{	//std::cout << key << " " << value << '\n';
	
	if(key == "byr") {
		if(stoi(value) >= 1920 && stoi(value) <= 2002) {	
			return true;	
		} 
	}

	else if(key == "iyr") {
		if(stoi(value) >= 2010 && stoi(value) <= 2020) {
			return true;
		}
	}

	else if(key == "eyr") {
		if(stoi(value) >= 2020 && stoi(value) <= 2030) {
			return true;
		}
	}

	else if(key == "hgt") {
		if(value.substr(value.size() - 2) == "cm")  {// need to figure out how to get the last two
			if(stoi(value) >= 150 && stoi(value) <= 193) {//need to get the digit
				return true;
			} 
			else return false;
		}
		else if(value.substr(value.size() - 2) == "in") {
			if(stoi(value) >= 59 && stoi(value) <= 76) {
				return true;
			}
			else return false;
		}
	}
	else if(key == "hcl") {
		if(value[0] == '#') {
			for(int i = 1; i < value.size(); i++) {
				if((value[i] >= 'a' && value[i] <= 'f') ||
					(value[i] >= '0' && value[i] <= '9')) {
					return true;
				}
				else return false;
			}
		}
		else return false;
	}
	else if(key == "ecl") {
		if(value == "amb" || value == "blu" || value == "brn" ||
			value == "gry" || value == "grn" || value == "hzl" ||
			value == "oth") {
			return true;
		}
		else return false;
	}
	else if(key == "pid" && value.size() == 9) {
		return true;
	}
	else if(key == "cid") {
		return true;
	}
	else return false;
}



bool isPassportValid(map<string,string> mp) 
{	
	if (mp.size() == 8) 
	{	bool prev = 1;
		for(auto a : mp) {
			//std::cout << a.first << " " << a.second << " ";
			bool result = isFieldValid(a.first, a.second);
			if (prev != result) {
				return false;
			}
			//std::cout << result << "\n";
		}
		return true;
	}

	else if(mp.size() == 7) 
	{
		auto it = mp.find("cid");
		if (it != mp.end()) // means i found cid part of this
		{
			return false;
		} 
		else {
			for(auto a : mp) {
				if(!isFieldValid(a.first, a.second))
					return false;
			}
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
	return isPassportValid(passportMap);
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
			
	std::cout << counter << " passport's are valid out of " << passport << "\n";
}