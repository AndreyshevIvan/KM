#pragma once
#include <queue>
#include <stack>
#include <set>
#include "CNode.h"

const std::string BFS_SEARCH_NAME = "bfs";
const std::string DFS_SEARCH_NAME = "dfs";
const std::string ASTAR_SEARCH_NAME = "astar";

typedef std::pair<size_t, CNode*> matrixPriority;
struct ComparePriority
{
	bool operator() (const matrixPriority &firstPair, const matrixPriority &secondPair) const
	{
		return firstPair.first < secondPair.first;
	}
};
typedef std::set<matrixPriority, ComparePriority> priorityMap;

class CSearchQueue
{
public:
	virtual CNode* Top() = 0;
	virtual void Push(CNode* node, const Matrix &searchMatrix = {}) = 0;
	virtual void Pop() = 0;
	virtual bool IsEmpty() = 0;

protected:
	std::queue<CNode*> m_queue;
	priorityMap m_priorityQueue;
	std::stack<CNode*> m_stack;
};

class CStack : public CSearchQueue
{
public:
	CNode* Top() override;
	void Push(CNode* node, const Matrix &searchMatrix = {}) override;
	void Pop() override;
	bool IsEmpty() override;
};

class CQueue : public CSearchQueue
{
public:
	CNode* Top() override;
	void Push(CNode* node, const Matrix &searchMatrix = {}) override;
	void Pop() override;
	bool IsEmpty() override;
};

class CPriorityQueue : public CSearchQueue
{
public:
	CNode* Top() override;
	void Push(CNode* node, const Matrix &searchMatrix = {}) override;
	void Pop() override;
	bool IsEmpty() override;

private:
	size_t CalculatePriority(const Matrix &newMatrix, const Matrix &searchMatrix);

};