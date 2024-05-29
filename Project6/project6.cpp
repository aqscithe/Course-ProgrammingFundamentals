/*
-------------------------------------------------------------------------
Name:			Leon Thompson
Date:			10/29/2023
Project #:		6
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	This program compiles a list of students 3 exam grades and assigns a
	score(average of the 3) The students are then assigned a letter grade 
	and a class average is calculated. After sorting the students by 
	score, a semester summary displays the students, their test grades,
	letter grades, as well as the class average and number of students
	to receive each grade.
-------------------------------------------------------------------------
*/

#include <iostream>				// for cin, cout, std::endl
#include <iomanip>				// for fixed, setprecision
#include <string>				// for string
#include <cctype> 				//for toupper()
#include <fstream>


// Contains student name, test scores and average score
struct TestScore
{
	std::string Name;
	int Tests[3];
	float Score;
};

// Contains a count of letter grades earned by the class
struct LetterGradeTally
{
	int A;
	int B;
	int C;
	int D;
	int F;

	LetterGradeTally()
	{
		A = 0;
		B = 0;
		C = 0;
		D = 0;
		F = 0;
	}
};

// Decleration of prototype 
void projectStart();
void projectEnd();
bool isInteger(const std::string& str);
int getIntegerData(std::string);
int getIntegerData(std::string, const int, const int);
float getFloatData(std::string);
char getCharData(std::string);
std::string getStringData(std::string, const int);
void clearCin();
void greetUser();
void inputStudentScores(TestScore*, const int);
void sortScores(TestScore*, const int);
void calculateClassAverage(TestScore*, const int, float&);
void displaySemesterSummary(TestScore*, const int, float);
void calculateLastTestWidth(TestScore* currentScore, int& startPoint, int& lastTestWidth);
char getLetterGrade(float);
void updateLetterGradeTally(const char, LetterGradeTally&);


int main()
{
	// setting to 2 decimal places
	std::cout << std::fixed << std::setprecision(2);

	// Displays start of project 
	projectStart();

	greetUser();

	// Declare Variables
	TestScore* scores;
	int studentCount;
	float classAverage;

	// Initialize Variables
	scores = nullptr;
	studentCount = 0;

	// Gets the number of students in the class
	studentCount = getIntegerData("\tEnter the number of students in your class: ");

	// Quits the program if there are no students
	if (studentCount == 0)
	{
		std::cout << "No students to enter. Closing program..." << std::endl;
		return 0;
	}

	// Allocating TestScores based on the number of students using new keyword
	scores = new TestScore[studentCount];

	inputStudentScores(scores, studentCount);

	sortScores(scores, studentCount);

	calculateClassAverage(scores, studentCount, classAverage);

	displaySemesterSummary(scores, studentCount, classAverage);

	// Free memory allocated with new
	delete[] scores;
	
	// Displays end of project
	projectEnd();

	return 0;

} // end of main()

// This function takes a number score as a parameter and returns the corresponding
// letter grade
char getLetterGrade(float score)
{
	if (score >= 90)
	{
		return 'A';
	}
	else if (score >= 80)
	{
		return 'B';
	}
	else if (score >= 70)
	{
		return 'C';
	}
	else if (score >= 60)
	{
		return 'D';
	}

	return 'F';
} // end of getLetterGrade()

// This function updates the tally for the different letter grades received
void updateLetterGradeTally(const char letterGrade, LetterGradeTally& tally)
{
	if (letterGrade == 'A')
	{
		tally.A++;
	}
	else if (letterGrade == 'B')
	{
		tally.B++;
	}
	else if (letterGrade == 'C')
	{
		tally.C++;
	}
	else if (letterGrade == 'D')
	{
		tally.D++;
	}
	else if (letterGrade == 'F')
	{
		tally.F++;
	}
} // end of updateLetterGradeTally()


// This functions displays a summary of the student's scores and letter grades
void displaySemesterSummary(TestScore* scores, const int studentCount, float classAverage)
{
	// Declare Variables
	TestScore* currentScore;
	LetterGradeTally tally;
	char letterGrade;

	// Table Title
	std::cout << "----------------------------------------------" << std::endl;
	std::cout << "Semester Summary: Bone Anatomy Class" << std::endl;
	std::cout << "----------------------------------------------" << std::endl;

	// Table Header
	std::cout << std::left << std::setw(31) << "Name" << std::setw(14) << "Scores" << std::setw(2) << 
		"Letter Grade" << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;

	// Loop Through Student Scores
	for (int student = 0; student < studentCount; student++)
	{
		// Declare Loop Variables
		int lastTestWidth;
		int startPoint;

		// Initialize Variables
		startPoint = 0;
		currentScore = &scores[student];
		

		// Determine the width of last test based on digits in score
		calculateLastTestWidth(currentScore, startPoint, lastTestWidth);


		// Get Letter Grade Info
		letterGrade = getLetterGrade(currentScore->Score);
		updateLetterGradeTally(letterGrade, tally);

		// Display Each Student's Score Info
		std::cout << std::left << std::setw(31) << currentScore->Name << currentScore->Tests[0] << 
			"," << currentScore->Tests[1] << "," << std::setw(lastTestWidth) << currentScore->Tests[2] <<
			std::setw(2) << letterGrade << std::endl;
	}

	std::cout << "----------------------------------------------------------" << std::endl;

	// Displaying Aggregated Student Data
	std::cout << std::left << std::setw(31) << "Number of Students" << studentCount << std::endl;
	std::cout << std::left << std::setw(31) << "Class Average" << classAverage << std::endl;
	std::cout << std::left << std::setw(31) << "Number of A's" << tally.A << std::endl;
	std::cout << std::left << std::setw(31) << "Number of B's" << tally.B << std::endl;
	std::cout << std::left << std::setw(31) << "Number of C's" << tally.C << std::endl;
	std::cout << std::left << std::setw(31) << "Number of D's" << tally.D << std::endl;
	std::cout << std::left << std::setw(31) << "Number of F's" << tally.F << std::endl;
	std::cout << std::endl;

} // end of displaySemesterSummary()

// This function calculates the width of tests scores in the semester summary
void calculateLastTestWidth(TestScore* currentScore, int& startPoint, int& lastTestWidth)
{
	for (int test = 0; test < 3; test++)
	{
		// Only the first two tests affect the start point of the cursor
		if (test != 2)
		{
			// Add 3 for 3 digits
			if (currentScore->Tests[test] > 99)
			{
				startPoint += 3;
			}
			// Add 2 for 2 digits
			else if (currentScore->Tests[test] > 9)
			{
				startPoint += 2;
			}
			// Add 1 for 1 digit
			else
			{
				startPoint += 1;
			}
		}
		else
		{
			// Accounting for 2 commas
			startPoint += 2;
		}

	}

	lastTestWidth = 14 - startPoint;
}

// This function calculates the class average score
void calculateClassAverage(TestScore* scores, const int studentCount, float& classAverage)
{
	// Declare Variables
	TestScore* currentScore;
	int sum;

	// Initialize variables
	sum = 0;

	// Loop through student scores
	for (int student = 0; student < studentCount; student++)
	{
		currentScore = &scores[student];

		// Add student score to sum
		sum += currentScore->Score;
	}

	// Ensure no division by 0
	if (studentCount == 0)
	{
		std::cout << "\t\t\tERROR. Division by 0" << std::endl;
		exit(-1);
	}
	
	// calculate average
	classAverage = (float)sum / studentCount;
	
	
} // end of calculateClassAverage()

// This function gets student score input from the user and stores it in
// an array
void inputStudentScores(TestScore* scores, const int studentCount)
{
	// Declare Variables
	std::string prompt;
	int studentNumber;
	int charLimit;
	TestScore* currentScore;
	int sum;
	int minScore;
	int maxScore;

	// Initialize variables
	charLimit = 30;
	minScore = 0;
	maxScore = 110;

	std::cout << std::endl;

	// Loop through Student Scores
	for (int student = 0; student < studentCount; student++)
	{
		// Set currentScore to address of current index in scores
		currentScore = &scores[student];
		sum = 0;

		studentNumber = student + 1;
		std::cout << "Student " << studentNumber << ":" << std::endl;
		std::cout << "----------------------------------------------" << std::endl;

		// Get name of student
		currentScore->Name = getStringData("\tEnter Name: ", charLimit);

		// Loop through 3 tests
		for (int test = 0; test < 3; test++)
		{
			prompt = "\tEnter Score for test " + std::to_string(test + 1) + (std::string)": ";

			// Get Test score
			currentScore->Tests[test] = getIntegerData(prompt, minScore, maxScore);

			// Add score to sum
			sum += currentScore->Tests[test];
		}
		
		// Calculate student's average score
		currentScore->Score = (float)sum / 3;

		std::cout << std::endl;

	}
} // end of inputStudentScores()

// This function uses the bubble sort algorithm to sort student scores
// in ascending order
void sortScores(TestScore* scores, const int studentCount)
{
	// Keeps track of whether a swap was made
	bool swapped;
	TestScore* currentScore;
	TestScore* nextScore;

	do
	{
		swapped = false;
		
		// Loop through student scores until 2nd to last
		for (int score = 0; score < studentCount - 1; score++)
		{
			currentScore = &scores[score];
			nextScore = &scores[score + 1];

			// Compare adjacent scores
			if (currentScore->Score > nextScore->Score)
			{
				// Create a temporary TestScore variable
				TestScore temp = *currentScore;

				// Set the current score's data to next score's data
				*currentScore = *nextScore;

				// Replace next score's data to the temp value
				*nextScore = temp;

				swapped = true;
			}
		}
	} 
	while (swapped);

} // end of sortScores()


// This function greets the user
void greetUser()
{
	std::cout << "" << std::endl;
	std::cout << "Bone Anatomy Class" << std::endl;
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
float getFloatData(std::string prompt)
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
	std::string strValue;

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
		else if (std::to_string(value).length() != 5)
		{
			std::cout << "\t\t\tERROR. Value must be 5 digits." << std::endl;
		}
		else
		{
			break;
		}
	}// 	while (!(cin >> value))

	clearCin();

	return value;


} // end of int getIntegerData()

// This function will get an integer value from the user. Includes min and max parameters
int getIntegerData(std::string prompt, const int min, const int max)
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
		else if (value < min || value > max)
		{
			std::cout << "\t\t\tERROR. Value can not be between " << min <<  " and " << max  << " (INCLUSIVE)." << std::endl;
		}
		else
		{
			break;
		}
	}// 	while (!(cin >> value))

	clearCin();

	return value;


} // end of int getIntegerData()

// This function will return a string data entered by users
std::string getStringData(std::string prompt, const int charLimit)
{
	std::string value;

	while (true)
	{
		std::cout << prompt;

		std::getline(std::cin, value); // accepts spaces in the entry

		// Verify string does not exceed character limit
		if (value.length() > charLimit)
		{
			std::cout << "\t\t\tERROR. Character limit of " << charLimit << " exceeded." << std::endl;
		}
		else
		{
			break;
		}
	}
	

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


