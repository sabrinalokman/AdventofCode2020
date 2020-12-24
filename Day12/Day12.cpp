#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;
vector<char> action;
vector<int> value;
map<int, pair<char, int>> instruction;
int direction = 90; // 0 , 90, 180, 270

void print(){
	for (auto a : instruction) {
		cout << a.first << " "
			<< a.second.first << " "
			<< a.second.second << endl;
	}
}

void loadFile (string file) {

	ifstream infile;
	infile.open(file);
	string line, temp;
	while (infile >> line) {
		for(auto a : line) {
			if(isalpha(a)) { action.push_back(a); }
			else if(isdigit(a)) { temp += a; }
		}
		value.push_back(stoi(temp));
		temp.clear();
	}

	int i = 0;
	for(auto a : action) {
		instruction[i] = make_pair(a, value[i]);
		i++;
	}
	infile.close();
}

void navigate() {
	int Y = 0, X = 0; 
	int waypointY = 1, waypointX = 10;
	int X2 = 0, Y2 = 0;
	for(auto a : instruction) {
		switch(a.second.first) {
			case 'N': 
				Y += a.second.second; 
				waypointY += a.second.second; break;
			case 'S': 
				Y -= a.second.second;
				waypointY -= a.second.second; break;
			case 'E': 
				X += a.second.second;
				waypointX += a.second.second; break;
			case 'W': 
				X -= a.second.second;
				waypointX -= a.second.second; break;
			case 'R':
				direction = (direction + a.second.second) % 360;
				for (int i=0; i<(a.second.second/90); i++) {
					swap(waypointX, waypointY);
					waypointY *= -1;
				}
				break;
			case 'L':
				direction = (direction + 360 - a.second.second) % 360;
				for (int i=0; i<(a.second.second/90); i++) {
					swap(waypointX, waypointY);
					waypointX *= -1;
				}
				break;
			case 'F':
			switch (direction) {
				case 0:
				Y += a.second.second; break;
				case 90:
				X += a.second.second; break;
				case 180:
				Y -= a.second.second; break;
				case 270:
				X -= a.second.second; break;
			}
			
			X2 += a.second.second*waypointX;
			Y2 += a.second.second*waypointY;
			break;
		}
	}

	cout << "Answer Q1 :" << abs(X) + abs(Y) << endl;
	cout << "Answer Q2 :" << abs(X2) + abs(Y2) << endl;
	
}
	
int main() {
	
	loadFile("Day12Data.txt");
	navigate();	
}