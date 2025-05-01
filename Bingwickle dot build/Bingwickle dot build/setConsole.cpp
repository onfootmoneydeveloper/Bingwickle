#pragma once

#include "setConsole.h"
#include "Defs.h"
#include "globals.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>

// Hides User Cursor **note, the order where you call this matters.
// call after setting up console window

// hides cursor in window
void hideTheCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

// show cursor in window
void showTheCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

// copies a STRING to user clipboard
void toClipboard(const std::string& s) {

	OpenClipboard(0);
	EmptyClipboard();

	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}

	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

// setting colour
void setcolor(concol textcol, concol backcol)
{
	// we set the colour here
	int textColour = (int)textcol;
	int backColour = (int)backcol;
	textColour = textColour % 16;
	backColour = backColour % 16;
	unsigned short wAttributes = ((unsigned)backColour << 4) | (unsigned)textColour;
	SetConsoleTextAttribute(std_con_out, wAttributes);
}

// Maximize button disabled
void disableMaximize() {

	// https://stackoverflow.com/questions/46145256/disable-maximize-button-c-console-application

	HWND hwnd = GetConsoleWindow();
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	SetWindowLong(hwnd, GWL_STYLE, style);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

// unable to highlight text in application
void disableMouseHighlighting() {
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS |
		(prev_mode & ~ENABLE_QUICK_EDIT_MODE));
}

// setting window size
void setWindowSize() {

	HWND console = GetConsoleWindow();
	HWND consoleWindow = GetConsoleWindow(); // for locking the console
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);

				// hWnd, x, y, nWidth, nHeight, bool
	MoveWindow(console, 500, 200, 320, 410, TRUE);

	// lock console window to size
	SetWindowLong(consoleWindow, GWL_STYLE, 
		GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

}

// set window title
void setWindowTitle() {

	SetConsoleTitle(L"Bingwickle v1.0");
}
	
// remove scroll bar
void removeScrollBar() {

	// removing scrollbar
	try {

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(console, &csbi);
		COORD scrollbar = {
			csbi.srWindow.Right - csbi.srWindow.Left + 1,
			csbi.srWindow.Bottom - csbi.srWindow.Top + 1
		};

		if (console == 0) {
			throw 0;
		}
		else {
			SetConsoleScreenBufferSize(console, scrollbar);
		}
	}
	catch (...) {
		std::cerr << "Error removing scrollbar" << endl;
	}

	// allows for input

	/*std::cin.sync(),
		std::cin.ignore(
			std::numeric_limits
			<std::streamsize>::max()
		); */
}

// setting window size
void setWindowSize320x420() {

	HWND console = GetConsoleWindow();
	HWND consoleWindow = GetConsoleWindow(); // for locking the console
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);

	// hWnd, x, y, nWidth, nHeight, bool
	MoveWindow(console, 500, 200, 320, 410, TRUE);

	// lock console window to size
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

}

// setting window size
void setWindowSize620x920() {

	HWND console = GetConsoleWindow();
	HWND consoleWindow = GetConsoleWindow(); // for locking the console
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);

	// hWnd, x, y, nWidth, nHeight, bool
	MoveWindow(console, 500, 200, 620, 910, TRUE);

	// lock console window to size
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

}