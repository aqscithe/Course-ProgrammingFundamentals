/*
Name:     		Leon Thompson
Date: 			September 3, 2023
Project #:		1
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	Retrieves input from user regarding name of movie and number of adult
	and child tickets. Then the income and distribution amounts to the
	movie distributor and theater are calculated and displayed.
*/

#include <iostream>				// for cin, cout, endl
#include <iomanip>				// for fixed, setprecision
#include <string>				// for string


using namespace std;

// Decleration of prototypes 
void ProjectStart();
void EnterBoxOfficeInfo(std::string& movieName, int& numAdultTickets, 
	int& numChildTickets);
void CalculateMovieIncomeDistribution(float& grossIncome, 
	int numAdultTickets, float adultTicketPrice, 
	int numChildTickets, float childTicketPrice, 
	float& theaterIncome, float theaterPercentIncome, 
	float& distributorIncome);
void DisplayBoxOfficeEntrySummary(std::string& movieName, 
	float grossIncome, float theaterIncome, float distributorIncome);
void ProjectEnd();

int main()
{
	// setting to 2 decimal places
	std::cout << std::fixed << std::setprecision(2);

	// Displays start of project 
	ProjectStart();

	// write your code below

	// Declare variables
	float adultTicketPrice;
	float childTicketPrice;
	float theaterPercentIncome;
	float grossIncome;
	float theaterIncome;
	float distributorIncome;
	int numAdultTickets;
	int numChildTickets;
	string movieName;

	// Initialize variables
	adultTicketPrice = 20.0f;
	childTicketPrice = 10.0f;
	theaterPercentIncome = 40.0f;
	grossIncome = 0.0f;
	theaterIncome = 0.0f;
	distributorIncome = 0.0f;
	numAdultTickets = 0;
	numChildTickets = 0;


	// Input Box Office Info
	EnterBoxOfficeInfo(movieName, numAdultTickets, numChildTickets);
	
	// Calculate gross income and incomes for the theater and distributor
	CalculateMovieIncomeDistribution(grossIncome, numAdultTickets, 
		adultTicketPrice, numChildTickets, childTicketPrice, theaterIncome, 
		theaterPercentIncome, distributorIncome);

	// Display Summary for Box Office Entry
	DisplayBoxOfficeEntrySummary(movieName, grossIncome, theaterIncome, 
		distributorIncome);
	
	// Displays end of project
	ProjectEnd();

	return 0;

} // end of main

// Displays the movie income results based on the box office info
// gathered from the user input.
void DisplayBoxOfficeEntrySummary(std::string& movieName, float grossIncome,
	float theaterIncome, float distributorIncome)
{
	cout << endl;
	cout << "Summary: Movie Income Information" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "\tMovie name: " << movieName << endl;
	cout << "\tGross Income: $" << grossIncome << endl;
	cout << "\tTheater Amount: $" << theaterIncome << endl;
	cout << "\tMovie Distributor Amount: $" << distributorIncome << endl;
	cout << endl;
	cout << "----------------------------------------------------------" << endl;
} // end of DisplayBoxOfficeEntrySummary

// Calculates the gross income, as well as the theater and movie distributor take 
// based on the box office info gathered from the user
void CalculateMovieIncomeDistribution(float& grossIncome, int numAdultTickets, 
	float adultTicketPrice, int numChildTickets, float childTicketPrice, 
	float& theaterIncome, float theaterPercentIncome, float& distributorIncome)
{
	grossIncome = (float)numAdultTickets * adultTicketPrice + 
		(float)numChildTickets * childTicketPrice;
	theaterIncome = theaterPercentIncome / 100.0f * grossIncome;
	distributorIncome = grossIncome - theaterIncome;
} // end of CalculateMovieIncomeDistribution

// Gathers the box office info from the user, to include the movie name,
// and the number of adult and child tickets sold
void EnterBoxOfficeInfo(std::string& movieName, int& numAdultTickets, int& numChildTickets)
{
	
	cout << "Box Office Entry" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "\tEnter the name of the movie: ";
	std::getline(cin, movieName);

	cout << "\tEnter the number of adult tickets sold: ";
	cin >> numAdultTickets;

	cout << "\tEnter the number of child tickets sold: ";
	cin >> numChildTickets;
	cout << endl;
	cout << "----------------------------------------------------------" << endl;
} // end of EnterBoxOfficeInfo


// The function will display the start of the project 
void ProjectStart()
{
	cout << "----------------------------------------------------------" << endl;
	cout << "Project 1" << endl;
	cout << "Written by: Leon Thompson" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << endl;
} // end of projectStart()

// The function will display the end of the project 
void ProjectEnd()
{
	cout << "----------------------------------------------------------" << endl;
	cout << "End of Project 1" << endl;
	cout << "----------------------------------------------------------" << endl;
} // end of projectEnd()


