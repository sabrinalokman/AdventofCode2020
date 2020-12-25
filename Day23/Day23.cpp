#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
vector<int> cups;
int moves = 100;




void print(vector<int> C){
	for (auto a : C) {
		cout << a << " ";
	}
	cout << endl;
}

void loadFile (string file) {

	ifstream infile;
	infile.open(file);
	string line;
	while (infile >> line) {
		for (char a : line)
			if(isdigit(a)) {
				cups.push_back(a - '0');
			}
			
	}
	infile.close();
}

int getIndex(vector<int> v, int K){

    auto it = find(v.begin(), v.end(), K);

    if (it != v.end()) {
        int index = it - v.begin();
        //cout << "Index found at " << index << endl;
        return index;

    }
    else {
    	return -1;
    }
}

int getDestination(vector<int> cup, int d) {
	if (d == 0) return getDestination(cup, *max_element(cup.begin(), cup.end()));

	if (getIndex(cup, d) < 0) {
		if(d-1 > 0) {
			return getDestination(cup, d-1);
		}
		else if(d-1 <= 0) {
			return getDestination(cup, *max_element(cup.begin(), cup.end()));
		}

	} else return getIndex(cup, d);
}

void adjustCups() {
	vector<int> temp;

	for(int i = 0; i < cups.size(); i++) {
		if(cups[i] != 0) {
			temp.push_back(cups[i]);
		}
	}

	for(int i = 0; i < temp.size(); i++) {
		cups[i] = temp[i];
	}

	for(int i = temp.size(); i < cups.size(); i++) {
		cups[i] = 0;
	}
}


void playCrabCups() {

	int destination;
	queue<int> pickUp;
	int i = 0;
	int curr = 0;
	int N = cups.size();

	while(moves--) {
		//cout << "\nMOVE " << 10 - moves << endl; 

		//Pick up 3 cups
		//cout << "Current cup (" << cups[i] << ")\n";
		curr = cups[i];
		int counter = 1;
		//cout << "Pick up ( ";
		while(counter <= 3) {
			//cout << cups[(i+counter)%N] << " ";
			pickUp.push(cups[(i+counter)%N]);
			cups[(i+counter)%N] = 0;
			counter++;
		} 
		//cout <<")\n";
		//print(cups);

		adjustCups();
		//cout << "After adjust :\t\t\t";
		//print(cups);

		int destInd = getDestination(cups, curr - 1);
		counter = cups.size() - 3;

		while((counter+i) > destInd) {
			cups[i+counter+3] = cups[counter+i];
			cups[counter+i] = 0; //optional
			counter--;
		}
		//cout << "Space after destination at " <<  cups[destInd] << " :\t";
		//print(cups);

		counter = 1;
		while(!pickUp.empty()){
			cups[destInd+counter] = pickUp.front();
			pickUp.pop();
			counter++;
		}

		//cout << "Final State before next move : \t";
		//print(cups);
		i = (getIndex(cups, curr) + 1)%N;
	}
	cout << "Question 1 : "; 
	print(cups);
}

	
int main() {
	
	loadFile("Day23Data.txt");
	playCrabCups();


}