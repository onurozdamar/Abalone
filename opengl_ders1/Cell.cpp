#include "Cell.h"

Cell::Cell(int x, int y) {
	m_r = 22;
	m_konum.setX(x + m_r / 2);
	m_konum.setY(y + m_r);
	m_topRengi = new Renk(0, 0, 0);
	m_type = Ball_type::BLANK;
	m_hareketEdecekMi = false;
	m_selected = false;
}

void Cell::draw() {

	if (m_selected) {
		Renk selectedBallColor(255, 0, 0);
		glColor3f(selectedBallColor.getRed(), selectedBallColor.getGreen(), selectedBallColor.getBlue());
		circleMidpoint(m_konum.getX(), m_konum.getY(), m_r + 2);
	}
	glColor3f(m_topRengi->getRed(), m_topRengi->getGreen(), m_topRengi->getBlue());
	circleMidpoint(m_konum.getX(), m_konum.getY(), m_r);
}

bool Cell::contains(float mx, float  my) {
	if (mx > m_konum.getX() - m_r && mx < m_konum.getX() + m_r
		&& my > m_konum.getY() - m_r && my < m_konum.getY() + m_r) {
		return true;
	}
	return false;
}

void Cell::resetCellToBlank() {
	setSelected(false);
	setHareketEdecekMi(false);
	setBallColor(new Renk(210, 110, 30));
	setTypeToBlank();
}

void Cell::setSelected(bool selected) {
	if (!isBlank()) {
		m_selected = selected;
	}
}

void Cell::setHareketEdecekMi(bool hareketEdecek) {
	if (!isBlank()) {
		m_hareketEdecekMi = hareketEdecek;
	}
}

bool Cell::isHareketEdecekMi() {
	return m_hareketEdecekMi;
}

void Cell::setBallColor(Renk* renk) {
	m_topRengi = renk;
}

void Cell::setTypeToBlank() {
	setBallColor(new Renk(210, 110, 30));
	m_type = Ball_type::BLANK;
}

void Cell::setTypeToWhite() {
	setBallColor(new Renk(221, 221, 221));
	m_type = Ball_type::WHITE;
}

void Cell::setTypeToBlack() {
	setBallColor(new Renk(1, 1, 1));
	m_type = Ball_type::BLACK;
}

void Cell::setType(Cell::Ball_type type) {
	switch (type) {
	case Ball_type::WHITE:
		setTypeToWhite();
		break;
	case Ball_type::BLACK:
		setTypeToBlack();
		break;
	case Ball_type::BLANK:
		setTypeToBlank();
		break;
	}
}

Cell::Ball_type Cell::getType() {
	return m_type;
}

Renk* Cell::getColor() {
	return m_topRengi;
}

Konum Cell::getKonum() {
	return m_konum;
}

bool Cell::greater(Cell* other) {
	if (m_konum.getY() == other->m_konum.getY()) {
		return m_konum.getX() > other->m_konum.getX();
	}
	return m_konum.getY() > other->m_konum.getY();
}

bool Cell::typeEqual(Cell* other) {
	return m_type == other->m_type;
}

bool Cell::equals(Cell* other) {
	return m_konum.getX() == other->m_konum.getX() && m_konum.getY() == other->m_konum.getY();
}

bool Cell::isWhite() {
	return m_type == Ball_type::WHITE;
}

bool Cell::isBlack() {
	return m_type == Ball_type::BLACK;
}

bool Cell::isBlank() {
	return m_type == Ball_type::BLANK;
}

void Cell::setNull(bool null) {
	m_null = null;
}

bool Cell::isNull() {
	return m_null;
}

void Cell::circleMidpoint(int xc, int yc, int r) {
	Konum cemberPt;
	//orta nokta parametresinin baþlangýç deðeri
	GLint p = 1 - r;
	cemberPt.setX(0); cemberPt.setY(r);
	//Her çember sekizli bölgesinde baþlangýç noktasýný çiz
	glBegin(GL_POLYGON);
	cemberNoktalarýCiz(xc, yc, cemberPt);
	//Bir sonraki noktayý hesapla ve her bir sekizli bölgede çizdir
	while (cemberPt.getX() < cemberPt.getY()) {
		cemberPt.setX(cemberPt.getX() + 1);
		if (p < 0)
			p += 2 * cemberPt.getX() + 1;
		else {
			cemberPt.setY(cemberPt.getY() - 1);
			p += 2 * (cemberPt.getX() - cemberPt.getY()) + 1;
		}
		cemberNoktalarýCiz(xc, yc, cemberPt);
	}
	glEnd();
}

void Cell::cemberNoktalarýCiz(int xc, int yc, Konum cemberPt) {
	glVertex2f(xc + cemberPt.getX(), yc + cemberPt.getY());
	glVertex2f(xc - cemberPt.getX(), yc + cemberPt.getY());
	glVertex2f(xc + cemberPt.getX(), yc - cemberPt.getY());
	glVertex2f(xc - cemberPt.getX(), yc - cemberPt.getY());
	glVertex2f(xc + cemberPt.getY(), yc + cemberPt.getX());
	glVertex2f(xc - cemberPt.getY(), yc + cemberPt.getX());
	glVertex2f(xc + cemberPt.getY(), yc - cemberPt.getX());
	glVertex2f(xc - cemberPt.getY(), yc - cemberPt.getX());
}