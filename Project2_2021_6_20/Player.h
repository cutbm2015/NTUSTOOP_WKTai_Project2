#pragma once
#include <string>
#include <vector>
#include "Chess.h"
using namespace std;

class Player {
public:
	virtual void OnMove(int,int,int,int, vector<vector<Chess>>&, int faction, int& throwBack) = 0; // 選擇要從 fromPos 走到 toPos
	virtual void OnPromote(vector<vector<Chess>>&) = 0; // 選擇升階類型
	virtual void ConfirmedPromote(vector<vector<Chess>>&, int type) = 0; //
	string playerName;
	bool isLose(vector<vector<Chess>>, int);
	bool AItakeOver = false;
};
class HumanPLayer : public Player {
public:
	void OnMove(int,int,int,int, vector<vector<Chess>>&, int, int&) override;
	void OnPromote(vector<vector<Chess>>&) override;
	void ConfirmedPromote(vector<vector<Chess>>&, int) override;
};
class AIPLayer : public Player {
	int difficulty = 0;
	void setDifficulty(int diff) { difficulty = diff; }
	void OnMove(int, int, int, int, vector<vector<Chess>>&, int, int&) override;
	void OnPromote(vector<vector<Chess>>&) override;
	void ConfirmedPromote(vector<vector<Chess>>&, int) override;
	bool AItakeOver = true;
};