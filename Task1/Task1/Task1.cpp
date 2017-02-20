#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> ReadLineFromFileToBoolVector(ifstream& file)
{
	vector<bool> vect;
	string line;
	getline(file, line);
	stringstream stream(line);
	char elem;
	while (stream >> elem)
	{
		vect.push_back(elem == '1');
	}
	return vect;
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

void FindConnection(vector<vector<bool>>& matrix, size_t y, size_t& connectionCount, vector<size_t>& connectionSizes, size_t& yToStop)
{
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
			FindConnection(matrix, x, connectionCount, connectionSizes, yToStop);
			break;
		}
	}
}

size_t ReadMatrixSize(ifstream& file)
{
	size_t size;
	string line;
	getline(file, line);
	stringstream stream(line);
	stream >> size;
	return size;
}

vector<vector<bool>> ReadMatrix(ifstream& file)
{
	size_t matrixSize = ReadMatrixSize(file);
	vector<vector<bool>> matrix(matrixSize);

	for (size_t i = 0; i < matrixSize; ++i)
	{
		matrix[i] = ReadLineFromFileToBoolVector(file);
	}

	return matrix;
}

vector<size_t> FindCycles(vector<vector<bool>> matrix)
{
	vector<size_t> connectionSizes;

	for (size_t y = 0; y < matrix.size(); ++y)
	{
		size_t connectionCount = 0;
		size_t yToStop = SIZE_MAX;
		FindConnection(matrix, y, connectionCount, connectionSizes, yToStop);
	}
	sort(connectionSizes.begin(), connectionSizes.end());

	return connectionSizes;
}

int main(int argc, char* argv[])
{
	(void)argc;
	setlocale(LC_ALL, "");

	ifstream input0(argv[1]);
	ifstream input1(argv[2]);

	auto firstMatrix = ReadMatrix(input0);
	auto connectionSizesFirst = FindCycles(firstMatrix);

	auto secondMatrix = ReadMatrix(input1);
	auto connectionSizesSecond = FindCycles(secondMatrix);

	if (connectionSizesFirst == connectionSizesSecond &&
		!connectionSizesFirst.empty() &&
		!connectionSizesSecond.empty())
	{
		cout << "Графы изоморфны" << endl;
	}
	else
	{
		cout << "Изоморфизм отсутствует!" << endl;
	}

	return 0;
}
