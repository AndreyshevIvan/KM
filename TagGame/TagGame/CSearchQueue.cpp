#include "CSearchQueue.h"
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

CNode* CStack::Top()
{
	return m_stack.top();
}
void CStack::Push(CNode* node, const Matrix &searchMatrix)
{
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

CNode* CQueue::Top()
{
	return m_queue.front();
}	
void CQueue::Push(CNode* node, const Matrix &searchMatrix)
{
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

CNode* CPriorityQueue::Top()
{
	return m_priorityQueue.begin()->second;
}
bool SortPredicate(matrixPriority firstPair, matrixPriority secondPair)
{
	return firstPair.first <= secondPair.first;
}
void CPriorityQueue::Push(CNode* node, const Matrix &searchMatrix)
{
	const Matrix newMatrix = node->GetMatrix();
	const size_t priority = CalculatePriority(newMatrix, searchMatrix);

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
size_t CPriorityQueue::CalculatePriority(const Matrix &newMatrix, const Matrix &searchMatrix)
{
	auto getCoordinateInMatrix = [](const Matrix &matrix, size_t cellNum) {
		const size_t matrixSize = matrix.size();
		for (size_t i = 0; i < matrixSize; i++)
		{
			for (size_t j = 0; j < matrixSize; j++)
			{
				if (matrix[i][j] == cellNum)
				{
					return Point(j, i);
				}
			}
		}
		return Point(0, 0);
	};

	size_t priority = 0;
	const size_t matrixSize = newMatrix.size();

	for (size_t row = 0; row < matrixSize; row++)
	{
		for (size_t coll = 0; coll < matrixSize; coll++)
		{
			const size_t cell = newMatrix[row][coll];
			Point currPoint(coll, row);
			Point destenation = getCoordinateInMatrix(searchMatrix, cell);
			int deltaX = static_cast<int>(destenation.x - currPoint.x);
			int deltaY = static_cast<int>(destenation.y - currPoint.y);
			size_t wayLength = abs(deltaX) + abs(deltaY);
			priority += wayLength;
		}
	}
	return priority;
}