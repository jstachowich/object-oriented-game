#include "textdisplay.h"
#include <iostream>
#include <vector>
#include "cell.h"
#include "info.h"
#include "observer.h"
#include "state.h"
#include "grid.h"
#include "subject.h"
using namespace std;

// building the display like gridinit but using character vectors instead
TextDisplay::TextDisplay(int n): gridSize{n} { //ctor build like grid.cc
	for (int row = 0; row < n; row += 1) {
		vector<char> newrow;
		for (int col = 0; col < n; col += 1) {
			if (row == (n/2) - 1) {
				if (col == (n/2) -1) {
					newrow.emplace_back('B');
				} else if (col == (n/2)) {
					newrow.emplace_back('W');
				} else {
					newrow.emplace_back('-');
				}
			} else if (row == (n/2)) {
				if (col == (n/2) - 1) {
					newrow.emplace_back('W');
				} else if (col == (n/2)) {
					newrow.emplace_back('B');
				} else {
					newrow.emplace_back('-');
				}
			} else {
				newrow.emplace_back('-');
			}
		}
		theDisplay.emplace_back(newrow);
	}
}

// just needs to check the colour of the cell who called it and change its colour
// notifying the other cells is done within grid
void TextDisplay::notify(Subject<Info, State> &whoNotified) {
	Info itemp = whoNotified.getInfo();
	if (itemp.colour == Colour::Black) {
		theDisplay[itemp.row][itemp.col] = 'B';
	} else if (itemp.colour == Colour::White) {
		theDisplay[itemp.row][itemp.col] = 'W';
	} else {
		theDisplay[itemp.row][itemp.col] = '-';
	}

}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for (auto row: td.theDisplay) {
		for( auto ncell : row) {
			out << ncell;
		}
		out << endl;
	}
	return out;
}
