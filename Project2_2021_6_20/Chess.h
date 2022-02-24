#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Chess {
public:
	Chess() {  };
	Chess(int typeI, int faction) {
		highlightColor = 2;
		moveCnt = 0;
		fromPromote = false;
		needPromote = false;
		canEnPassant = false;
		focused = false;
		pawnFirstMove = false;
		this->faction = faction;
		switch (typeI)
		{
		case 0:
			type = 0;
			name = "";
			break;
		case 1:
			type = 1;
			pawnFirstMove = true;
			name = "Pawn";
			break;
		case 2:
			type = 2;
			name = "Knight";
			break;
		case 3:
			type = 3;
			name = "Bishop";
			break;
		case 4:
			type = 4;
			name = "Rook";
			break;
		case 5:
			type = 5;
			name = "Queen";
			break;
		case 6:
			type = 6;
			name = "King";
			break;
		case 7:
			type = 7;
			name = "X";
			break;
		case 888:
			type = 888;
			name = "Undo";
			break;
		case 999:
			type = 999;
			name = "Redo";
			break;
		case 8:
			type = 8;
			name = "giveUp";
			break;
		case 9:		//chess command empty
			type = 9;
			name = "empty";
			break;
		case 1000:	//"KING"
			type = 1000;
			name = "wordKING";
			break;
		case 1001:	//"QUEEN"
			type = 1001;
			name = "wordQUEEN";
			break;
		case 1002:	//"ROOK"
			type = 1002;
			name = "wordROOK";
			break;
		case 1003:	//"BISHOP"
			type = 1003;
			name = "wordBISHOP";
			break;
		case 1004:	//"KNIGHT"
			type = 1004;
			name = "wordKNIGHT";
			break;
		case 1005:	//"PAWN"
			type = 1005;
			name = "wordPAWN";
			break;
		default:
			type = -1;
			name = "unknown";
			cout << "invalid chess init" << endl;
			break;
		}
	};
	bool fromPromote;
	bool needPromote;
	bool canEnPassant;
	bool pawnFirstMove;
	bool focused;
	
	int highlightColor;
	int moveCnt;
	int faction;
	int type; // 1 2 3 4 5 6
	string name;
	string location;
	bool isValidMove(int startX, int startY, int endX, int endY, vector<vector<Chess>>&, int&, bool checkCheckmate = false);
	bool isCheckmate(vector<vector<Chess>>);
};