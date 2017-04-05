#include "stdafx.h"
#include "Node.h"

using namespace std;

void StartBFS(Node* firstNode);
void ProcessSearch(queue<Node*> &searchQueue, set<size_t> &passedHashes);

int main()
{
	Node* firstNode = new Node(START_MATRIX);

	//StartBFS(firstNode);

	return 0;
}

void StartBFS(Node* firstNode)
{
	set<size_t> passedHashes;
	queue<Node*> searchQueue;
	searchQueue.push(firstNode);

	while (!searchQueue.empty())
	{

	}

	cout << passedHashes.size();
}

void ProcessSearch(queue<Node*> &searchQueue, set<size_t> &passedHashes)
{
	Node* currentNode = searchQueue.front();
	passedHashes.insert(currentNode->GetHash());
	searchQueue.pop();
}