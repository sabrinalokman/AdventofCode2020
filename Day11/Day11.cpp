#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
vector<string> seats;

void printSeats(){
	for (int row = 0; row < seats.size(); row++){
		for (int col = 0; col < seats[row].size(); col++){
			cout << seats[row][col];
		}
		cout << endl;
	}
	cout << endl;
}

void loadFile (string file) {

	seats.clear();

	ifstream infile;
	infile.open(file);
	string line;
	while (infile >> line) {
		seats.push_back(line);
	}
	infile.close();
}

int adjMatrix(int row, int col) {
		int count = 0;

		// Above
		if (row-1 >= 0 && seats[row-1][col] == '#')
			count++;
		// Below
		if (row+1 < seats.size() && seats[row+1][col] == '#')
			count++;
		// Right
		if (col+1 < seats[row].size() && seats[row][col+1] == '#')
			count++;
		// Left
		if (col-1 >= 0 && seats[row][col-1] == '#')
			count++;
		// Top left corner
		if (row-1 >= 0 && col-1 >= 0 && seats[row-1][col-1] == '#')
			count++;
		// Below left corner
		if (row+1 < seats.size() && col-1 >= 0 && seats[row+1][col-1] == '#')
			count++;
		// Above right corner
		if (row-1 >= 0 && col+1 < seats[row].size() && seats[row-1][col+1] == '#')
			count++;
		// Below right corner
		if (row+1 < seats.size() && col+1 < seats[row].size() && seats[row+1][col+1] == '#')
			count++;

		return count;

}

//Part 2 Rule change

enum direction {N, E, S, W, NE, NW, SE, SW};

bool checkDirection(int row, int col, direction dir) {
// First return false if we went out of bounds (we didn't find an occupied seat)
	if (row < 0 || row >= seats.size() || col < 0 || col >= seats[row].size())
		return false;

	// Check if the seat is occupied and return true if so
	if (seats[row][col] == '#')
		return true;
	// Check if we hit an unoccupied seat and return false if so
	if (seats[row][col] == 'L')
		return false;

	// Recursively check the next seat in the given direction
	switch (dir){
		case N:  return checkDirection(row-1, col, N);
		case S:  return checkDirection(row+1, col, S);
		case E:  return checkDirection(row, col+1, E);
		case W:  return checkDirection(row, col-1, W);
		case NE: return checkDirection(row-1, col+1, NE);
		case NW: return checkDirection(row-1, col-1, NW);
		case SE: return checkDirection(row+1, col+1, SE);
		case SW: return checkDirection(row+1, col-1, SW);
	}
}

int directionMatrix (int row, int col) {
	int count = 0;

	if (checkDirection(row-1, col, N))
		count++;
	if (checkDirection(row+1, col, S))
		count++;
	if (checkDirection(row, col+1, E))
		count++;
	if (checkDirection(row, col-1, W))
		count++;
	if (checkDirection(row-1, col+1, NE))
		count++;
	if (checkDirection(row-1, col-1, NW))
		count++;
	if (checkDirection(row+1, col+1, SE))
		count++;
	if (checkDirection(row+1, col-1, SW))
		count++;

	return count;
}

bool isChanged(int rule) {
	vector<string> tempSeats = seats;
	bool changed = false;

	if (rule == 4) {
		for(int i = 0; i < seats.size(); i++ ) {
			for(int j = 0; j < seats[i].size(); j++) {
				if(seats[i][j] == 'L' && adjMatrix(i,j) == 0){
					tempSeats[i][j] = '#';
					changed = true;
				}
				if(seats[i][j] == '#' && adjMatrix(i,j) >= rule){
					tempSeats[i][j] = 'L';
					changed = true;
				}
			}
		} 
	}

	if (rule == 5) { 
		for(int i = 0; i < seats.size(); i++ ) {
			for(int j = 0; j < seats[i].size(); j++) {
				if(seats[i][j] == 'L' && directionMatrix(i,j) == 0){
					tempSeats[i][j] = '#';
					changed = true;
				}
				if(seats[i][j] == '#' && directionMatrix(i,j) >= rule){
					tempSeats[i][j] = 'L';
					changed = true;
				}
			}
		}
	}

	seats = tempSeats;

	return changed;
}

int solution(int part) {
	int occupied = 0;
	
	if (part == 1) { while (isChanged(4)); }

	if (part == 2) { while (isChanged(5)); }

	for(int i = 0; i < seats.size(); i++) {
		for(int j = 0; j < seats[i].size(); j++) {
			if(seats[i][j] == '#')
				occupied++;
		}
	}

	return occupied;
}
	
int main() {
	
	loadFile("Day11Data.txt");

	cout << "Answer Q1 : "<< solution(1) << "\n";

	loadFile("Day11Data.txt");

	cout << "Answer Q2 : "<< solution(2) << "\n";	
}