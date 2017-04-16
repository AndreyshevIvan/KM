#pragma once
#include <vector>
#include <fstream>
#include <set>
#include <string>
#include "CNode.h"

class CSearchData
{
public:
	CSearchData(std::ifstream &input);

	size_t GetFieldSize();
	std::string GetSearchName();
	Matrix GetSearchMatrix();

	void SetPath(const std::vector<Direction> &direction);

	void IncreaseGeneratedNodes(size_t addingCount = 1);
	void IncreaseOpenNodes(size_t addingCount = 1);
	void InsertHash(size_t hash);

	bool IsHashValid(size_t hash);
	bool IsSearchComplete();
	bool IsDepthValid(size_t depth);

	void Print(std::ostream &output);

private:
	size_t m_fieldSize;
	size_t m_searchDepth;
	size_t m_generateNodesCount = 0;
	size_t m_openNodesCount = 0;
	size_t m_searchHash;
	Matrix m_searchMatrix;
	std::string m_searchHashStr;
	std::vector<Direction> m_path;
	std::set<size_t> m_passedHashes;
	std::string m_searchName;
	bool m_isSearchComplete = false;

};