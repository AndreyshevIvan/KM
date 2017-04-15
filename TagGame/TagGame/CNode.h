#pragma once
#include <vector>

enum struct Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Point
{
	Point(size_t x, size_t y)
	{
		this->x = x;
		this->y = y;
	}

	size_t x = 0;
	size_t y = 0;
};

const std::vector<std::vector<size_t>> START_MATRIX = {
	{ 0, 1, 2 },
	{ 3, 4, 5 },
	{ 6, 7, 8 }
};

class CNode
{
public:
	CNode(const std::vector<std::vector<size_t>> &matrix);

	static size_t GetHashFromMatrix(const std::vector<std::vector<size_t>> &matrix);
	static std::vector<std::vector<size_t>> CreateStartMatrix(size_t size);

	std::vector<std::vector<size_t>> GetMatrix();
	size_t GetHash();
	size_t GetDepth();
	Point GetEmptyPoint();
	void IncreaseDepth(size_t addingDepth = 1);

private:
	size_t m_hash = 0;
	size_t m_depth = 0;
	Point m_emptyPosition = { 0, 0 };
	std::vector<std::vector<size_t>> m_matrix;

	void CalculateHash();
	void CalculateEmptyPosition();
};