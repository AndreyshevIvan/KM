#include "stdafx.h"
#include <iostream>

int Sum(int first, int second)
{
	if (first > 0 && second == 0)
		return 0;

	if (first == 0 && second == 0)
		return 1;

	if (second > first)
		return Sum(first, first);

	return Sum(first, second - 1) + Sum(first - second, second);
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	int nodeCount = 0;
	std::cin >> nodeCount;

	std::cout << Sum(nodeCount, nodeCount);

	return 0;
}