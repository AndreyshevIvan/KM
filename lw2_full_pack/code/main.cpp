#include "CSearchData.h"
#include "CSearchQueue.h"

#include <iostream>

using namespace std;

const string CFG_FILE_NAME = "config.txt";

void StartSearch(CSearchData &searcData, CSearchQueue* searchQueue);
void ProcessSearch(CSearchQueue* searchQueue, CSearchData &searcData);
CSearchQueue* CreateSearchQueue(CSearchData &searchData);

int main(int argc, char* argv[])
{
	ifstream input(CFG_FILE_NAME);
	if (!input.is_open())
	{
		cerr << "Config file not found" << endl;
		return 1;
	}

	CSearchData searchData(input);
	CSearchQueue* searchQueue = CreateSearchQueue(searchData);
	if (searchQueue == nullptr)
	{
		std::cerr << "Invalid search type." << endl;
		return 1;
	}

	StartSearch(searchData, searchQueue);

	if (argc > 1)
	{
		ofstream output(argv[1]);
		searchData.Print(output);
	}
	else
	{
		searchData.Print(cout);
	}

	searchData.Clear();

	return 0;
}

void StartSearch(CSearchData &searchData, CSearchQueue* searchQueue)
{
	const size_t fieldSize = searchData.GetFieldSize();
	Matrix startMatrix = CNode::CreateStartMatrix(fieldSize);

	const size_t newHash = CNode::GetHashFromMatrix(startMatrix);
	CNode* firstNode = new CNode(move(startMatrix), newHash);
	searchQueue->Push(firstNode);

	while (!searchQueue->IsEmpty())
	{
		ProcessSearch(searchQueue, searchData);

		if (searchData.IsSearchComplete())
		{
			break;
		}
	}
}

void ProcessSearch(CSearchQueue* searchQueue, CSearchData &searchData)
{
	CNode* currentNode = searchQueue->Top();
	bool isNodeOpen = false;
	const Point emptyPos = currentNode->GetEmptyPoint();
	vector<short> prevPath = currentNode->GetPath();
	searchQueue->Pop();

	auto addToQueue_if = [&](Matrix && newMatrix, Direction newDirect) {
		const size_t newHash = CNode::GetHashFromMatrix(newMatrix);
		const short prevDepth = currentNode->GetDepth();
		const short newDepth = prevDepth + 1;

		if (searchData.IsHashValid(newHash) && searchData.IsDepthValid(newDepth))
		{
			CNode* newNode = new CNode(move(newMatrix), newHash, prevPath, newDepth);
			newNode->MoveEmptyPos(move(currentNode->GetEmptyPoint()), newDirect);
			searchQueue->Push(newNode);
			searchData.IncreaseGeneratedNodes();

			if (!isNodeOpen)
			{
				isNodeOpen = true;
				searchData.IncreaseOpenNodes();
			}
		}
	};

	searchData.InsertHash(currentNode->GetHash());
	if (searchData.IsSearchComplete())
	{
		searchData.SetPath(prevPath);
		return;
	}

	if (emptyPos.x > 0)
	{
		auto matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y][emptyPos.x - 1], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(move(matrix), Direction::RIGHT);
	}
	if (emptyPos.x < searchData.GetFieldSize() - 1)
	{
		auto matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y][emptyPos.x + 1], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(move(matrix), Direction::LEFT);
	}
	if (emptyPos.y < searchData.GetFieldSize() - 1)
	{
		auto matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y + 1][emptyPos.x], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(move(matrix), Direction::UP);
	}
	if (emptyPos.y > 0)
	{
		auto matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y - 1][emptyPos.x], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(move(matrix), Direction::DOWN);
	}

	delete currentNode;
}

CSearchQueue* CreateSearchQueue(CSearchData &searchData)
{
	const string searchName = searchData.GetSearchName();

	if (searchName == BFS_SEARCH_NAME)
	{
		return new CQueue();
	}
	if (searchName == DFS_SEARCH_NAME)
	{
		return new CStack();
	}
	if (searchName == ASTAR_SEARCH_NAME)
	{
		return new CPriorityQueue(searchData.GetCoordinates());
	}

	return nullptr;
}