#pragma once
#include"Cell.h"
#include<vector>
#include"MyCellList.h"

class GameManager
{
public:
	GameManager();

	void resetGame();
	void setup();
	void drawCells();
	void mousePressed(float, float);

	void play(Cell*);
	void push(Cell*);
	void addToSelectedCells(Cell* cell);
	bool canSelect(Cell* cell);

	Cell* getNextCell(Cell* cell, int dx, int dy);
	Cell* getCell(int x, int y);

	static int const CELL_SIZE = 70;
	static int const OFFSETX = 15;

private:
	std::vector<Cell*> m_cells[9];
	MyCellList m_cellList;
	const int m_rowCount = 9;

	//altýgen tahta olmasý için her satýrda kaç top eksik olacaðýný tutar
	int m_eksikTopSayisi[9] = { 4, 3, 2, 1, 0, 1, 2, 3, 4 };

	bool m_whiteTurn;
	void play(Cell*, std::vector<Cell*>);
	bool canPush(Cell*);
	bool canPlay(Cell*);
	void play(Cell* source, Cell* dest);
	bool isDiagonel();
	int getDiffrenceX(Cell* source, Cell* dest);
	int getDiffrenceY(Cell* source, Cell* dest);
	bool isDistanceOneCell(Cell* source, Cell* destination);
	bool isNecessaryReverse(Cell* destination);
};

