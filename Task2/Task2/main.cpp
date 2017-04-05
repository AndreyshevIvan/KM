#include "stdafx.h"
#include "Node.h"

using namespace std;

void StartBFS(Node* firstNode);
void ProcessSearch(queue<Node*> &searchQueue, set<size_t> &passedHashes);
bool IsHashValid(set<size_t> &passedHashes, size_t hash);

int main()
{
	Node* firstNode = new Node(START_MATRIX);
	(void)firstNode;
	StartBFS(firstNode);

	return 0;
}

void StartBFS(Node* firstNode)
{
	set<size_t> passedHashes;
	queue<Node*> searchQueue;
	searchQueue.push(firstNode);

	while (!searchQueue.empty())
	{
		ProcessSearch(searchQueue, passedHashes);
	}
	cout << passedHashes.size() << endl;
}

void ProcessSearch(queue<Node*> &searchQueue, set<size_t> &passedHashes)
{
	auto addToQueue_if = [&](const vector<vector<size_t>> &newMatrix) {
		size_t newHash = Node::GetHashFromMatrix(newMatrix);
		if (IsHashValid(passedHashes, newHash))
		{
			searchQueue.push(new Node(newMatrix));
		}
	};

	Node* currentNode = searchQueue.front();
	Point emptyPos = currentNode->GetEmptyPoint();
	passedHashes.insert(currentNode->GetHash());
	searchQueue.pop();

	if (emptyPos.x > 0)
	{
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y][emptyPos.x - 1], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix);
	}
	if (emptyPos.x < FIELD_SIZE - 1)
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
	if (emptyPos.y < FIELD_SIZE - 1)
	{
		vector<vector<size_t>> matrix = currentNode->GetMatrix();
		swap(matrix[emptyPos.y + 1][emptyPos.x], matrix[emptyPos.y][emptyPos.x]);
		addToQueue_if(matrix);
	}
}

bool IsHashValid(set<size_t> &passedHashes, size_t hash)
{
	return (passedHashes.find(hash) == passedHashes.end());
}