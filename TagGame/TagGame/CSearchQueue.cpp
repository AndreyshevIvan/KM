#include "CSearchQueue.h"
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

CNode* CStack::Top()
{
	return m_stack.top();
}
void CStack::Push(CNode* node)
{
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
void CStack::Clear()
{
	while (!m_stack.empty())
	{
		delete m_stack.top();
		m_stack.pop();
	}
}

CNode* CQueue::Top()
{
	return m_queue.front();
}	
void CQueue::Push(CNode* node)
{
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
void CQueue::Clear()
{
	while (!m_queue.empty())
	{
		delete m_queue.front();
		m_queue.pop();
	}
}

CNode* CPriorityQueue::Top()
{
	return m_priorityQueue.begin()->second;
}
bool SortPredicate(matrixPriority firstPair, matrixPriority secondPair)
{
	return firstPair.first <= secondPair.first;
}
void CPriorityQueue::Push(CNode* node)
{
	auto newMatrix = node->GetMatrix();
	const size_t &priority = CalculatePriority(newMatrix);

	m_priorityQueue.insert(priorityMap::value_type(priority, node));
}
void CPriorityQueue::Pop()
{
	if (!IsEmpty())
	{
		m_priorityQueue.erase(m_priorityQueue.begin());
	}
}
bool CPriorityQueue::IsEmpty()
{
	return m_priorityQueue.empty();
}
size_t CPriorityQueue::CalculatePriority(const Matrix &newMatrix)
{
	size_t priority = 0;
	const size_t &matrixSize = newMatrix.size();

	for (size_t row = 0; row < matrixSize; row++)
	{
		for (size_t coll = 0; coll < matrixSize; coll++)
		{
			const size_t &cell = newMatrix[row][coll];
			Point currPoint(coll, row);
			Point destenation = m_coordinates.find(cell)->second;
			int deltaX = static_cast<int>(destenation.x - currPoint.x);
			int deltaY = static_cast<int>(destenation.y - currPoint.y);
			size_t wayLength = abs(deltaX) + abs(deltaY);
			priority += wayLength;
		}
	}
	return priority;
}
void CPriorityQueue::Clear()
{
	while (!m_priorityQueue.empty())
	{
		delete m_priorityQueue.begin()->second;
		m_priorityQueue.erase(m_priorityQueue.begin());
	}
}

void CPriorityQueue::Write()
{
	for (auto& queueUnit : m_priorityQueue)
	{
		cout << queueUnit.first << " ";
	}

	cout << endl;
}