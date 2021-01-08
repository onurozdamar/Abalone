#include "GameManager.h"
#include <algorithm>

GameManager::GameManager() {
	m_whiteTurn = true;
}

void  GameManager::setup() {
	for (int i = 0; i < m_rowCount; i++) {
		for (int j = 0; j < m_rowCount; j++) {
			if (j >= m_eksikTopSayisi[i]) {
				Cell* newCell = new Cell((j + 1) * CELL_SIZE + OFFSETX - CELL_SIZE / 2 * m_eksikTopSayisi[i],
					i * CELL_SIZE + CELL_SIZE / 2);
				m_cells[i].push_back(newCell);
			}
		}
	}

	resetGame();
}

void GameManager::drawCells() {
	for (int i = 0; i < m_rowCount; i++) {
		for (Cell* cell : m_cells[i]) {
			cell->draw();
		}
	}
}

void GameManager::mousePressed(float xMouse, float yMouse) {
	for (int i = 0; i < m_rowCount; i++) {
		for (int j = 0; j < m_cells[i].size(); j++) {
			Cell* selectedCell = m_cells[i].at(j);
			if (selectedCell->contains(xMouse, yMouse)) {
				if (canSelect(selectedCell)) { // seçimi yap
					addToSelectedCells(m_cells[i].at(j));
				}
				else if (selectedCell->isBlank()) { //oyna
					play(m_cells[i].at(j));
				}
				else { // ittir
					push(m_cells[i].at(j));
				}
			}
		}
	}
}

void GameManager::resetGame() {
	// set all cells to blank
	for (int i = 0; i < m_rowCount; i++) {
		for (int j = 0; j < m_cells[i].size(); j++) {
			m_cells[i].at(j)->setTypeToBlank();
		}
	}

	// set the white balls
	for (int i = 0; i < 3; i++) {
		for (int j = i == 2 ? 2 : 0; j < (i == 2 ? 5 : m_cells[i].size()); j++) {
			m_cells[i].at(j)->setTypeToWhite();
		}
	}

	// set the black balls
	for (int i = m_rowCount - 3; i < m_rowCount; i++) {
		for (int j = i == 6 ? 2 : 0; j < (i == 6 ? 5 : m_cells[i].size()); j++) {
			m_cells[i].at(j)->setTypeToBlack();
		}
	}
}

Cell* GameManager::getNextCell(Cell* cell, int dx, int dy) {
	return getCell(cell->getKonum().getX() - dx, cell->getKonum().getY() - dy);
}

Cell* GameManager::getCell(int x, int y) {
	for (int i = 0; i < m_rowCount; i++) {
		for (int j = 0; j < m_cells[i].size(); j++) {
			if (m_cells[i].at(j)->getKonum().getX() == x
				&& m_cells[i].at(j)->getKonum().getY() == y) {
				return m_cells[i].at(j);
			}
		}
	}

	Cell* nullCell = new Cell(-1, -1);
	nullCell->setNull(true);
	return nullCell;
}

void GameManager::play(Cell* destination) {
	if (!canPlay(destination)) return;

	play(destination, m_cellList.getSelectedCells());

	m_cellList.clearList();

	m_whiteTurn = !m_whiteTurn;
}

void GameManager::push(Cell* destination) {
	if (!canPush(destination)) return;

	int dx = getDiffrenceX(m_cellList.getSelectedCell(0), m_cellList.getCellToPush(0));
	int dy = getDiffrenceY(m_cellList.getSelectedCell(0), m_cellList.getCellToPush(0));

	std::reverse(m_cellList.getCellsToPush().begin(), m_cellList.getCellsToPush().end());
	Cell* pushDestination = getNextCell(m_cellList.getCellToPush(0), dx, dy);
	play(pushDestination, m_cellList.getCellsToPush());

	play(destination);
}

void GameManager::play(Cell* destination, std::vector<Cell*> ittirilecekler) {

	int dx, dy;
	if (destination->isNull()) {
		if (ittirilecekler.size() == 1) {
			ittirilecekler.at(0)->resetCellToBlank();
			return;
		}
		dx = getDiffrenceX(ittirilecekler.at(1), ittirilecekler.at(0));
		dy = getDiffrenceY(ittirilecekler.at(1), ittirilecekler.at(0));
	}
	else {
		dx = getDiffrenceX(ittirilecekler.at(0), destination);
		dy = getDiffrenceY(ittirilecekler.at(0), destination);
	}

	for (int i = 0; i < ittirilecekler.size(); i++) {
		Cell* nextDest = getNextCell(ittirilecekler.at(i), dx, dy);

		if (!nextDest->isNull()) {
			play(ittirilecekler.at(i), nextDest);
		}
		else {
			ittirilecekler.at(i)->resetCellToBlank();
		}
	}
}

bool GameManager::canPush(Cell* destination) {
	// size 1 ise veya seçilenler diyagonal deðilse ittiremez
	if (m_cellList.size() < 2 || !isDiagonel()) return false;

	m_cellList.sort(m_cellList.getSelectedCells(), false);

	int dx = getDiffrenceX(m_cellList.getSelectedCell(0), destination);
	int dy = getDiffrenceY(m_cellList.getSelectedCell(0), destination);

	int cellsSlopeX =
		getDiffrenceX(m_cellList.getSelectedCell(1), m_cellList.getSelectedCell(0));
	int cellsSlopeY =
		getDiffrenceY(m_cellList.getSelectedCell(1), m_cellList.getSelectedCell(0));

	// ayný diyagonal üzerindeler mi
	if (dx != cellsSlopeX || dy != cellsSlopeY) return false;

	Cell* nextCell = getCell(destination->getKonum().getX(), destination->getKonum().getY());

	while (!nextCell->isNull() && !nextCell->isBlank()) {
		if (nextCell->typeEqual(m_cellList.getSelectedCell(0))) {
			return false;
		}
		m_cellList.addToCellsToPush(nextCell);
		nextCell = getNextCell(nextCell, dx, dy);
	}

	if (m_cellList.sizeCellsToPush() >= m_cellList.size()) {
		m_cellList.clearCellsToPush();
		return false;
	}
	return true;
}

float tan(int dx, int dy) {
	return (float)dx / (float)dy;
}

bool GameManager::isNecessaryReverse(Cell* destination) {
	if (m_cellList.size() < 2) return false;

	int dx = getDiffrenceX(m_cellList.getSelectedCell(0), destination);
	int dy = getDiffrenceY(m_cellList.getSelectedCell(0), destination);

	int cellsSlopeX =
		getDiffrenceX(m_cellList.getSelectedCell(1), m_cellList.getSelectedCell(0));
	int cellsSlopeY =
		getDiffrenceY(m_cellList.getSelectedCell(1), m_cellList.getSelectedCell(0));

	std::cout << "dx " << dx << " " << dy << std::endl;
	std::cout << "sx " << cellsSlopeX << " " << cellsSlopeY << std::endl;
	if ((dy == 0 && cellsSlopeY == 0) || tan(dx, dy) == tan(cellsSlopeX, cellsSlopeY)) {
		std::cout << "as" << std::endl;
		m_cellList.getSelectedCell(0)->greater(destination);
	}

	return m_cellList.getSelectedCell(1)->getKonum().getX() > destination->getKonum().getX();
}

bool GameManager::canPlay(Cell* destination) {
	if (m_cellList.isEmpty()) return false;

	m_cellList.sort(m_cellList.getSelectedCells(), isNecessaryReverse(destination));

	int dx = getDiffrenceX(m_cellList.getSelectedCell(0), destination);
	int dy = getDiffrenceY(m_cellList.getSelectedCell(0), destination);

	if (!isDistanceOneCell(m_cellList.getSelectedCell(0), destination)) return false;

	if (!isDiagonel()) return false;

	for (Cell* p : m_cellList.getSelectedCells()) {
		Cell* dest = getNextCell(p, dx, dy);
		if (dest->isNull() || !dest->isBlank() && !dest->isHareketEdecekMi()) {
			return false;
		}
	}
	return true;
}

void GameManager::play(Cell* source, Cell* dest) {
	source->setSelected(false);
	source->setHareketEdecekMi(false);
	dest->setType(source->getType());
	source->setTypeToBlank();
}

void GameManager::addToSelectedCells(Cell* cell) {
	m_cellList.add(cell);
}

bool GameManager::canSelect(Cell* cell) {
	return cell->getType() == (m_whiteTurn ? Cell::Ball_type::WHITE : Cell::Ball_type::BLACK);
}

bool compare(Cell* r, Cell* s) {
	if (s->getKonum().getY() == r->getKonum().getY()) {
		return s->getKonum().getX() > r->getKonum().getX();
	}
	return s->getKonum().getY() > r->getKonum().getY();
}

bool GameManager::isDiagonel() {
	std::vector<Cell*> temp = std::vector<Cell*>(m_cellList.getSelectedCells().begin(),
		m_cellList.getSelectedCells().end());
	std::sort(temp.begin(), temp.end(), compare);

	if (m_cellList.size() > 1) {
		if (!isDistanceOneCell(temp.at(1), temp.at(0))) return false;

		int slopeX = getDiffrenceX(temp.at(1), temp.at(0));
		int slopeY = getDiffrenceY(temp.at(1), temp.at(0));

		for (int i = 0; i < temp.size() - 1; i++) {
			if (getDiffrenceX(temp.at(i + 1), temp.at(i)) != slopeX
				|| getDiffrenceY(temp.at(i + 1), temp.at(i)) != slopeY)
				return false;
		}
	}
	return true;
}

int GameManager::getDiffrenceX(Cell* source, Cell* dest) {
	return source->getKonum().getX() - dest->getKonum().getX();
}

int GameManager::getDiffrenceY(Cell* source, Cell* dest) {
	return source->getKonum().getY() - dest->getKonum().getY();
}

bool GameManager::isDistanceOneCell(Cell* source, Cell* destination) {
	int dx = getDiffrenceX(source, destination);
	int dy = getDiffrenceY(source, destination);
	std::cout << source->getKonum() - destination->getKonum() << std::endl;
	if (abs(dx) > CELL_SIZE || abs(dy) > CELL_SIZE) return false;
	return true;
}