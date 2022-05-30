#include <iostream>
#include <string>
#include "grid.h"
#include "state.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std;


int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  int turn = 0; // 0 black 1 white

  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      g.init(n);
      turn = 0;
      //display
      //cout << g;
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      if (turn == 0) {
	      try {
      		g.setPiece(r,c,Colour::Black);
	//	cout << g;
		turn += 1;
	      }
	      catch (InvalidMove) {} // does nothing if invalid
      } else if (turn == 1) {
	      try {
	      g.setPiece(r,c,Colour::White);
	 //     cout << g;
	      turn -= 1;
	      }
	      catch (InvalidMove) {} // does nothing if invalid
      }
      if (g.isFull() == 1) { // checks if game is over after each play
	      Colour winner = g.whoWon();
	      if (winner == Colour::Black) {
		      cout << "Black wins!" << endl;
	      } else if (winner == Colour::White) {
		      cout << "White wins!" << endl;
	      } else {
		      cout << "Tie!" << endl;
	      }
	      break;
      }
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
