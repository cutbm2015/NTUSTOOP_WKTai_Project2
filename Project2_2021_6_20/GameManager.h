#include <vector>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Chess.h"
#include "Viewer.h"
#include "Board.h"

#define ERRORLINE 59
using namespace std;

class GameManager {
public:
	static string logPath;
	static bool prmote;
	static int onMoveThrowBack;
	GameManager() {
		viewer.printMenu();
		string temp;
		while (cin >> temp) {
			if (temp == "1") {
				viewer.printGameSelectionMenu();
				while (cin >> temp) {
					if (temp == "1" || temp == "2") {
						if (temp == "1") {
							players[0] = new HumanPLayer;
							players[1] = new HumanPLayer;
							players[0]->playerName = "player0";
							players[1]->playerName = "player1";
							viewer.printPriority(1);

						}
						else if (temp == "2") {
							//play with ai
							players[0] = new HumanPLayer;
							players[1] = new AIPLayer;
							players[1]->AItakeOver = true;
							players[0]->playerName = "player0";
							players[1]->playerName = "player1_AI";
							viewer.printPriority(2);

						}

						while (cin >> temp) {
							if (temp == "1") {
								break;
							}
							else if (temp == "2") {
								Player* temp = players[0];
								players[0] = players[1];
								players[1] = temp;
								break;
							}
							else {
								cout << "Sorry, I don't understand '" << temp << "'." << endl;
								continue;
							}
						}
						initGame();
						return;
					}
					if (temp == "3") {
						viewer.printMenu();

						break;
					}
					else {
						cout << "Sorry, I don't understand '" << temp << "'." << endl;
						continue;
					}
				}
			}
			else if (temp == "2") {
				//game history
				historyList();
				string buffer;

				while (cin >> buffer) {
					if (buffer == "L") {
						cin >> logfileindex;
						if (logfileindex < 0 || logfileindex >= logfilename.size()) {
							cout << "index not found" << endl;
							break;
						}
						players[0] = new HumanPLayer;
						players[1] = new HumanPLayer;
						initGame();
						loadGame();

						//viewer.printMenu();
						return;
						//loading
					}
					else if (buffer == "R") {
						cin >> logfileindex;
						if (logfileindex < 0 || logfileindex >= logfilename.size()) {
							cout << "index not found" << endl;
							break;
						}
						players[0] = new HumanPLayer;
						players[1] = new HumanPLayer;
						initGame();
						replayGame();

						viewer.printMenu();
						break;
						//replay
					}
					else if (buffer == "D") {
						//delete all file
						fstream temp("loglist.txt", ios::out);
						temp << "";
						temp.close();
						cout << "Done!" << endl;
					}
					else if (buffer == "E") {
						//exit
						viewer.printMenu();
						break;
					}
					else {
						cout << "Sorry, I don't understand '" << temp << "'." << endl;
						continue;
					}
				}
				continue;
			}
			else if (temp == "3") {

			}
			else if (temp == "0") {
				exit(0);
			}
		}

	};
	~GameManager() {};
	void initGame();
	void startGame();
	void revBoard();
	void historyList();
	void loadGame();
	void replayGame();
	bool isTie(vector<vector<Chess>>);
	POINT getCursorLocation();

private:
	vector<string> logfilename;
	vector<vector<Chess>> board;
	Player* players[2];
	Board myBoard;
	int current_player;
	int logfileindex;
	Viewer viewer;
};
