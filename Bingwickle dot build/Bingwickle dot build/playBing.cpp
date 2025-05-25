#include <iostream>
#include <windows.h>
#include <thread>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>	
#include <chrono>
#include <format>      // For C++20 std::format 

#include <ctime>

#include "setConsole.h"
#include "globals.h"
#include "audio.h"
#include "mainMenu.h"
#include "commandLPrmpt.h"

#pragma region
// when yo hit play - GET all stats, display stats
// current stats: 

/*

	currentEXP
	currentLVL
	dailyTicketCount
	expRemaining
	loginCount
	ticketCount

	shave down to:

	total EXP						the total amount of experience points you have
	current Level					your current level based on your experience
	daily Ticket count				how many tickets you have logged in a day
	logInCount						how many times you have logged in ( ++ at file set up)
	totalTicketCount				how many tickets you have done OVERALL

	ticketCount_date_here			e.g ticketCount_29_04_2025 <-- will create new files each day,
									so if you log on the day after, Bingwickle will create
									ticketCount_30_04_2025. The file will hold the list of "references"
									that you have actioned or completed, like this:

									1938394
									1937835
									1955...

									Duplicates will be ignored with a messaged (ticket already been actioned)

*/
#pragma endregion SETUP

int number;
std::string input;


bool isDuplicate = false;

int dailyTicketCount = 0;
int totalTicketCount = 0;



namespace fs = std::filesystem;

void printAtPosition(int x, int y, const std::string& text) {

	COORD coord;
	coord.X = x;
	coord.Y = y;

	// Get handle to the console output
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);

	std::cout << text;
}

void playTestToExit() {
	exit(0);
}

void saveTicket() {

	// Get current date in YYYY-MM-DD format

	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm local_tm;
	localtime_s(&local_tm, &t);

	char dateBuffer[11];
	std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", &local_tm);
	std::string currentDate(dateBuffer);

	// Construct file path
	std::string baseDir = "C:\\Bingwickle\\Users\\" + globalUsername + "\\tickets\\";
	std::string fileName = "ticket_list_" + currentDate + ".txt";
	std::string fullPath = baseDir + fileName;

	// Create directory if it doesn't exist
	std::filesystem::create_directories(baseDir);

	// Read existing contents
	std::ifstream inFile(fullPath);
	std::string line;
	std::vector<std::string> lines;

	//bool isDuplicate = false;

	while (std::getline(inFile, line)) {
		if (line == input) {
			isDuplicate = true;
			break;
		}
		lines.push_back(line);
	}
	inFile.close();

	if (isDuplicate) {
		setcolor(red, black);
		std::cout << "               Duplicate ticket." << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(800));
		setcolor(white, black);
		return;
	}

	// Insert new ticket at the top
	lines.insert(lines.begin(), input);

	// Write back to file
	std::ofstream outFile(fullPath, std::ios::trunc);
	for (const auto& l : lines) {
		outFile << l << "\n";
	}
	outFile.close();

	setcolor(yellow, black);


	// only play ticket sound if global sound is ON
	if (soundOn == true) {
		playTicketSound();
	}
	
	std::cout << "              +1 Ticket!" << "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	playSnapAnimationROAM();
	setcolor(white, black);
}

void saveDailyTicketPoint() {

	namespace fs = std::filesystem;

	fs::path directoryPath = "C:\\Bingwickle\\Users\\" + globalUsername + "\\v1";
	fs::path filePath = directoryPath / "dailyTicketCount.txt";

	// Ensure directory exists
	if (!fs::exists(directoryPath)) {
		try {
			fs::create_directories(directoryPath);
		}
		catch (const fs::filesystem_error& e) {
			std::cerr << "Error creating directory: " << e.what() << std::endl;
			return;
		}
	}

	// Read current value if file exists
	if (fs::exists(filePath)) {
		std::ifstream inFile(filePath);
		if (inFile >> dailyTicketCount) {
			// Read successful
		}
		else {
			dailyTicketCount = 0; // Reset if unreadable
		}
		inFile.close();
	}
	else {
		dailyTicketCount = 0; // No file yet
	}

	// Increment and write back
	dailyTicketCount++;

	std::ofstream outFile(filePath);
	if (outFile) {
		outFile << dailyTicketCount;
		outFile.close();
	}
	else {
		std::cerr << "Failed to write daily ticket count." << std::endl;
	}
}

void loadTicketCountsFromFile() {

	namespace fs = std::filesystem;
	fs::path dirPath = "C:\\Bingwickle\\Users\\" + globalUsername + "\\v1";

	fs::path dailyFile = dirPath / "dailyTicketCount.txt";
	fs::path totalFile = dirPath / "totalTicketCount.txt";

	// Read daily ticket count
	if (fs::exists(dailyFile)) {
		std::ifstream inFile(dailyFile);
		if (inFile >> dailyTicketCount) {
			// Success
		}
		else {
			dailyTicketCount = 0; // fallback
		}
		inFile.close();
	}

	// Read total ticket count
	if (fs::exists(totalFile)) {
		std::ifstream inFile(totalFile);
		if (inFile >> totalTicketCount) {
			// Success
		}
		else {
			totalTicketCount = 0; // fallback
		}
		inFile.close();
	}
}

void mergeDailyIntoTotal() {

	namespace fs = std::filesystem;
	fs::path dirPath = "C:\\Bingwickle\\Users\\" + globalUsername + "\\v1";

	fs::path dailyFile = dirPath / "dailyTicketCount.txt";
	fs::path totalFile = dirPath / "totalTicketCount.txt";

	// Load both values from file (safely)
	int daily = 0, total = 0;

	if (fs::exists(dailyFile)) {
		std::ifstream inFile(dailyFile);
		inFile >> daily;
		inFile.close();
	}

	if (fs::exists(totalFile)) {
		std::ifstream inFile(totalFile);
		inFile >> total;
		inFile.close();
	}

	// Merge and update values
	total += daily;
	daily = 0;

	// Save updated total
	std::ofstream outTotal(totalFile);
	if (outTotal) {
		outTotal << total;
		outTotal.close();
	}
	else {
		std::cerr << "Failed to write totalTicketCount.txt" << std::endl;
	}

	// Reset daily
	std::ofstream outDaily(dailyFile);
	if (outDaily) {
		outDaily << daily;
		outDaily.close();
	}
	else {
		std::cerr << "Failed to write dailyTicketCount.txt" << std::endl;
	}

	// Optional: update global variables too
	dailyTicketCount = 0;
	totalTicketCount = total;
}

// loading screen
void bouncingDot(int row, int startCol, int endCol, int durationMs = 2000, int delayMs = 100) {

	int steps = durationMs / delayMs;
	bool forward = true;
	int pos = startCol;

	system("cls");

	for (int i = 0; i < steps; ++i) {
		std::cout << "\033[" << row << ";" << pos << "H" << "." << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
		std::cout << "\033[" << row << ";" << pos << "H" << " " << std::flush; // erase dot

		if (forward) {
			if (pos < endCol) pos++;
			else {
				pos--;
				forward = false;
			}
		}
		else {
			if (pos > startCol) pos--;
			else {
				pos++;
				forward = true;
			}
		}
	}
}

// merge function animation
void slapConsoleWindowAnimation(int impact = 30, int wobble = 6, int wobbleTimes = 6, int delayMs = 20) {
	HWND hwnd = GetConsoleWindow();
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int originalX = rect.left;
	int originalY = rect.top;

	// Step 1: Sudden slap to the right
	SetWindowPos(hwnd, nullptr, originalX + impact, originalY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	std::this_thread::sleep_for(std::chrono::milliseconds(30));

	// Step 2: Wobble back and forth like recoil
	for (int i = 0; i < wobbleTimes; ++i) {
		int offset = (i % 2 == 0 ? -wobble : wobble);
		SetWindowPos(hwnd, nullptr, originalX + offset, originalY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
	}

	// Step 3: Settle back to original position
	SetWindowPos(hwnd, nullptr, originalX, originalY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}




void play() {

	system("cls");
	std::this_thread::sleep_for(std::chrono::seconds(1));

	if (!cursorOff) {

		showTheCursor();
	}

	std::vector<std::string> outputLog;

	const int maxLines = 15;

	const SHORT inputY = 19; // <-- adjust this to move everything up or down

	COORD inputPos = { 3, inputY };

	bool displayCommandList = true;

	outputLog.push_back("    Cmds: stats, merge, exit");
	//outputLog.push_back("    Cmds: copy, clear. ");
	outputLog.push_back("  ");
	

	while (true) {

		setcolor(dark_white, black);

		// Clear previous lines
		for (int i = 0; i <= maxLines; ++i) {
			COORD clearPos = { 0, static_cast<SHORT>(inputPos.Y - i) };
			SetConsoleCursorPosition(hConsole, clearPos);
			std::cout << std::string(80, ' ');
		}
	

		// tracks output log and removing the oldest when MAX
		if (outputLog.size() > maxLines) {
			outputLog.erase(outputLog.begin());
		}

		int line = 0;

		// renders latest message starting from most recent - prints each one by one
		for (auto it = outputLog.rbegin(); it != outputLog.rend(); ++it) {
			if (line >= maxLines) break;

			COORD logPos = { 0, static_cast<SHORT>(inputPos.Y - 2 - line) };
			SetConsoleCursorPosition(hConsole, logPos);

			// Always print 80 characters, even if message is shorter
			std::cout << std::left << std::setw(30) << *it;

			++line;
		}

		// set new console position before getting input
		SetConsoleCursorPosition(hConsole, inputPos);
		std::cout << "    Users\\" << globalUsername << ">  ";
		std::cin >> input;

		// check if DONE command was used
		if (input == "exit") {
			hideTheCursor();
			gameActive = false;
			isMainMenuActive = true;
			break;
		}

		else if (input == "stats") {
			hideTheCursor();
			playRiseAndSlamAnimationROAM();
			loadTicketCountsFromFile();

			if (soundOn == true) {
				playStatsSound();
			}

			outputLog.push_back("    daily = " + std::to_string(dailyTicketCount) + ", total = " + std::to_string(totalTicketCount));
		}

		else if (input == "merge") {

			if (dailyTicketCount == 0) { // there is nothing to merge

				hideTheCursor();

				if (soundOn == true) {
					playBadInputSound();
				}

				outputLog.push_back("    There's no need to merge.");
			
			}

			else { // we have a ticket to merge

				hideTheCursor();
				mergeDailyIntoTotal();
				slapConsoleWindowAnimation();

				if (soundOn == true) {
					playMergeSound();
				}

				outputLog.push_back("    Merged stats.");
			
			}
		
		}

		// gets/checks the length of string if its not a command
		else if (input.length() == 7 && std::all_of(input.begin(), input.end(), ::isdigit)) {

			hideTheCursor(); // now the cursor will hide if it peaks by accident

			try {
				saveTicket();
				number = std::stoi(input);

				if (isDuplicate == true) {
					setcolor(red, black);

					if (soundOn == true) {
						playBadInputSound();
					}

					outputLog.push_back("    Duplicate.");
					setcolor(white, black);
					isDuplicate = false;
				}

				else {
					outputLog.push_back("    Saved ticket: " + input);
					saveDailyTicketPoint();
				}
			}
			catch (std::exception&) {
				outputLog.push_back("Weird... try again?");
			}
		}

		else {


			if (soundOn == true) {
				playBadInputSound();
			}

			outputLog.push_back("    Invalid reference!");
		}
	}

	// load back to MM
	system("cls");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	if (soundOn == true) {
		playThemeSong();
	}

}



