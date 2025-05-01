#pragma once

// This is a declaration of your variable, which tells the linker this value
// is found elsewhere.  Anyone who wishes to use it must include global.h,
// either directly or indirectly.

//std::this_thread::sleep_for(chrono::seconds(2)); (using std::)

#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)	// for adding colours to text

#define KEY_UP 72		// Key defines & codes
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_F12 0x7B //123
#define KEY_MOUSERIGHT 201
#define KEY_MOUSE 200
#define KEY_ALT_ENTER 10
#define KEY_SHIFT  16
#define KEY_DOT 056 // Keyboard . and >