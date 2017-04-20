#include "CNode.h"
#include <iostream>

using namespace std;

const size_t EMPTY_NUMBER = 0;

CNode::CNode(Matrix && matrix, size_t hash, const vector<short> &path, short depth)
{
	m_matrix = move(matrix);
	m_hash = hash;
	m_path = path;
	m_depth = depth;
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
	short cell = 0;

	for (size_t i = 0; i < size; i++)
	{
		vector<short> matrixRow;

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

short CNode::GetDepth()
{
	return m_depth;
}

vector<short> CNode::GetPath()
{
	return m_path;
}

void CNode::IncreaseDepth(short addingDepth)
{
	m_depth += addingDepth;
}

void CNode::MoveEmptyPos(Point && fatherEmptyPos, Direction direction)
{
	m_emptyPosition = move(fatherEmptyPos);

	switch (direction)
	{
	case Direction::UP:
		m_emptyPosition.y++;
		break;
	case Direction::DOWN:
		m_emptyPosition.y--;
		break;
	case Direction::LEFT:
		m_emptyPosition.x++;
		break;
	case Direction::RIGHT:
		m_emptyPosition.x--;
		break;
	default:
		break;
	}

	m_path.push_back((short)direction);
}