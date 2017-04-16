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

typedef std::vector<std::vector<size_t>> Matrix;

const Matrix START_MATRIX = {
	{ 0, 1, 2 },
	{ 3, 4, 5 },
	{ 6, 7, 8 }
};

class CNode
{
public:
	CNode(const Matrix &matrix, const std::vector<Direction> &path = {}, size_t depth = 0);

	static size_t GetHashFromMatrix(const Matrix &matrix);
	static Matrix CreateStartMatrix(size_t size);

	Matrix GetMatrix();
	size_t GetHash();
	size_t GetDepth();
	std::vector<Direction> GetPath();
	Point GetEmptyPoint();

	void IncreaseDepth(size_t addingDepth = 1);
	void AddToPath(Direction direction);

private:
	size_t m_hash = 0;
	size_t m_depth = 0;
	Point m_emptyPosition = { 0, 0 };
	Matrix m_matrix;
	std::vector<Direction> m_path;

	void CalculateHash();
	void CalculateEmptyPosition();
};