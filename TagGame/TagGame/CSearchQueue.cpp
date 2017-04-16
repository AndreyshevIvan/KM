#include "CSearchQueue.h"
#include <string>
#include <iostream>

using namespace std;

CNode* CStack::Top()
{
	return m_stack.top();
}
void CStack::Push(CNode* node, const Matrix &searchMatrix, const Matrix &newMatrix)
{
	(void)newMatrix;
	(void)searchMatrix;
	m_stack.push(node);
}
void CStack::Pop()
{
	if (!IsEmpty())
	{
		m_stack.pop();
	}
}
bool CStack::IsEmpty()
{
	return m_stack.empty();
}
size_t CStack::CalculatePriority(const Matrix &searchMatrix, const Matrix &newMatrix)
{
	return 0;
}

CNode* CQueue::Top()
{
	return m_queue.front();
}	
void CQueue::Push(CNode* node, const Matrix &searchMatrix, const Matrix &newMatrix)
{
	(void)newMatrix;
	(void)searchMatrix;
	m_queue.push(node);
}
void CQueue::Pop()
{
	if (!IsEmpty())
	{
		m_queue.pop();
	}
}
bool CQueue::IsEmpty()
{
	return m_queue.empty();
}
size_t CQueue::CalculatePriority(const Matrix &searchMatrix, const Matrix &newMatrix)
{
	return 0;
}

CNode* CPriorityQueue::Top()
{
	return m_map.begin()->second;
}
void CPriorityQueue::Push(CNode* node, const Matrix &searchMatrix, const Matrix &newMatrix)
{
	const size_t priority = CalculatePriority(searchMatrix, newMatrix);
	(void)node;
}
void CPriorityQueue::Pop()
{
	if (!IsEmpty())
	{
		m_map.erase(m_map.begin());
	}
}
bool CPriorityQueue::IsEmpty()
{
	return m_map.empty();
}
size_t CPriorityQueue::CalculatePriority(const Matrix &searchMatrix, const Matrix &newMatrix)
{
	(void)searchMatrix;
	(void)newMatrix;

	return 0;
}