#pragma once
#include "stdafx.h"

using namespace std;

const size_t FIELD_SIZE = 3;
const vector<vector<size_t>> START_MATRIX = {
	{ 0, 1, 2 },
	{ 3, 4, 5 },
	{ 6, 7, 8 }
};

struct Point
{
	Point(size_t x, size_t y)
	{
		this->x = x;
		this->y = y;
	}

	size_t x = 0;
	size_t y = 0;
};

class Node
{
public:
	Node(const vector<vector<size_t>> &matrix);

	static size_t GetHashFromMatrix(const vector<vector<size_t>> &matrix);

	vector<vector<size_t>> GetMatrix();
	size_t GetHash();
	Point GetEmptyPoint();

private:
	size_t m_hash = 0;
	Point m_emptyPosition = { 0, 0 };
	vector<vector<size_t>> m_matrix = vector<vector<size_t>>(FIELD_SIZE, vector<size_t>(FIELD_SIZE, 0));

	void CalculateHash();
	void CalculateEmptyPosition();
};