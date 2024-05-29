/*
-------------------------------------------------------------------------
Name:			Leon Thompson
Date:			12/03/2023
Project #:		8
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	The program reads employee meta and timesheet data and calculates
	their pay information (gross, net, tax, insurance). The pay report
	is output to a txt file called payrollReport.txt and an error 
	report is printed to std out.
-------------------------------------------------------------------------
*/


#include <string>
#include <iostream>
#include <iomanip>				// for fixed, setprecision
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>


// Forward Declarations
class Employee;
struct Payroll;


// Decleration of prototype 
void ReadEmployeeFile(Employee  employees[100], int&);
void ReadEmployeeTimeData(Employee  employees[100], float&, float&, Payroll payroll[100], std::vector<std::string>&, int&);
Payroll CalculateEmployeePay(Employee&, float);
float CalculateGrossPay(int, float, float);
void DisplayErrorReport(std::vector<std::string>&, int);
void WritePayrollReport(Employee employees[100], Payroll payroll[100], int, float, float);
void ProjectStart();
void ProjectEnd();
void GreetUser();


// This class holds information about employees
class Employee
{
public:
	// Default constructor to initialize member variables
	Employee()
	{
		m_ID = 0;
		m_PayRate = 0.f;
		m_Dependents = 0;
		m_Type = -1;
	}

	// Constructor takes in variables corresponding to members and intializes them
	Employee(int ID, std::string name, float payRate, int dependents, int employeeType)
		: m_ID(ID), m_PayRate(payRate), m_Dependents(dependents), m_Type(employeeType)
	{
		strncpy_s(m_Name, name.c_str(), 20);
	}

	~Employee() = default;

	// -- Getter Functions -- //

	int GetID() 
	{
		return m_ID;
	}

	const char* GetName()
	{
		return m_Name;
	}

	float GetPayrate()
	{
		return m_PayRate;
	}

	int GetDependents()
	{
		return m_Dependents;
	}

	int GetType()
	{
		return m_Type;
	}

private:
	 
	int   m_ID;
	char  m_Name[21];
	float m_PayRate;
	int   m_Dependents;
	int   m_Type;

}; // end of Employee class

// This struct organizes payroll information
struct Payroll
{
	Payroll()
	{
		ID = 0;
		Tax = 0.f;
		Insurance = 0.f;
		GrossPay = 0.f;
		NetPay = 0.f;
	}

	Payroll(int id, float tax, float insurance, float gross, float net) :
		ID(id), Tax(tax), Insurance(insurance), GrossPay(gross), NetPay(net)
	{}

	int ID;
	float Tax;
	float Insurance;
	float GrossPay;
	float NetPay;
};



int main()
{

	// setting to 2 decimal places
	std::cout << std::fixed << std::setprecision(2);

	// Display start of project
	ProjectStart();


	// Declare variables
	Employee employees[100];
	Payroll payroll[100];
	int employeeCount;
	std::vector<std::string> unprocessedTransactions;
	int processedTransactionCount;
	float totalGross;
	float totalNet;

	// Initialize variables
	employeeCount = 0;
	processedTransactionCount = 0;
	totalGross = 0.f;
	totalNet = 0.f;

	GreetUser();

	ReadEmployeeFile(employees, employeeCount);

	ReadEmployeeTimeData(employees, totalGross, totalNet, payroll, unprocessedTransactions, processedTransactionCount);

	WritePayrollReport(employees, payroll, employeeCount, totalGross, totalNet);

	std::cout << std::endl;
	std::cout << "REPORTS PROCESSING COMPLETE. SEE REPORTS" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	DisplayErrorReport(unprocessedTransactions, processedTransactionCount);

	ProjectEnd();

} // end of main()


// This function reads the employee text file places the info in an array
void ReadEmployeeFile(Employee  employees[100], int& employeeCount)
{
	std::fstream inputFile;
	std::string line;
	inputFile.open("employees.txt");

	if (!inputFile.is_open())
	{
		std::cout << "\t\t\tERROR. File did not open correctly." << std::endl;
		exit(1);
	}

	// Loop through lines in employee file
	while (std::getline(inputFile, line))
	{
		
		// Employee declaration variables
		int   id;
		std::string name;
		std::string part;
		float payRate;
		int   dependents;
		int   type;

		// Create stream from line
		std::stringstream ss(line);

		// Read employee id
		ss >> id;

		// skip space after id
		ss.ignore();

		// Read employee name
		while (ss.peek() != '\t')
		{
			ss >> part;
			if (!name.empty())
			{
				name += " ";
			}
			name += part;
		}

		// Retrieve remaining line data
		ss >> payRate >> dependents >> type;

		// Initialize and add employee to array
		employees[id - 1] = Employee(id, name.c_str(), payRate, dependents, type);

		// Increment employee count
		employeeCount++;

		
	}

	inputFile.close();
}

// This function reads the employee timesheet file calculates corresponding pay info
void ReadEmployeeTimeData(Employee  employees[100], float& totalGross, float& totalNet, Payroll payroll[100], std::vector<std::string>& unprocessedLines, int& processedTransactionCount)
{
	std::fstream inputFile;
	std::string line;
	int index = 0;
	inputFile.open("weekly_timesheet.txt");


	if (!inputFile.is_open())
	{
		std::cout << "\t\t\tERROR. File did not open correctly." << std::endl;
		exit(1);
	}

	// Loop through lines in employee file
	while (std::getline(inputFile, line))
	{
		// Employee declaration variables
		int id;
		float hoursWorked;

		// Create string stream from line
		std::stringstream ss(line);

		while (ss >> id >> hoursWorked)
		{
			// If data is invalid add to array of unprocessed lines
			if (id < 1 || employees[id - 1].GetID() == 0 || hoursWorked < 0)
			{
				unprocessedLines.emplace_back(line);
			}
			else
			{
				// Calculate employee pay info
				payroll[index] = CalculateEmployeePay(employees[id - 1], hoursWorked);
				
				// Update Pay totals
				totalGross += payroll[index].GrossPay;
				totalNet += payroll[index].NetPay;

				processedTransactionCount++;

				// Increment payroll index
				index++;
			}
		}
	}
} // end of ReadEmployeeTimeData()


// This function calculates employee pay data and returns it
Payroll CalculateEmployeePay(Employee& employee, float hoursWorked)
{
	// Declare variables
	float tax;
	float insurance;
	float gross;
	float net;

	float taxRate = 15.f;
	float perDependentPrice = 30.f;

	// Pay calculations
	gross = CalculateGrossPay(employee.GetType(), employee.GetPayrate(), hoursWorked);
	tax = gross * taxRate / 100.f;
	insurance = employee.GetDependents() * perDependentPrice;
	net = gross - tax - insurance;

	return
	{
		employee.GetID(),
		tax,
		insurance,
		gross,
		net
	};

} // endo of CalculateEmployeePay()

// This function calculates a user's Gross Pay
float CalculateGrossPay(int type, float payRate, float hoursWorked)
{
	// Declare Variables
	float grossPay;

	// Initialize Variables
	grossPay = 0.f;

	switch (type)
	{
		// Union Employee
		case 0:
		{
			// Applies overtime pay rate to any hours worked over 40
			if (hoursWorked > 40)
			{
				float overtimeRate;

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
		case 1:
		{
			grossPay = payRate * hoursWorked;
			break;
		}
	}

	return grossPay;
} // end of calculateGrossPay

// This function writes payroll report to a file
void WritePayrollReport(Employee employees[100], Payroll payroll[100], int employeeCount, float totalGross, float totalNet)
{
	// Create output file
	std::ofstream outputFile("payrollReport.txt");

	// Verify file has opened
	if (!outputFile.is_open())
	{
		std::cout << "\t\t\tERROR. Output file did not open correctly." << std::endl;
		exit(1);
	}

	// Format decimal to 2 places
	outputFile << std::fixed << std::setprecision(2);

	// Report title
	outputFile << "-----------------------------------------------------------------------------------------------" 
		<< std::endl;
	outputFile << "PAYROLL REPORT" << std::endl;
	outputFile << "-----------------------------------------------------------------------------------------------" 
		<< std::endl;
	
	// Create Table Header Row
	outputFile << std::left << std::setw(10) << "ID"
		<< std::setw(22) << "Name"
		<< std::setw(16) << "Tax"
		<< std::setw(16) << "Insurance"
		<< std::setw(21) << "Gross Pay"
		<< std::setw(15) << "Net Pay"
		<< std::endl;
	outputFile << "-----------------------------------------------------------------------------------------------"
		<< std::endl;

	// Loop over employee payroll data
	for (int employee = 0; employee < employeeCount; employee++)
	{
		outputFile << std::left << std::setw(10) << payroll[employee].ID
			<< std::setw(22) << employees[payroll[employee].ID - 1].GetName()
			<< "$" << std::setw(15) << payroll[employee].Tax
			<< "$" << std::setw(15) << payroll[employee].Insurance
			<< "$" << std::setw(20) << payroll[employee].GrossPay
			<< "$" << std::setw(15) << payroll[employee].NetPay
			<< std::endl;
	}

	outputFile << "-----------------------------------------------------------------------------------------------"
		<< std::endl;
	outputFile << "Number of Employees: " << employeeCount << std::endl;
	outputFile << "Total Gross Pay: $" << totalGross << std::endl;
	outputFile << "Total Net Pay: $" << totalNet << std::endl;
	
	outputFile.close();
} // end of WritePayrollReport

// This function displays unprocessed transactions
void DisplayErrorReport(std::vector<std::string>& unprocessedTransactions, int processedTransactionCount)
{
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Error and Control Report" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "The following items could not be processed:" << std::endl;
	std::cout << std::endl;
	for (auto& transaction : unprocessedTransactions)
	{
		std::cout << transaction << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Correctly processed transactions: " << processedTransactionCount << std::endl;
	std::cout << std::endl;

} // end of DisplayErrorReport()

// This function greets the user
void GreetUser()
{
	std::cout << "WELCOME TO MAPTech Corp. Payroll Processor" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
} // end of greetUser()


// The function will display the start of the project 
void ProjectStart()
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
void ProjectEnd()
{
	std::cout << "-----------------------------" << std::endl;
	std::cout << "End of Project" << std::endl;
	std::cout << "-----------------------------" << std::endl;
} // end of projectEnd()
