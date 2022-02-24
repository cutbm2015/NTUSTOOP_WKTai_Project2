#include "Viewer.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   
#include <fstream>

using namespace std;

#define BANNER "=============================================================================="
#define ERRORLINE 59
#define MSGLINE1 57
#define MSGLINE2 58

using namespace std;
//1 local 2 playwithAI
void printHeader() {
	cout << "   _____   _                           _____                            " << endl;
	cout << "  / ____| | |                         / ____|                           " << endl;
	cout << " | |      | |__     ___   ___   ___  | |  __    __ _   _ __ ___     ___ " << endl;
	cout << " | |      | '_ \\   / _ \\ / __| / __| | | |_ |  / _` | | '_ ` _ \\   / _ \\" << endl;
	cout << " | |____  | | | | |  __/ \\__ \\ \\__ \\ | |__| | | (_| | | | | | | | |  __/" << endl;
	cout << "  \\_____| |_| |_|  \\___| |___/ |___/  \\_____|  \\__,_| |_| |_| |_|  \\___|" << endl;
	cout << "                                                                        " << endl;
	cout << "           _____                                    ___    ___          " << endl;
	cout << "          / ____|                                  |__ \\  |__ \\         " << endl;
	cout << "         | |  __   _ __    ___    _   _   _ __        ) |    ) |        " << endl;
	cout << "         | | |_ | | '__|  / _ \\  | | | | | '_ \\      / /    / /         " << endl;
	cout << "         | |__| | | |    | (_) | | |_| | | |_) |    / /_   / /_         " << endl;
	cout << "          \\_____| |_|     \\___/   \\__,_| | .__/    |____| |____|        " << endl;
	cout << "                                         | |                            " << endl;
	cout << "                                         |_|                            " << endl;
	cout << "===========================================================================================" << endl;
}

void Viewer::printPriority(int type) {
	system("cls");
	printHeader();
	if (type == 1) {
		cout << "[1] player 0 執白棋 (先手)" << endl;
		cout << "[2] player 1 執黑棋 (後手)" << endl;
	}
	else {
		cout << "[1] 玩家 執白棋 (先手) / AI 執黑棋 (後手)" << endl;
		cout << "[2] 玩家 執黑棋 (後手) / AI 執白棋 (先手)" << endl;
	}

}

void Viewer::printGameSelectionMenu() {
	system("cls");
	printHeader();
	cout << "[1] local game" << endl;
	cout << "[2] play with AI" << endl;
	cout << "[3] previous page" << endl;
}

void Viewer::printMenu() {
	system("cls");
	printHeader();
	cout << "[1] Start new game" << endl;
	cout << "[2] Game History" << endl;
	//cout << "[3] Setting" << endl;
	cout << "[0] Exit" << endl;
}

void Viewer::printHistoryList(vector<string>& logfilename) {
	system("cls");
	printHeader();
	cout << "Command: " << endl;
	cout << "L [index] - Loading log file and continue play." << endl;
	cout << "R [index] - Replay game." << endl;
	cout << "D - Delete all logs file." << endl;
	cout << "E - Exit logs page." << endl;
	cout << "===========================================================================================" << endl;
	int index = 0;
	fstream fs;
	fs.open("loglist.txt", ios::in);
	if (!fs) {
		fs.open("loglist.txt", ios::out);
	}
	else {
		string temp;
		while (fs >> temp) {
			logfilename.push_back(temp);
			cout << "[" << index++ << "] - " << temp << "\n";
		}
	}
	fs.close();
}

void changeColor(int);
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD originCOORD = { 0,0 };
COORD messageLine1 = { 0, MSGLINE1 };
COORD messageLine2 = { 0, MSGLINE2 };
COORD errorLine = { 0, ERRORLINE };

//enum colour { black, blue, green, lake_blue, red, purple, yellow, white, grey, baby_blue };
enum colour { black, blue, green, red, yellow, yellow_darken, white, grey ,blue_darken};
enum chessType {
	PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, EMPTY, UNDO = 887, REDO = 998, giveUp = 7, empty2 = 8,
	wordKING = 999, wordQUEEN = 1000, wordROOK = 1001, wordBISHOP = 1002, wordKNIGHT = 1003, wordPAWN = 1004
};
void draw(int cType,int blackOrWhite, int faction, int stage, bool highlight, int highlightColor = blue) {
	int undobg = blue;
	int undofore = white;
	int redobg = red;
	int redofore = white;

	int bg, fore;
	if (blackOrWhite == 0) {
		bg = yellow;
	}else{ bg = yellow_darken; }
	if(faction == 0){		
		fore = grey;
	}
	else { fore = black; }
	if (cType == PAWN) {
		switch (stage) {
		case 0:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "              " ;
			break;
		case 1:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << "          ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  " ;
			break;
		case 2:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << "   ";
			changeColor(fore);
			cout << "    ";
			changeColor(bg);
			cout << "   ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  " ;
			break;
		case 3:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << "  ";
			changeColor(fore);
			cout << "      ";
			changeColor(bg);
			cout << "  ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			break;
		case 4:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << "   ";
			changeColor(fore);
			cout << "    ";
			changeColor(bg);
			cout << "   ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  " ;
			break;
		case 5:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << " ";
			changeColor(fore);
			cout << "        ";
			changeColor(bg);
			cout << " ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  " ;
			break;
		case 6:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "              " ;
			break;
		default:
			cout << "error draw" ;
			break;
		}
	}
	else if (cType == KNIGHT) {
		switch (stage) {
		case 0:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "              " ;
			break;
		case 1:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << "  ";
			changeColor(fore);
			cout << "     ";
			changeColor(bg);
			cout << "   ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			break;
		case 2:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << " ";
			changeColor(fore);
			cout << "  ";
			changeColor(bg);
			cout << "  ";
			changeColor(fore);
			cout << "     ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			break;
		case 3:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << "   ";
			changeColor(fore);
			cout << "      ";
			changeColor(bg);
			cout << " ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  " ;
			break;
		case 4:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << "  ";
			changeColor(fore);
			cout << "      ";
			changeColor(bg);
			cout << "  ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  " ;
			break;
		case 5:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  ";
			changeColor(bg);
			cout << " ";
			changeColor(fore);
			cout << "        ";
			changeColor(bg);
			cout << " ";
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "  " ;
			break;
		case 6:
			(highlight ? changeColor(highlightColor) : changeColor(bg));
			cout << "              " ;
			break;
		default:
			cout << "error draw" ;
			break;
		}
	}
	else if (cType == BISHOP) {
	switch (stage) {
	case 0:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	case 1:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "    ";
		changeColor(fore);
		cout << "  ";
		changeColor(bg);
		cout << "    ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 2:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "   ";
		changeColor(fore);
		cout << "    ";
		changeColor(bg);
		cout << "   ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 3:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "  ";
		changeColor(fore);
		cout << "      ";
		changeColor(bg);
		cout << "  ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 4:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "   ";
		changeColor(fore);
		cout << "    ";
		changeColor(bg);
		cout << "   ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 5:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << "        ";
		changeColor(bg);
		cout << " ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 6:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == ROOK) {
	switch (stage) {
	case 0:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	case 1:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "  ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << "  ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << "  ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 2:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "  ";
		changeColor(fore);
		cout << "      ";
		changeColor(bg);
		cout << "  ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 3:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "   ";
		changeColor(fore);
		cout << "    ";
		changeColor(bg);
		cout << "   ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 4:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "  ";
		changeColor(fore);
		cout << "      ";
		changeColor(bg);
		cout << "  ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 5:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << "        ";
		changeColor(bg);
		cout << " ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 6:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == QUEEN) {
	switch (stage) {
	case 0:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	case 1:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << "  ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 2:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "  ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << "   ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 3:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "   ";
		changeColor(fore);
		cout << "   ";
		changeColor(bg);
		cout << "    ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 4:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "  ";
		changeColor(fore);
		cout << "     ";
		changeColor(bg);
		cout << "   ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 5:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << "       ";
		changeColor(bg);
		cout << "  ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 6:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == KING) {
	switch (stage) {
	case 0:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	case 1:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "  ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << "  ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << "  ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 2:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << "    ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 3:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "  ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << "  ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << " ";
		changeColor(bg);
		cout << "  ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 4:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "  ";
		changeColor(fore);
		cout << "      ";
		changeColor(bg);
		changeColor(bg);
		cout << "  ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 5:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << " ";
		changeColor(fore);
		cout << "        ";
		changeColor(bg);
		changeColor(bg);
		cout << " ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 6:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == UNDO) {
	switch (stage) {
	case 0:
		changeColor(undobg);
		cout << "    ";
		changeColor(undofore);
		cout << "  ";
		changeColor(undobg);
		cout << "        ";
		break;
	case 1:
		changeColor(undobg);
		cout << "   ";
		changeColor(undofore);
		cout << "  ";
		changeColor(undobg);
		cout << "         ";
		break;
	case 2:
		changeColor(undobg);
		cout << "  ";
		changeColor(undofore);
		cout << "  ";
		changeColor(undobg);
		cout << "          ";
		break;
	case 3:
		changeColor(undofore);
		cout << "              ";
		break;
	case 4:
		changeColor(undobg);
		cout << "  ";
		changeColor(undofore);
		cout << "  ";
		changeColor(undobg);
		cout << "          ";
		break;
	case 5:
		changeColor(undobg);
		cout << "   ";
		changeColor(undofore);
		cout << "  ";
		changeColor(undobg);
		cout << "         ";
		break;
	case 6:
		changeColor(undobg);
		cout << "    ";
		changeColor(undofore);
		cout << "  ";
		changeColor(undobg);
		cout << "        ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == REDO) {
	switch (stage) {
	case 0:
		changeColor(redobg);
		cout << "      ";
		changeColor(redofore);
		cout << "  ";
		changeColor(redobg);
		cout << "      ";
		break;
	case 1:
		changeColor(redobg);
		cout << "        ";
		changeColor(redofore);
		cout << "  ";
		changeColor(redobg);
		cout << "    ";
		break;
	case 2:
		changeColor(redobg);
		cout << "          ";
		changeColor(redofore);
		cout << "  ";
		changeColor(redobg);
		cout << "  ";
		break;
	case 3:
		changeColor(redofore);
		cout << "              ";
		break;
	case 4:
		changeColor(redobg);
		cout << "          ";
		changeColor(redofore);
		cout << "  ";
		changeColor(redobg);
		cout << "  ";
		break;
	case 5:
		changeColor(redobg);
		cout << "        ";
		changeColor(redofore);
		cout << "  ";
		changeColor(redobg);
		cout << "    ";
		break;
	case 6:
		changeColor(redobg);
		cout << "      ";
		changeColor(redofore);
		cout << "  ";
		changeColor(redobg);
		cout << "      ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == giveUp) {

	int flag = white;
	int flagbg = blue_darken;

	switch (stage) {
	case 0:
		if (highlight) {
			changeColor(red);
			cout << "              ";
		}
		else {
			changeColor(flagbg);
			cout << "              ";
		}
		break;
	case 1:
		if (highlight) {
			changeColor(red);
			cout << "  ";
			changeColor(flagbg);
			cout << " ";
		}
		else {
			changeColor(flagbg);
			cout << "   ";
		}
		changeColor(flag);
		cout << "        ";
		if (highlight) {
			changeColor(flagbg);
			cout << " ";
			changeColor(red);
			cout << "  ";
		}
		else {
			changeColor(flagbg);
			cout << "   ";
		}
		break;
	case 2:
		if (highlight) {
			changeColor(red);
			cout << "  ";
			changeColor(flagbg);
			cout << " ";
		}
		else {
			changeColor(flagbg);
			cout << "   ";
		}
		changeColor(flag);
		cout << "        ";
		if (highlight) {
			changeColor(flagbg);
			cout << " ";
			changeColor(red);
			cout << "  ";
		}
		else {
			changeColor(flagbg);
			cout << "   ";
		}
		break;
	case 3:
		if (highlight) {
			changeColor(red);
			cout << "  ";
			changeColor(flagbg);
			cout << " ";
		}
		else {
			changeColor(flagbg);
			cout << "   ";
		}
		changeColor(flag);
		cout << " ";
		if (highlight) {
			changeColor(flagbg);
			cout << "        ";
			changeColor(red);
			cout << "  ";
		}
		else {
			changeColor(flagbg);
			cout << "          ";
		}
		break;
	case 4:
		if (highlight) {
			changeColor(red);
			cout << "  ";
			changeColor(flagbg);
			cout << " ";
		}
		else {
			changeColor(flagbg);
			cout << "   ";
		}
		changeColor(flag);
		cout << " ";
		if (highlight) {
			changeColor(flagbg);
			cout << "        ";
			changeColor(red);
			cout << "  ";
		}
		else {
			changeColor(flagbg);
			cout << "          ";
		}
		break;
	case 5:
		if (highlight) {
			changeColor(red);
			cout << "  ";
			changeColor(flagbg);
			cout << " ";
		}
		else {
			changeColor(flagbg);
			cout << "   ";
		}
		changeColor(flag);
		cout << " ";
		if (highlight) {
			changeColor(flagbg);
			cout << "        ";
			changeColor(red);
			cout << "  ";
		}
		else {
			changeColor(flagbg);
			cout << "          ";
		}
		break;
	case 6:
		if (highlight) {
			changeColor(red);
			cout << "              ";
		}
		else {
			changeColor(flagbg);
			cout << "              ";
		}
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == empty2) {


	switch (stage) {
	case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
		changeColor(black);
		cout << "              ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == wordKING) {

	switch (stage) {
	case 0: case 1: case 2: case 4: case 5: case 6:
		changeColor(black);
		cout << "              ";
		break;
	case 3:
		changeColor(black);
		cout << "  ";
		changeColor(green);
		cout << "KING";
		changeColor(black);
		cout << "        ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == wordQUEEN) {

	switch (stage) {
	case 0: case 1: case 2: case 4: case 5: case 6:
		changeColor(black);
		cout << "              ";
		break;
	case 3:
		changeColor(black);
		cout << "  ";
		changeColor(green);
		cout << "QUEEN";
		changeColor(black);
		cout << "        ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == wordROOK) {

	switch (stage) {
	case 0: case 1: case 2: case 4: case 5: case 6:
		changeColor(black);
		cout << "              ";
		break;
	case 3:
		changeColor(black);
		cout << "  ";
		changeColor(green);
		cout << "ROOK";
		changeColor(black);
		cout << "        ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == wordBISHOP) {

	switch (stage) {
	case 0: case 1: case 2: case 4: case 5: case 6:
		changeColor(black);
		cout << "              ";
		break;
	case 3:
		changeColor(black);
		cout << "  ";
		changeColor(green);
		cout << "BISHOP";
		changeColor(black);
		cout << "        ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == wordKNIGHT) {

	switch (stage) {
	case 0: case 1: case 2: case 4: case 5: case 6:
		changeColor(black);
		cout << "              ";
		break;
	case 3:
		changeColor(black);
		cout << "  ";
		changeColor(green);
		cout << "KNIGHT";
		changeColor(black);
		cout << "        ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else if (cType == wordPAWN) {

	switch (stage) {
	case 0: case 1: case 2: case 4: case 5: case 6:
		changeColor(black);
		cout << "              ";
		break;
	case 3:
		changeColor(black);
		cout << "  ";
		changeColor(green);
		cout << "PAWN";
		changeColor(black);
		cout << "        ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
	else {
	switch (stage) {
	case 0:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	case 1:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "          ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 2:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "          ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 3:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "          ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 4:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "          ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 5:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		changeColor(bg);
		cout << "          ";
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "  ";
		break;
	case 6:
		(highlight ? changeColor(highlightColor) : changeColor(bg));
		cout << "              ";
		break;
	default:
		cout << "error draw";
		break;
	}
	}
};
void changeColor(int backcolour = black) {  //forecolour 
	HANDLE handle;    //
	//COORD coord;   //
	//coord.X = x;
	//coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);  //
	//SetConsoleCursorPosition(handle, coord);   //
	switch (backcolour) {
	case black:
		backcolour = BACKGROUND_BLUE & BACKGROUND_GREEN & BACKGROUND_RED;
		break;
	case blue:
		backcolour = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case green:
		backcolour = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case red:
		backcolour = BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case yellow:
		backcolour = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case yellow_darken:
		backcolour = BACKGROUND_RED | BACKGROUND_GREEN;
		break;
	case white:
		backcolour = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case grey:
		backcolour = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	case blue_darken:
		backcolour = BACKGROUND_BLUE;
		break;
	}
	SetConsoleTextAttribute(handle, backcolour);//
	//SetConsoleTextAttribute(handle, forecolour + backcolour * 0x10);//
};
void resetColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_BLUE |
		FOREGROUND_INTENSITY);
	return;
}
void Viewer::printPossible(int startX, int startY, vector<vector<Chess>> board) {



	vector<vector<Chess>> fakeBoard;
	int throwBack;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ( (board[startY][startX].faction == board[i][j].faction) || board[startY][startX].faction==-1 || (i == startY && j == startX)) {
				continue;
			}
			fakeBoard = board;
			if (board[startY][startX].isValidMove(startX, startY, j, i, fakeBoard, throwBack)) {
				board[i][j].focused = true;
				board[i][j].highlightColor = blue;

			}
		}
	}
	
	
	//被將軍?
	//找敵方國王在哪
	/*bool leaveLoop = false;
	int perspective = board[startY][startX].faction;
	int myKingX = 0, myKingY = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].faction != perspective && board[i][j].type == 6) {
				myKingY = i;
				myKingX = j;
				break;
				leaveLoop = true;
			}
		}
		if (leaveLoop)
			break;
	}
	leaveLoop = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].faction != -1 && board[i][j].faction == perspective) {
				//我的子
				vector<vector<Chess>> fake = board;
				int tb;
				if (board[i][j].isValidMove(j, i, myKingX, myKingY, fake, tb)) {
					//把敵方國王highlight
					board[myKingY][myKingX].focused = true;
					board[myKingY][myKingX].highlightColor = red;
					leaveLoop = true;
					break;
				}
			}
		}
		if (leaveLoop)
			break;
	}
	//將軍提示結束*/
	printBoard(0, board);
	return;
}
void Viewer::printError(int code, string testMsg) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), errorLine);
	printf("%c[2K", 27);
	changeColor(red);
	switch (code) {
	case -1:
		cout << "use skills: en passant";
		break;
	case 0:
		cout << ""; //normal
		break;
	case 1:
		cout << testMsg; //testMsg
		break;
	case 2:
		cout << "invalid movement (out of range)";
		break;
	case 3:
		cout << "invalid movement (no chess selected)";
		break;
	case 4:
		cout << "invalid movement (you can only select your own chess)";
		break;
	case 5:
		cout << "invaild movement";
		break;
	case 6:
		cout << "click out of range";
		break;
	case 7:
		cout << "the place you select is empty";
		break;
	case 8:
		cout << "you can only select your own chess";
		break;
	case 9:
		cout << "invlid move (checkmate)";
		break;
	case 10:
		cout << "unavailable (no previous movement)";
		break;
	case 11:
		cout << "unavailable (no next movement)";
		break;
	case 12:
		cout << "Time exceed";
		break;
	default:
		break;
	}
	resetColor();
}
void Viewer::clearError() {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), errorLine);
	printf("%c[2K", 27);
}
string Viewer::timeToString(int input) {
	int hour = 0, minute = 0, second = 0;
	hour += input / 3600;
	input -= hour * 3600;
	minute += input / 60;
	input -= minute * 60;
	second = input;
	return to_string(hour) + "h " + to_string(minute) + "m " + to_string(second) + "s ";
}
void Viewer::printTimeInfo(unsigned long long int totalTime, unsigned long long int player0Time, unsigned long long int player1Time, int current_player, const Player *playerPtr, int timeLimit) {
	SetConsoleCursorPosition(hStdout, messageLine1);
	printf("%c[2K", 27);
	if (current_player == 0) {
		cout << "WHITE(" << playerPtr->playerName << ") turn | ";
	}
	else {
		cout << "BLACK(" << playerPtr->playerName << ") turn | ";
	}
	cout << "TIME elapsed: " << timeToString(totalTime) << " | WHITE use: " << timeToString(player0Time) << " | BLACK use: " << timeToString(player1Time) 
		<< " | Remaining: " << timeToString(timeLimit - totalTime);
}
void Viewer::printWinner(int current_player) {

	SetConsoleCursorPosition(hStdout, messageLine2);
	printf("%c[2K", 27);
	changeColor(red);
	if (current_player == 0) {
		cout << "WHITE WIN, GAME PAUSE, return to lobby in 5 second.";
	
	}
	else if(current_player == 1){
		cout << "BLACK WIN, GAME PAUSE, return to lobby in 5 second.";
	}
	else if (current_player == -1) {
		changeColor(blue);
		cout << "TIE, GAME PAUSE, return to lobby in 5 second.";
	}
	resetColor();
}
void Viewer::printBoard(int perspective, vector<vector<Chess>> board) {
	
	SetConsoleCursorPosition(hStdout, originCOORD);
	resetColor();
	//被將軍?
	//找我方國王在哪
	bool leaveLoop = false;
	int myKingX = 0, myKingY = 0;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j].faction == perspective && board[i][j].type == 6) {
				myKingY = i;
				myKingX = j;
				leaveLoop = true;
				break;				
			}
		}
		if (leaveLoop)
			break;
	}
	leaveLoop = false;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j].faction != -1 && board[i][j].faction != perspective) {
				//敵人的子
				vector<vector<Chess>> fake = board;
				int tb;
				if (board[i][j].isValidMove(j, i, myKingX, myKingY, fake, tb)) {
					//把我方國王highlight
					board[myKingY][myKingX].focused = true;
					board[myKingY][myKingX].highlightColor = red;
					
					leaveLoop = true;
					break;

				}
			}
		}
		if (leaveLoop)
			break;
	}
	leaveLoop = false;
	//找敵方國王在哪
	int againstKingX = 0, againstKingY = 0;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j].faction != perspective && board[i][j].type == 6) {
				againstKingY = i;
				againstKingX = j;
				leaveLoop = true;
				break;
			}
		}
		if (leaveLoop)
			break;
	}
	leaveLoop = false;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j].faction != -1 && board[i][j].faction == perspective) {
				//我的子
				vector<vector<Chess>> fake = board;
				int tb;
				if (board[i][j].isValidMove(j, i, againstKingX, againstKingY, fake, tb)) {
					//把敵方國王highlight
					board[againstKingY][againstKingX].focused = true;
					board[againstKingY][againstKingX].highlightColor = red;
					leaveLoop = true;
					break;
				}
			}
		}
		if (leaveLoop)
			break;
	}
	//將軍提示結束


	for (int j = 0; j < board.size(); j++) {
		for (int i = 0; i < 7; i++) {
			for (int k = 0; k < board[j].size(); k++) {			
				draw(board[j][k].type-1, ((k+j)%2), board[j][k].faction, i, board[j][k].focused, board[j][k].highlightColor);
			}
			resetColor();
			cout << endl;
		}		
	}
	cout << endl;
	resetColor();
	return;
	//system("cls");
	//unsigned int bg = bg = BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_GREEN;
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bg);
	/*if (perspective == 0) {
		//白方視角
	}
	else {
		//黑方視角
		reverse(board.begin(), board.end());
		for (int i = 0; i < board.size(); i++) {
			reverse(board[i].begin(), board[i].end());
		}
	}*/
	cout << BANNER << endl;
	cout << left << setw(10) << " ";
	for (char a = 'a'; a <= 'h'; ++a) {
		cout << setw(8) << a;
	}
	cout << endl;
	string fStr;
	for (int i = 0; i < board.size(); i++) {
		cout << setw(8) << 8 - i;
		for (Chess c : board[i]) {
			if (c.faction == 1) {
				fStr = "B";
			}
			else if (c.faction == 0) {
				fStr = "W";
			}
			else {
				fStr = "";
			}
			cout << std::setw(7) << fStr + c.name << " ";
		}
		cout << setw(8) << 8 - i;
		cout << endl << endl;
	}
	cout << left << setw(10) << " ";
	for (char a = 'a'; a <= 'h'; ++a) {
		cout << setw(8) << a;
	}
	cout << endl;
	cout << BANNER << endl;
	/*if (perspective == 0) {

	}
	else {
		reverse(board.begin(), board.end());
		for (int i = 0; i < board.size(); i++) {
			reverse(board[i].begin(), board[i].end());
		}
	}*/
}
void Viewer::printMessage(string msg) {

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), errorLine);
	printf("%c[2K", 27);
	changeColor(green);
	cout << msg;
	resetColor();
	return;
}
//未做違規操作判斷

void Viewer::showValidPos(int x, int y, vector<vector<Chess>> board) {
	
	/*
	switch (board[y][x].type) {

	case 1:	//pawn
		if (board[y][x].pawnFirstMove) {

		}


		break;
	}
	*/

}