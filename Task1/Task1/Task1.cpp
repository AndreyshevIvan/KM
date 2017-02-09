#include "stdafx.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

bool ReadMatrix(vector<vector<int>>& matrix, ifstream& input);
void ProcessMatrix(vector<vector<int>> matrix);

int main()
{
	ifstream input("input.txt");
	vector<vector<int>> matrix;
	
	ReadMatrix(matrix, input);

	for (size_t i = 0; i != matrix.size(); i++)
	{
		for (size_t j = 0; j != matrix[0].size(); j++)
		{
			cout << matrix[i][j];
		}
		cout << "\n";
	}

	ProcessMatrix(matrix);

	return 0;
}

bool ReadMatrix(vector<vector<int>>& matrix, ifstream& input)
{
	size_t numCount = 0;

	input >> numCount;

	for (int i = 0; i != numCount; i++)
	{
		vector<int> numbers;
		matrix.push_back(numbers);
		for (int j = 0; j != numCount; j++)
		{
			char symbol;
			input >> symbol;
			int num = (symbol == '1') ? 1 : 0;
			matrix[i].push_back(num);
		}
	}



	return true;
}

void ProcessMatrix(vector<vector<int>> matrix)
{
	for (size_t row = 0; row < matrix.size(); row++)
	{
		for (size_t colls = 0; colls < matrix[row].size(); colls++)
		{
		}
	}
}