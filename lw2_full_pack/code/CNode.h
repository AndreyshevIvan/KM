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
	Point(short x, short y)
	{
		this->x = x;
		this->y = y;
	}

	short x = 0;
	short y = 0;
};


typedef std::map<short, Point> CellCoordinates;
typedef std::vector<std::vector<short>> Matrix;

class CNode
{
public:
	CNode(Matrix && matrix, size_t hash, const std::vector<short> &path = {}, short depth = 0);

	static size_t GetHashFromMatrix(const Matrix &matrix);
	static Matrix CreateStartMatrix(size_t size);

	Matrix GetMatrix();
	size_t GetHash();
	short GetDepth();
	std::vector<short> GetPath();
	Point GetEmptyPoint();

	void MoveEmptyPos(Point && fatherEmptyPos, Direction direction);
	void IncreaseDepth(short addingDepth = 1);

private:
	size_t m_hash = 0;
	short m_depth = 0;
	Point m_emptyPosition = { 0, 0 };
	Matrix m_matrix;
	std::vector<short> m_path;
};