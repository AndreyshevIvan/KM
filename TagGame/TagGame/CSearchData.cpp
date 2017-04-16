#include "CSearchData.h"
#include <sstream>
#include <iostream>
#include <locale> 
#include <boost/algorithm/string.hpp>

using namespace std;

CSearchData::CSearchData(ifstream &input)
{
	string str;

	getline(input, m_searchName);
	boost::to_lower(m_searchName);

	getline(input, str);
	stringstream streamFieldSize(str);
	streamFieldSize >> m_fieldSize;

	getline(input, str);
	stringstream streamDepthLimit(str);
	streamDepthLimit >> m_searchDepth;

	getline(input, m_searchHashStr);
	stringstream stramMatrix(m_searchHashStr);
	m_searchHash = 0;
	for (size_t i = 0; i < m_fieldSize; i++)
	{
		vector<size_t> matrixRow;
		for (size_t j = 0; j < m_fieldSize; j++)
		{
			size_t cell;
			stramMatrix >> cell;
			m_searchHash = m_searchHash * 10 + cell;
			matrixRow.push_back(cell);
		}
		m_searchMatrix.push_back(matrixRow);
	}
}

size_t CSearchData::GetFieldSize()
{
	return m_fieldSize;
}
string CSearchData::GetSearchName()
{
	return m_searchName;
}
Matrix CSearchData::GetSearchMatrix()
{
	return m_searchMatrix;
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

	if (hash == m_searchHash)
	{
		m_isSearchComplete = true;
	}
}

bool CSearchData::IsHashValid(size_t hash)
{
	return (m_passedHashes.find(hash) == m_passedHashes.end());
}
bool CSearchData::IsSearchComplete()
{
	return m_isSearchComplete;
}
bool CSearchData::IsDepthValid(size_t depth)
{
	return (depth <= m_searchDepth);
}

void CSearchData::Print(ostream &output)
{
	output << "--- Tag game info ---" << endl;
	output << "Field size: " << m_fieldSize << "x" << m_fieldSize << endl;
	output << "Search type: " << m_searchName << endl;
	output << "Depth limit: " << m_searchDepth << endl;
	output << "Search hash: " << m_searchHashStr << endl;
	output << "Nodes generate: " << m_generateNodesCount << endl;
	output << "Nodes open: " << m_openNodesCount << endl;
	output << "Path length: " << m_path.size() << endl;
	
	if (IsSearchComplete())
	{
		output << "Path was found: ";
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
	}
	else
	{
		output << "Path not found";
	}

	output << endl;
}

void CSearchData::Clear()
{
	m_passedHashes.clear();
}