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

	return 0;
}

void StartSearch(CSearchData &searchData, CSearchQueue* searchQueue)
{
	const size_t fieldSize = searchData.GetFieldSize();
	const Matrix startMatrix = CNode::CreateStartMatrix(fieldSize);

	CNode* firstNode = new CNode(startMatrix);
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
	const Point emptyPos = currentNode->GetEmptyPoint();
	const size_t currHash = currentNode->GetHash();
	const vector<Direction> prevPath = currentNode->GetPath();
	searchQueue->Pop();

	auto addToQueue_if = [&](const Matrix &newMatrix, Direction newDirect) {
		const size_t newHash = CNode::GetHashFromMatrix(newMatrix);
		const size_t prevDepth = currentNode->GetDepth();
		const size_t newDepth = prevDepth + 1;

		if (searchData.IsHashValid(newHash) && searchData.IsDepthValid(newDepth))
		{
			CNode* newNode = new CNode(newMatrix, prevPath, newDepth);
			newNode->AddToPath(newDirect);
			searchQueue->Push(newNode, searchData.GetSearchMatrix());
			searchData.IncreaseGeneratedNodes();
		}
	};
	
	searchData.InsertHash(currHash);
	if (searchData.IsSearchComplete())
	{
		searchData.SetPath(prevPath);
		return;
	}

	if (emptyPos.x > 0)
	{
		Matrix matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y][emptyPos.x - 1], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix, Direction::RIGHT);
	}
	if (emptyPos.x < searchData.GetFieldSize() - 1)
	{
		Matrix matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y][emptyPos.x + 1], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix, Direction::LEFT);
	}
	if (emptyPos.y > 0)
	{
		Matrix matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y - 1][emptyPos.x], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix, Direction::DOWN);
	}
	if (emptyPos.y < searchData.GetFieldSize() - 1)
	{
		Matrix matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y + 1][emptyPos.x], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix, Direction::UP);
	}
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
		return new CPriorityQueue();
	}

	return nullptr;
}