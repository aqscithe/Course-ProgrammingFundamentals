/*
-------------------------------------------------------------------------
Name:			Leon Thompson
Date:			10/15/2023
Project #:		4
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	This program takes on the role of a shipping service. It determines
	the shipping location of user packages, as well as the weight and
	dimensions. Then it determines whether the package is rejected or 
	accepted and calculates final shipping cost. Once the user exits,
	a summary of all packages is displayed.
-------------------------------------------------------------------------
*/

#include <iostream>				// for cin, cout, std::endl
#include <iomanip>				// for fixed, setprecision
#include <string>				// for string
#include <cctype> 				//for toupper()


// Global Const Values
const int MAX_WEIGHT = 50;
const int MAX_GIRTH = 10;
const int MAX_DIMENSION = 6;

// Forward Declaration
struct Package;


// Decleration of prototype 
void projectStart();
void projectEnd();
int getIntegerData(std::string);
float getFloatData(std::string);
char getCharData(std::string);
std::string getstringData(std::string);
void clearCin();
void greetUser();
void showMainMenu();
void processTransactionSelection(char, Package&, bool&, bool&);
void displayShippingSummary(int, int, float);

// Struct containing package related variables and functions
struct Package
{
	// -- Member Variables -- //

	int          m_weight;
	int          m_length;
	int          m_width;
	int          m_height;
	std::string  m_destination;
	float        m_cost;
	bool         m_accepted;
	int          m_girth;

	// -- Member Functions -- //

	// Package constructor
	Package()
	{
		// Initializing member variables
		m_weight = 0;
		m_length = 0;
		m_width = 0;
		m_height = 0;
		m_destination = "";
		m_cost = 0.f;
		m_accepted = false;
		m_girth = 0;
	}

	// This function calculates the shipping charge based on weight
	// and adds it to the shipping cost
	void calculateShippingCharge(int packageWeights[15], float shippingCharges[15])
	{
		// Loop through package weights
		for (int i = 0; i < 15; i++)
		{
			if (packageWeights[i] == m_weight)
			{
				m_cost += shippingCharges[i];
				break;
			}
			// if weight is not listed explicitly, the charge will be that of
			// the next lowest weight
			else if (packageWeights[i] > m_weight)
			{
				m_cost += shippingCharges[i - 1];
				break;
			}
		}

	} // end of calculateShippingCharge()

	// This function displays the shipping results
	void displayPackageResults(int packageWeights[15], float shippingCharges[15])
	{
		if (m_accepted)
		{
			// Calculate weight based shipping charges
			calculateShippingCharge(packageWeights, shippingCharges);

			// Display acceptance info
			std::cout << "\tTransaction Completed. Shipping to " << m_destination << "." << std::endl;
			std::cout << "\t------------------------------------------" << std::endl;
			std::cout << std::endl;
			std::cout << "\t\tLocation..................." << m_destination << std::endl;
			std::cout << "\t\tStatus.....................Accepted" << std::endl;
			std::cout << "\t\tWeight....................." << m_weight << " lbs." << std::endl;
			std::cout << "\t\tCost.......................$" << m_cost << std::endl;

		}
		else
		{
			// Display rejection info
			std::cout << "\tTransaction Completed. Rejected mail to " << m_destination << "." << std::endl;
			std::cout << "\t------------------------------------------" << std::endl;
			std::cout << std::endl;
			std::cout << "\t\tLocation..................." << m_destination << std::endl;
			std::cout << "\t\tStatus.....................Rejected" << std::endl;
			std::cout << "\t\tWeight....................." << m_weight << " lbs." << std::endl;
			std::cout << "\t\tCost.......................N/A" << std::endl;
		}

	} // end of displayShippingResults()

	// This function obtains the weight and package dimensions from the user
	bool processSizeAndWeight()
	{
		std::cout << "\tShipping to " << m_destination << std::endl;
		std::cout << "\tEnter package weight and the 3 dimensions." << std::endl;
		std::cout << std::endl;

		// Get Dimension Input
		m_weight = getIntegerData("\t\tEnter weight: ");
		m_length = getIntegerData("\t\tEnter length: ");
		m_width = getIntegerData("\t\tEnter width: ");
		m_height = getIntegerData("\t\tEnter height: ");

		// Verify if package dimensions and weight are valid values
		if (m_weight == -1 || m_length == -1 || m_width == -1 ||
			m_height == -1)
		{
			std::cout << "\t\tINVALID PACKAGE DATA. SKIPPING PROCESSING..." << std::endl;
			return false;
		}

		return true;

	} // end of processSizeAndWeight

	// This function calculates the girth
	void calculateGirth()
	{
		// Declaring variables
		int largest;

		// Initializing largest
		largest = std::max(std::max(m_length, m_width), m_height);

		// Applying girth formula
		m_girth = 2 * (m_length + m_width + m_height - largest);

	} // end of calculateGirth()

	// This function determines if the package fits the shipping requirements
	void processRequirements()
	{
		calculateGirth();

		if (m_girth > MAX_GIRTH || m_weight > MAX_WEIGHT || m_length > MAX_DIMENSION || m_width > MAX_DIMENSION ||
			m_height > MAX_DIMENSION)
		{
			m_accepted = false;
		}
		else
		{
			m_accepted = true;
		}

	} // end of processRequirements
};



int main()
{
	// setting to 2 decimal places
	std::cout << std::fixed << std::setprecision(2);

	// Displays start of project 
	projectStart();

	// Declare Variables
	char transactionType;
	bool exitRunLoop;
	bool skipRunLoop;
	int packageWeights[15] = { 1, 2, 3, 5, 7, 10, 13, 16, 20, 25, 30 , 35, 40 , 45, 50 };

	float shippingCharges[15] = { 
		1.5f, 2.1f, 4.f, 6.75f, 9.9f, 
		14.95f, 19.4f, 24.2f, 27.3f, 31.9, 
		38.5f, 43.5, 44.8f, 47.4f, 55.2f 
	};

	int rejectedCount;
	int acceptedCount;
	float totalCost;

	// Initialize Variables
	exitRunLoop = false;
	skipRunLoop = false;
	rejectedCount = 0;
	acceptedCount = 0;
	totalCost = 0.f;

	greetUser();

	while (true)
	{
		// Initialize Package
		Package package;

		// Show main menu
		showMainMenu();

		// Get and Process transaction selection
		transactionType = getCharData("\tEnter Your Package Shipping Destination: ");
		processTransactionSelection(transactionType, package, exitRunLoop, skipRunLoop);

		// Break from run loop if user selects exit
		if (exitRunLoop)
		{
			break;
		}
		else if (skipRunLoop)
		{
			skipRunLoop = false;
			continue;
		}

		// Verify valid values for size and weight
		if (!package.processSizeAndWeight())
		{
			// If not skip processing of package
			continue;
		}

		// Determine if package is accepted or rejected
		package.processRequirements();

		// Display package results
		package.displayPackageResults(packageWeights, shippingCharges);

		// Update package count and total cost
		if (package.m_accepted)
		{
			acceptedCount++;
			totalCost += package.m_cost;
		}
		else
		{
			rejectedCount++;
		}

	}

	// Displays final shipping summary
	displayShippingSummary(acceptedCount, rejectedCount, totalCost);
	

	// Displays end of project
	projectEnd();

	return 0;

}

// This function displays the count of accepted and rejected packages, as well as
// the total cost
void displayShippingSummary(int acceptedCount, int rejectedCount, float totalCost)
{
	std::cout << " Final Shipping Transaction " << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "\tAccepted Packages:\t" << acceptedCount << std::endl;
	std::cout << "\tRejected Packages:\t" << rejectedCount << std::endl;
	std::cout << "\tTotal Cost:\t\t$" << totalCost << std::endl;
	std::cout << std::endl;
} // end of displayShippingSummary()


// This function processes the transaction selected by the user
void processTransactionSelection(char transactionType, Package& package, bool& exitRunLoop, 
	bool& skipRunLoop)
{
	std::cout << std::endl;

	switch (transactionType)
	{
		// Texas
		case 'T':
		{
			package.m_destination = "Texas";
			package.m_cost = 0.f;
			break;
		}

		// Out of State
		case 'O':
		{
			package.m_destination = "Out of State";
			package.m_cost = 35.f;
			break;
		}

		// Foreign
		case 'F':
		{
			package.m_destination = "Foreign";
			package.m_cost = 40.f;
			break;
		}

		// Exit 
		case 'X':
		case 'E':
		{
			exitRunLoop = true;
			std::cout << "\n\tExiting Application...\n" << std::endl;
			break;
		}

		// Default - means an invalid selection was made
		default:
		{
			std::cout << "\t\tERROR: Invalid Transaction Selection." << std::endl;
			skipRunLoop = true;
			break;
		}

	}
} // end of processTransactionSelection()


// This function displays the main menu
void showMainMenu()
{
	std::cout << "\n----------------------------------------------------------------" << std::endl;
	std::cout << "Available Shipping Destinations:" << std::endl;
	std::cout << "\tT.........Texas" << std::endl;
	std::cout << "\tO.........Out of State" << std::endl;
	std::cout << "\tF.........Foreign" << std::endl;
	std::cout << "\tE.........End Transaction" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
} // end of showMainMenu()


// This function greets the user
void greetUser()
{
	std::cout << "WELCOME TO THE SAFARI SHIPPING SERVICE" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
} // end of greetUser()


// This functions clears the cin and then clears up to 120
// characters or hits enter.
void clearCin()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

} // end of ClearCin()


// This function will get a char value from the user
char getCharData(std::string prompt)
{
	char value;

	while (true)
	{
		std::cout << prompt;
		std::cin >> value;

		clearCin();

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

		if (value >= 1 && value <= 10)
		{
			return value;
		} // end of 	if (value >= 0)

		std::cout << "\t\tError Message. ONLY integers between 1 and 10" << std::endl;
	} // end of while (true)
} // end of int getFloatData()

// This function will get an integer value from the user
int getIntegerData(std::string prompt)
{
	int value;
	
	std::cout << prompt;
	if (!(std::cin >> value))
	{
		std::cout << "\t\t\tError Message. Non numeric is entered" << std::endl;
		std::cin.clear(); // clear error buffer
		std::cin.ignore(120, '\n');  // c;lear upto 120 chars or it reaches an enter
		
		return -1;
	} // 	while (!(cin >> value))
	else if (value < 0)
	{
		std::cout << "\t\t\tError Message. Number must be positive" << std::endl;
		return -1;
	}

	return value;

	
} // end of int getIntegerData()

// This function will return a string data entered by users
std::string getStringData(std::string prompt)
{
	std::string value;
	std::cout << prompt;
	std::getline(std::cin, value, '\n'); // accepts spaces in the entry

	return value;

} // end of int getstd::stringData(std::string prompt)

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
	std::cout << std::endl;

} // end of projectStart()

// The function will display the end of the project 
void projectEnd()
{
	std::cout << "-----------------------------" << std::endl;
	std::cout << "End of Project" << std::endl;
	std::cout << "-----------------------------" << std::endl;
} // end of projectEnd()


