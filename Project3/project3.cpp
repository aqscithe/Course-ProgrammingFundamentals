/*
-------------------------------------------------------------------------
Name:			Leon Thompson
Date:			10/8/23
Project #:		3
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	Retrieves input from user regarding weekly food intake amounts for
	3 monkeys, prints the data into a neatly formatted table, and
	calculates the average, greatest and least amount of food eaten
	by the 3 monkeys.

-------------------------------------------------------------------------
*/

#include <iostream>				// for cin, cout, endl
#include <iomanip>				// for fixed, setprecision
#include <string>


// Decleration of prototype 
void projectStart();
void projectEnd();
int getIntegerData(std::string);
float getFloatData(std::string);
char getCharData(std::string);
std::string getStringData(std::string);
void inputMonkeyFoodIntake(float [3][7], std::string []);
void printFoodIntakeSummary(float [3][7]);
float getAvgFoodEaten(float [3][7]);
float getLeastFoodEaten(float [3][7]);
float getMostFoodEaten(float [3][7]);

int main()
{
	// setting to 1 decimal places
	std::cout << std::fixed << std::setprecision(1);

	// Displays start of project 
	projectStart();

	// write your code below
	
	// Declare variables
	float monkeyFoodIntake[3][7];
	float avgFoodEaten;
	float leastFoodEaten;
	float mostFoodEaten;

	// Initialize variables
	std::string weekDays[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	avgFoodEaten = 0.f;
	leastFoodEaten = 0.f;
	mostFoodEaten = 0.f;

	// Retrieve monkey food intake data
	inputMonkeyFoodIntake(monkeyFoodIntake, weekDays);

	// Print summary of monkey food data
	printFoodIntakeSummary(monkeyFoodIntake);

	// Calculate average, least and most food eaten by a monkey
	avgFoodEaten = getAvgFoodEaten(monkeyFoodIntake);
	leastFoodEaten = getLeastFoodEaten(monkeyFoodIntake);
	mostFoodEaten = getMostFoodEaten(monkeyFoodIntake);

	// setting to 2 decimal places
	std::cout << std::fixed << std::setprecision(2);

	// Print calculated average, least and most food eaten
	std::cout << "\nThe average food eaten per day by all monkeys: \t\t\t     " << avgFoodEaten << " lbs" << std::endl;
	std::cout << "The least amount of food eaten by any monkey: \t\t\t     " << leastFoodEaten << " lbs" << std::endl;
	std::cout << "The largest amount of food eaten per by any monkey: \t\t     " << mostFoodEaten << " lbs" << std::endl;
	std::cout << std::endl;

	// Displays end of project
	projectEnd();

	return 0;

}// end of main

// This function gets the food intake amounts each day of the week for the
// 3 monkeys
void inputMonkeyFoodIntake(float monkeyFoodIntake[3][7], std::string weekDays[])
{
	std::cout << "\nWelcome to Aurelius Zoo." << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Weekly Food Intake(pounds)" << std::endl;

	// Loop though monkeys
	for (int monkey = 0; monkey < 3; monkey++)
	{
		// Set monkey description
		int monkeyDescription = monkey + 1;

		std::cout << "\tMonkey " << monkeyDescription << std::endl;
		std::cout << "\t\tEnter food intake for each day" << std::endl;

		// Loop through days of week
		for (int day = 0; day < 7; day++)
		{
			// Declare prompt variable
			std::string prompt;

			// Set prompt variable
			prompt = "\t\t\t" + weekDays[day] + ": ";

			// Get food intake values
			monkeyFoodIntake[monkey][day] = getFloatData(prompt);
		}
	}
	
} // end of getMonkeyFoodIntake()

// This function prints a summary of the monkey weekly food intake data
void printFoodIntakeSummary(float monkeyFoodIntake[3][7])
{
	std::cout << "\nSummary: Weekly Monkey Food Intake" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "\nPounds of Food Eaten by Monkey for Each Day of Week" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;

	// Set monkey labels
	int monkeys[3] = { 1, 2, 3 };

	// Create Table Header Row
	std::cout << std::left << std::setw(9) << "Monkey"
		<< std::setw(10) << "Mon"
		<< std::setw(10) << "Tue"
		<< std::setw(10) << "Wed"
		<< std::setw(10) << "Thu"
		<< std::setw(10) << "Fri"
		<< std::setw(10) << "Sat"
		<< std::setw(10) << "Sun"
		<< std::endl;

	// Loop through monkeys
	for (int monkey = 0; monkey < 3; monkey++)
	{
		// Print monkey number
		std::cout << std::left << std::setw(9) << monkeys[monkey];

		// Loop through days of week
		for (int day = 0; day < 7; day++)
		{
			std::cout << std::left << std::setw(10) << monkeyFoodIntake[monkey][day];
		}

		// Go to new line in table
		std::cout << std::endl;
	}

} // end of printFoodIntakeSummary

// This function calculates average food eaten
float getAvgFoodEaten(float monkeyFoodIntake[3][7])
{
	// Declare Variables
	float sum;
	float average;
	int count;

	// Initialize Variables
	sum = 0.f;
	average = 0.f;
	count = 0;

	// Loop through data table
	for (int monkey = 0; monkey < 3; monkey++)
	{
		for (int day = 0; day < 7; day++)
		{
			// Add food eaten to sum
			sum += monkeyFoodIntake[monkey][day];
			count++;
		}
	}

	// Calculate the average
	average = sum / (float)count;

	return average;

} // end of getAvgFoodEaten()

// This function calculates the least amount of food eaten
float getLeastFoodEaten(float monkeyFoodIntake[3][7])
{
	// Declare variables
	float least;
	float tableEntry;

	// Initialize least to first entry in table
	least = monkeyFoodIntake[0][0];

	// Loop through data table
	for (int monkey = 0; monkey < 3; monkey++)
	{
		for (int day = 0; day < 7; day++)
		{
			// Setting current table index to a variable
			tableEntry = monkeyFoodIntake[monkey][day];

			// Checking if table entry is less than current least amount
			if (tableEntry < least)
			{
				least = tableEntry;
			}
		}
	}

	return least;
} // end of getLeastFoodEaten()

// This function calculates the greatest amount of food eaten
float getMostFoodEaten(float monkeyFoodIntake[3][7])
{
	// Declare variables
	float greatest;
	float tableEntry;

	// Initialize greatest to first entry in table
	greatest = monkeyFoodIntake[0][0];

	// Loop through data table
	for (int monkey = 0; monkey < 3; monkey++)
	{
		for (int day = 0; day < 7; day++)
		{
			// Setting current table index to a variable
			tableEntry = monkeyFoodIntake[monkey][day];

			// Checking if table entry is greater than current greatest amount
			if (tableEntry > greatest)
			{
				greatest = tableEntry;
			}
		}
	}

	return greatest;

} // end of getMostFoodEaten()


// This function will get a char value from the user
char getCharData(std::string prompt)
{
	char value;

	while (true)
	{
		std::cout << prompt;
		std::cin >> value;

		value = toupper(value);

		return value;

		std::cout << "\t\tError Message. Selection does not exist" << std::endl;
	} // end of while(true)

} // end of int getFloatData()

// This function will get a float value from the user
float getFloatData(std::string prompt)
{
	float value;

	while (true)
	{
		std::cout << prompt;
		while (!(std::cin >> value))
		{
			std::cout << "\t\tError Message. Non numeric is entered" << std::endl;
			std::cin.clear(); // clear error buffer
			std::cin.ignore(120, '\n');  // clear upto 120 chars or it reaches an enter
			std::cout << prompt;
		} // 	while (!(cin >> value))

		if (value >= 0)
		{
			return value;
		} // end of 	if (value >= 0)

		std::cout << "\t\tError Message. Enter value GREATER THAN or EQUAL to 0." << std::endl;
	} // end of while (true)

} // end of int getFloatData()

// This function will get an integer value from the user
int getIntegerData(std::string prompt)
{
	int value;

	while (true)
	{
		std::cout << prompt;
		while (!(std::cin >> value))
		{
			std::cout << "\t\t\tError Message. Non numeric is entered" << std::endl;
			std::cin.clear(); // clear error buffer
			std::cin.ignore(120, '\n');  // c;lear upto 120 chars or it reaches an enter
			std::cout << prompt;
		} // 	while (!(cin >> value))

		return value;

	} // end of while (true)
} // end of int getIntegerData()

// This function will return a string data entered by users
std::string getStringData(std::string prompt)
{
	std::string value;
	std::cout << prompt;
	std::getline(std::cin, value); // accepts spaces in the entry

	return value;

} // end of int getStringData(string prompt)

// The function will display the start of the project 
void projectStart()
{
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Project " << std::endl;
	std::cout << "Written by: Leon Thompson" << std::endl;
	std::cout << "Objectives" << std::endl;
	std::cout << "\t" << std::endl;
	std::cout << "\t " << std::endl;
	std::cout << "-----------------------------" << std::endl;
} // end of projectStart()

// The function will display the end of the project 
void projectEnd()
{
	std::cout << "-----------------------------" << std::endl;
	std::cout << "End of Project 3" << std::endl;
	std::cout << "-----------------------------" << std::endl;
} // end of projectEnd()


