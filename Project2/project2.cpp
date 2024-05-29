/*
-------------------------------------------------------------------------
Name:           Leon Thompson
Date:			September  24, 2023
Project #:		2
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	Retrieves input from users regarding their name, account balance and
	transaction type. Calculates daily deposits, withdrawals, and 
	provides a final balance.
-------------------------------------------------------------------------
*/

#include <iostream>				// for std::cin, std::cout, std::endl
#include <iomanip>				// for fixed, setprecision
#include <string>				// for string


// Decleration of prototype 
void ProjectStart();
void ProjectEnd();
int GetIntegerData(std::string);
float GetFloatData(std::string);
char GetCharData(std::string);
std::string GetStringData(std::string);
void MainMenu();
void ClearCin();
void Greeting(std::string& name, float& userBalance);
void WithdrawFunds(float& transactionAmount, float& userBalance, float overdraftFee, 
	float serviceCharge, float& totalCharges);
void DepositFunds(float& transactionAmount, float& userBalance, float& totalCharges, 
	float serviceCharge);
void EndTransactions(std::string& name, float& userBalance, float totalCharges);

int main()
{
	// setting to 2 decimal places
	std::cout << std::fixed << std::setprecision(2);

	// Displays start of project 
	ProjectStart();

	// Declare main() variables
	std::string name;
	float userBalance;
	char transactionType;
	float serviceCharge;
	float totalCharges;
	float overdraftFee;
	bool exitRunLoop;

	// Initialize main() variables
	userBalance = 0.f;
	serviceCharge = 0.25f;
	totalCharges = 0.f;
	overdraftFee = 100.f;
	exitRunLoop = false;

	
	Greeting(name, userBalance);

	// Run Loop
	while (true)
	{
		MainMenu();

		transactionType = GetCharData("\nSelect Transaction: ");
		
		switch (transactionType)
		{
			// Declare switch variables
			float transactionAmount;

			// Withdrawal transaction
			case 'W':
			{
				WithdrawFunds(transactionAmount, userBalance, overdraftFee, serviceCharge, 
					totalCharges);
				break;
			}

			// Deposit transaction
			case 'D':
			{
				DepositFunds(transactionAmount, userBalance, totalCharges, serviceCharge);
				break;
			}

			// End of Transactions
			case 'E':
			{
				EndTransactions(name, userBalance, totalCharges);
				exitRunLoop = true;
				break;
			}

			// Invalid Transaction
			default:
			{
				std::cout << "\t\tERROR: Invalid Transaction Selection." << std::endl;
				break;
			}

		} // switch (transactionType)

		if (exitRunLoop)
		{
			break;
		}
		
	} // while (true)

	// Displays end of project
	ProjectEnd();

	return 0;

}

// This function stops all transactions and displays an account summary
void EndTransactions(std::string& name, float& userBalance, float totalCharges)
{
	// Display account summary
	std::cout << "\nAccount Summary" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "\tName: " << name << std::endl;
	std::cout << "\tCurrent Balance: $" << userBalance << std::endl;
	std::cout << "\tAccrued Service/Overdraft Charges: $" << totalCharges << std::endl;

	// Process service charges and overdraft fees
	userBalance -= totalCharges;

	// Display final balance
	std::cout << "\n\tFinal Balance: $" << userBalance << std::endl;
	std::cout << std::endl;

} // end of EndTransactions()

// This function processes and calculates the deposits into the user's account.
void DepositFunds(float& transactionAmount, float& userBalance, float& totalCharges, 
	float serviceCharge)
{
	transactionAmount = GetFloatData("Enter transaction amount: $");

	// Update balance and service charges
	userBalance += transactionAmount;
	totalCharges += serviceCharge;

	// Display deposit info
	std::cout << "\tDeposit Processed..." << std::endl;
	std::cout << "\tService Charge: $" << serviceCharge << " for deposit." << std::endl;

	// Display updated balance info
	std::cout << "\n\tCurrent Balance: $" << userBalance << std::endl;
	std::cout << "\tAccrued Service/Overdraft Charges: $" << totalCharges << std::endl;

} // end of DepositFunds

// This function processes and calculates the withdrawals from the user's account.
void WithdrawFunds(float& transactionAmount, float& userBalance, float overdraftFee, 
	float serviceCharge, float& totalCharges)
{
	transactionAmount = GetFloatData("Enter transaction amount: $");

	if (transactionAmount > userBalance)
	{
		// Apply overdraft if transaction exceeds user's balance
		std::cout << "\tERROR: Cannot withdraw more than available balance." << std::endl;
		std::cout << "\tTransaction Cancelled." << std::endl;
		std::cout << "\tOverdraft Fee: $" << overdraftFee << std::endl;
		std::cout << "\tService Charge: $" << serviceCharge << " for withdrawal." << std::endl;
		totalCharges += overdraftFee + serviceCharge;
	}
	else
	{
		// Update balance and service charges
		userBalance -= transactionAmount;
		totalCharges += serviceCharge;

		// Display withdrawal info
		std::cout << "\tWithdrawal Processed..." << std::endl;
		std::cout << "\tService Charge: $" << serviceCharge << " for withdrawal." << std::endl;
	}

	// Display updated balance info
	std::cout << "\n\tCurrent Balance: $" << userBalance << std::endl;
	std::cout << "\tAccrued Service/Overdraft Charges: $" << totalCharges << std::endl;

} // end of WithdrawFunds


// This function greets the user and obtains their name
// and beginning balance.
void Greeting(std::string& name, float& userBalance)
{
	std::cout << "\nWelcome to Sparks Funding, Inc." << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	name = GetStringData("Name: ");
	userBalance = GetFloatData("Enter beginning balance: $");

}// end of Greeting()

// This function displays a menu with all the user transaction options.
void MainMenu()
{
	std::cout << "\n----------------------------------------------------------------" << std::endl;
	std::cout << "Available Transaction Types:" << std::endl;
	std::cout << "\tW.........Withdrawal" << std::endl;
	std::cout << "\tD.........Deposit" << std::endl;
	std::cout << "\tE.........End Transaction" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;

} // end of MainMenu()


// This function will return an integer data entered by users
int GetIntegerData(std::string prompt)
{
	int value;
	std::cout << prompt;
	std::cin >> value;

	return value;

} // end of int getIntegerData(std::string prompt)

// This function will return a float data entered by users
float GetFloatData(std::string prompt)
{
	float value;

	while (true)
	{
		std::cout << prompt;
		while (!(std::cin >> value))
		{
			std::cout << "\t\tERROR: Invalid entry. Enter a NUMBER value." << std::endl;
			ClearCin();
			std::cout << prompt;
		} // while (!(cin >> value))

		// Clear cin buffer
		ClearCin();

		if (value > 0.f)
		{
			return value;
		}

		std::cout << "\t\tERROR: Invalid entry. Number must be greater than 0." << std::endl;
	} // while (true)
	

	return value;

} // end of int getFloatData(std::string prompt)

// This functions clears the cin and then clears up to 120
// characters or hits enter.
void ClearCin()
{
	std::cin.clear();  
	std::cin.ignore(120, '\n');

} // end of ClearCin()


// This function will return a char data entered by users
char GetCharData(std::string prompt)
{
	char value;

	while (true)
	{
		std::cout << prompt;
		std::cin >> value;

		// Clear cin buffer
		ClearCin();

		value = toupper(value);

		if (value == 'D' || value == 'E' || value == 'W')
		{
			return value;
		}

		std::cout << "\t\tERROR: Invalid entry. Incorrect character selected." << std::endl;

	}	// while (true)

} // end of int GetCharData(std::string prompt)

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
	std::cout << "Project 2" << std::endl;
	std::cout << "Written by: Leon Thompson" << std::endl;
	std::cout << "Objectives" << std::endl;
	std::cout << "\tCalculates daily deposits, withdrawals, and provides a final balance." << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
} // end of ProjectStart()

// The function will display the end of the project 
void ProjectEnd()
{
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "End of Project 2" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
} // end of ProjectEnd()

