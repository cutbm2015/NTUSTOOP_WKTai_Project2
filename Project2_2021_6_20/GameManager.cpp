#include "GameManager.h"
#include "Viewer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
//#define DEBUG

#define MSGLINE1 57
#define MSGLINE2 58
#define ERRORLINE 59
#define TIME_LIMIT 50

unsigned long long int totalTime = 0;
unsigned long long int player0Time = 0;
unsigned long long int player1Time = 0;

bool isInUndo;
int nowStep;
//vector<vector<int>> movementLog;
vector<vector<vector<Chess>>> boardLog;

void GameManager::initGame() {
	//players[0] = new HumanPLayer;
	//players[1] = new HumanPLayer;
	//players[1] = new AIPLayer;
	//players[1]->AItakeOver = true;
	board.resize(8);
	for (int i = 0; i < 8; i++) {
		board[i].resize(8);
	}
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			Chess temp(0, -1);
			board[i][j] = temp;
		}
	}
	//小兵
	for (int i = 0; i < 8; i++) {
		Chess PawnW(1, 0);
		Chess PawnB(1, 1);
		board[1][i] = PawnB;
		board[6][i] = PawnW;
	}
	//城堡
	Chess RookW(4, 0);
	Chess RookB(4, 1);
	board[0][0] = RookB;
	board[0][7] = RookB;
	board[7][0] = RookW;
	board[7][7] = RookW;
	//騎士
	Chess KnightW(2, 0);
	Chess KnightB(2, 1);
	board[0][1] = KnightB;
	board[0][6] = KnightB;
	board[7][1] = KnightW;
	board[7][6] = KnightW;
	//主教
	Chess BishopW(3, 0);
	Chess BishopB(3, 1);
	board[0][2] = BishopB;
	board[0][5] = BishopB;
	board[7][2] = BishopW;
	board[7][5] = BishopW;
	//
	Chess QueenW(5, 0);
	Chess QueenB(5, 1);
	Chess KingW(6, 0);
	Chess KingB(6, 1);
	board[0][3] = QueenB;
	board[0][4] = KingB;
	board[7][3] = QueenW;
	board[7][4] = KingW;

	Chess undo(888, 1);
	Chess redo(999, 1);
	board[3].push_back(undo);
	board[4].push_back(redo);

	Chess giveUp(8, 1);
	board[2].push_back(giveUp);

	Chess empty2(9, 1);
	Chess wordKING(1000, 1);
	board[2].push_back(empty2);
	board[2].push_back(KingW);
	board[2].push_back(wordKING);

	Chess wordQUEEN(1001, 1);
	board[3].push_back(empty2);
	board[3].push_back(QueenW);
	board[3].push_back(wordQUEEN);

	Chess wordROOK(1002, 1);
	board[4].push_back(empty2);
	board[4].push_back(RookW);
	board[4].push_back(wordROOK);

	Chess wordBISHOP(1003, 1);
	board[5].push_back(empty2);
	board[5].push_back(empty2);
	board[5].push_back(BishopW);
	board[5].push_back(wordBISHOP);

	Chess wordKNIGHT(1004, 1);
	board[6].push_back(empty2);
	board[6].push_back(empty2);
	board[6].push_back(KnightW);
	board[6].push_back(wordKNIGHT);

	Chess PawnW(1, 0);
	Chess wordPAWN(1005, 1);
	board[7].push_back(empty2);
	board[7].push_back(empty2);
	board[7].push_back(PawnW);
	board[7].push_back(wordPAWN);

	//log system start
	nowStep = 0;
	isInUndo = false;
	boardLog.clear();
	//movementLog.clear();
	boardLog.push_back(board);
	myBoard.updateLog(boardLog, player0Time, player1Time, players[0], players[1]);
	//log system end


#ifdef DEBUG
	cout << "successfully init chess" << endl;
#endif // DEBUG
}

POINT GameManager::getCursorLocation() {
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(GetConsoleWindow(), &p);
#ifdef DEBUG
	//cout << p.x << " " << p.y << endl;
#endif // DEBUG	
	return p;
}
bool GameManager::isTie(vector<vector<Chess>> board) {
	int validMove = 0, tb;
	vector<vector<Chess>> fake;
	//無子可動?
	fake = board;
	bool canMove = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 8; k++) {
				for (int l = 0; l < 8; l++) {
					if (fake[i][j].faction == -1 || fake[i][j].faction != current_player)
						continue;
					if (fake[i][j].isValidMove(j, i, k, l, fake, tb)) {
						canMove = true;
						break;
					}
				}
				if (canMove)
					break;
			}
			if (canMove)
				break;
		}
		if (canMove)
			break;
	}
	if (!canMove) {
		return true;
	}

	/*
	王對王
王和象對王
王和馬對王
王和象對王和象

	*/
	int chessRemaining = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].type >= 1 && board[i][j].type <= 6) {
				++chessRemaining;
			}
			if (chessRemaining > 4) {
				break;
			}
		}
		if (chessRemaining > 4) {
			break;
		}
	}
	if (chessRemaining <= 4) {
		//判斷
		if (chessRemaining == 2){
			viewer.printError(1, "reason: remain white king and black king");
			return true;
		}
		else if (chessRemaining == 3) {
			//king and bishop vs king
			//king and knight vs king
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (board[i][j].type == 2 || board[i][j].type == 3) {
						viewer.printError(1, "reason: remain king/bishop vs king or king/knight vs king");
						return true;
					}
				}
			}
		}
		else if (chessRemaining == 4) {
			///若任一方的象是因升變而出現的象，這種情況不能出現
			bool notMatch = false;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if ( board[i][j].fromPromote || board[i][j].type != 3 && board[i][j].type != 6) {
						notMatch = true;
						break;
					}
				}
				if (notMatch) {
					break;
				}
				else {
					viewer.printError(1, "reason: remain king/bishop vs king/bishop");
					return true;
				}
			}
		}

	}
	//
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 8; k++) {
				for (int l = 0; l < 8; l++) {
					fake = board;
					if (board[i][j].isValidMove(j, i, l, k, fake, tb))					
						return false;					
				}
			}
		}
	}
	viewer.printError(1, "reason: no valid move");
	return true;
}
void GameManager::startGame() {
	clock_t t1 = clock();
	bool promote = false;
	POINT cursorLoc;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD originCOORD = { 0,0 };
	COORD messageLine1 = { 0,MSGLINE1 };
	COORD outputCOORD = { 0,ERRORLINE };
	int selectY, selectX, firstX, firstY, secondX, secondY, throwBack;
	bool isSelected = false;
	bool judgeGameStatus = false;
	viewer.printBoard(current_player, board);
	while (1) {
		int deltaT = ((clock() - t1) / (double)(CLOCKS_PER_SEC));
		totalTime += deltaT;
		if (current_player == 0) {
			player0Time += deltaT;
		}
		else {
			player1Time += deltaT;
		}
		if (deltaT != 0)
			t1 = clock();

		viewer.printTimeInfo(totalTime, player0Time, player1Time, current_player, players[current_player], TIME_LIMIT);
		if (totalTime > TIME_LIMIT) {
			viewer.printError(12);
			viewer.printWinner(-1);
			Sleep(5000);
			return;
		}
		Sleep(50);

		if (judgeGameStatus) {
			
			if (!promote && isTie(board) ) {
				viewer.printWinner(-1);
				Sleep(5000);
				return;
			}
			else if (players[current_player]->isLose(board, current_player)) {
				viewer.printWinner((current_player == 0 ? 1 : 0));
				Sleep(5000);
				return;
			}
			judgeGameStatus = false;
		}


		if (players[current_player]->AItakeOver) {
			
			int tb;
			players[current_player]->OnMove(0, 0, 0, 0, board, current_player, tb);
			players[current_player]->OnPromote(board);
			players[current_player]->ConfirmedPromote(board, 0);
			current_player = (current_player == 0 ? 1 : 0);
			viewer.printBoard(current_player, board);
			//log				
			++nowStep;
			if (boardLog.size() <= nowStep) {
				boardLog.push_back(board);
			}
			else {
				boardLog[nowStep] = board;
			}
			if (isInUndo) {
				boardLog.erase(boardLog.begin() + 1 + nowStep, boardLog.end());
				isInUndo = false;
			}
			myBoard.updateLog(boardLog, player0Time, player1Time, players[0], players[1]);
			//log end
			continue;
		}

		if (KEY_DOWN(MOUSE_EVENT))
		{
			judgeGameStatus = true;
			cursorLoc = getCursorLocation();
			selectY = cursorLoc.y / 110;
			selectX = cursorLoc.x / 110;
			if (promote) {
				//必須選擇
				if (selectY == 0 && selectX >= 8 && selectX <= 11) {
					players[current_player]->ConfirmedPromote(board, selectX - 6);
					current_player = (current_player == 0 ? 1 : 0);
					viewer.printBoard(current_player, board);					
					promote = false;					
				}
				else {
					viewer.printBoard(current_player, board);				
				}
				continue;
			}
			if (selectY == 2 && selectX == 8) {
				//投降
				viewer.printWinner((current_player == 0?1:0));
				Sleep(5000);
				return;
			}
			else if (selectY == 3 && selectX == 8) {
				//undo
				if (boardLog.size() == 0 || nowStep - 1 < 0) {
					viewer.printError(10);
				}
				else {
					--nowStep;
					viewer.printMessage("back to move " + to_string(nowStep));
					current_player = (current_player == 0 ? 1 : 0);
					board = boardLog[nowStep];
					isInUndo = true;
				}
				viewer.printBoard(current_player, board);
				continue;
			}
			else if (selectY == 4 && selectX == 8) {
				//redo
				if (!isInUndo) {
					viewer.printMessage("you already re-place your chess. Redo to future is invalid" + to_string(nowStep));
					continue;
				}
				if (boardLog.size() == 0 || nowStep + 1 >= boardLog.size()) {
					viewer.printError(11);
				}
				else {
					++nowStep;
					viewer.printMessage("next to move " + to_string(nowStep));
					current_player = (current_player == 0 ? 1 : 0);
					board = boardLog[nowStep];
				}
				viewer.printBoard(current_player, board);
				continue;
			}

			if (selectY < 0 || selectY > 7 || selectX < 0 || selectX > 7) {
				viewer.printError(6);
				SetConsoleCursorPosition(hStdout, outputCOORD);
				continue;
			}

			if (isSelected == false) {
				//第一次選不可以是空白的土地 也不能是非我方的棋
				if (board[selectY][selectX].faction == -1) {
					viewer.printError(7);
					continue;
				}
				if (board[selectY][selectX].faction != current_player) {
					viewer.printError(8);
					continue;
				}
				board[selectY][selectX].focused = true;

				viewer.printPossible(selectX, selectY, board);

				isSelected = true;
				firstX = selectX;
				firstY = selectY;

				
			}
			else {
				//do action
				board[firstY][firstX].focused = false;
				board[selectY][selectX].focused = false;

				isSelected = false;
				secondX = selectX;
				secondY = selectY;
				players[current_player]->OnMove(firstX, firstY, secondX, secondY, board, current_player, throwBack);
				promote = (throwBack == -3 ? true : false);
				if (throwBack > 0) {
					viewer.printBoard(current_player, board);
					viewer.printError(throwBack);
					continue;
				}
				//核可行動

				//log				
				++nowStep;				
				if (boardLog.size() <= nowStep) {
					boardLog.push_back(board);
				}
				else {
					boardLog[nowStep] = board;
				}
				if (isInUndo) {
					boardLog.erase(boardLog.begin()+1 + nowStep, boardLog.end());
					isInUndo = false;
				}
				myBoard.updateLog(boardLog, player0Time, player1Time, players[0], players[1]);
				
				//log end

				viewer.clearError();
				//viewer.printMessage("auto save to " + myBoard.fileName);
				if (promote) {
					players[current_player]->OnPromote(board);
					current_player = (current_player == 0 ? 1 : 0);
				}
				current_player = (current_player == 0 ? 1 : 0);
				viewer.printBoard(current_player, board);
			
			}
			//判斷是否結束
			bool whiteKingExist = false , blackKingExist = false;
			for (int i = 0; i < board.size(); i++) {
				for (int j = 0; j < board[i].size(); j++) {
					if (board[i][j].faction == 0 && board[i][j].type == 6) {
						whiteKingExist = true;
					}
					else if (board[i][j].faction == 1 && board[i][j].type == 6) {
						blackKingExist = true;
					}
				}
			}
			if (!blackKingExist || !whiteKingExist) {
				if (whiteKingExist && !blackKingExist) {
					//white win
					viewer.printWinner(0);
					
				}
				else if (blackKingExist && !whiteKingExist) {
					//black win
					viewer.printWinner(1);
					
				}
				Sleep(5000);
				return;
			}

		}



	}
	return;
}

void GameManager::revBoard() {
	reverse(board.begin(), board.end());
	for (int i = 0; i < board.size(); i++) {
		//reverse(board[i].begin(), board[i].end());
	}
}

void GameManager::historyList() {
	viewer.printHistoryList(logfilename);
}

void GameManager::loadGame() {
	string filename = logfilename[logfileindex];
	fstream fs(filename, ios::in);
	if (!fs.is_open()) {
		cout << "loading failed" << endl;
		fs.close();
		return;
	}
	string buffer, buffer_str;
	bool startWriting = false;
	int type = 0, faction = 0, moveCnt = 0, canEnPassant = 0 , pawnFirstMove = 0;
	bool canEP = false;
	bool pawnFM = false;
	int buffer_int;
	
	while (fs >> buffer) {
		/*
totaltime 0
player0time 0
player1time 0
player0type Human
player1type Human
player0name 
player1name 
		*/
		if (buffer == "totaltime") {			
			fs >> buffer_int;
			totalTime = buffer_int;
			continue;
		}
		else if (buffer == "player0time") {
			fs >> buffer_int;
			player0Time = buffer_int;
			continue;
		}
		else if (buffer == "player1time") {
			fs >> buffer_int;
			player1Time = buffer_int;
			continue;
		}
		else if (buffer == "player0type") {
			fs >> buffer_str;
			if (buffer_str == "Human") {
				players[0] = new HumanPLayer;
			}
			else {
				players[0] = new AIPLayer;
				players[0]->AItakeOver = true;
			}
			continue;
		}
		else if (buffer == "player1type") {
			fs >> buffer_str;
			if (buffer_str == "Human") {
				players[1] = new HumanPLayer;
			}
			else {
				players[1] = new AIPLayer;
				players[1]->AItakeOver = true;
			}
			continue;
		}
		else if (buffer == "player0name") {
			fs >> buffer_str;
			players[0]->playerName = buffer_str;
			continue;
		}
		else if (buffer == "player1name") {
			fs >> buffer_str;
			players[1]->playerName = buffer_str;
			continue;
		}


		if (buffer.length() > 0 && buffer[0] == '-') {
			startWriting = true;
		}
		if (startWriting) {
		
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					/*
					ofs << board[i][j][k].type << " " 
					<< board[i][j][k].faction << " " 
					<< board[i][j][k].moveCnt << " "
					<< (board[i][j][k].canEnPassant ? 1 : 0) << " "
					<< (board[i][j][k].pawnFirstMove ? 1 : 0) << " "
					<< "\n";
					*/
					fs >> type >> faction >> moveCnt >> canEnPassant >> pawnFirstMove;
					if (canEnPassant == 0)
						canEP = false;
					else
						canEP = true;
					if (pawnFirstMove == 0)
						pawnFM = false;
					else
						pawnFM = true;
					Chess temp(type, faction);
					temp.moveCnt = moveCnt;
					temp.canEnPassant = canEP;
					temp.pawnFirstMove = pawnFM;
					board[i][j] = temp;
				}
			}
			startWriting = false;		
		}
		
		
	}
	fs.close();
}

void GameManager::replayGame() {
	string filename = logfilename[logfileindex];
	fstream fs(filename, ios::in);
	if (!fs.is_open()) {
		cout << "loading failed" << endl;
		fs.close();
		return;
	}
	string buffer, buffer_str;
	bool startWriting = false;
	int type = 0, faction = 0, moveCnt = 0, canEnPassant = 0, pawnFirstMove = 0;
	bool canEP = false;
	bool pawnFM = false;
	bool autoReplay = false;
	int buffer_int;
	int move = 0;
	while (fs >> buffer) {
		/*
totaltime 0
player0time 0
player1time 0
player0type Human
player1type Human
player0name
player1name
		*/
		if (buffer == "totaltime") {
			fs >> buffer_int;
			totalTime = buffer_int;
			continue;
		}
		else if (buffer == "player0time") {
			fs >> buffer_int;
			player0Time = buffer_int;
			continue;
		}
		else if (buffer == "player1time") {
			fs >> buffer_int;
			player1Time = buffer_int;
			continue;
		}
		else if (buffer == "player0type") {
			fs >> buffer_str;
			if (buffer_str == "Human") {
				players[0] = new HumanPLayer;
			}
			else {
				players[0] = new AIPLayer;
				players[0]->AItakeOver = true;
			}
			continue;
		}
		else if (buffer == "player1type") {
			fs >> buffer_str;
			if (buffer_str == "Human") {
				players[1] = new HumanPLayer;
			}
			else {
				players[1] = new AIPLayer;
				players[1]->AItakeOver = true;
			}
			continue;
		}
		else if (buffer == "player0name") {
			fs >> buffer_str;
			players[0]->playerName = buffer_str;
			continue;
		}
		else if (buffer == "player1name") {
			fs >> buffer_str;
			players[1]->playerName = buffer_str;
			continue;
		}


		if (buffer.length() > 0 && buffer[0] == '-') {
			startWriting = true;
		}
		if (startWriting) {

			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					/*
					ofs << board[i][j][k].type << " "
					<< board[i][j][k].faction << " "
					<< board[i][j][k].moveCnt << " "
					<< (board[i][j][k].canEnPassant ? 1 : 0) << " "
					<< (board[i][j][k].pawnFirstMove ? 1 : 0) << " "
					<< "\n";
					*/
					fs >> type >> faction >> moveCnt >> canEnPassant >> pawnFirstMove;
					if (canEnPassant == 0)
						canEP = false;
					else
						canEP = true;
					if (pawnFirstMove == 0)
						pawnFM = false;
					else
						pawnFM = true;
					Chess temp(type, faction);
					temp.moveCnt = moveCnt;
					temp.canEnPassant = canEP;
					temp.pawnFirstMove = pawnFM;
					board[i][j] = temp;
				}
			}
			startWriting = false;
			++move;
			
			viewer.printBoard(current_player ,board);
			printf("%c[2K", 27);
			cout << "第 " << to_string(move)<< " 步, 執棋 " << players[current_player]->playerName << "\n";
			current_player = (current_player == 0 ? 1 : 0);
			if (autoReplay) {
				Sleep(1000);
				continue;
			}
			else {
				printf("%c[2K", 27);
				cout << "\n";
				printf("%c[2K", 27);
				cout << "輸入 auto 自動撥放, 輸入 next 顯示下一步: ";
				while (cin >> buffer_str) {					
					if (buffer_str == "auto") {
						autoReplay = true;
						break;
					}
					else if (buffer_str == "next") {
						break;
					}
				}				
			}
		}
	}
	printf("%c[2K", 27);
	cout << "\n";
	printf("%c[2K", 27);
	cout << "播放已結束, 輸入 exit 離開: ";
	while (cin >> buffer_str) {
		if (buffer_str == "exit")
			break;
	}
	fs.close();
}