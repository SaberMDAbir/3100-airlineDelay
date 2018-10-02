//MD Abir A. Choudhury
//041618
//Airline Delay

#include <cstdlib>
#include <iostream>
#include <string>
#include <iterator>
#include <fstream>

//Prototypes
void load(std::string airlineName[], int minDelay[]);
double avgDelay(std::string airlineName[], int minDelay[], double& average);
void displayAvg(double average);
double maxDelay(std::string airLine[], int minDelay[]);
void displayFlightCount(std::string airlineName[], int minDelay[]);

const int NUMOFLINES = 999;

int main() {
	//Create the arrays
	std::string airlineName[NUMOFLINES];
	int minDelay[NUMOFLINES];
	
	load(airlineName, minDelay);

	int choice = 0;
	//Display menu
	do {
		std::cout << "Airport Delay Report v1.2\n"
			<< "=========================\n"
			<< "1- Average Delay\n"
			<< "2- Maximum Delay\n"
			<< "3- Flight Count\n"
			<< "-1 - Exit\n"
			<< "Choose an option: ";
		std::cin >> choice;

		//Option 1
		if (choice == 1) {
			double average = 0.0;
			avgDelay(airlineName, minDelay, average);
			displayAvg(average);
		}
		//Option 2
		else if (choice == 2) {
			double maxTime = 0.0;
			maxTime = maxDelay(airlineName, minDelay);
			std::cout << "Maximum Delay: " << maxTime << "hours \n";
		}
		//Option 3
		else if (choice == 3) {
			displayFlightCount(airlineName, minDelay);
		}
	} while (choice != -1);

	std::system("PAUSE");
	return 0;
}

//Fucntion Defintions

void load(std::string airlineName[], int minDelay[]) {
	std::ifstream fileName("C:\\Users\\abirc\\source\\repos\\airlineDelay\\airlineDelay\\airline_delays.txt");

	//filestream not inputting the variable
	//throw an exception
	if (!fileName)
	{
		std::cout << "Error opening file.\n";
		system("Pause");
		exit;
	}

	//read data in to the array
	int count = 0;
	while (fileName >> airlineName[count] >> minDelay[count]) {
		count++;
	}

	//close the file
	fileName.close();

	/*
	//For Debugging
	//new lines will be skipped unless we stop it from happening
	fileName.unsetf(std::ios_base::skipws);
	unsigned int lineCount = 0; //holds the number of lines in file
	//count the number of newlines
	logNumLines(lineCount, fileName);
	std::cout << lineCount << std::endl; //Debugger
	*/
}

double avgDelay(std::string airlineName[], int minDelay[], double& average) {
	std::string code;
	std::cout << "Enter an airline code: ";
	std::cin >> code;
	double total = 0.0;

	if (code == "ALL") {
		for (int i = 0; i < NUMOFLINES; i++) {
			total += minDelay[i];
			average = total / NUMOFLINES;
			return average;
		}
	}
	else if (code == "JFK") {
		//nested for loops for both arrays
		for (int i = 0; i < NUMOFLINES; i++) {
			if (airlineName[i] == "JFK") {
				total += minDelay[i];
				average = total / NUMOFLINES;
				return average;
			}
		}
	}
	else if (code == "LGA") {
		//nested for loops for both arrays
		for (int i = 0; i < NUMOFLINES; i++) {
			if (airlineName[i] == "LGA") {
				total += minDelay[i];
				average = total / NUMOFLINES;
				return average;
			}
		}
	}
}

void displayAvg(double average) {
	std::cout << "Average Delay is:" << average << "\n";
}

double maxDelay(std::string airlineName[], int minDelay[]) {
	double max = minDelay[0]; 
	//look for maxtime in loop
	for (int i = 0; i < NUMOFLINES; i++) {
		if (minDelay[i] > max) {
			max = minDelay[i];
		}
		else if(i == (NUMOFLINES -1)) {
			std::cout << "At Airport: " << airlineName[i] << "\n";
		}
	}
	max /= 60;
	return max;
}

void displayFlightCount(std::string airlineName[], int minDelay[]) {
	std::cout << "For which airport {JFK, LGA, ALL}: ";
	std::string code;
	std::cin >> code;
	std::cout << "What is the minimum delay in minutes? ";
	int min = 0;
	std::cin >> min;

	int count = 0;
	if (code == "JFK") {
		for (int i = 0; i < NUMOFLINES; i++) {
			if ((minDelay[i] > min || minDelay[i] == min) && airlineName[i] == "JFK") {
				std::cout << airlineName[i] << "\t" << minDelay[i] << std::endl;
				count++;
			}
		}
		std::cout << "Minimum Delay: " << min << std::endl;
		std::cout << "There are " << count << " flights that have matched the criteria.\n";
	}
	else if (code == "LGA") {
		for (int i = 0; i < NUMOFLINES; i++) {
			if ((minDelay[i] > min || minDelay[i] == min) && airlineName[i] == "LGA") {
				std::cout << airlineName[i] << "\t" << minDelay[i] << std::endl;
				count++;
			}
		}
		std::cout << "Minimum Delay: " << min << std::endl;
		std::cout << "There are " << count << " flights that have matched the criteria.\n";
	}
	else if (code == "ALL") {
		bool output = false;
		for (int i = 0; i < NUMOFLINES; i++) {
			if (minDelay[i] > min) {
				std::cout << airlineName[i] << "\t" << minDelay[i] << std::endl;
				output = true;
			}
		}
		if (output == false) {
			std::cout << "There are no flights that were delayed higher than your number.\n";
		}
	}
}