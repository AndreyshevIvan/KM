#include "stdafx.h"
#include "Node.h"

Node::Node(const vector<vector<size_t>> &matrix)
{
	this->m_matrix = matrix;
	//cout << "Create node\n";
	CalculateHash();
	CalculateEmptyPosition();
}

size_t Node::GetHashFromMatrix(const vector<vector<size_t>> &matrix)
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

vector<vector<size_t>> Node::GetMatrix()
{
	return m_matrix;
}

Point Node::GetEmptyPoint()
{
	return m_emptyPosition;
}

size_t Node::GetHash()
{
	return m_hash;
}

void Node::CalculateHash()
{
	m_hash = GetHashFromMatrix(m_matrix);
}

void Node::CalculateEmptyPosition()
{
	for (size_t i = 0; i < m_matrix.size(); i++)
	{
		for (size_t j = 0; j < m_matrix.front().size(); j++)
		{
			if (m_matrix[i][j] == 0)
			{
				m_emptyPosition = { i, j };
			}
		}
	}
}