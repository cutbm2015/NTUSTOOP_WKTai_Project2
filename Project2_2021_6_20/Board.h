#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "Chess.h"
#include "Player.h"

using namespace std;

class Board {
public:
	Board(){		
		fileName = "";
		time_t now = time(0);
		tm* ltm = localtime(&now);
		fileName += to_string(1900 + ltm->tm_year);
		fileName += to_string(1 + ltm->tm_mon);
		fileName += to_string(ltm->tm_mday);
		fileName += to_string(ltm->tm_hour);
		fileName += to_string(ltm->tm_min);
		fileName += to_string(ltm->tm_sec);
		fileName += ".txt";

	}
	bool isRecord = false;
	string fileName;
	ofstream ofs;
	void updateLog(vector<vector<vector<Chess>>>, int player0time, int player1time, const Player* player0Ptr, const Player* player1Ptr);
	void saveLog(vector<vector<int>>);
	void loadLog(vector<vector<int>>);
};