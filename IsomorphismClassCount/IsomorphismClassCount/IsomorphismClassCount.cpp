#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

const char WRITE_CHECK_SYMBOL = 'Y';

typedef std::vector<int> IsomClasses;
typedef std::list<IsomClasses> IsomClassesPack;

void GetIsomClassesPack(IsomClassesPack &pack, IsomClasses &isomClasses, int bound, int sum, int max);
void Write(const IsomClassesPack &classesPack, bool isWriteClasses);

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	int nodeCount = 0;
	std::cout << "Enter nodes count:" << std::endl;
	std::cin >> nodeCount;

	std::cout << "Enter '" << WRITE_CHECK_SYMBOL << "' if need to write classes:" << std::endl;
	char writeCheckSymbol;
	std::cin >> writeCheckSymbol;
	bool isWriteClasses = (writeCheckSymbol == WRITE_CHECK_SYMBOL);

	IsomClasses terms;
	IsomClassesPack termsPack;
	GetIsomClassesPack(termsPack, terms, nodeCount, 0, nodeCount);

	Write(termsPack, isWriteClasses);

	return 0;
}

void GetIsomClassesPack(IsomClassesPack &pack, IsomClasses &isomClasses, int bound, int sum, int max)
{
	for (int number = bound; number >= 1; --number)
	{
		if (sum == max)
		{
			pack.push_back(isomClasses);
			return;
		}
		else if (sum + number <= max)
		{
			isomClasses.push_back(number);
			GetIsomClassesPack(pack, isomClasses, number, sum + number, max);
			isomClasses.pop_back();
		}
	}
}

void Write(const IsomClassesPack &classesPack, bool isWriteClasses)
{
	std::cout << "Classes count: " << classesPack.size() << std::endl;
	if (!isWriteClasses)
	{
		return;
	}

	auto writeClasses = [&](const IsomClasses &classes) {
		std::for_each(classes.begin(), classes.end(), [](int isomClass) {
			std::cout << isomClass << " ";
		});
		std::cout << std::endl;
	};

	std::for_each(classesPack.begin(), classesPack.end(), writeClasses);
	std::cout << std::endl;
}