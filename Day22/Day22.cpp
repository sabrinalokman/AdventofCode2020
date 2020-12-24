#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
queue<int> player1;
queue<int> player2;
queue<int> temp1;
queue<int> temp2;




// void printCards() {
// 	for (auto p1 : player1) {
// 		cout << p1 << " ";
// 	}
// 	cout << endl;

// 	for (auto p2 : player2) {
// 		cout << p2 << " ";
// 	}
// 	cout << endl;
// }

void clearQueue(queue<int> q) {
	while(!q.empty()) {
		q.pop();
	}
}

void loadFile (string file) {

	clearQueue(player1);
	clearQueue(player2);

	bool anotherPlayer = false;

	ifstream infile;
	infile.open(file);
	string line;
	int card;
	while (infile >> line) {
		if(line == "Player") { }
		else if(line == "1:") { anotherPlayer = false; }
		else if(line == "2:") { anotherPlayer = true; }
		else {
			if(!anotherPlayer) {
				player1.push(stoi(line));
			}
			if(anotherPlayer) {
				player2.push(stoi(line));
			}
		}
	}
	//printCards();
	infile.close();
}

int playCombat() {

	while(!player1.empty() && !player2.empty()) {
		if(player1.front() > player2.front()) {
			player1.push(player1.front());
			player1.push(player2.front());
		}
		else {
			player2.push(player2.front());
			player2.push(player1.front());
		}
		player1.pop();
		player2.pop();
	}
	return player1.empty() ? 2 : 1;
}

int playRecursiveCombat(queue<int> p1, queue<int> p2) {
	
		bool roundStart = false;

		queue<int> initstate1 = p1;
		queue<int> initstate2 = p2;

	while(!player1.empty() && !player2.empty()) {
		if(roundStart == true && 
			initstate1 == player1 && initstate2 == player2) { 
			return 1; 
		}

		if (player1.front() <= player1.size() - 1 
				&& player2.front() <= player2.size() - 1) {

			temp1.push(player1.front());
			temp2.push(player2.front());

			player1.pop();
			player2.pop();

			queue<int> cpyPlayer1 = player1;
			queue<int> cpyPlayer2 = player2;
			int subWinner = 0;

			while (subWinner == 0) {
				subWinner = playRecursiveCombat(cpyPlayer1, cpyPlayer2);
			}

			if (subWinner == 1) {
				player1.push(temp1.front());
				player1.push(temp2.front());
			} 

			else {
				player2.push(temp2.front());
				player2.push(temp1.front());
			}
	 
			temp1.pop();
			temp2.pop();
			
		} else {

			if(player1.front() > player2.front()) {
				player1.push(player1.front());
				player1.push(player2.front());
			}
			else {
				player2.push(player2.front());
				player2.push(player1.front());
			}
			player1.pop();
			player2.pop();
			roundStart = true;
		}
	}

	return player1.empty() ? 2 : 1;
}

int solution(int a) {
	int sum = 0;
	//Part 1
	if (a == 1) {
		//P1 won
		if(playCombat() == 1) {
			for (int i = player1.size(); i > 0; i--) {
				sum += i * player1.front();
				player1.pop();
			}
		}
		//P2 won
		else if(playCombat() == 2) {
			for (int i = player2.size(); i > 0; i--) {
				sum += i * player2.front();
				player2.pop();
			}
		}
	}

	if (a == 2) {
		if(playRecursiveCombat(player1, player2) == 1) {
			for (int i = player1.size(); i > 0; i--) {
				sum += i * player1.front();
				player1.pop();
			}
		}
		//P2 won
		else if(playRecursiveCombat(player1, player2) == 2) {
			for (int i = player2.size(); i > 0; i--) {
				sum += i * player2.front();
				player2.pop();
			}
		}


	}
	return sum;
}

	
int main() {
	
	loadFile("Day22Data1.txt");

	cout << "Answer Q1 : "<< solution(1) << "\n";

	loadFile("Day22Data1.txt");

	cout << "Answer Q2 : "<< solution(2) << "\n";	
}