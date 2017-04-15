#include "CSearchData.h"
#include <sstream>
#include <iostream>

using namespace std;

CSearchData::CSearchData(ifstream &input)
{
	string str;

	getline(input, str);
	stringstream streamFieldSize(str);
	streamFieldSize >> m_fieldSize;

	getline(input, str);
	stringstream streamDepthLimit(str);
	streamDepthLimit >> m_searchDepth;

	vector<vector<size_t>> searchMatrix;
	getline(input, str);
	stringstream stramMatrix(str);
	m_searchHash = 0;
	m_searchHashStr = str;
	for (size_t i = 0; i < m_fieldSize; i++)
	{
		size_t cell;
		stramMatrix >> cell;
		m_searchHash = m_searchHash * 10 + cell;
	}
}

size_t CSearchData::GetFieldSize()
{
	return m_fieldSize;
}

void CSearchData::SetPath(const vector<Direction> &path)
{
	m_path = move(path);
}

void CSearchData::IncreaseGeneratedNodes(size_t addingCount)
{
	m_generateNodesCount += addingCount;
}

void CSearchData::IncreaseOpenNodes(size_t addingCount)
{
	m_openNodesCount += addingCount;
}

void CSearchData::InsertHash(size_t hash)
{
	m_passedHashes.insert(hash);
}

bool CSearchData::IsHashValid(size_t hash)
{
	return (m_passedHashes.find(hash) == m_passedHashes.end());
}

void CSearchData::Print(ofstream &output)
{
	output << "--- Tag game info ---" << endl;
	output << "Field size: " << m_fieldSize << "x" << m_fieldSize << endl;
	output << "Depth limit: " << m_searchDepth << endl;
	output << "Search hash: " << m_searchHashStr << endl;
	output << "Nodes generate: " << m_passedHashes.size() << endl;
	output << "Nodes open: " << m_openNodesCount << endl;
	output << "Path: ";

	for (size_t i = 0; i < m_path.size(); i++)
	{
		switch (m_path[i])
		{
		case Direction::UP:
			output << "Up";
			break;
		case Direction::DOWN:
			output << "Down";
			break;
		case Direction::LEFT:
			output << "Left";
			break;
		case Direction::RIGHT:
			output << "Right";
			break;
		default:
			break;
		}

		if (i != m_path.size() - 1)
		{
			output << ", ";
		}
	}
	output << endl;
}