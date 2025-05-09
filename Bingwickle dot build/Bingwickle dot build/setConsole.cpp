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

// setting window size (CURRENTLY USED)
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

// snap animation 
void playSnapAnimation() {

	HWND console = GetConsoleWindow();
	HWND consoleWindow = GetConsoleWindow(); // same as above, could just use one
	RECT screen;
	GetWindowRect(GetDesktopWindow(), &screen); // get screen size

	const int windowWidth = 320;
	const int windowHeight = 410;

	// Final centered position
	int centerX = (screen.right - windowWidth) / 2;
	int centerY = (screen.bottom - windowHeight) / 2;

	// Shake: oscillate side-to-side around centerX
	const int shakeDistance = 10;
	const int shakeCount = 6;
	const int shakeDelayMs = 30;

	for (int i = 0; i < shakeCount; ++i) {
		int offset = (i % 2 == 0) ? -shakeDistance : shakeDistance;
		MoveWindow(console, centerX + offset, centerY, windowWidth, windowHeight, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(shakeDelayMs));
	}

	// Snap to center
	MoveWindow(console, centerX, centerY, windowWidth, windowHeight, TRUE);

	// Lock window resizing
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	// Optional: flash background (blink effect)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to normal

}

// snap animation ROAM
void playSnapAnimationROAM() {
	HWND console = GetConsoleWindow();
	HWND consoleWindow = GetConsoleWindow();
	RECT currentPos;
	GetWindowRect(console, &currentPos); // Get current window position

	const int windowWidth = 320;
	const int windowHeight = 410;

	// Current top-left position
	int startX = currentPos.left;
	int startY = currentPos.top;

	// Shake settings
	const int shakeDistance = 10;
	const int shakeCount = 6;
	const int shakeDelayMs = 30;

	// Shake side to side around current position
	for (int i = 0; i < shakeCount; ++i) {
		int offset = (i % 2 == 0) ? -shakeDistance : shakeDistance;
		MoveWindow(console, startX + offset, startY, windowWidth, windowHeight, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(shakeDelayMs));
	}

	// Snap back to current position (not center)
	MoveWindow(console, startX, startY, windowWidth, windowHeight, TRUE);

	// Lock window resizing
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	// Optional: blink background
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset color

}

// play slam animation ROAM
void playRiseAndSlamAnimationROAM() {
	HWND console = GetConsoleWindow();
	RECT currentRect;
	GetWindowRect(console, &currentRect);

	const int windowWidth = 320;
	const int windowHeight = 410;

	// Get current top-left position of the window
	int startX = currentRect.left;
	int startY = currentRect.top;

	// RISE UP - smooth rise in small steps
	const int riseAmount = 30;
	const int riseSteps = 10;
	const int riseDelay = 25;

	for (int i = 0; i < riseSteps; ++i) {
		int newY = startY - (riseAmount * (i + 1)) / riseSteps;
		MoveWindow(console, startX, newY, windowWidth, windowHeight, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(riseDelay));
	}

	// SHORT PAUSE AT PEAK
	std::this_thread::sleep_for(std::chrono::milliseconds(80));

	// SLAM DOWN - fast drop back to original position
	const int slamSteps = 4;
	for (int i = slamSteps; i >= 0; --i) {
		int newY = startY - (riseAmount * i) / slamSteps;
		MoveWindow(console, startX, newY, windowWidth, windowHeight, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}

	// LITTLE SHOCK SHAKE ON IMPACT
	const int shakeOffset = 5;
	for (int i = 0; i < 4; ++i) {
		int offset = (i % 2 == 0) ? shakeOffset : -shakeOffset;
		MoveWindow(console, startX + offset, startY, windowWidth, windowHeight, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	// Final snap to original position
	MoveWindow(console, startX, startY, windowWidth, windowHeight, TRUE);
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

// play slam animtion
void playRiseAndSlamAnimation() {
	HWND console = GetConsoleWindow();
	RECT screen;
	GetWindowRect(GetDesktopWindow(), &screen);

	const int windowWidth = 320;
	const int windowHeight = 410;

	int centerX = (screen.right - windowWidth) / 2;
	int centerY = (screen.bottom - windowHeight) / 2;

	// RISE UP - smooth rise in small steps
	const int riseAmount = 30;
	const int riseSteps = 10;
	const int riseDelay = 25;

	for (int i = 0; i < riseSteps; ++i) {
		int newY = centerY - (riseAmount * (i + 1)) / riseSteps;
		MoveWindow(console, centerX, newY, windowWidth, windowHeight, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(riseDelay));
	}

	// SHORT PAUSE AT PEAK
	std::this_thread::sleep_for(std::chrono::milliseconds(80));

	// SLAM DOWN - fast drop back to center
	const int slamSteps = 4;
	for (int i = slamSteps; i >= 0; --i) {
		int newY = centerY - (riseAmount * i) / slamSteps;
		MoveWindow(console, centerX, newY, windowWidth, windowHeight, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}

	// LITTLE SHOCK SHAKE ON IMPACT
	const int shakeOffset = 5;
	for (int i = 0; i < 4; ++i) {
		int offset = (i % 2 == 0) ? shakeOffset : -shakeOffset;
		MoveWindow(console, centerX + offset, centerY, windowWidth, windowHeight, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	// Final snap to center
	MoveWindow(console, centerX, centerY, windowWidth, windowHeight, TRUE);
}
