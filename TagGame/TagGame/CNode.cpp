#include "CNode.h"
#include <iostream>

using namespace std;

CNode::CNode(const Matrix &matrix, const vector<Direction> &path, size_t depth)
{
	m_matrix = move(matrix);
	m_path = move(path);
	m_depth = depth;
	CalculateHash();
	CalculateEmptyPosition();
}

size_t CNode::GetHashFromMatrix(const Matrix &matrix)
{
	size_t hash = 0;

	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix.front().size(); j++)
		{
			hash = hash * 10 + matrix[i][j];
		}
	}

	return hash;
}

Matrix CNode::CreateStartMatrix(size_t size)
{
	Matrix matrix;
	size_t cell = 0;

	for (size_t i = 0; i < size; i++)
	{
		vector<size_t> matrixRow;

		for (size_t j = 0; j < size; j++)
		{
			matrixRow.push_back(cell);
			cell++;
		}

		matrix.push_back(matrixRow);
	}

	return matrix;
}

Matrix CNode::GetMatrix()
{
	return m_matrix;
}

Point CNode::GetEmptyPoint()
{
	return m_emptyPosition;
}

size_t CNode::GetHash()
{
	return m_hash;
}

size_t CNode::GetDepth()
{
	return m_depth;
}

vector<Direction> CNode::GetPath()
{
	return m_path;
}

void CNode::IncreaseDepth(size_t addingDepth)
{
	m_depth += addingDepth;
}

void CNode::AddToPath(Direction direction)
{
	m_path.push_back(direction);
}

void CNode::CalculateHash()
{
	m_hash = GetHashFromMatrix(m_matrix);
}

void CNode::CalculateEmptyPosition()
{
	for (size_t i = 0; i < m_matrix.size(); i++)
	{
		for (size_t j = 0; j < m_matrix.front().size(); j++)
		{
			if (m_matrix[i][j] == 0)
			{
				m_emptyPosition = Point(j, i);
			}
		}
	}
}