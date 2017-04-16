#include "CSearchData.h"

#include <queue>
#include <iostream>

using namespace std;

const int ARGUMENTS_COUNT = 3;

void StartBFS(CSearchData &searcData);
void ProcessSearch(queue<CNode*> &searchQueue, CSearchData &searcData);

int main(int argc, char* argv[])
{
	if (argc < ARGUMENTS_COUNT)
	{
		std::cerr << "Invalid arguments" << endl;
		return 1;
	}

	ifstream input(argv[1]);
	CSearchData searchData(input);

	StartBFS(searchData);

	ofstream output(argv[2]);
	searchData.Print(output);

	return 0;
}

void StartBFS(CSearchData &searchData)
{
	const size_t fieldSize = searchData.GetFieldSize();
	const vector<vector<size_t>> startMatrix = CNode::CreateStartMatrix(fieldSize);

	queue<CNode*> searchQueue;
	vector<Direction> nullPath;
	CNode* firstNode = new CNode(startMatrix, nullPath, 0);
	searchQueue.push(firstNode);

	while (!searchQueue.empty())
	{
		ProcessSearch(searchQueue, searchData);

		if (searchData.IsSearchComplete())
		{
			break;
		}
	}
}

void ProcessSearch(queue<CNode*> &searchQueue, CSearchData &searchData)
{
	CNode* currentNode = searchQueue.front();
	const Point emptyPos = currentNode->GetEmptyPoint();
	const size_t currHash = currentNode->GetHash();
	const vector<Direction> prevPath = currentNode->GetPath();
	searchQueue.pop();

	auto addToQueue_if = [&](const vector<vector<size_t>> &newMatrix, Direction newDirect) {
		const size_t newHash = CNode::GetHashFromMatrix(newMatrix);
		const size_t prevDepth = currentNode->GetDepth();
		const size_t newDepth = prevDepth + 1;

		if (searchData.IsHashValid(newHash) && searchData.IsDepthValid(newDepth))
		{
			CNode* newNode = new CNode(newMatrix, prevPath, newDepth);
			newNode->AddToPath(newDirect);
			searchQueue.push(newNode);
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
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y][emptyPos.x - 1], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix, Direction::RIGHT);
	}
	if (emptyPos.x < searchData.GetFieldSize() - 1)
	{
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y][emptyPos.x + 1], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix, Direction::LEFT);
	}
	if (emptyPos.y > 0)
	{
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y - 1][emptyPos.x], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix, Direction::DOWN);
	}
	if (emptyPos.y < searchData.GetFieldSize() - 1)
	{
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y + 1][emptyPos.x], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix, Direction::UP);
	}
}