#pragma once
#include <vector>
#include "Cell.h"

class MyCellList
{
public:
	MyCellList();
	void clearList();
	void clearCellsToPush();
	std::vector<Cell*>& getSelectedCells();
	std::vector<Cell*>& getCellsToPush();
	Cell* getSelectedCell(int index);
	Cell* getCellToPush(int index);
	void add(Cell* cell);
	int size();
	int sizeCellsToPush();
	void addToCellsToPush(Cell* cell);
	bool isEmpty();
	void sort(std::vector<Cell*>& list, bool reverse);
private:
	std::vector<Cell*> m_selectedCells;
	std::vector<Cell*> m_sortedSelectedCells;
	std::vector<Cell*> m_cellsToPush;
	int m_size = 0;
	int m_MAX_SIZE = 3;
	void pop();
	void pop(Cell* pos);
	bool contains(Cell* pos);
};

