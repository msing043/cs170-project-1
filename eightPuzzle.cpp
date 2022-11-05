#include <iostream>
#include <queue>
#include <list>
#include <cstdlib>
#include <vector>
#include <string>
#include "eightPuzzle.h"
using namespace std;
eightPuzzle::eightPuzzle()
{
	root = NULL;
}
void eightPuzzle::makeRoot(int x)
{
	tile* t = new tile;
	t->heuristic = 0; 
	t->movementCost = 0;
	totalNodesExpanded = 0;
	totalNodesInQueue = 0;
	t->child1 = NULL;
	t->child2 = NULL;
	t->child3 = NULL;
	t->child4 = NULL;
	t->parent = NULL;
	goalState = false;
		// pre-set puzzle
		// 1 2 3
		// 4 * 6
		// 7 5 8
		cout << "Default puzzle will be:\n";
		vector<char> vec1;
		vec1.push_back('1');
		vec1.push_back('2');
		vec1.push_back('3');
		vector<char> vec2;
		vec2.push_back('4');
		vec2.push_back('*');
		vec2.push_back('6');
		vector<char> vec3;
		vec3.push_back('7');
		vec3.push_back('5');
		vec3.push_back('8');
		t->puzzle.push_back(vec1);
		t->puzzle.push_back(vec2);
		t->puzzle.push_back(vec3);
		root = t;
		q.push(root);
		list.push_back(root->puzzle);
		displayPuzzle(root);
		cout<<"Go to lines 34-44 to change puzzle in eightPuzzle.cpp\n";
}
// checks if puzzle contains numbers 1-8 and *
bool eightPuzzle::checkValid(tile* curr)
{
	bool isTrue = false;
	for(int k = 1; k < 9; k++)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(curr->puzzle.at(i).at(j) == (char)k || curr->puzzle.at(i).at(j) == '*')
				{
					isTrue = true;
				}
				if((i == 2) && (j == 2) && isTrue == false)
				{
					return false;
				}
			}
		}
		isTrue = false;
	}
	return true;
}
void eightPuzzle::algChoice(int x)
{
	if(root == NULL)
	{
		cout << "Invalid root" << endl;
		return;
	}
	if(!checkValid(root))
	{
		cout << "Invalid puzzle" << endl;
		return;
	}
	algOption=x;
	cout<<"Expanding state:\n";
	if(x==1)
	{
		puzzleSearch(root);
	}
	else if(x==2)
	{
		puzzleSearch(root);
	}
	else if(x==3)
	{
		puzzleSearch(root);
	}
	else
	{
		cout << "Invalid number" << endl;
		return;
	}
}
void eightPuzzle::puzzleSearch(tile* curr)
{	
	int index = 10; //change if we want to do 15 puzzle
	int tempIndex = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(curr->puzzle.at(i).at(j) == '*')
			{
				index = tempIndex;
			}
			else
			{
				tempIndex++;
			}
		}
	}
	if(checkComplete(curr->puzzle))
	{
		goalState = true;
		goalNode = curr;
	}
	else
	{
		q.pop();
	}

	switch(index)
	{
		case 0: 
		{
			topLeftSwap(curr);
			break;
		}
		case 1:
		{
			topMiddleSwap(curr);
			break;
		}
		case 2:
		{
			topRightSwap(curr);
			break;
		}
		case 3:
		{
			middleLeftSwap(curr);
			break;
		}
		case 4:
		{
			middleMiddleSwap(curr);
			break;
		}
		case 5:
		{
			middleRightSwap(curr);
			break;
		}
		case 6:
		{
			bottomLeftSwap(curr);
			break;
		}
		case 7:
		{
			bottomMiddleSwap(curr);
			break;
		}
		case 8:
		{
			bottomRightSwap(curr);
			break;
		}
		default:
		{
			cout << "not working" << endl;
			return;
		}
	}
	if(goalState)
	{
		while(q.top() != goalNode)
		{
			q.pop();
		}
		displayPuzzle(q.top());
		cout << "Goal state" << endl;
		cout << "The search algorithm expanded ";
		cout << totalNodesExpanded << " nodes." << endl;
		cout << "The maximum nodes in the queue at any one time was ";
		cout << totalNodesInQueue << "." << endl;
		cout << "The depth of the goal state node was ";
		cout << q.top()->movementCost << "." << endl;
		cout << "Would you like to see the final solution? (Type Y or Yes)" << endl;
		string response;
		cin >> response;
		if(response == "Y" || response == "Yes" || response == "y" || response == "yes")
		{
			reorderPath(q.top());
		}
		return;
	}
	else
	{
		if(q.top()!= NULL)
		{
			displayPuzzle(q.top());
			puzzleSearch(q.top());
		}
	}

}
// 9 different possibile swaps
void eightPuzzle::topLeftSwap(tile* curr)
{
	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	swap(tempvector1.at(0).at(0), tempvector1.at(0).at(1));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(0).at(0), tempvector2.at(1).at(0));
	assignChild2(curr, tempvector2);
}
void eightPuzzle::topMiddleSwap(tile* curr)
{
	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;

	swap(tempvector1.at(0).at(1), tempvector1.at(0).at(0));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(0).at(1), tempvector2.at(0).at(2));
	assignChild2(curr, tempvector2);

	swap(tempvector3.at(0).at(1), tempvector3.at(1).at(1));
	assignChild3(curr, tempvector3);
}
void eightPuzzle::topRightSwap(tile* curr)
{
	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;

	swap(tempvector1.at(0).at(2), tempvector1.at(0).at(1));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(0).at(2), tempvector2.at(1).at(2));
	assignChild2(curr, tempvector2);
}
void eightPuzzle::middleLeftSwap(tile* curr)
{
	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;

	swap(tempvector1.at(1).at(0), tempvector1.at(0).at(0));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(1).at(0), tempvector2.at(1).at(1));
	assignChild2(curr, tempvector2);
	

	swap(tempvector3.at(1).at(0), tempvector3.at(2).at(0));
	assignChild3(curr, tempvector3);
}

void eightPuzzle::middleMiddleSwap(tile* curr)
{
	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;
	vector< vector<char> > tempvector4 = curr->puzzle;

	swap(tempvector1.at(1).at(1), tempvector1.at(0).at(1));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(1).at(1), tempvector2.at(1).at(0));
	assignChild2(curr, tempvector2);

	swap(tempvector3.at(1).at(1), tempvector3.at(1).at(2));
	assignChild3(curr, tempvector3);

	swap(tempvector4.at(1).at(1), tempvector4.at(2).at(1));
	assignChild4(curr, tempvector4);
}

void eightPuzzle::middleRightSwap(tile* curr)
{
	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;

	swap(tempvector1.at(1).at(2), tempvector1.at(0).at(2));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(1).at(2), tempvector2.at(1).at(1));
	assignChild2(curr, tempvector2);

	swap(tempvector3.at(1).at(2), tempvector3.at(2).at(2));
	assignChild3(curr, tempvector3);
}

void eightPuzzle::bottomLeftSwap(tile* curr)
{
	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;

	swap(tempvector1.at(2).at(0), tempvector1.at(1).at(0));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(2).at(0), tempvector2.at(2).at(1));
	assignChild2(curr, tempvector2);
}
void eightPuzzle::bottomMiddleSwap(tile* curr)
{
	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;

	swap(tempvector1.at(2).at(1), tempvector1.at(1).at(1));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(2).at(1), tempvector2.at(2).at(0));
	assignChild2(curr, tempvector2);

	swap(tempvector3.at(2).at(1), tempvector3.at(2).at(2));
	assignChild3(curr, tempvector3);

}
void eightPuzzle::bottomRightSwap(tile* curr)
{
	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;

	swap(tempvector1.at(2).at(2), tempvector1.at(1).at(2));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(2).at(2), tempvector2.at(2).at(1));
	assignChild2(curr, tempvector2);
	
}

void eightPuzzle::assignChild1(tile* curr, vector< vector<char> > tempvector1)
{
	tile* tempStruct1 = new tile;

	if(goalState)
	{
		return;
	}
	if(checkComplete(tempvector1))
	{
		goalState = true;
		list.push_back(tempvector1);
		tempStruct1->movementCost = curr->movementCost + 1;
		tempStruct1->puzzle = tempvector1;
		tempStruct1->heuristic = heuristicCalc(tempvector1);
		curr->child1 = tempStruct1;
		curr->child1->parent = curr;
		q.push(curr->child1);
		totalNodesExpanded=totalNodesExpanded + 1;
		maxQueue();
		goalNode = curr->child1;
		return;
	}
	if(comparePuzzle(tempvector1))
	{
		curr->child1 = NULL;
	}
	else if(!comparePuzzle(tempvector1))
	{
		list.push_back(tempvector1);
		tempStruct1->movementCost = curr->movementCost + 1;
		tempStruct1->puzzle = tempvector1;
		tempStruct1->heuristic = heuristicCalc(tempvector1);

		curr->child1 = tempStruct1;
		curr->child1->parent = curr;
		q.push(curr->child1);
        totalNodesExpanded=totalNodesExpanded + 1;		
        maxQueue();
	}
}
void eightPuzzle::assignChild2(tile* curr, vector< vector<char> > tempvector2)
{
	tile* tempStruct2 = new tile;
	if(goalState)
	{
		return;
	}
	if(checkComplete(tempvector2))
	{
		goalState = true;
		list.push_back(tempvector2);

		tempStruct2->movementCost = curr->movementCost + 1;
		tempStruct2->puzzle = tempvector2;
		tempStruct2->heuristic = heuristicCalc(tempvector2);

		curr->child2 = tempStruct2;
		curr->child2->parent = curr;
		q.push(curr->child2);
		totalNodesExpanded=totalNodesExpanded + 1;
		maxQueue();

		goalNode = curr->child2;

		return;
	}
	if(comparePuzzle(tempvector2))
	{
		curr->child2 = NULL;
	}
	else if(!comparePuzzle(tempvector2))
	{
		list.push_back(tempvector2);

		tempStruct2->movementCost = curr->movementCost + 1;
		tempStruct2->puzzle = tempvector2;
		tempStruct2->heuristic = heuristicCalc(tempvector2);

		curr->child2 = tempStruct2;
		curr->child2->parent = curr;
		q.push(curr->child2);
		totalNodesExpanded=totalNodesExpanded + 1;
		maxQueue();
	}
	
}
void eightPuzzle::assignChild3(tile* curr, vector< vector<char> > tempvector3)
{
	tile* tempStruct3 = new tile;
	if(goalState)
	{
		return;
	}
	if(checkComplete(tempvector3))
	{
		goalState = true;

		list.push_back(tempvector3);

		tempStruct3->movementCost = curr->movementCost + 1;
		tempStruct3->puzzle = tempvector3;
		tempStruct3->heuristic = heuristicCalc(tempvector3);

		curr->child3 = tempStruct3;
		curr->child3->parent = curr;
		q.push(curr->child3);
		totalNodesExpanded=totalNodesExpanded + 1;
		maxQueue();

		goalNode = curr->child3;

		return;
	}
	if(comparePuzzle(tempvector3))
	{
		curr->child3 = NULL;
	}
	else if(!comparePuzzle(tempvector3))
	{
		list.push_back(tempvector3);

		tempStruct3->movementCost = curr->movementCost + 1;
		tempStruct3->puzzle = tempvector3;
		tempStruct3->heuristic = heuristicCalc(tempvector3);

		curr->child3 = tempStruct3;
		curr->child3->parent = curr;
		q.push(curr->child3);
		totalNodesExpanded=totalNodesExpanded + 1;
		maxQueue();
	}
	
}
void eightPuzzle::assignChild4(tile* curr, vector< vector<char> > tempvector4)
{
	tile* tempStruct4 = new tile;

	if(goalState)
	{
		return;
	}
	if(checkComplete(tempvector4))
	{
		goalState = true;

		list.push_back(tempvector4);

		tempStruct4->movementCost = curr->movementCost + 1;
		tempStruct4->puzzle = tempvector4;
		tempStruct4->heuristic = heuristicCalc(tempvector4);

		curr->child4 = tempStruct4;
		curr->child4->parent = curr;
		q.push(curr->child4);
		totalNodesExpanded=totalNodesExpanded + 1;
		maxQueue();

		goalNode = curr->child4;

		return;
	}
	if(comparePuzzle(tempvector4))
	{
		curr->child4 = NULL;
	}
	else if(!comparePuzzle(tempvector4))
	{
	
		list.push_back(tempvector4);

		tempStruct4->movementCost = curr->movementCost + 1;
		tempStruct4->puzzle = tempvector4;
		tempStruct4->heuristic = heuristicCalc(tempvector4);

		curr->child4 = tempStruct4;
		curr->child4->parent = curr;
		q.push(curr->child4);
		totalNodesExpanded=totalNodesExpanded + 1;
		maxQueue();
		
	}
}
int eightPuzzle::heuristicCalc(vector< vector<char> > puzzle)
{
	int tempHeuristic = 0;
	vector< vector<char> > solvedPuzzle;
	static const char arr1[] = {'1', '2', '3'};
	static const char arr2[] = {'4', '5', '6'};
	static const char arr3[] = {'7', '8', '*'};
	vector<char> vec1 (arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]) );
	vector<char> vec2 (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
	vector<char> vec3 (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );
	solvedPuzzle.push_back(vec1);
	solvedPuzzle.push_back(vec2);
	solvedPuzzle.push_back(vec3);

	if(algOption == 1) // uniform cost 
	{
		return tempHeuristic;
	}
	else if(algOption == 2) // misplaced tile 
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(puzzle.at(i).at(j) != solvedPuzzle.at(i).at(j))
				{
					tempHeuristic++;
				}
			}
		}
		return tempHeuristic;
	}
	else if(algOption == 3) // Manhattan 
	{	
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				for(int k = 0; k < 3; k++)
				{
					for(int l = 0; l < 3; l++)
					{
						if(solvedPuzzle.at(i).at(j) == puzzle.at(k).at(l))
						{
							tempHeuristic += abs(i - k);
							tempHeuristic += abs(j - l);
						}
					}
				}
			}
		}
		return tempHeuristic;
	}
	return 0;
}
void eightPuzzle::maxQueue()
{
	if(q.size() > totalNodesInQueue)
	{
		totalNodesInQueue = q.size();
	}
}
bool eightPuzzle::comparePuzzle(vector< vector<char> > puzzle)
{
	for(int i = 0; i < list.size(); i++)
	{
		if(puzzle == list.at(i))
		{
			return true;
		}
	}
	return false;
}
bool eightPuzzle::checkComplete(vector< vector<char> > puzzle)
{
	vector< vector<char> > solvedPuzzle;
	static const char arr1[] = {'1', '2', '3'};
	static const char arr2[] = {'4', '5', '6'};
	static const char arr3[] = {'7', '8', '*'};
	vector<char> vec1 (arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]) );
	vector<char> vec2 (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
	vector<char> vec3 (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );
	solvedPuzzle.push_back(vec1);
	solvedPuzzle.push_back(vec2);
	solvedPuzzle.push_back(vec3);
	if(puzzle == solvedPuzzle)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void eightPuzzle::displayPuzzle(tile* curr)
{
	if(curr != root)
	{
		cout << "The best state to expand with a g(n) = ";
		cout << curr->movementCost;
		cout << " and h(n) = ";
		cout << curr->heuristic;
		cout <<" is "<<endl;
	}
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << curr->puzzle.at(i).at(j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void eightPuzzle::reorderPath(tile* curr)
{
	if(curr == root)
	{
		solution.push_front(curr);
		displayPath();
	}
	else
	{
		solution.push_front(curr);
		reorderPath(curr->parent);
	}
}
void eightPuzzle::displayPath()
{
	int solutionSize = solution.size();
	for(int i = 0; i < solutionSize; i++)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				cout << solution.front()->puzzle.at(i).at(j) << " ";
			}
			cout << endl;
		}
		cout << endl;
		solution.pop_front();
	}
	cout << "Goal state";
	return;
}