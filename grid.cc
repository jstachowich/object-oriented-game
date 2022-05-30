#include "grid.h"
#include "cell.h"
#include "state.h"
#include "info.h"
#include "textdisplay.h"
#include "subject.h"
#include "observer.h"
#include "graphicsdisplay.h"
#include <vector>
#include <iostream>
#include <cstddef> 
using namespace std;

Grid::~Grid() {
	killGrid();
}

void Grid::killGrid() { // clear a grid
	delete w;
	for  ( auto row: theGrid) {
		row.clear();
	}
	theGrid.clear();
}

void Grid::setObserver(Observer<Info, State> *ob) {

	
}

// checks if one of the cells has no colour => can't be full
bool Grid::isFull() const {
	for (auto row : theGrid) {
		for (auto ncell : row) {
			if (ncell.getInfo().colour == Colour::NoColour) {
				return 0;
			}
		}
	}
	return 1;
}

// only called if grid is full;
Colour Grid::whoWon() const {
	int cblack = 0; // counters
	int cwhite = 0; 
	for (auto row : theGrid) {
		for (auto ncell : row) {
			if (ncell.getInfo().colour == Colour::White) {
				cwhite += 1;
			} else if (ncell.getInfo().colour == Colour::Black) {
				cblack += 1;
			}
		}
	}
	if (cblack > cwhite) {
		return Colour::Black;
	} else if (cwhite > cblack) {
		return Colour::White;
	} else { // return no colour in the case of a tie
		return Colour::NoColour;
	}
}

void Grid::init(size_t n) {
	if (n < 4 || ( n % 2 ) != 0) {
		return;
	}
	killGrid();
	gSize = n;
	for (unsigned int row = 0; row < n; row += 1) {
		vector<Cell> newrow;
		for (unsigned int col = 0; col < n; col += 1) {
			Cell ncell{row, col};
			newrow.emplace_back(ncell);
		}
		theGrid.emplace_back(newrow);
	}
	// set the middle 4 positions to black white
	theGrid[(gSize/2)-1][(gSize/2)-1].setPiece(Colour::Black);
	theGrid[(gSize/2)-1][(gSize/2)].setPiece(Colour::White);
	theGrid[(gSize/2)][(gSize/2)-1].setPiece(Colour::White);
	theGrid[(gSize/2)][(gSize/2)].setPiece(Colour::Black);

	// build the list of observers on each cell
	
	for (int row = 0; row < gSize; row += 1) {
		for (int col = 0; col < gSize; col += 1) {
			if ((row != 0) && (col != 0)) { 
				Cell *obs = &theGrid[row-1][col-1];
				theGrid[row][col].attach(obs); 
			} if (row != 0) {
				Cell *obs2 = &theGrid[row-1][col]; 
				theGrid[row][col].attach(obs2);
			} if ((row != 0) && (col != gSize-1)) {
				Cell *obs3 = &theGrid[row-1][col+1];
				theGrid[row][col].attach(obs3);
			} if (col != 0) {
				Cell *obs4 = &theGrid[row][col-1];
				theGrid[row][col].attach(obs4);
			} if (col != gSize-1) {
				Cell *obs5 = &theGrid[row][col+1];
				theGrid[row][col].attach(obs5);
			} if ((row != gSize-1) && (col != 0)) {
				Cell *obs6 = &theGrid[row+1][col-1];
				theGrid[row][col].attach(obs6);
			} if (row != gSize-1) {
				Cell *obs7 = &theGrid[row+1][col];
				theGrid[row][col].attach(obs7);
			} if ((row != gSize-1) && (col != gSize-1)) {
				Cell *obs8 = &theGrid[row+1][col+1];
				theGrid[row][col].attach(obs8);
			}
		}
	}
	// initialize the text display
	w = new GraphicsDisplay{gSize};
}

// the grid is a vector of vectors, first call row then column
void Grid::setPiece(size_t r, size_t c, Colour colour) {
	unsigned int temp = gSize;
	if (r < temp && c < temp && theGrid[r][c].getInfo().colour == Colour::NoColour) {
		theGrid[r][c].setPiece(colour);
		theGrid[r][c].notifyObservers();
		for (int i = 0; i < gSize; i += 1) {
			for (int j = 0; j < gSize; j += 1) {
				w->notify(theGrid[i][j]);
			}
		}
	} else {
		throw InvalidMove{};
	}
}
// toggle a colour from the grid (note unused in this code since setpiece can act the 
// same way
void Grid::toggle(size_t r, size_t c) {
	theGrid[r][c].toggle();
}

// calling output
ostream &operator<<(ostream &out, const Grid &g) {
	out << *(g.td);
	return out;
}

