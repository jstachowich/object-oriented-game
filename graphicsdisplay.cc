#include "graphicsdisplay.h"
#include "window.h"
#include "grid.h"
#include "subject.h"
#include "info.h"
#include "state.h"
#include "cell.h"
#include <vector>
#include <iostream>
using namespace std;

// buildling the default window with the middle black white initialized 
// and all the other cells are set to be blue
GraphicsDisplay::GraphicsDisplay(int n): gridSize{n}, cellSize{500/n} {

	int c;

	for (int row = 0; row < gridSize; row += 1) {
		for (int col = 0; col < gridSize; col += 1) {
			if ((row == (gridSize/2) -1) && (col == (gridSize/2)-1)) {
				c = Xwindow::Black;
			} else if ((row == (gridSize/2)-1) && (col == gridSize/2)) {
				c = Xwindow::White;
			} else if ((row == gridSize/2) && (col == (gridSize/2)-1)) {
				c = Xwindow::White;
			} else if ((row == gridSize/2) && (col == gridSize/2)) {
				c = Xwindow::Black;
			} else {
				c = Xwindow::Blue;
			}
			w.fillRectangle(col * cellSize, row * cellSize,
					cellSize, cellSize, c);
		}
	}
}

void GraphicsDisplay::fill(int row, int col, int colour) {
	w.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, colour);
}

void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {
	Info itemp = whoNotified.getInfo();
	if (itemp.colour == Colour::Black) {
		fill(itemp.row, itemp.col, Xwindow::Black);
	} else if (itemp.colour == Colour::White) {
		fill(itemp.row, itemp.col, Xwindow::White);
	} else {
		// blue so do nothing
	}
}




