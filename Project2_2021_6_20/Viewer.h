#pragma once
#include <vector>
#include "Chess.h"
#include "Player.h"


using namespace std;

class Viewer {

public:
	void printMenu();
	void printGameSelectionMenu();
	void printBoard(int, vector<vector<Chess>>);
	void showValidPos(int, int, vector<vector<Chess>>);
	void printError(int code, string testMsg = "");
	void printPossible(int, int, vector<vector<Chess>>);
	void printTimeInfo(unsigned long long int, unsigned long long int, unsigned long long int, int, const Player *playerPtr, int timeLimit);
	void printWinner(int);
	void clearError();
	void printPriority(int);
	void printMessage(string);
	void printHistoryList(vector<string>&);
	string timeToString(int);
};