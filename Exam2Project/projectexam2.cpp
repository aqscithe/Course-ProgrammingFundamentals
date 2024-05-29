/*
-------------------------------------------------------------------------
Name:			Leon Thompson
Date:			10/27/2023
Project #:		Exam 2
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	The program acts as a shopping center kiosk where menu items can be 
	purchased by the user. The user can browse the list of available
	items, and sees a summary of their purchases after each transaction.
	Upon quiting, the user sees a summary of all their transactions for
	the day.
-------------------------------------------------------------------------
*/

#include <iostream>				// for cin, cout, std::endl
#include <iomanip>				// for fixed, setprecision
#include <string>				// for string
#include <cctype> 				//for toupper()
#include <fstream>



// Global Const Values
const int MAX_ITEM_COUNT = 25;
const float SALES_TAX_PERCENT = 8.25f;

// Grocery Menu Item
struct GroceryItem
{
	std::string Name;
	float Price;
};

// Grocery Cart Item
struct GroceryItemCart
{
	std::string Name;
	int Pounds;
	float Cost;
};



// Decleration of prototype 
void projectStart();
void projectEnd();
bool isInteger(const std::string& str);
int getIntegerData(std::string);
float getFloatData(std::string);
char getCharData(std::string);
std::string getStringData(std::string);
void clearCin();
void greetUser();
bool getGroceryMenu(std::string, GroceryItem [MAX_ITEM_COUNT], int &);
void displayStoreHeader();
void displayMainMenu();
void displayShoppingMenu(GroceryItem [MAX_ITEM_COUNT], int);
void displayTransactionSummary(int, GroceryItemCart [25], float, float, float);
void obtainShoppingSelection(std::string&, char&);
void handleTransactionCompleted(float&, float, float&, bool&, int, GroceryItemCart [25]);
void handleTransactionCancelled(bool&);
void updateCartItems(int&, GroceryItemCart [25], int, GroceryItem&, float, float&);



int main()
{
	// setting to 2 decimal places
	std::cout << std::fixed << std::setprecision(2);

	// Displays start of project 
	projectStart();

	// Declare Variables
	bool obtainedGroceryMenu;
	int  groceryItemCount;
	char mainSelection;
	bool exitRunLoop;
	bool cancelled;
	bool completed;
	std::string prompt;
	int itemsInCart;
	float subTotal;
	float total;
	float salesTax;
	

	// Initialize Variables
	GroceryItem groceryMenu[MAX_ITEM_COUNT];
	GroceryItemCart groceryItemsCart[MAX_ITEM_COUNT];
	obtainedGroceryMenu = false;
	exitRunLoop = false;
	cancelled = false;
	completed = false;
	itemsInCart = 0;
	subTotal = 0.f;
	total = 0.f;

	// -- Validate Grocery Menu -- //

	// Read from menu
	obtainedGroceryMenu = getGroceryMenu("menu.txt", groceryMenu, groceryItemCount);

	// Verify there was no issue reading from menu file
	if (!obtainedGroceryMenu)
	{
		std::cout << "\t\t\tERROR. An issue occured obtaining the list of grocery items. Closing..." << std::endl;
		return -1;
	}


	// -- Main run loop -- //

	while (true)
	{
		displayMainMenu();

		mainSelection = getCharData("Make Your Selection: ");

		switch (mainSelection)
		{
			
			// Shopping Selection
			case 'S':
			{
				// Declare shopping specific variables
				GroceryItem  item;
				std::string  shoppingSelection;
				char selection;
				int shoppingItem;
				int pounds;
				float cost;

				while (true)
				{
					// Initialize shopping variables
					shoppingItem = 0;
					pounds = 0;

					displayShoppingMenu(groceryMenu, groceryItemCount);

					obtainShoppingSelection(shoppingSelection, selection);

					
					// A string longer than 2 chars results in error
					// because there is a max of 25 menu items
					if (shoppingSelection.length() > 2)
					{
						std::cout << "\t\t\tERROR. Selection impossible. Too many characters entered." << std::endl;
						continue;
					}

					// Check if user entered a char
					else if (shoppingSelection.length() == 1 && !isdigit(selection))
					{
						// If char is T
						if (toupper(selection) == 'T')
						{
							handleTransactionCompleted(salesTax, subTotal, total, completed, itemsInCart, groceryItemsCart);
							break;
						}
						// If char is X
						else if (toupper(selection) == 'X')
						{
							handleTransactionCancelled(cancelled);
							break;
						}
						
					}

					// Check if user entered an integer
					else if (isInteger(shoppingSelection))
					{
						// Convert selection from str to int
						shoppingItem = std::stoi(shoppingSelection);

						// Verify integer is a value on the grocery menu
						if (shoppingItem > groceryItemCount || shoppingItem < 1)
						{
							std::cout << "\n\t\t\tERROR. The selection entered is too large or small. Enter a value between 1 and" << 
								groceryItemCount << std::endl;
							continue;
						}
					}

					// Set grocery item based on user selection
					item = groceryMenu[shoppingItem - 1];

					// Obtain pounds of item to be purchased
					prompt = "Pounds of " + item.Name + ": ";
					pounds = getIntegerData(prompt);

					// Calculate and display cost
					cost = pounds * item.Price;
					std::cout << "Cost: " << pounds << " lbs of " << item.Name << ": $" << cost << std::endl;

					updateCartItems(itemsInCart, groceryItemsCart, pounds, item, cost, subTotal);

					displayStoreHeader();

				} // end of while(true)

				// Check if transaction has completed or cancelled
				if (cancelled || completed)
				{
					std::cout << "\nPress ENTER to continue. ";

					// Wait for newline character input
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}

				
				break;
			} // end of case 'S'

			// Quit Selection
			case 'Q':
			case 'X':
			{
				std::cout << "\nExiting...\n" << std::endl;
				exitRunLoop = true;
				break;
			} // end of case 'X'

			default:
			{
				std::cout << "\t\tINTERNAL ERROR. Menu type does not exist." << std::endl;
				break;
			}
		}

		// Reset completed and cancelled values if either is true
		if (completed || cancelled)
		{
			completed = false;
			cancelled = false;

			continue;
		}

		// Otherwise if user selected quit, exit the run loop
		else if (exitRunLoop)
		{
			break;
		}

		
	}
	
	// Display Transaction Summary
	std::cout << "\tDaily Sales Transactions Summary" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << std::endl;
	displayTransactionSummary(itemsInCart, groceryItemsCart, subTotal, salesTax, total);
	std::cout << std::endl;

	// Displays end of project
	projectEnd();

	return 0;

} // end of main()

// This function updates the user's cart with the item selected, pounds and cost
void updateCartItems(int& itemsInCart, GroceryItemCart  groceryItemsCart[25], int pounds, GroceryItem& item, float cost, float& subTotal)
{
	
	// Declare variables
	bool newItem;
		
	// Initialize variables
	newItem = true;

	// Loop through items in user's cart
	for (int cartItem = 0; cartItem < itemsInCart; cartItem++)
	{
		// Check if user already has item in their cart
		if (groceryItemsCart[cartItem].Name == item.Name)
		{
			// Update item's pounds and cost
			groceryItemsCart[cartItem].Pounds += pounds;
			groceryItemsCart[cartItem].Cost += cost;

			// Update subtotal
			subTotal += cost;

			// Indicate that this is not a new item
			newItem = false;

		}
	}

	if (newItem)
	{
		// Add new item to cart
		groceryItemsCart[itemsInCart].Name = item.Name;
		groceryItemsCart[itemsInCart].Pounds = pounds;
		groceryItemsCart[itemsInCart].Cost = cost;

		// Update subtotal
		subTotal += cost;

		// Increment itemsInCart
		itemsInCart++;

	}
	
} // end of updateCartItems()

// This function handles the case where the user cancels a transaction
void handleTransactionCancelled(bool& cancelled)
{
	cancelled = true;

	std::cout << "\nTransaction Cancelled!!" << std::endl;
} // end of handleTransactionCancelled()

// This function calculates sales tax based on the subtotal and the total sales amount, then displays the reuslts
void handleTransactionCompleted(float& salesTax, float subTotal, float& total, bool& completed, int itemsInCart, GroceryItemCart  groceryItemsCart[25])
{
	// Calculate sales info
	salesTax = subTotal * SALES_TAX_PERCENT / 100.f;
	total = subTotal + salesTax;
	completed = true;

	// Display Grocery List
	std::cout << "\nGrocery List" << std::endl;
	displayTransactionSummary(itemsInCart, groceryItemsCart, subTotal, salesTax, total);

} // end of handleTransactionCompleted()

// This function gets the shopping menu item selected by the user and converts it to a char
void obtainShoppingSelection(std::string& shoppingSelection, char& selection)
{
	// Get input from user
	shoppingSelection = getStringData("Make Your Selection: ");

	// Converting to char
	selection = shoppingSelection[0];
}

// This function displays a summary of the user's transactions
void displayTransactionSummary(int itemsInCart, GroceryItemCart  groceryItemsCart[25], float subTotal, float salesTax, float total)
{
	// Loop through cart items
	for (int item = 0; item < itemsInCart; item++)
	{
		// Display each cart item
		std::cout << std::left << std::setw(15) << groceryItemsCart[item].Name <<
			std::setw(4) << groceryItemsCart[item].Pounds << std::setw(7) << " lbs. " << "$" << groceryItemsCart[item].Cost <<
			std::endl;
	}

	// Display summary info
	std::cout << "------------------------------------------" << std::endl;
	std::cout << std::left << std::setw(26) << "Sub Total" << "$" << subTotal << std::endl;
	std::cout << std::left << std::setw(10) << "Sales Tax (" << SALES_TAX_PERCENT << std::setw(11) << "%) " << "$" << salesTax << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << std::left << std::setw(26) << "Total Sales" << "$" << total << std::endl;

} // end of displayTransactionSummary()


// This function displays the main menu
void displayMainMenu()
{
	displayStoreHeader();
	std::cout << "Main Menu" << std::endl;
	std::cout << std::endl;
	std::cout << "S\tShop" << std::endl;
	std::cout << "Q\tQuit" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

} // end of displayMainMenu()

// This function displays the shopping menu
void displayShoppingMenu(GroceryItem groceryMenu[MAX_ITEM_COUNT], int groceryItemCount)
{
	// Declare variables
	int lineNum;

	displayStoreHeader();

	std::cout << "Shopping" << std::endl;

	// Loop through grocery menu
	for (int item = 0; item < groceryItemCount; item++)
	{
		lineNum = item + 1;
		std::cout << std::left << std::setw(3) << lineNum << std::setw(15) << groceryMenu[item].Name << "($" << groceryMenu[item].Price << " per lb.)" << std::endl;
	}
	
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	std::cout << "T\tComplete Transaction" << std::endl;
	std::cout << "X\tCancel Transaction" << std::endl;
	std::cout << std::endl;

} // end of displayShoppingMenu()

// This function reads the grocery menu items from the menu file
bool getGroceryMenu(std::string filename, GroceryItem groceryMenu[MAX_ITEM_COUNT], int& groceryItemCount)
{
	// Declare variables
	std::ifstream inputFile;
	std::string   line;
	int lineNumber;
	int itemIndex;

	// Initialize variables
	lineNumber = 1;
	itemIndex = 0;

	// Open file
	inputFile.open(filename);

	// Verify file opened correctly
	if (!inputFile)
	{
		std::cout << "\t\t\tERROR. File did not open correctly." << std::endl;
		return false;
	}

	// Loop through lines in file
	while (std::getline(inputFile, line))
	{
		// Odd line numbers contain item names
		if (lineNumber % 2 == 1)
		{
			groceryMenu[itemIndex].Name = line;
		}
		// Even line numbers contain item prices
		else if (lineNumber % 2 == 0)
		{
			groceryMenu[itemIndex].Price = std::stof(line);

			// Increment item index after every price line
			itemIndex++;
		}

		// Increment line number on every line
		lineNumber++;
	}
	
	// Getting count of grocery menu items
	groceryItemCount = itemIndex;

	return true;
} // end of getGroceryItems()

// This function displays the store header
void displayStoreHeader()
{
	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "SAFARI GROCERY STORE" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;

} // end of displayStoreHeader()


// This function greets the user
void greetUser()
{
	std::cout << "WELCOME TO..." << std::endl;
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

	std::cout << prompt;
	std::cin >> value;

	clearCin();

	value = toupper(value);

	return value;


} // end of int getCharData()

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
			clearCin();

			continue;

		} // 	while (!(cin >> value))

		break;
	}

	clearCin();

	return value;
} // end of int getFloatData()


// This function takes a string and returns true if it is an integer
bool isInteger(const std::string& str) 
{
	// Empty string is not an integer.
	if (str.empty()) 
	{
		return false; 
	}

	size_t start = 0;
	if (str[0] == '-' || str[0] == '+') 
	{
		// Skip the optional sign.
		start = 1; 
	}

	// Loop through chars in str
	for (size_t i = start; i < str.length(); ++i) 
	{
		// Non-digit character found.
		if (!std::isdigit(str[i])) 
		{
			return false; 
		}
	}

	return true;
} // end of isInteger()

// This function will get an integer value from the user
int getIntegerData(std::string prompt)
{
	int value;

	while (true)
	{
		std::cout << prompt;
		if (!(std::cin >> value))
		{
			std::cout << "\t\t\tError Message. Non numeric is entered" << std::endl;
			clearCin();

		} 
		else if (value < 0)
		{
			std::cout << "\t\t\tERROR. Value can not be negative" << std::endl;
		}

		break;
	}// 	while (!(cin >> value))

	clearCin();

	return value;


} // end of int getIntegerData()

// This function will return a string data entered by users
std::string getStringData(std::string prompt)
{
	std::string value;

	std::cout << prompt;	

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


