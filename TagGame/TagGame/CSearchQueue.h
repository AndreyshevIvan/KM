#pragma once
#include <queue>
#include <stack>
#include <map>
#include "CNode.h"

const std::string BFS_SEARCH_NAME = "bfs";
const std::string DFS_SEARCH_NAME = "dfs";
const std::string ASTAR_SEARCH_NAME = "astar";

typedef std::map<size_t, CNode*> priorityMap;

class CSearchQueue
{
public:
	virtual CNode* Top() = 0;
	virtual void Push(CNode* node, const Matrix &searchMatrix = {}, const Matrix &newMatrix = {}) = 0;
	virtual void Pop() = 0;
	virtual bool IsEmpty() = 0;

protected:
	std::queue<CNode*> m_queue;
	priorityMap m_map;
	std::stack<CNode*> m_stack;

	virtual size_t CalculatePriority(const Matrix &searchMatrix, const Matrix &newMatrix) = 0;
};

class CStack : public CSearchQueue
{
public:
	CNode* Top() override;
	void Push(CNode* node, const Matrix &searchMatrix = {}, const Matrix &newMatrix = {}) override;
	void Pop() override;
	bool IsEmpty() override;

protected:
	size_t CalculatePriority(const Matrix &searchMatrix, const Matrix &newMatrix) override;
};

class CQueue : public CSearchQueue
{
public:
	CNode* Top() override;
	void Push(CNode* node, const Matrix &searchMatrix = {}, const Matrix &newMatrix = {}) override;
	void Pop() override;
	bool IsEmpty() override;

protected:
	size_t CalculatePriority(const Matrix &searchMatrix, const Matrix &newMatrix) override;
};

class CPriorityQueue : public CSearchQueue
{
public:
	CNode* Top() override;
	void Push(CNode* node, const Matrix &searchMatrix = {}, const Matrix &newMatrix = {}) override;
	void Pop() override;
	bool IsEmpty() override;

protected:
	size_t CalculatePriority(const Matrix &searchMatrix, const Matrix &newMatrix) override;

};