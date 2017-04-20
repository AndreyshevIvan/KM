#pragma once
#include <queue>
#include <stack>
#include <set>
#include <iostream>
#include "CNode.h"

const std::string BFS_SEARCH_NAME = "bfs";
const std::string DFS_SEARCH_NAME = "dfs";
const std::string ASTAR_SEARCH_NAME = "astar";

typedef std::map<size_t, std::vector<CNode*>> priorityMap;

class CSearchQueue
{
public:
	virtual CNode* Top() = 0;
	virtual void Push(CNode* node) = 0;
	virtual void Pop() = 0;
	virtual bool IsEmpty() = 0;
	virtual void Clear() = 0;
	virtual void Write() = 0;

protected:
	std::queue<CNode*> m_queue;
	priorityMap m_priorityQueue;
	std::stack<CNode*> m_stack;
};

class CStack : public CSearchQueue
{
public:
	CNode* Top() override;
	void Push(CNode* node) override;
	void Pop() override;
	bool IsEmpty() override;
	void Clear() override;
	void Write() override {};
};

class CQueue : public CSearchQueue
{
public:
	CNode* Top() override;
	void Push(CNode* node) override;
	void Pop() override;
	bool IsEmpty() override;
	void Clear() override;
	void Write() override {};
};

class CPriorityQueue : public CSearchQueue
{
public:
	CPriorityQueue(CellCoordinates coordinates)
	{
		m_coordinates = coordinates;
	}

	CNode* Top() override;
	void Push(CNode* node) override;
	void Pop() override;
	bool IsEmpty() override;
	void Clear() override;
	void Write() override;

private:
	size_t CalculatePriority(const Matrix &newMatrix);

	CellCoordinates m_coordinates;
};