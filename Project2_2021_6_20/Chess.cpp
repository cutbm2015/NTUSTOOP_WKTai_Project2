#include "Chess.h"
//#define DEBUG
bool Chess::isValidMove(int startX, int startY, int endX, int endY, vector<vector<Chess>>& board, int& throwBack, bool checkCheckmate) {
	if (startX == endX && startY == endY) {
		return false;
	}
	if (startX < 0 || endX < 0 || startY < 0 || endY < 0) {
		return false;
	}
	else if (startX > 7 || startY > 7 || endX > 7 || endY > 7) {
		return false;
	}
#ifdef DEBUG
	cout << "move x" << startX << "y" << startY << " to x" << endX << " y" << endY << endl;
#endif // DEBUG
	throwBack = 0;
	if (board[startY][startX].faction == board[endY][endX].faction) {	//目的地有友方棋子
		return false;
	}
	if (board[startY][startX].type == 888 || board[startY][startX].type == 999) {	//目的地有友方棋子
		return false;
	}

	if (type == 0) {
		return false;
	}
	else if (type == 1) {
		//小兵
		if (board[startY][startX].faction == 0) {
			if (startX == endX) {
				if (endY + 2 == startY) {	//走兩步
					if (pawnFirstMove) {
						if ((startY - 1 >= 0 && board[startY - 1][startX].type != 0) || (startY - 2 >= 0 && board[startY - 2][startX].type != 0)) {	//路徑上有棋子
							return false;
						}
					}
					else {
						return false;
					}
				}
				else if (endY + 1 == startY) {	//走一步
					//null
					if (board[endY][endX].faction != -1) {
						return false;
					}
				}
				else {	//走其他步數
					return false;
				}
			}
			else {
				//判斷是否能 吃過路兵			
				if (startX + 1 < 8 && endX - 1 == startX && endY + 1 == startY) {
					//右前
					if (board[startY][startX + 1].faction != -1 && board[startY][startX + 1].faction != board[startY][startX].faction && board[startY][startX + 1].type == 1) {
						//旁邊有敵方棋子 且 是小兵
						if (board[endY][endX].faction == -1) {
							//而且目的地是空白
							//吃過路冰
							if (board[startY][startX].canEnPassant) {
								//需要立即執行
								throwBack = -1;
								Chess empty(0, -1);
								board[startY][startX + 1] = empty;
							}
							else { return false; }
						}
					}
					else {
						//旁邊沒有棋子 可能是普通斜吃
						if (board[endY][endX].faction != -1) {
							//目標不是空白 = 有敵人 = 協吃
						}
						else {
							//旁邊沒有棋子 目的地又是空白
							return false;
						}
					}


				}
				else if (startX - 1 >= 0 && endX + 1 == startX && endY + 1 == startY) {
					//左前
					if (board[startY][startX - 1].faction != -1 && board[startY][startX - 1].faction != board[startY][startX].faction && board[startY][startX - 1].type == 1) {
						//旁邊有棋子 且是小兵
						if (board[endY][endX].faction == -1) {
							//而且目的地是空白
							//吃過路冰
							if (board[startY][startX].canEnPassant) {
								//需要立即執行
								throwBack = -1;
								Chess empty(0, -1);
								board[startY][startX - 1] = empty;
							}
							else { return false; }
						}
					}
					else {
						//旁邊沒有棋子 可能是普通斜吃
						if (board[endY][endX].faction != -1) {
							//目標不是空白 = 有敵人 = 協吃
							//null
						}
						else {
							//旁邊沒有棋子 目的地又是空白
							return false;
						}
					}
				}
				else {
					//unknown
					return false;
				}
			}
		}
		else {
			//black side
			if (startX == endX) {
				if (endY - 2 == startY) {	//走兩步
					if (pawnFirstMove) {
						if ((startY + 1 < 8 && board[startY + 1][startX].type != 0) || (startY + 2 < 8 && board[startY + 2][startX].type != 0)) {	//路徑上有棋子
							return false;
						}
					}
					else {
						return false;
					}
				}
				else if (endY - 1 == startY) {	//走一步
					//null
					if (board[endY][endX].faction != -1) {
						return false;
					}
				}
				else {	//走其他步數
					return false;
				}
			}
			else {
				//判斷是否能 吃過路兵				
				if (startX - 1 >= 0 && endX + 1 == startX && endY - 1 == startY) {
					//左下吃
					if (board[startY][startX - 1].faction != -1 && board[startY][startX - 1].faction != board[startY][startX].faction && board[startY][startX - 1].type == 1) {
						//旁邊有棋子且是小兵
						if (board[endY][endX].faction == -1) {
							//而且目的地是空白
							//吃過路冰
							if (board[startY][startX].canEnPassant) {
								//需要立即執行
								throwBack = -1;
								Chess empty(0, -1);
								board[startY][startX - 1] = empty;
							}
							else { return false; }
						}
					}
					else {
						//旁邊沒有棋子 可能是普通斜吃
						if (board[endY][endX].faction != -1) {
							//目標不是空白 = 有敵人 = 協吃
							//null
						}
						else {
							//旁邊沒有棋子 目的地又是空白
							return false;
						}
					}
				}
				else if (startX + 1 <= 7 && endX - 1 == startX && endY - 1 == startY) {
					//右下吃

					if (board[startY][startX + 1].faction != -1 && board[startY][startX + 1].faction != board[startY][startX].faction && board[startY][startX + 1].type == 1) {
						//旁邊有棋子且是小兵
						if (board[endY][endX].faction == -1) {
							//而且目的地是空白
							//吃過路冰
							if (board[startY][startX].canEnPassant) {
								//需要立即執行
								throwBack = -1;
								Chess empty(0, -1);
								board[startY][startX + 1] = empty;
							}
							else { return false; }
						}
					}
					else {
						//旁邊沒有棋子 可能是普通斜吃
						if (board[endY][endX].faction != -1) {
							//目標不是空白 = 有敵人 = 協吃
							//null
						}
						else {
							//旁邊沒有棋子 目的地又是空白
							return false;
						}
					}
				}
				else {
					//unknown
					return false;
				}
			}
		}
	}
	else if (type == 2) {
		//knight
		//allow coordination
		vector<int> allowX;
		vector<int> allowY;
		allowX.push_back(startX + 1);
		allowY.push_back(startY - 2);
		allowX.push_back(startX + 2);
		allowY.push_back(startY - 1);
		allowX.push_back(startX + 2);
		allowY.push_back(startY + 1);
		allowX.push_back(startX + 1);
		allowY.push_back(startY + 2);
		allowX.push_back(startX - 1);
		allowY.push_back(startY + 2);
		allowX.push_back(startX - 2);
		allowY.push_back(startY + 1);
		allowX.push_back(startX - 2);
		allowY.push_back(startY - 1);
		allowX.push_back(startX - 1);
		allowY.push_back(startY - 2);
		bool validExist = false;
		for (int i = 0; i < 8; i++) {
			if (endX == allowX[i] && endY == allowY[i]) {
				validExist = true;
			}
		}
		if (!validExist) {
			return false;
		}

	}
	else if (type == 3) {
		//Bishop
		//allow coordination
		vector<int> allowX;
		vector<int> allowY;
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX + i);
			allowY.push_back(startY + i);
			if (startX + i < 8 && startY + i < 8) {
				if (board[startY + i][startX + i].faction != -1)
					break;
			}
			else { break; }
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX - i);
			allowY.push_back(startY - i);
			if (startX - i >= 0 && startY - i >= 0) {
				if (board[startY - i][startX - i].faction != -1)
					break;
			}
			else { break; }
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX + i);
			allowY.push_back(startY - i);
			if (startX + i < 8 && startY - i >= 0) {
				if (board[startY - i][startX + i].faction != -1)
					break;
			}
			else { break; }
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX - i);
			allowY.push_back(startY + i);
			if (startX - i >= 0 && startY + i < 8) {
				if (board[startY + i][startX - i].faction != -1)
					break;
			}
			else { break; }
		}
		bool validExist = false;
		for (int i = 0; i < allowX.size(); i++) {
			if (endX == allowX[i] && endY == allowY[i]) {
				validExist = true;
			}
		}
		if (!validExist) {
			return false;
		}
	}
	else if (type == 4) {
		//Rook
		//allow coordination
		vector<int> allowX;
		vector<int> allowY;
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX + i);
			allowY.push_back(startY);
			if (startX + i < 8 && startY < 8) {
				if (board[startY][startX + i].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX - i);
			allowY.push_back(startY);
			if (startX - i >= 0 && startY >= 0) {
				if (board[startY][startX - i].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX);
			allowY.push_back(startY + i);
			if (startX < 8 && startY + i < 8) {
				if (board[startY + i][startX].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX);
			allowY.push_back(startY - i);
			if (startX >= 0 && startY - i >= 0) {
				if (board[startY - i][startX].faction != -1)
					break;
			}
		}
		bool validExist = false;
		for (int i = 0; i < allowX.size(); i++) {
			if (endX == allowX[i] && endY == allowY[i]) {
				validExist = true;
			}
		}
		if (!validExist) {
			return false;
		}

	}
	else if (type == 5) {
		//queen
			//allow coordination
		vector<int> allowX;
		vector<int> allowY;
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX + i);
			allowY.push_back(startY);
			if (startX + i < 8 && startY < 8) {
				if (board[startY][startX + i].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX - i);
			allowY.push_back(startY);
			if (startX - i >= 0 && startY >= 0) {
				if (board[startY][startX - i].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX);
			allowY.push_back(startY + i);
			if (startX < 8 && startY + i < 8) {
				if (board[startY + i][startX].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX);
			allowY.push_back(startY - i);
			if (startX >= 0 && startY - i >= 0) {
				if (board[startY - i][startX].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX + i);
			allowY.push_back(startY + i);
			if (startX + i < 8 && startY + i < 8) {
				if (board[startY + i][startX + i].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX - i);
			allowY.push_back(startY - i);
			if (startX - i >= 0 && startY - i >= 0) {
				if (board[startY - i][startX - i].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX + i);
			allowY.push_back(startY - i);
			if (startX + i < 8 && startY - i >= 0) {
				if (board[startY - i][startX + i].faction != -1)
					break;
			}
		}
		for (int i = 1; i <= 7; i++) {

			allowX.push_back(startX - i);
			allowY.push_back(startY + i);
			if (startX - i >= 0 && startY + i < 8) {
				if (board[startY + i][startX - i].faction != -1)
					break;
			}
		}
		bool validExist = false;
		for (int i = 0; i < allowX.size(); i++) {
			if (endX == allowX[i] && endY == allowY[i]) {
				validExist = true;
			}
		}
		if (!validExist) {
			return false;
		}

	}
	else if (type == 6) {
		//易位 必須是都沒動過的棋子


		if (faction == 0 && board[startY][startX].moveCnt == 0 && board[endY][endX].moveCnt == 0) {
			//白方易位
			if (startX == 4 && startY == 7) {
				if (endX == 6 && endY == 7) {
					//短易位

					if (board[startY][startX + 1].faction == -1 && board[startY][startX + 2].faction == -1) {
						//中間沒棋子
						bool beAttack = false;
						int tb;
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								if (board[j][i].faction == board[startY][startX].faction)
									continue;
								if (board[j][i].isValidMove(i, j, startX, startY, board, tb)
									|| board[j][i].isValidMove(i, j, startX + 1, startY, board, tb)
									|| board[j][i].isValidMove(i, j, startX + 2, startY, board, tb)) {
									beAttack = true;
									break;
								}
							}
							if (beAttack)
								break;
						}
						if (!beAttack) {
							//沒有威脅
							//開始易位
							Chess empty(0, -1);
							board[endY][endX] = board[startY][startX];
							board[startY][startX] = empty;
							board[startY][startX + 1] = board[7][7];
							board[7][7] = empty;
							throwBack = -2;
							return true;
						}
					}
				}
				else if (endX == 2 && endY == 7) {
					//長易位
					if (board[startY][startX - 1].faction == -1 && board[startY][startX - 2].faction == -1 && board[startY][startX - 3].faction == -1) {
						//中間沒棋子
						bool beAttack = false;
						int tb;
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								if (board[j][i].faction == board[startY][startX].faction)
									continue;
								if (board[j][i].isValidMove(i, j, startX, startY, board, tb)
									|| board[j][i].isValidMove(i, j, startX - 1, startY, board, tb)
									|| board[j][i].isValidMove(i, j, startX - 2, startY, board, tb)
									|| board[j][i].isValidMove(i, j, startX - 3, startY, board, tb)) {
									beAttack = true;
									break;
								}
							}
							if (beAttack)
								break;
						}
						if (!beAttack) {
							//沒有威脅
							//開始易位
							Chess empty(0, -1);
							board[startY][startX - 2] = board[startY][startX];
							board[startY][startX] = empty;
							board[startY][startX - 1] = board[7][0];
							board[7][0] = empty;
							throwBack = -2;
							return true;
						}
					}
				}

			}
		}
		else if (faction == 1 && board[startY][startX].moveCnt == 0 && board[endY][endX].moveCnt == 0) {
			//黑方易位
			if (startX == 4 && startY == 0) {
				if (endX == 6 && endY == 0) {
					//短易位
					if (board[startY][startX + 1].faction == -1 && board[startY][startX + 2].faction == -1) {
						//中間沒棋子
						bool beAttack = false;
						int tb;
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								if (board[j][i].faction == board[startY][startX].faction)
									continue;
								if (board[j][i].isValidMove(i, j, startX, startY, board, tb)
									|| board[j][i].isValidMove(i, j, startX + 1, startY, board, tb)
									|| board[j][i].isValidMove(i, j, startX + 2, startY, board, tb)) {
									beAttack = true;
									break;
								}
							}
							if (beAttack)
								break;
						}
						if (!beAttack) {
							//沒有威脅
							//開始易位
							Chess empty(0, -1);
							board[endY][endX] = board[startY][startX];
							board[startY][startX] = empty;
							board[startY][startX + 1] = board[0][7];
							board[0][7] = empty;
							throwBack = -2;
							return true;
						}
					}
				}
				else if (endX == 2 && endY == 0) {
					//中間沒棋子
					bool beAttack = false;
					int tb;
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (board[j][i].faction == board[startY][startX].faction)
								continue;
							if (board[j][i].isValidMove(i, j, startX, startY, board, tb)
								|| board[j][i].isValidMove(i, j, startX - 1, startY, board, tb)
								|| board[j][i].isValidMove(i, j, startX - 2, startY, board, tb)
								|| board[j][i].isValidMove(i, j, startX - 3, startY, board, tb)) {
								beAttack = true;
								break;
							}
						}
						if (beAttack)
							break;
					}
					if (!beAttack) {
						//沒有威脅
						//開始易位
						Chess empty(0, -1);
						board[startY][startX - 2] = board[startY][startX];
						board[startY][startX] = empty;
						board[startY][startX - 1] = board[0][0];
						board[0][0] = empty;
						throwBack = -2;
						return true;
					}

				}

			}
		}
		//國王
		/*
		XXX
		X X
		XXX
		*/
		//allow coordination
		vector<int> allowX;
		vector<int> allowY;
		allowX.push_back(startX + 1);
		allowY.push_back(startY);
		allowX.push_back(startX - 1);
		allowY.push_back(startY);
		allowX.push_back(startX);
		allowY.push_back(startY + 1);
		allowX.push_back(startX);
		allowY.push_back(startY - 1);
		allowX.push_back(startX + 1);
		allowY.push_back(startY + 1);
		allowX.push_back(startX - 1);
		allowY.push_back(startY - 1);
		allowX.push_back(startX + 1);
		allowY.push_back(startY - 1);
		allowX.push_back(startX - 1);
		allowY.push_back(startY + 1);
		bool isAllowMove = false;
		for (int i = 0; i < allowX.size(); i++) {
			if (endX == allowX[i] && endY == allowY[i]) {
				isAllowMove = true;
			}
		}
		if (!isAllowMove) {
			return false;
		}


		//除了自己以外的其他棋子不能移動到終點
		//也就是假設攻擊
		int throwBack;
		bool beAttack = false;
		Chess empty(0, -1);
		vector<vector<Chess>> fake;
		fake = board;
		fake[endY][endX] = fake[startY][startX];
		fake[startY][startX] = empty;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (fake[i][j].faction == -1 || fake[endY][endX].faction == fake[i][j].faction) {
					continue;
				}
				//	cout << j << i << endX << endY << endl;
				if (j == 1 && i == 4) {
					cout << " ";
				}
				if (fake[i][j].isValidMove(j, i, endX, endY, fake, throwBack)) {
					cout << j << i << endX << endY;

					return false;
				}
			}
		}
		//	beAttack = 0;
		//	return true;

	}

	/*
	//吃子 or 移動棋子
	Chess empty(0, -1);
	board[endY][endX] = board[startY][startX];
	board[startY][startX] = empty;*/
	//vector<vector<Chess>> fake = board;
	//Chess empty(0, -1);
	//fake[endY][endX] = board[startY][startX];
	//board[startY][startX] = empty;
	//if (checkCheckmate && isCheckmate(board)) 	//判斷是否被將軍
	//	return false;

	return true;
}

//未做
bool Chess::isCheckmate(vector<vector<Chess>> board) {
	//構成威脅?


	return false;

}