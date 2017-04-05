#include "stdafx.h"
#include "Node.h"

Node::Node(const vector<vector<size_t>> &matrix)
{
	this->m_matrix = matrix;
	CalculateHash();
	CalculateEmptyPosition();
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
	m_hash = 0;

	for each (vector<size_t> row in m_matrix)
	{
		for each (size_t num in row)
		{
			m_hash += m_hash * 10 + num;
		}
	}
}

void Node::CalculateEmptyPosition()
{
	bool isSearchEnded = false;

	for (size_t i = 0; i < m_matrix.size(); i++)
	{
		for (size_t j = 0; j < m_matrix.front().size(); j++)
		{
			if (m_matrix[i][j] == 0)
			{
				m_emptyPosition = { i, j };
				isSearchEnded = true;
				break;
			}

			if (isSearchEnded) break;
		}
	}
}