#include "cell.h"
#include <cstddef>
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "state.h"
#include <iostream>
using namespace std;

Cell::Cell(size_t r, size_t c): r{r}, c{c}, colour{Colour::NoColour} {} // ctor

void Cell::setPiece(Colour colour) {
	this->colour = colour;
	setState({StateType::NewPiece, colour}); // dont need dir for new piece
       	// if a piece is made it needs a newPiece type and Colour colour
}

void Cell::toggle() { 
	if (colour == Colour::NoColour) { // no colour so does nothing
		return;
	} else if ( colour == Colour::White) { //switch from white to black
		colour = Colour::Black;
	} else { // switch from black to white
		colour = Colour::White;
	}
}

void Cell::notify(Subject<Info, State> &whoFrom) {
	State stemp = whoFrom.getState();
	Info itemp = whoFrom.getInfo();
	Direction d;

	// determine which direction the notify came from
	if (r == itemp.row -1) {
		if (c == itemp.col -1) {
			d = Direction::SE;
		} else if (c == itemp.col) {
			d = Direction::S;
		} else if (c == itemp.col + 1) {
			d = Direction::SW;
		}
	} else if ( r == itemp.row) {
		if (c == itemp.col -1) {
			d = Direction::E;
		} else if ( c == itemp.col +1) {
			d = Direction::W;
		}
	} else if ( r == itemp.row +1) {
		if (c == itemp.col -1) {
			d = Direction::NE;
		} else if (c == itemp.col) {
			d = Direction::N;
		} else if (c == itemp.col +1) {
			d = Direction::NW;
		}
	}
	// determine the type of the piece who notified
	//
	if (stemp.type == StateType::NewPiece) {
		if ((colour != stemp.colour) && (colour != Colour::NoColour)) {
			setState({StateType::Relay, stemp.colour, d}); // make a relay
		} else { return; }

	} else if (stemp.type == StateType::Relay) {
		if ((colour != stemp.colour) && (colour != Colour::NoColour)) {
			if (d == stemp.direction) {
				setState({StateType::Relay, stemp.colour, d}); 
			} else { return; }
		} else if (colour == stemp.colour) {
			if (d == stemp.direction) {
				setState({StateType::Reply, stemp.colour, d});
			} else {
			       	return;
		       	}
		} else { return; }

	} else if (stemp.type == StateType::Reply) { // if you are a relay toggle
		if (getState().type == StateType::Relay) {
			if (getState().direction == stemp.direction) { 
				if (getState().colour == stemp.colour) {
					toggle();
					setState({StateType::Reply, stemp.colour, 
							stemp.direction});
				} else { return; }
			} else { return; }
		} else { return; }
	}
	notifyObservers();
}

Info Cell::getInfo() const {
	Info i;
	i.row = r; // set row
	i.col = c; // set column
	i.colour = colour; // set colour
	return i;
}
