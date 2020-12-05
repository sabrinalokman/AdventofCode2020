#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
std::ifstream infile ("Day5Data.txt");

using namespace std;


int main() {
	std::string line;
	std::priority_queue<int> q;
	

	while(std::getline(infile, line)) {
		std:istringstream iss(line);
		int front = 0, back = 127;
		int left = 0, right = 7;
		int resultRow, resultCol;

		for (int i = 0; i < 6; i++) {
			int row = back - front;
			//std::cout << line[i] << " ";
			if (line[i] == 'F') {
				back -= row/2 + 1 ;
				//std::cout << " : [" << front << "," << back << "]\n"; 
			} else if (line[i] == 'B') {
				front += row/2 + 1;
				//std::cout << " : [" << front << "," << back << "]\n"; 
			}
		} 

		if (line[6] == 'F') {
			resultRow = front;
		} else resultRow = back;

	//std::cout << line[6] << "  : [" << resultRow << "]\n";

		for (int i = 7; i < line.size() - 1; i++) {
			int column = right - left;
			//std::cout << line[i] << " ";
			if (line[i] == 'L') {
				right -= column/2 + 1;
				//std::cout << " : [" << left << "," << right << "]\n"; 
			} else if (line[i] == 'R') {
				left += column/2 + 1;
				//std::cout << " : [" << left << "," << right << "]\n"; 
			}
		}

		if (line[9] == 'L') {
			resultCol = left;
		} else resultCol = right;

		//std::cout << line[9] << "  : [" << resultCol << "]\n";

		q.push(resultCol + resultRow * 8);

		//std::cout << "\n" << resultCol + resultRow * 8 << "\n";
	}
	
	std::cout << "Part 1 Answer: " << q.top() << "\n";
	int temp = q.top();
	while(!q.empty()) {
		if(q.top() != temp) {
			std::cout << "Part 2 Answer: " << temp << "\n";
			return 0;
		}
		else {
			q.pop();
			temp--;
		}
	}
}

//Alternative solution to part 1
//Use one pointer and keep track of step sizes