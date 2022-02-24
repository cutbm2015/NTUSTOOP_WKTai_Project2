#include "Player.h"
#include "Chess.h"

#define AIATTEMPT 5000

bool Player::isLose(vector<vector<Chess>> board, int faction) {
	Chess empty(0, -1);
	vector<vector<Chess>> fake1 = board;
	vector<vector<Chess>> fake2 = board;
	int tb;
	bool leaveLoop = false, beThreat = false;
	int myKingX = 0, myKingY = 0;
	int threatX = 0, threatY = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (fake2[i][j].faction == faction && fake2[i][j].type == 6) {
				myKingY = i;
				myKingX = j;
				leaveLoop = true;
				break;
			}
		}
		if (leaveLoop)
			break;
	}
	//我有被威脅嗎？	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			fake1 = board;
			if (fake1[j][i].isValidMove(i, j, myKingX, myKingY, fake1, tb)) {
				threatX = i;
				threatY = j;
				beThreat = true;
			}
		}
	}
	if (!beThreat) {
		return false;
	}
	//我被威脅了
	//那我可以逃跑嗎？
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			fake1 = board;
			if (fake1[myKingY][myKingX].isValidMove(myKingX, myKingY, i, j, fake1,tb)) {
				//我可以逃跑 代表我還沒輸
				return false;
			}
		}
	}
	//我可以攻擊威脅到我的棋子嗎？
	//等於移除威脅
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			fake1 = board;
			fake2 = board;
			if (fake1[j][i].faction != -1 && fake1[j][i].faction != faction && fake1[j][i].isValidMove(i, j, threatX, threatY, fake1, tb)) {
				//移除威脅後 我還會被將軍嗎？
				fake2[threatY][threatX] = board[j][i];
				fake2[j][i] = empty;
				//移除威脅後 我還會被將軍嗎？
				bool stillCheckMate = false;
				for (int k = 0; k < 8; k++) {
					for (int l = 0; l < 8; l++) {
						if (fake2[k][l].faction != faction && fake2[k][l].faction != -1 && fake2[k][l].isValidMove(l, k, myKingX, myKingY, fake2, tb)) {
							//我的王還是會被吃
							stillCheckMate = true;
							break;
						}
					}
					if (stillCheckMate)
						break;
				}
				if (stillCheckMate == false) {
					return false;
				}
			}
		}
	}
	return true;
	/*
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 8; k++) {
				for (int l = 0; l < 8; l++) {
					fake1 = board;
					if (fake1[j][i].isValidMove(j, i, l, k, fake1, tb)) {
						fake2 = board;
						fake2[k][l] = board[i][j];
						fake2[i][j] = empty;
						//check mate 判定
						bool leaveLoop = false;
						int myKingX = 0, myKingY = 0;
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								if (fake2[i][j].faction != -1 && fake2[i][j].faction != faction) {
									//敵人的子						
									int tb;
									if (fake2[i][j].isValidMove(j, i, myKingX, myKingY, fake2, tb)) {
										//此操作會使得我方國王被吃
										//等於不合法操作
										leaveLoop = true;
										break;
									}
								}
							}
							if (leaveLoop)
								break;
						}
						if (!leaveLoop) {
							return false;
						}
						//check mate 判定結束
					}
				}
			}
		}
	}

	return true;*/
}
/// <summary>
/// 
/// 
/// </summary>
/// <param name="sx">開始的x</param>
/// <param name="sy">開始的y</param>
/// <param name="ex">結束的x</param>
/// <param name="ey">結束的y</param>
/// <param name="board">棋盤</param>
/// <param name="faction">哪方</param>
/// <param name="throwBack">回傳值</param>
void HumanPLayer::OnMove(int sx, int sy, int ex, int ey, vector<vector<Chess>>& board, int faction, int& throwBack) {
	throwBack = 0; //succ
	int startX = sx, startY = sy, endX = ex, endY = ey;
		
	if (startX < 0 || startX >= 8 || endX < 0 || endY >= 8) {
		//cout << "invalid movement" << endl;
		throwBack = 2;
		return;
	}
	
	Chess& temp = board[startY][startX];
	if (temp.type == 0) {
		//cout << "invalid movement, no chess selected" << endl;
		throwBack = 3;
		return;
	}
	else if (temp.faction != faction) {
		//cout << "invalid movement, you can only select your own chess" << endl;
		throwBack = 4;
		return;

	}
	else {
		vector<vector<Chess>> boardTmp = board;
		int IVMThrowBack; // is valid move throw back
		bool potentialEnPassent = false;
		if (board[startY][startX].type == 1 && (startY + 2 == endY || startY - 2 == endY) && board[startY][startX].moveCnt == 0)
			potentialEnPassent = true;
		if (temp.isValidMove(startX, startY, endX, endY, board, IVMThrowBack)) {
			throwBack = IVMThrowBack;

			


			//check mate 判定
			//找我方國王在哪
			vector<vector<Chess>> fake = board;
			if (throwBack != -2) {
				Chess empty(0, -1);
				fake[endY][endX] = board[startY][startX];
				fake[startY][startX] = empty;
			}
			bool leaveLoop = false;
			int myKingX = 0, myKingY = 0;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (fake[i][j].faction == faction && fake[i][j].type == 6) {
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
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j <8; j++) {
					if (fake[i][j].faction != -1 && fake[i][j].faction != faction) {
						//敵人的子						
						int tb;
						if (fake[i][j].isValidMove(j, i, myKingX, myKingY, fake, tb)) {
							//此操作會使得我方國王被將軍
							//等於不合法操作
							throwBack = 9;
							return;
						}
					}
				}
			}
			//check mate 判定結束



			for (int i = 0; i < board.size(); i++) {
				for (int j = 0; j < board[i].size(); j++) {
					board[i][j].canEnPassant = false;
				}
			}			
			if (potentialEnPassent) {			
				if (endX + 1 < 8)
					board[endY][endX + 1].canEnPassant = true;
				if (endX - 1 >= 0)
					board[endY][endX - 1].canEnPassant = true;
			}

			temp.moveCnt++;
			//throwBack != -2 //非易位 -2 = 易位
			if (throwBack != -2) {
				//非易位操作
				//do move and eat chess
				//Chess origin = board[startY][startX];
				Chess empty(0, -1);
				board[endY][endX] = board[startY][startX];
				board[startY][startX] = empty;
				if (board[endY][endX].type == 1) {	//pawn
					board[endY][endX].pawnFirstMove = false;
				}

			}
			//判斷可不可以promote
			if (board[endY][endX].faction == 0 && board[endY][endX].type == 1) {
				//白方
				if (endY == 0) {
					//需要被promote
					throwBack = -3;
					board[endY][endX].needPromote = true;
				}
			}else if (board[endY][endX].faction == 1 && board[endY][endX].type == 1) {
				//黑方
				if (endY == 7) {
					//需要被promote
					throwBack = -3;
					board[endY][endX].needPromote = true;
				}
			}


		}
		else {
			throwBack = 5;
			//cout << "invaild move" << endl;
			return;
		}

	}
}
void HumanPLayer::OnPromote(vector<vector<Chess>>& board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j].needPromote) {
				//doing promote
				//cout << "hi";
				Chess a(2,board[i][j].faction);
				Chess b(3,board[i][j].faction);
				Chess c(4,board[i][j].faction);
				Chess d(5,board[i][j].faction);
				board[0].push_back(a);
				board[0].push_back(b);
				board[0].push_back(c);
				board[0].push_back(d);

			}
		}
	}
};
void HumanPLayer::ConfirmedPromote(vector<vector<Chess>>& board, int type) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j].needPromote) {
				//doing promote
				//cout << "hi";
				Chess newChess(type, board[i][j].faction);
				newChess.fromPromote = true;
				board[0].pop_back();
				board[0].pop_back();
				board[0].pop_back();
				board[0].pop_back();
				system("cls");
				board[i][j] = newChess;

			}
		}
	}
}

void AIPLayer::OnMove(int sx, int sy, int ex, int ey, vector<vector<Chess>>& board, int faction, int& throwBack) {
	int startX = 0, startY = 0, endX = 0, endY = 0, attempt = 0;
	
	while (attempt < AIATTEMPT) {
		++attempt;
		startX = rand() % 8;
		startY = rand() % 8;
		endX = rand() % 8;
		endY = rand() % 8;
		if (board[startY][startX].faction != faction) {
			--attempt;
			continue;
		}

		//被將軍就閃
		int perspective = board[startY][startX].faction;
		int myKingX = 0, myKingY = 0;
		int threatX = 0, threatY = 0; //威脅所在位置
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j].faction == perspective && board[i][j].type == 6) {
					myKingY = i;
					myKingX = j;
					break;
				}
			}
		}

		bool beingAttack = false;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j].faction != -1 && board[i][j].faction != perspective) {
					vector<vector<Chess>> fake = board;
					int tb;
					if (board[i][j].isValidMove(j, i, myKingX, myKingY, fake, tb)) {
						//確認我被攻擊了
						threatX = j;
						threatY = i;
						beingAttack = true;
						break;
					}
				}
			}
			if (beingAttack)
				break;
		}

		bool canDealWith = false;
		if (beingAttack) {
			//尋找我方旗子所有排除威脅的可能
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (board[i][j].faction == perspective) {
						vector<vector<Chess>> fake = board;
						int tb;
						if (board[i][j].isValidMove(j, i, threatX, threatY, fake, tb)) {
							//有辦法排除
							startX = j;
							startY = i;
							endX = threatX;
							endY = threatY;
						
							canDealWith = true;
							break;
						}
					}
				}
				if (canDealWith)
					break;
			}
		}

		if (beingAttack && !canDealWith) {
			//無法解決威脅 那就逃跑吧
			startX = myKingX;
			startY = myKingY;
		}

		//可以將軍就將軍	
		//找敵方國王在哪
		bool canCheck = false;
		//int perspective = board[startY][startX].faction;
		int againstKingX = 0, againstKingY = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j].faction != perspective && board[i][j].type == 6) {
					againstKingY = i;
					againstKingX = j;
					break;
				}
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j].faction != -1 && board[i][j].faction == perspective) {
					//我的子
					vector<vector<Chess>> fake = board;
					int tb;
					if (board[i][j].isValidMove(j, i, againstKingX, againstKingY, fake, tb)) {
						startX = j;
						startY = i;
						endX = againstKingX;
						endY = againstKingY;
						canCheck = true;
						break;
					}
				}
			}
			if (canCheck)
				break;
		}


		
		if (board[startY][startX].faction != faction)
			continue;

		

		bool potentialEnPassent = false;
		if (board[startY][startX].type == 1 && (startY + 2 == endY || startY - 2 == endY) && board[startY][startX].moveCnt == 0)
			potentialEnPassent = true;
		if (board[startY][startX].isValidMove(startX, startY, endX, endY, board, throwBack)) {

		

			for (int i = 0; i < board.size(); i++) {
				for (int j = 0; j < board[i].size(); j++) {
					board[i][j].canEnPassant = false;
				}
			}
			if (potentialEnPassent) {

				if (endX + 1 < 8)
					board[endY][endX + 1].canEnPassant = true;
				if (endX - 1 >= 0)
					board[endY][endX - 1].canEnPassant = true;
			}

			board[startY][startX].moveCnt++;
			//throwBack = -2 //易位
			if (throwBack != -2) {
				//非易位操作

				//do move and eat chess
				//Chess origin = board[startY][startX];
				Chess empty(0, -1);
				board[endY][endX] = board[startY][startX];
				board[startY][startX] = empty;
				if (board[endY][endX].type == 1) {	//pawn
					board[endY][endX].pawnFirstMove = false;
				}

			}
			//判斷可不可以promote
			if (board[endY][endX].faction == 0 && board[endY][endX].type == 1) {
				//白方
				if (endY == 0) {
					//需要被promote
					throwBack = -3;
					board[endY][endX].needPromote = true;
				}
			}
			else if (board[endY][endX].faction == 1 && board[endY][endX].type == 1) {
				//黑方
				if (endY == 7) {
					//需要被promote
					throwBack = -3;
					board[endY][endX].needPromote = true;
				}
			}
			return;
		}
	}
};
void AIPLayer::OnPromote(vector<vector<Chess>>& board) {
	/*
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j].needPromote) {
				//doing promote
				//cout << "hi";
				Chess a(2, board[i][j].faction);
				Chess b(3, board[i][j].faction);
				Chess c(4, board[i][j].faction);
				Chess d(5, board[i][j].faction);
				board[0].push_back(a);
				board[0].push_back(b);
				board[0].push_back(c);
				board[0].push_back(d);

			}
		}
	}*/
};
void AIPLayer::ConfirmedPromote(vector<vector<Chess>>& board, int type) {
	type = rand() % 4;
	type += 2;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j].needPromote) {
				//doing promote
				//cout << "hi";
				Chess newChess(type, board[i][j].faction);
				newChess.fromPromote = true;
				system("cls");
				board[i][j] = newChess;
			}
		}
	}
}