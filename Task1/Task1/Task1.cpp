#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>

using namespace std;

void ReadLineFromFileToBoolVector(ifstream& file, vector<bool>& vect, char ifTrue)
{
	string line;
	getline(file, line);
	stringstream stream(line);
	char elem;
	while (stream >> elem)
	{
		vect.push_back(elem == ifTrue);
	}
}

template<typename T>
void PrintVector(vector<T> const& vect)
{
	copy(vect.begin(), vect.end(), ostream_iterator<T>(cout, " "));
	cout << endl;
}

template<typename T>
void PrintMatrix(vector<vector<T>> const& boolMatrix)
{
	for (size_t i = 0; i < boolMatrix.size(); ++i)
	{
		PrintVector(boolMatrix[i]);

		for (size_t j = 0; j < boolMatrix[i].size(); ++j)
		{
			char symbol = (boolMatrix[i][j]) ? '1' : '0';
			cout << symbol;
		}
		cout << "\n";
	}
}

void FindConnection(vector<vector<bool>>& matrix, size_t y, size_t& connectionCount, vector<size_t>& connectionSizes, size_t& yToStop, set<size_t>& checkedRows)
{
	checkedRows.insert(y);
	for (size_t x = 0; x < matrix[y].size(); ++x)
	{
		if (matrix[y][x])
		{
			if (yToStop == SIZE_MAX)
			{
				yToStop = y;
			}
			connectionCount++;
			matrix[y][x] = false;
			if (x == yToStop)
			{
				connectionSizes.push_back(connectionCount);
				break;
			}
			FindConnection(matrix, x, connectionCount, connectionSizes, yToStop, checkedRows);
			break;
		}
	}
}

void ReadMatrixSize(ifstream& file, size_t& size)
{
	string line;
	getline(file, line);
	stringstream stream(line);
	stream >> size;
}

vector<vector<bool>> ReadMatrix(ifstream& file)
{
	size_t matrixCollumsCount = 0;
	ReadMatrixSize(file, matrixCollumsCount);
	vector<vector<bool>> matrix(matrixCollumsCount);

	for (size_t i = 0; i < matrixCollumsCount; ++i)
	{
		ReadLineFromFileToBoolVector(file, matrix[i], '1');
	}

	return matrix;
}

vector<size_t> FindCycles(vector<vector<bool>> const& sourceMatrix)
{
	auto matrix = sourceMatrix;
	vector<size_t> connectionSizes;
	set<size_t> checkedRows;

	for (size_t y = 0; y < matrix.size(); ++y)
	{
		if (checkedRows.find(y) == checkedRows.end())
		{
			size_t connectionCount = 0;
			size_t yToStop = SIZE_MAX;
			FindConnection(matrix, y, connectionCount, connectionSizes, yToStop, checkedRows);
		}
	}
	sort(connectionSizes.begin(), connectionSizes.end());

	return connectionSizes;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	ifstream input0(argv[1]);
	ifstream input1(argv[2]);

	auto firstMatrix = ReadMatrix(input0);
	auto connectionSizesFirst = FindCycles(firstMatrix);

	auto secondMatrix = ReadMatrix(input1);
	auto connectionSizesSecond = FindCycles(secondMatrix);

	PrintVector(connectionSizesFirst);
	PrintVector(connectionSizesSecond);

	if (connectionSizesFirst == connectionSizesSecond)
	{
		cout << "Графы изоморфны" << endl;
	}
	else
	{
		cout << "Изоморфизм отсутствует!" << endl;
	}

	return 0;
}
