#pragma once
#include"konum.h"
#include "renk.h"
#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include"Renk.h"

class Cell
{
public:
	enum class Ball_type {
		BLANK,
		WHITE,
		BLACK
	};
	Cell(int x, int y);
	void draw();
	void circleMidpoint(int xc, int yc, int r);
	void cemberNoktalarýCiz(int xc, int yc, Konum cemberPt);

	bool contains(float mx, float my);
	void setBallColor(Renk* renk);
	Renk* getColor();
	void setTypeToBlank(); void setTypeToWhite(); void setTypeToBlack();
	void setType(Ball_type);
	Ball_type getType();
	void resetCellToBlank();
	void setSelected(bool); void setHareketEdecekMi(bool);
	bool isHareketEdecekMi();
	Konum getKonum();
	bool isWhite(); bool isBlack(); bool isBlank();
	bool greater(Cell* other);
	bool typeEqual(Cell* other);
	bool equals(Cell* other);
	bool isNull(); void setNull(bool);
private:
	Konum m_konum;
	Renk* m_topRengi;
	Ball_type m_type;
	int m_r;
	bool m_selected, m_hareketEdecekMi;
	int w = 70;
	bool m_null = false;
	friend class Cell;
};

