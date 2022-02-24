#include "Board.h"


void Board::updateLog(vector<vector<vector<Chess>>> board, int player0time, int player1time, const Player* player0Ptr, const Player* player1Ptr){
	if (!isRecord) {
		isRecord = true;
		//write file name to loglist.txt
		fstream fs;
		fs.open("loglist.txt", ios::app);
		if (fs.is_open()) {
			fs << fileName << "\n";
		}
		fs.close();
	}

	ofs.open(fileName, ios::out);
	if (!ofs) {
		//error
		return;
	}
	ofs << "totaltime" << " " << player0time+player1time << "\n";
	ofs << "player0time" << " " << player0time << "\n";
	ofs << "player1time" << " " << player1time << "\n";
	ofs << "player0type" << " " << (player0Ptr->AItakeOver?"AI":"Human") << "\n";
	ofs << "player1type" << " " << (player1Ptr->AItakeOver ? "AI" : "Human") << "\n";
	ofs << "player0name" << " " << player0Ptr->playerName << "\n";
	ofs << "player1name" << " " << player1Ptr->playerName << "\n";
	int number = 0;
	for (int i = 0; i < board.size(); i++) {
		ofs << "-" << number++ << "\n";
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 8; k++) {
				ofs << board[i][j][k].type << " " 
					<< board[i][j][k].faction << " " 
					<< board[i][j][k].moveCnt << " "
					<< (board[i][j][k].canEnPassant ? 1 : 0) << " "
					<< (board[i][j][k].pawnFirstMove ? 1 : 0) << " "
					<< "\n";
			}
		}
	}
	ofs.close();
};
void Board::saveLog(vector<vector<int>> log) {

};
void Board::loadLog(vector<vector<int>> log) {

};
