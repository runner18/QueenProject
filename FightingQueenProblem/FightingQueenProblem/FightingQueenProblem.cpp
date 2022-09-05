// FightingQueenProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class BruteForceMethod
{
public:
	//will need to figure out the permutation class
	BruteForceMethod(int size);

	

	void purmutate()
	{
		/*next_permutation(board.begin(), board.end());
		next_permutation(board.begin(), board.end());
		next_permutation(board.begin(), board.end());
		next_permutation(board.begin(), board.end());*/

		cout << "All board layouts where no queens are within fighting range: " << endl << endl;
		do
		{
			bool check;
			check = checkPermutation();
			//else cout << "failure. two or more queens are in fighting range" << endl;
		
			//cout << "{ " << board[0] << ", " << board[1] << ", " << board[2] << ", " << board[3] << " }" << endl;
			if (check == true)
			{
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
					{
						if (board[j] == i) cout << "X  ";
						else cout << "O  ";
					}
					cout << endl;
				}
				cout << endl;
			}
			
			
		} 
		while (
			next_permutation(board.begin(),board.end())
			);

	}

	bool checkPermutation()
	{
		queenRLD.clear();
		//calculate right-leaning diagonal coordinates
		for (int i = 0; i < size; i++)
		{
			queenRLD.push_back(columns[i] + board[i]);
		}
		

		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j <= size - 1; j++)
			{
				//cout << "queenRLD = " << queenRLD[i] << " and " << queenRLD[j] << endl;
				if (queenRLD[i] == queenRLD[j])
				{
					return false;
				}
			}
		}

		queenLLD.clear();
		//calculate left-leaning diagonal coordinates
		for (int i = 0; i < size; i++)
		{
			queenLLD.push_back(columns[i] + ((size - 1) - board[i]));
		}


		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j <= size - 1; j++)
			{
				//cout << "queenLLD = " << queenLLD[i] << " and " << queenLLD[j] << endl;
				if (queenLLD[i] == queenLLD[j])
				{
					return false;
				}
			}
		}

		return true;

	}

private:
	int size;
	vector<int> board;
	vector<int> queenRLD;
	vector<int> queenLLD;
	vector<int> columns;
};

BruteForceMethod::BruteForceMethod(int size) : size(size) 
{
	board.reserve(size);
	for (int i = 0; i < size; i++)
	{
		board.push_back(i);
	}
	for (int i = 0; i < size; i++)
	{
		columns.push_back(i);
	}
	queenRLD.reserve(size);
	queenLLD.reserve(size);
}

class BacktrackingMethod
{
public:

	BacktrackingMethod(int size);
	void backtrack()
	{
		vector<int> queensSoFar;
		vector<vector<int>> possibleSolutions;

		//checking each possible solution for the first column queen in each row
		for (int i = 0; i < size; i++)
		{
			queensSoFar.push_back(i); //adds the 1st column queen to the i'th row

			//places this queen and returns all possible solutions of queens to the columns on the right
			vector<vector<int>> newSolutions = placeQueen(queensSoFar);
			possibleSolutions.insert(possibleSolutions.end(), newSolutions.begin(), newSolutions.end()); //adds the newfound solutions
			
			queensSoFar.clear(); //resets the queensSoFar for the next row 1st column queen
		}

		for (vector<int> possibleSolution : possibleSolutions)
		{
			int queenIter = 0;
			for (int i = 0; i < size; i++) //each row
			{
				for (int queen : possibleSolution) //each column
				{
					if (queen == i) cout << "X  ";
					else cout << "O  ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}

	vector<vector<int>> placeQueen(vector<int>queensSoFar)
	{
		vector<vector<int>> possibleSolutions;
		vector<int> availableRows;

		
		//eliminate already used rows
		int column = 0;
		int rowLD;
		int rowRD;
		availableRows = allRows;

		//determines rows available on this column, based on queens in previous columns to the left
		for (int queenColRowNum : queensSoFar)
		{
			//removes space on the same row as a queen
			
			availableRows.erase(remove(availableRows.begin(), availableRows.end(), queenColRowNum), availableRows.end());

			//removes space LD to a queen
			rowLD = queenColRowNum + (queensSoFar.size() - column);
			availableRows.erase(remove(availableRows.begin(), availableRows.end(), rowLD), availableRows.end());

			//removes space RD to a queen
			rowRD = queenColRowNum - (queensSoFar.size() - column);
			availableRows.erase(remove(availableRows.begin(), availableRows.end(), rowRD), availableRows.end());

			column++;
		}

		//takes available rows on this column, create solution for each available row
		//if more rows to the right, recursively calculate solution by calling this function
		//if last row, return the solutions
		vector<int> solution;
		vector<vector<int>> newSolutions;

		for (int availableRow : availableRows) //for each individual row/solution
		{
			solution = queensSoFar;
			solution.push_back(availableRow); //creates single solution
			

			if (queensSoFar.size() < size - 1)
			{
				newSolutions = placeQueen(solution); //input updated queens, get new solutions
				
				 //add new solutions to the possibleSolutions 
			}
			if (queensSoFar.size() == size - 1)
			{
				possibleSolutions.push_back(solution); //pushes solution onto new solutions
			}

			solution.clear();
			possibleSolutions.insert(possibleSolutions.end(), newSolutions.begin(), newSolutions.end());
		}

		
		return possibleSolutions;
	}

private:
	int size;
	vector<int> allRows;
};

BacktrackingMethod::BacktrackingMethod(int size) : size(size)
{
	
	for (int i = 0; i < size; i++)
	{
		allRows.push_back(i);
	}
}

int main()
{
	
	int size;
	cout << "Please enter the size of the board needed: ";
	cin >> size;
	cout << endl << "We will first use brute force: " << endl << endl;

	BruteForceMethod bruteBoard(size);
	bruteBoard.purmutate();

	cout << endl << endl << "We will use backtracking next: " << endl;

	BacktrackingMethod board(size);
	board.backtrack();
	


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
