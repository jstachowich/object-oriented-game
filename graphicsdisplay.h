#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "window.h"

class GraphicsDisplay : public Observer<Info, State> {
	Xwindow w;
	const int gridSize;
	const int cellSize;
	public:
	GraphicsDisplay(int n); // should make an xwindow


	void fill(int row, int col, int colour);
	void notify(Subject<Info, State> &whoNotified) override;
};
#endif
