#include <iostream>
#include <windows.h>
#include <thread>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>	
#include <chrono>
#include <ctime>

// calling headers
#include "setConsole.h"
#include "globals.h"
#include "audio.h"
#include "mainMenu.h"
#include "commandLPrmpt.h"

int number;
std::string input;

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
	bool isDuplicate = false;

	while (std::getline(inFile, line)) {
		if (line == input) {
			isDuplicate = true;
			break;
		}
		lines.push_back(line);
	}
	inFile.close();

	if (isDuplicate) {
		std::cout << "Duplicate ticket: #" << input << "\n";
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

	std::cout << "Ticket " << input << " was saved.\n";
}

void play() {
	system("cls");
	std::this_thread::sleep_for(std::chrono::seconds(1));


	std::cout << "\n\n\n\n";
	COORD pos = { 3, 20 };
	SetConsoleCursorPosition(hConsole, pos);

	std::cout << "   Reference:\n";

	while (true) {
		std::cout << "> ";
		std::cin >> input;

		if (input == "done") {
			gameActive = false;			// not in-game
			isMainMenuActive = true;	// switch on menu
			break;
		}
		
		if (input.length() == 7 && std::all_of(input.begin(), input.end(), ::isdigit)) {
			try {
				number = std::stoi(input);
				std::cout << "saved!: " << number << std::endl;

				saveTicket();
				// Do something with 'number' here
			}
			catch (std::exception&) {
				std::cout << "Weird...try again?\n";
			}
		}
		else {
			std::cout << "Invalid reference.\n";
		}
	}

	std::cout << "Exiting play function.\n";
}






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

