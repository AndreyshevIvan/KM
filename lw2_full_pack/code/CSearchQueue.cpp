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
	auto topPair = m_priorityQueue.begin();
	return topPair->second.front();
}
void CPriorityQueue::Push(CNode* node)
{
	const Matrix &newMatrix = node->GetMatrix();
	const size_t &priority = CalculatePriority(newMatrix) + node->GetDepth();

	auto findPair = m_priorityQueue.find(priority);

	if (findPair == m_priorityQueue.end())
	{
		auto newPack = new vector<CNode*>;
		newPack->push_back(node);
		m_priorityQueue.insert(std::make_pair(priority, *newPack));
	}
	else
	{
		findPair->second.push_back(node);
	}
}
void CPriorityQueue::Pop()
{
	if (IsEmpty())
	{
		return;
	}

	auto nodesPack = &m_priorityQueue.begin()->second;
	if (!nodesPack->empty())
	{
		auto topNode = nodesPack->begin();
		nodesPack->erase(topNode);
	}

	if (nodesPack->empty())
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
			const short &cell = newMatrix[row][coll];
			Point currPoint((short)coll, (short)row);
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

}

void CPriorityQueue::Write()
{
	for (auto& queueUnit : m_priorityQueue)
	{
		cout << queueUnit.first << " ";
	}

	cout << endl;
}