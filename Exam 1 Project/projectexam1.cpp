/*
-------------------------------------------------------------------------
Name:           Leon Thompson
Date:			September  29, 2023
Project Exam #:	1
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	This program acts as a rudimentary calculator, with the ability to 
	perform basic math operations such as addition, subtraction, 
	multiplication, division, and modulus.
-------------------------------------------------------------------------
*/

#include <iostream>				// for std::cin, std::cout, std::endl
#include <iomanip>				// for fixed, setprecision
#include <string>				// for string
#include <random>				// for random_device, mt19937, uniform_int_distribution


// Decleration of prototype 
void ProjectStart();
void ProjectEnd();
int GetIntegerData(std::string);
float GetFloatData(std::string);
char GetCharData(std::string);
std::string GetStringData(std::string);
void MainMenu();
void ClearCin();
void Greeting();
void Add(int&, int&, int&);
void DisplayResults(int, int, int);
void Subtract(int&, int&, int&);
void Multiply(int&, int&, int&);
void Divide(int&, int&, int&);
void Modulo(int&, int&, int&);
void UpdateResults(char,int, int, int&, int, int, int&, int&);
void GetRandomIntegers(int&, int&);

int main()
{
	// setting to 2 decimal places
	std::cout << std::fixed << std::setprecision(2);

	// Displays start of project 
	ProjectStart();

	// Declare main() variables
	bool exitRunLoop;
	char operationType;
	int answerAttempts;
	int correctAnswers;
	int incorrectAnswers;

	// Initialize main() variables
	exitRunLoop = false;
	answerAttempts = 0;
	correctAnswers = 0;
	incorrectAnswers = 0;


	Greeting();

	// Run Loop
	while (true)
	{
		MainMenu();

		operationType = GetCharData("Select the operation you would like to perform: ");

		switch (operationType)
		{

			// Addition
			case '+':
			{
				Add(answerAttempts, correctAnswers, incorrectAnswers);
				break;
			}

			// Subtraction
			case '-':
			{
				Subtract(answerAttempts, correctAnswers, incorrectAnswers);
				break;
			}

			// Multiplication
			case '*':
			{
				Multiply(answerAttempts, correctAnswers, incorrectAnswers);
				break;
			}

			// Division
			case '/':
			{
				Divide(answerAttempts, correctAnswers, incorrectAnswers);
				break;
			}

			// Modulo
			case '%':
			{
				Modulo(answerAttempts, correctAnswers, incorrectAnswers);
				break;
			}

			// Quit
			case 'X':
			case 'Q':
			{
				exitRunLoop = true;
				break;
			}

			// Invalid Transaction
			default:
			{
				std::cout << "\n\t\tERROR: Invalid Operation Selection." << std::endl;
				break;
			}

		} // switch (transactionType)

		if (exitRunLoop)
		{
			break;
		}

	} // while (true)

	// Displays User Results
	DisplayResults(answerAttempts, correctAnswers, incorrectAnswers);

	// Displays End of Project
	ProjectEnd();

	return 0;

}

// This function displays the results of the user's answer attempts
void DisplayResults(int answerAttempts, int correctAnswers, int incorrectAnswers)
{
	// Declare variables
	int percentCorrect;

	// Verify no division by 0
	if (answerAttempts > 0)
	{
		// Calculate percentage correct
		percentCorrect = (float)correctAnswers / answerAttempts * 100;
	}
	else
	{
		percentCorrect = 0;
	}

	// Display results
	std::cout << std::endl;
	std::cout << "RESULTS" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Total Attempts: " << answerAttempts << std::endl;
	std::cout << "Correct Answers: " << correctAnswers << std::endl;
	std::cout << "Incorrect Answers: " << incorrectAnswers << std::endl;
	if (answerAttempts > 0)
	{
		std::cout << "Percent Correct: " << percentCorrect << "%" << std::endl;
	}
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

} // end of DisplayResults()

// This function generates the addition expression and calculates the solution
void Add(int& answerAttempts, int& correctAnswers, int& incorrectAnswers)
{
	// Declare variables
	int valueA;
	int valueB;
	int solution;
	int userResponse;

	// Initialize variables
	solution = 0;
	userResponse = 0;

	// Get Random Int Values
	GetRandomIntegers(valueA, valueB);

	// Calculate Solution
	solution = valueA + valueB;

	// Get user solution
	std::cout << "Expression: " << valueA << " + " << valueB << std::endl;
	userResponse = GetIntegerData("Enter the result: ");

	// Update User and Response Data
	UpdateResults('+', userResponse, solution, correctAnswers, valueA, valueB, incorrectAnswers, 
		answerAttempts);

} // end of Add()

// This function generates the subtraction expression and calculates the solution
void Subtract(int& answerAttempts, int& correctAnswers, int& incorrectAnswers)
{
	// Declare variables
	int valueA;
	int valueB;
	int solution;
	int userResponse;

	// Initialize variables
	solution = 0;
	userResponse = 0;

	// Get Random Int Values
	GetRandomIntegers(valueA, valueB);

	// Calculate Solution
	solution = valueA - valueB;

	// Get user solution
	std::cout << "Expression: " << valueA << " - " << valueB << std::endl;
	userResponse = GetIntegerData("Enter the result: ");

	// Update User and Response Data
	UpdateResults('-', userResponse, solution, correctAnswers, valueA, valueB, incorrectAnswers, 
		answerAttempts);

} // end of Subtract()

// This function generates the multiplication expression and calculates the solution
void Multiply(int& answerAttempts, int& correctAnswers, int& incorrectAnswers)
{
	// Declare variables
	int valueA;
	int valueB;
	int solution;
	int userResponse;

	// Initialize variables
	solution = 0;
	userResponse = 0;

	// Get Random Int Values
	GetRandomIntegers(valueA, valueB);

	// Calculate Solution
	solution = valueA * valueB;

	// Get user solution
	std::cout << "Expression: " << valueA << " * " << valueB << std::endl;
	userResponse = GetIntegerData("Enter the result: ");

	// Update User and Response Data
	UpdateResults('*', userResponse, solution, correctAnswers, valueA, valueB, incorrectAnswers, 
		answerAttempts);
} // end of Multiply()

// This function generates the division expression and calculates the solution
void Divide(int& answerAttempts, int& correctAnswers, int& incorrectAnswers)
{
	// Declare variables
	int valueA;
	int valueB;
	int solution;
	int userResponse;

	// Initialize variables
	solution = 0;
	userResponse = 0;

	// Get Random Int Values
	GetRandomIntegers(valueA, valueB);

	// Ensure that we do not divide by 0
	while (valueB == 0)
	{
		GetRandomIntegers(valueA, valueB);
	}

	// Calculate Solution
	solution = valueA / valueB;

	// Get user solution
	std::cout << "Expression: " << valueA << " / " << valueB << std::endl;
	userResponse = GetIntegerData("Enter the result(INTEGER ONLY: ");

	// Update User and Response Data
	UpdateResults('/', userResponse, solution, correctAnswers, valueA, valueB, incorrectAnswers, 
		answerAttempts);

} // end of Divide()

// This function generates the modulo expression and calculates the solution
void Modulo(int& answerAttempts, int& correctAnswers, int& incorrectAnswers)
{
	// Declare variables
	int valueA;
	int valueB;
	int solution;
	int userResponse;

	// Initialize variables
	solution = 0;
	userResponse = 0;

	// Get Random Int Values
	GetRandomIntegers(valueA, valueB);

	// Ensure that we do not divide by 0
	while (valueB == 0)
	{
		GetRandomIntegers(valueA, valueB);
	}

	// Calculate Solution
	solution = valueA % valueB;

	// Get user solution
	std::cout << "Expression: " << valueA << " % " << valueB << std::endl;
	userResponse = GetIntegerData("Enter the result: ");

	// Update User and Response Data
	UpdateResults('%', userResponse, solution, correctAnswers, valueA, valueB, incorrectAnswers, 
		answerAttempts);

} // end of Modulo()

// This function informs user if they were correct and updates answer data
void UpdateResults(char operation, int userResponse, int solution, int& correctAnswers, 
	int valueA, int valueB, int& incorrectAnswers, int& answerAttempts)
{
	if (userResponse == solution)
	{
		std::cout << "Congrats! That's correct!" << std::endl;
		correctAnswers++;
	}
	else
	{
		std::cout << "Tough break. That's not correct." << std::endl;
		std::cout << valueA << " " << operation << " " << valueB << " = " << solution << std::endl;
		incorrectAnswers++;
	}
	answerAttempts++;
} // end of UpdateResults()

// This function generates 2 random integers between a min and max value(inclusive)
void GetRandomIntegers(int& x, int& y)
{
	// Declare variables

	// Create a random number generator
	std::random_device rd;
	std::mt19937 gen(rd());

	// Min and max variables
	int min;
	int max;

	// Set min and max
	min = 1;
	max = 20;

	// Create a uniform distribution
	std::uniform_int_distribution<int> distribution(min, max);

	// Set random numbers for variables
	x = distribution(gen);
	y = distribution(gen);

} // end of GetRandomIntegers()


// This function greets the user
void Greeting()
{
	std::cout << "\nWelcome to the Sparky Model L-32 Calculator!" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;

}// end of Greeting()

// This function displays a menu with all the user transaction options.
void MainMenu()
{
	std::cout << "\n----------------------------------------------------------------" << std::endl;
	std::cout << "Here are the Available Operations:" << std::endl;
	std::cout << "\t+.........Addition" << std::endl;
	std::cout << "\t-.........Subtraction" << std::endl;
	std::cout << "\t*.........Multiplication" << std::endl;
	std::cout << "\t/.........Division" << std::endl;
	std::cout << "\t%.........Modulo" << std::endl;
	std::cout << "\tQ.........Quit" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;

} // end of MainMenu()


// This function will return an integer data entered by users
int GetIntegerData(std::string prompt)
{
	int value;

	while (true)
	{
		std::cout << prompt;
		if (std::cin >> value) 
		{
			// Input was successful, break out of the loop
			break;
		}
		else 
		{
			std::cout << "\n\t\tERROR: Invalid entry. Enter an NUMBER value." << std::endl;

			// Clear the input buffer to prevent infinite loop
			ClearCin();
		}
	}

	return value;

} // end of int getIntegerData(std::string prompt)

// This function will return a float data entered by users
float GetFloatData(std::string prompt)
{
	float value;

	while (true)
	{
		std::cout << prompt;
		if (std::cin >> value)
		{
			// Input was successful, break out of the loop
			break;
		}
		else
		{
			std::cout << "\n\t\tERROR: Invalid entry. Enter an NUMBER value." << std::endl;

			// Clear the input buffer to prevent infinite loop
			ClearCin();
		}

	} // while (true)


	return value;

} // end of int getFloatData(std::string prompt)

// This functions clears the cin and then clears up to 120
// characters or hits enter.
void ClearCin()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

} // end of ClearCin()


// This function will return a char data entered by users
char GetCharData(std::string prompt)
{
	char value;
	
	std::cout << prompt;
	std::cin >> value;

	// Clear cin buffer
	ClearCin();

	value = toupper(value);

	return value;

} // end of char GetCharData(std::string prompt)

// This function will return a std::string data entered by users
std::string GetStringData(std::string prompt)
{
	std::string value;
	std::cout << prompt;
	getline(std::cin, value, '\n'); // accepts spaces in the entry

	return value;

} // end of int GetStringData(std::string prompt)

// The function will display the start of the project 
void ProjectStart()
{
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Project Exam 1" << std::endl;
	std::cout << "Written by: Leon Thompson" << std::endl;
	std::cout << "Objectives" << std::endl;
	std::cout << "\t." << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
} // end of ProjectStart()

// The function will display the end of the project 
void ProjectEnd()
{
	std::cout << "\n----------------------------------------------------------------" << std::endl;
	std::cout << "Project Exam 1" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
} // end of ProjectEnd()

