/*
-------------------------------------------------------------------------
Name:			Leon Thompson
Date:			11/10/2023
Project #:		7
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	This program creates a Date class that validates the creation of a
	proper date based on user input. If the date is valid, it is printed
	out in several formats.
-------------------------------------------------------------------------
*/

#include <iostream>		 // for cout, cin, endl
#include <string>        // for string

// Forward Declarations
class Date;


// Declare Prototypes
void PrintDateFormats(Date& date);
int GetIntegerData(std::string prompt);
void ClearCin();
void ProjectStart();
void ProjectEnd();



// Data Struct Containing Date Requirements
struct DateConstraints
{
	int MaxMonths = 12;
	int MinMonths = 1;
	int MaxDays = 31;
	int MinDays = 1;
	int MaxYear = 2022;
	int MinYear = 1900;
	int ThirtyDayMonths[4] = { 4, 6, 9, 11 };
	std::string StrMonths[12] = { 
		"January", "February", "March", "April", "May", "June", 
		"July", "August", "September", "October", "November", "December" 
	};
};


// This class defines, sets, validates and prints a date
class Date
{
	public:

		// The constructor initializes the day, month and year
		Date()
		{
			m_Day = 1;
			m_Month = 1;
			m_Year = 2020;

		}

		// This function sets the date
		bool SetDate(int day, int month, int year)
		{
			// Checks if date info is valid
			if (!IsValidDate(day, month, year))
			{
				return false;
			}
			
			m_Day = day;
			m_Month = month;
			m_Year = year;

			return true;

		} // end of SetDate()

		// This function checks if it is a leap year
		bool IsLeapYear(int year)
		{
			// Leap years are divisible by 4
			return year % 4 == 0;

		} // end of IsLeapYear()

		// Prints date in the American number format
		void PrintAmericanNumberFormat()
		{
			std::cout << m_Month << "/" << m_Day << "/" << m_Year << std::endl;

		} // end of PrintAmericanNumberFormat()

		// Prints date in the American name format
		void PrintAmericanNameFormat()
		{
			std::string& month = GetMonthName();
			std::cout << month << " " << m_Day << ", " << m_Year << std::endl;

		} // end of PrintAmericanNameFormat()

		// Prints date in the European name format
		void PrintEuropeanNameFormat()
		{
			std::string& month = GetMonthName();
			std::cout << m_Day << " " << month << " " << m_Year << std::endl;

		} // end of PrintEuropeanNameFormat()

	private:

		bool IsValidDate(int day, int month, int year) 
		{
			// Validate Value Ranges
			if (year < m_Constraints.MinYear || year > m_Constraints.MaxYear ||
				month < m_Constraints.MinMonths || month > m_Constraints.MaxMonths ||
				day < m_Constraints.MinDays || day > m_Constraints.MaxDays)
			{
				std::cout << "\t\t\tERROR: Date value(s) out of range. Valid Values: Day(1 - 31) | Month(1 - 12) | Year(1900 - 2020)" << std::endl;
				return false;
			}

			// Validate 31 day months
			if (day == 31)
			{
				for (int monthIndex = 0; monthIndex < 4; monthIndex++)
				{
					// Check if month should only have thirty days
					if (m_Constraints.ThirtyDayMonths[monthIndex] == month)
					{
						std::cout << "\t\t\tERROR: Month '" << GetMonthName(month) << "' only has 30 days" << std::endl;
						std::cout << std::endl;
						return false;
					}
				}
			} 

			// Validate February
			if (month == 2)
			{
				// Ensure Feb has 29 days or less
				if (day > 29)
				{
					std::cout << "\t\t\tERROR: February can not have more than 29 days." << std::endl;
					std::cout << std::endl;
					return false;
				}

				// Ensure that it is a leap year if Feb has 29 days
				else if (day == 29 && !IsLeapYear(year))
				{
					std::cout << "\t\t\tERROR: February only has a 29th day on leap years. " << year << " is not a leap year." << std::endl;
					std::cout << std::endl;
					return false;
				}
			}
		}

		// This function returns the object's month as a string
		std::string& GetMonthName()
		{
			return m_Constraints.StrMonths[m_Month - 1];
		}

		// This function returns the month parameter as a string
		std::string& GetMonthName(int month)
		{
			return m_Constraints.StrMonths[month - 1];
		}

	private:

		int m_Day;
		int m_Month;
		int m_Year;
		
		DateConstraints m_Constraints;

};



int main()
{
	// Declare variables
	int month;
	int day;
	int year;

	// Initialize variables
	Date date;

	ProjectStart();

	while (true)
	{
		// Get date data input
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Date Entry" << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		day = GetIntegerData("\tEnter the day: ");
		month = GetIntegerData("\tEnter the month: ");
		year = GetIntegerData("\tEnter the year: ");

		// Check if date was set correctly
		if (!date.SetDate(day, month, year))
		{
			// Restart loop if invalid date
			continue;
		}
		else
		{
			// Print Date Formats
			PrintDateFormats(date);
			break;
		}
		
	}

	
	ProjectEnd();

	return 0;
}

void PrintDateFormats(Date& date)
{
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Date Formats:" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "\tFormat 1 | ";
	date.PrintAmericanNumberFormat();
	std::cout << "\tFormat 2 | ";
	date.PrintAmericanNameFormat();
	std::cout << "\tFormat 3 | ";
	date.PrintEuropeanNameFormat();
	std::cout << std::endl;
}

// This functions clears the cin and then clears up to 120
// characters or hits enter.
void ClearCin()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

} // end of ClearCin()


// This function will get an integer value from the user
int GetIntegerData(std::string prompt)
{
	int value;
	std::string strValue;

	while (true)
	{
		std::cout << prompt;
		if (!(std::cin >> value))
		{
			std::cout << "\t\t\tError Message. A non-numeric value was entered" << std::endl;
			ClearCin();

		}
		else
		{
			break;
		}
	}// 	while (!(cin >> value))

	ClearCin();

	return value;


} // end of int getIntegerData()


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