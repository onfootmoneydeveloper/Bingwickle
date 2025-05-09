#include <iostream>
#include <windows.h>
#include <thread>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>	
#include <chrono>

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

	while (true) {

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

			// change output to input space (inputPos.Y - (digit) - line)
			COORD logPos = { 0, static_cast<SHORT>(inputPos.Y - 2 - line) };
			SetConsoleCursorPosition(hConsole, logPos);
			std::cout << *it;
			++line;
		}

		// set new console position before getting input
		SetConsoleCursorPosition(hConsole, inputPos);
		std::cout << "    Users\\" << globalUsername << ">  ";
		std::cin >> input;

		// check if DONE command was used
		if (input == "done") {
			hideTheCursor();
			gameActive = false;
			isMainMenuActive = true;
			break;
		}

		else if (input == "stats") {
			playRiseAndSlamAnimationROAM();
			loadTicketCountsFromFile();
			outputLog.push_back("   daily = " + std::to_string(dailyTicketCount) + ", total = " + std::to_string(totalTicketCount));
		}

		else if (input == "merge") {

			// no anim
			mergeDailyIntoTotal();
			outputLog.push_back("   Merged stats.");
		
		}

		// gets/checks the length of string if its not a command
		else if (input.length() == 7 && std::all_of(input.begin(), input.end(), ::isdigit)) {

			try {
				saveTicket();
				number = std::stoi(input);

				if (isDuplicate == true) {
					setcolor(red, black);
					outputLog.push_back("   Duplicate.");
					setcolor(white, black);
					isDuplicate = false;
				}

				else {
					outputLog.push_back("   Saved ticket: " + input);
					saveDailyTicketPoint();
				}
			}
			catch (std::exception&) {
				outputLog.push_back("Weird... try again?");
			}
		}

		else {
			outputLog.push_back("   Invalid reference!");
		}
	}

	// load back to MM
	system("cls");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	if (soundOn == true) {
		playSong0();
	}

}



