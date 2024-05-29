/*
-------------------------------------------------------------------------
Name:			Leon Thompson
Date:			10/22/2023
Project #:		5
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	This program takes on the role of a company payroll calculator. It
	takes in the employee info such as id, name, pay rate and type, as 
	well as hours worked. Then gross and net pay is calculated for each
	employee and a summary is printed.
-------------------------------------------------------------------------
*/

#include <iostream>				// for cin, cout, std::endl
#include <iomanip>				// for fixed, setprecision
#include <string>				// for string
#include <cctype> 				//for toupper()


// Global Const Values
const int TOTAL_EMPLOYEES = 25;

// Forward Declaration
struct Employee;
enum EmployeeType;


// Decleration of prototype 
void projectStart();
void projectEnd();
int getIntegerData(std::string, int min = -9999, int max = -9999);
float getFloatData(std::string, float min = -9999, float max = -9999);
char getCharData(std::string);
std::string getStringData(std::string);
EmployeeType getEmployeeType(std::string);
void clearCin();
void greetUser();
void collectEmployeeInfo(int, Employee [TOTAL_EMPLOYEES]);
void collectTimecardInfo(int, Employee [TOTAL_EMPLOYEES], float [TOTAL_EMPLOYEES], 
	float[TOTAL_EMPLOYEES], float [TOTAL_EMPLOYEES]);
void calculateTotalPay(int, float&, float [TOTAL_EMPLOYEES], float&, float [TOTAL_EMPLOYEES]);
float calculateGrossPay(EmployeeType, float, int);
void displayPayrollSummary(int payrollCount, Employee [TOTAL_EMPLOYEES], float [TOTAL_EMPLOYEES], 
	float [TOTAL_EMPLOYEES], float [TOTAL_EMPLOYEES], float totalGrossPay, float totalNetPay);


// Enum for different employee types
enum EmployeeType
{
	UNION = 0,
	MANAGEMENT = 1
};


// This struct contains info relating to each employee
struct Employee
{
	int          ID;
	std::string  Name;
	float        PayRate;
	EmployeeType Type;
};



int main()
{
	// setting to 2 decimal places
	std::cout << std::fixed << std::setprecision(2);

	// Displays start of project 
	projectStart();

	// Declare Variables
	int payrollCount;
	Employee employees[TOTAL_EMPLOYEES];
	float grossPay[TOTAL_EMPLOYEES];
	float tax[TOTAL_EMPLOYEES];
	float netPay[TOTAL_EMPLOYEES];
	float totalGrossPay;
	float totalNetPay;


	// Initialize Variables
	payrollCount = 0;
	totalGrossPay = 0.f;
	totalNetPay = 0.f;


	// Greeting
	greetUser();

	// Determine number of employee payrolls being processed
	payrollCount = getIntegerData("\tEnter the number of payrolls to be processed: ");
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	// Collect Employee Info
	collectEmployeeInfo(payrollCount, employees);

	// Collect hours worked and calculate gross and net pays
	collectTimecardInfo(payrollCount, employees, grossPay, tax, netPay);

	// Calculate total gross and net pay for for all employees
	calculateTotalPay(payrollCount, totalGrossPay, grossPay, totalNetPay, netPay);

	// Print a summary of collected and calculated payroll info
	displayPayrollSummary(payrollCount, employees, grossPay, tax, netPay, totalGrossPay, 
		totalNetPay);

	// Displays end of project
	projectEnd();

	return 0;

} // end of main()

// This function prints a summary of employee payroll info
void displayPayrollSummary(int payrollCount, Employee  employees[TOTAL_EMPLOYEES], 
	float  grossPay[TOTAL_EMPLOYEES], float tax[TOTAL_EMPLOYEES], float  netPay[TOTAL_EMPLOYEES], 
	float totalGrossPay, float totalNetPay)
{

	std::cout << std::endl;
	std::cout << "Summary: Payroll Report" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" 
		<< std::endl;
	std::cout << "Number of Employees Processed: " << payrollCount << std::endl;
	std::cout << "--------------------------------------------------------------------------------" 
		<< std::endl;

	// Create Table Header Row
	std::cout << std::left << std::setw(10) << "ID"
		<< std::setw(22) << "Name"
		<< std::setw(21) << "Gross Pay"
		<< std::setw(16) << "Tax"
		<< std::setw(15) << "Net Pay"
		<< std::endl;
	std::cout << "--------------------------------------------------------------------------------" 
		<< std::endl;

	// Create Subsequent Table Rows
	for (int employee = 0; employee < payrollCount; employee++)
	{
		std::cout << std::left << std::setw(10) << employees[employee].ID
			<< std::setw(22) << employees[employee].Name
			<< "$" << std::setw(20) << grossPay[employee]
			<< "$" << std::setw(15) << tax[employee]
			<< "$" << std::setw(15) << netPay[employee]
			<< std::endl;
	}
	std::cout << "--------------------------------------------------------------------------------" 
		<< std::endl;

	// Print Total Pay Amounts
	std::cout << "\tTotal Gross Pay $" << totalGrossPay << std::endl;
	std::cout << "\tTotal Net Pay $" << totalNetPay << std::endl;
	std::cout << std::endl;
} // end of displayPayrollSummary

// This function calculates the combined totals of all employee gross and net pays
void calculateTotalPay(int payrollCount, float& totalGrossPay, float  grossPay[TOTAL_EMPLOYEES], 
	float& totalNetPay, float  netPay[TOTAL_EMPLOYEES])
{
	for (int employee = 0; employee < payrollCount; employee++)
	{
		totalGrossPay += grossPay[employee];
		totalNetPay += netPay[employee];
	}
} // end of calculateTotalPay

// This function collects the info on employee hours worked, as well as
// calculate per user gross and net pay
void collectTimecardInfo(int payrollCount, Employee  employees[TOTAL_EMPLOYEES], 
	float grossPay[TOTAL_EMPLOYEES],  float tax[TOTAL_EMPLOYEES], float netPay[TOTAL_EMPLOYEES])
{
	// Declare variables
	int hoursWorked;
	float taxRate;

	// Initialte variables
	hoursWorked = 0;
	taxRate = 15.f;

	// Display message if there are entries in the payroll
	if (payrollCount > 0)
	{
		std::cout << "\tEnter timecard info for each employee:" << std::endl;
	}

	// Loop through employees and their corresponding payroll info
	for (int payrollIndex = 0; payrollIndex < payrollCount; payrollIndex++)
	{
		// Declare Variables
		std::string prompt;
		
		// Initialize
		prompt = "\t\tHours worked for " + employees[payrollIndex].Name + ": ";
		hoursWorked = getFloatData(prompt, 0);

		// Pay and tax calculations
		grossPay[payrollIndex] = calculateGrossPay(employees[payrollIndex].Type, employees[payrollIndex].PayRate, hoursWorked);
		tax[payrollIndex] = grossPay[payrollIndex] * taxRate / 100.f;
		netPay[payrollIndex] = grossPay[payrollIndex] - tax[payrollIndex];
	}
} // end of collectTimecardInfo

// This function calculates a user's Gross Pay
float calculateGrossPay(EmployeeType type, float payRate, int hoursWorked)
{
	// Declare Variables
	float grossPay;
		
	// Initialize Variables
	grossPay = 0.f;

	switch (type)
	{
		// Union Employee
		case EmployeeType::UNION:
		{
			// Applies overtime pay rate to any hours worked over 40
			if (hoursWorked > 40)
			{
				int overtimeRate;
				
				overtimeRate = payRate * 1.5f;
				grossPay = payRate * 40;
				grossPay += overtimeRate * (hoursWorked - 40);
				
			}
			else
			{
				grossPay = payRate * hoursWorked;
			}

			break;
		}

		// Management Employee
		case EmployeeType::MANAGEMENT:
		{
			grossPay = payRate * hoursWorked;
			break;
		}
	}
	
	return grossPay;
} // end of calculateGrossPay


// This function collects employee info and stores it in an array of structs
void collectEmployeeInfo(int payrollCount, Employee  employees[TOTAL_EMPLOYEES])
{
	// Loop through employees
	for (int payrollIndex = 0; payrollIndex < payrollCount; payrollIndex++)
	{
		int employeeNum;
		
		employeeNum = payrollIndex + 1;

		// Collecting employee info
		std::cout << "\tEnter information for Employee #" << employeeNum << ": " << std::endl;
		employees[payrollIndex].ID = getIntegerData("\t\tEmployee ID: ", 1);
		employees[payrollIndex].Name = getStringData("\t\tEmployee Name: ");
		employees[payrollIndex].PayRate = getFloatData("\t\tPay Rate: ", 0);
		employees[payrollIndex].Type = getEmployeeType("\t\tEmployee Type (0 - Union, 1 - Management): ");
		std::cout << std::endl;

	}

	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
} // end of collectEmployeeInfo



// This function greets the user
void greetUser()
{
	std::cout << "WELCOME TO THE SAFARI AUTOMOTIVE GROUP" << std::endl;
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


// This function gets the employee type
EmployeeType getEmployeeType(std::string prompt)
{
	int value;

	while (true)
	{
		std::cout << prompt;
		std::cin >> value;

		clearCin();

		// Ensure that the value is 0 or 1
		if (value == 0 || value == 1)
		{
			break;
		}
		else
		{
			std::cout << "\t\t\tError Message. Not a valid employee type." << std::endl;
		}
	}

	return static_cast<EmployeeType>(value);
} // end of getEmployeeType


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
float getFloatData(std::string prompt, float min, float max)
{
	float value;

	
	while (true)
	{
		std::cout << prompt;
		if (!(std::cin >> value))
		{
			std::cout << "\t\t\tError Message. Non numeric is entered" << std::endl;
			std::cin.clear(); // clear error buffer
			std::cin.ignore(120, '\n');  // c;lear upto 120 chars or it reaches an enter

		} // 	while (!(cin >> value))
		else if (value < min && min != -9999)
		{
			std::cout << "\t\t\tError Message. Number can't be lower than " << min << std::endl;
		}
		else if (value > max && max != -9999)
		{
			std::cout << "\t\t\tError Message. Number can't be greater than" << max << std::endl;
		}
		else
		{
			break;
		}
	}
	

		return value;
} // end of int getFloatData()

// This function will get an integer value from the user
int getIntegerData(std::string prompt, int min, int max)
{
	int value;

	while (true)
	{
		std::cout << prompt;
		if (!(std::cin >> value))
		{
			std::cout << "\t\t\tError Message. Non numeric is entered" << std::endl;
			std::cin.clear(); // clear error buffer
			std::cin.ignore(120, '\n');  // c;lear upto 120 chars or it reaches an enter

		} // 	while (!(cin >> value))
		else if (value < min && min != -9999)
		{
			std::cout << "\t\t\tError Message. Number can't be lass than " << min << std::endl;
		}
		else if (value > max && max != -9999)
		{
			std::cout << "\t\t\tError Message. Number can't be greater than than " << max << std::endl;
		}
		else
		{
			break;
		}
	}

	return value;


} // end of int getIntegerData()

// This function will return a string data entered by users
std::string getStringData(std::string prompt)
{
	std::string value;

	std::cout << prompt;

	// Flush the input buffer.
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::getline(std::cin, value); // accepts spaces in the entry

	

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


