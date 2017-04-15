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
	CNode* firstNode = new CNode(startMatrix);
	searchQueue.push(firstNode);

	while (!searchQueue.empty())
	{
		ProcessSearch(searchQueue, searchData);
	}
}

void ProcessSearch(queue<CNode*> &searchQueue, CSearchData &searcData)
{
	auto addToQueue_if = [&](const vector<vector<size_t>> &newMatrix) {
		size_t newHash = CNode::GetHashFromMatrix(newMatrix);
		if (searcData.IsHashValid(newHash))
		{
			searchQueue.push(new CNode(newMatrix));
		}
	};

	CNode* currentNode = searchQueue.front();
	const Point emptyPos = currentNode->GetEmptyPoint();
	searcData.InsertHash(currentNode->GetHash());
	searchQueue.pop();

	if (emptyPos.x > 0)
	{
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y][emptyPos.x - 1], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix);
	}
	if (emptyPos.x < searcData.GetFieldSize() - 1)
	{
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y][emptyPos.x + 1], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix);
	}
	if (emptyPos.y > 0)
	{
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y - 1][emptyPos.x], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix);
	}
	if (emptyPos.y < searcData.GetFieldSize() - 1)
	{
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y + 1][emptyPos.x], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix);
	}
}