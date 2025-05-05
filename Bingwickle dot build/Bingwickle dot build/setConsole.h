#pragma once

#include <windows.h>
#include <string>

using namespace std;

// window size seems to be more consitent at a resolution 
// of 1366 x 768 - default is 1920 x 1080


// we are able to pick between 16 colours to text or background
enum concol
{
	black = 0,
	dark_blue = 1,
	dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};

// hides cursor in window
void hideTheCursor();

// show the cursor in window
void showTheCursor();

// copies a STRING to user clipboard
void toClipboard(const std::string& s);

// setting colour
void setcolor(concol textcol, concol backcol);

// disable mouse highlighting on console
void disableMouseHighlighting();

// Maximize button disabled
void disableMaximize();

// setting the window size
void setWindowSize();

// setting the window title
void setWindowTitle();

// remove scrollbar
void removeScrollBar();

// setting the window size
void setWindowSize320x420();

// setting the window size
void setWindowSize620x920();

// snap animation
void playSnapAnimation();