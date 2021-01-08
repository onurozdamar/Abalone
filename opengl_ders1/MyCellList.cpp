#include "MyCellList.h"
#include <algorithm>

MyCellList::MyCellList() {
	m_size = 0;
}

void MyCellList::clearList() {
	m_selectedCells.clear();
	m_cellsToPush.clear();
	m_sortedSelectedCells.clear();
	m_size = 0;
}

void MyCellList::clearCellsToPush() {
	m_cellsToPush.clear();
}

std::vector<Cell*>& MyCellList::getSelectedCells() {
	return m_sortedSelectedCells;
}

std::vector<Cell*>& MyCellList::getCellsToPush() {
	return m_cellsToPush;
}

Cell* MyCellList::getSelectedCell(int index) {
	return m_sortedSelectedCells.at(index);
}

Cell* MyCellList::getCellToPush(int index) {
	return m_cellsToPush.at(index);
}

bool comp(Cell* f, Cell* s) {
	if (f->getKonum().getY() == s->getKonum().getY()) {
		return f->getKonum().getX() > s->getKonum().getX();
	}
	return f->getKonum().getY() > s->getKonum().getY();
}

void MyCellList::add(Cell* cell) {
	if (contains(cell)) {
		pop(cell);
		std::vector<Cell*> newVector = std::vector<Cell*>(m_selectedCells.begin(), m_selectedCells.end());
		m_sortedSelectedCells = newVector;
		std::sort(m_sortedSelectedCells.begin(), m_sortedSelectedCells.end(), comp);
		return;
	}

	m_size++;
	m_selectedCells.push_back(cell);
	cell->setSelected(true);
	cell->setHareketEdecekMi(true);
	pop();

	m_sortedSelectedCells = m_selectedCells;
	std::sort(m_sortedSelectedCells.begin(), m_sortedSelectedCells.end(), comp);
}

void MyCellList::pop() {
	if (m_size <= m_MAX_SIZE) return;
	pop(m_selectedCells.at(0));
}

void MyCellList::pop(Cell* pos) {
	int v_size = m_selectedCells.size();
	for (int i = 0; i < v_size; i++) {
		if (m_selectedCells.at(i)->equals(pos)) {
			m_selectedCells.at(i)->setSelected(false);
			m_selectedCells.at(i)->setHareketEdecekMi(false);
			m_selectedCells.erase(m_selectedCells.begin() + i);
			m_size--;
			return;
		}
	}
}

void MyCellList::sort(std::vector<Cell*>& list, bool reverse) {
	if (list.size() <= 1) return;

	std::sort(list.begin(), list.end(), comp);

	if (reverse) {
		std::reverse(list.begin(), list.end());
		std::cout << "ters" << std::endl;
	}
}

int MyCellList::size() {
	return m_selectedCells.size();
}

int MyCellList::sizeCellsToPush() {
	return m_cellsToPush.size();
}

void MyCellList::addToCellsToPush(Cell* cell) {
	m_cellsToPush.push_back(cell);
}

bool MyCellList::contains(Cell* pos) {
	for (Cell* p : m_selectedCells) {
		if (p->equals(pos)) return true;
	}
	return false;
}

bool MyCellList::isEmpty() {
	return m_size <= 0;
}

