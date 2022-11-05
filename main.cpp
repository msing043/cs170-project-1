#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <string>
#include "eightPuzzle.h"
using namespace std;
int main()
{
	eightPuzzle x;
	int puzzleChoice = 1;
    cout << "8 puzzle solver"<< "\n";
	x.makeRoot(puzzleChoice);
	cout << "Enter a number to choose your algorithm"<< "\n";
	cout << "1) Uniform Cost Search"<< "\n";
	cout << "2) A* with Misplaced Tile Heuristic"<< "\n";
	cout << "3) A* with Manhattan Distance Heuristic"<< "\n";
	int userIn = 0;
	cin >> userIn;
	x.algChoice(userIn);
    return 0;
}
