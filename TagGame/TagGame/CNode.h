#pragma once
#include <vector>
#include <map>

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


typedef std::map<size_t, Point> CellCoordinates;
typedef std::vector<std::vector<size_t>> Matrix;

class CNode
{
public:
	CNode(Matrix && matrix, size_t hash, const std::vector<Direction> &path = {}, size_t depth = 0);

	static size_t GetHashFromMatrix(const Matrix &matrix);
	static Matrix CreateStartMatrix(size_t size);

	Matrix GetMatrix();
	size_t GetHash();
	size_t GetDepth();
	std::vector<Direction> GetPath();
	Point GetEmptyPoint();

	void MoveEmptyPos(Point && fatherEmptyPos, Direction direction);
	void IncreaseDepth(size_t addingDepth = 1);

private:
	size_t m_hash = 0;
	size_t m_depth = 0;
	Point m_emptyPosition = { 0, 0 };
	Matrix m_matrix;
	std::vector<Direction> m_path;
};