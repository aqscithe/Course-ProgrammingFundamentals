/*
-------------------------------------------------------------------------
Name:			Leon Thompson
Date:			12/06/2023
Project #:		Exam 3
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Description
	The program takes a data file containing questions and answers and
	constructs a quiz, whose number of questions is determined by the 
	user. The result of the quiz answers and results are tracked in a
	file "quizSummary.txt" that can be viewed after completion of 
	quizzes.
-------------------------------------------------------------------------
*/

#include <iostream>				// for cin, cout, std::endl
#include <iomanip>				// for fixed, setprecision
#include <string>				// for string
#include <cctype> 				//for toupper()
#include <fstream>
#include <sstream>
#include <random>
#include <vector>

using namespace std;

// Forward Declaration
struct Question;
struct QuizAttemptSummary;


// Decleration of prototype 
void projectStart();
void projectEnd();
bool isInteger(const std::string& str);
int getIntegerData(std::string, int);
float getFloatData(std::string);
char getCharData(std::string);
std::string getStringData(std::string);
void clearCin();
void greetUser();
void loadDictionary(string*, string*, int&);
void displayQuizHeader();
void writeQuizNumberToFile(std::ofstream&, QuizAttemptSummary&);
void GenerateNextQuestion(int questionCount, std::vector<int>& asked, Question& question, std::string  english[100], std::string  french[100]);
void AskNextQuestion(int ctr, Question& question, std::string& answer, int& correctCount);
void writeQuestionResultsToFile(std::ofstream& outputFile, int ctr, Question& question, std::string& answer);
void displayQuizSummary(float& grade, int correctCount, int questionCount, std::string& name, float passingScore, QuizAttemptSummary& summary);
void updateSummaryInfo(QuizAttemptSummary& summary, float grade);
void writeQuizResultsToFile(std::ofstream& outputFile, std::string& name, int questionCount, int correctCount, float grade);
void displayQuizAttemptsSummary(int& failed, QuizAttemptSummary& summary, std::string& name);
void writeQuizAttemptsSummaryToFile(std::ofstream& outputFile, std::string& name, QuizAttemptSummary& summary, int failed);



// This struct organizes the questions posed to user
struct Question
{
	string english;
	string french;
}; // end of struct Question


// This struct contains quiz attempts data
struct QuizAttemptSummary
{
	QuizAttemptSummary()
	{
		Attempted = 0;
		Passed = 0;
		Highest = 0.f;
	}

	int Attempted;
	int Passed;
	float Highest;

}; // end of QuizAttemptSummary




int main()
{
	std::cout << std::fixed << std::setprecision(2);

	projectStart();

	greetUser();

	// Declare variables
	string english[100];
	string french[100];
	std::vector<int> asked;
	string name;
	int wordCount;
	int correctCount;
	float passingScore;
	int failed;
	QuizAttemptSummary summary;
	std::ofstream outputFile;


	// Initialize variables
	outputFile.open("quizSummary.txt");
	wordCount = 0;
	correctCount = 0;
	passingScore = 80.f;

	loadDictionary(english, french, wordCount);

	name = getStringData("Please enter your name: ");

	cout << "Maximum words available: " << wordCount << std::endl;

	// Quiz Run Loop
	while (true)
	{
		// Declare quiz variables
		int questionCount;
		string answer;
		float grade;
		char retake;

		questionCount = getIntegerData("How many words would you like to be quizzed on? ", wordCount);

		displayQuizHeader();

		// Write quiz number to file
		writeQuizNumberToFile(outputFile, summary);

		// Loop through quiz questions
		for (int ctr = 0; ctr < questionCount; ctr++)
		{
			Question question;

			GenerateNextQuestion(questionCount, asked, question, english, french);
			
			AskNextQuestion(ctr, question, answer, correctCount);

			writeQuestionResultsToFile(outputFile, ctr, question, answer);

		}

		displayQuizSummary(grade, correctCount, questionCount, name, passingScore, summary);

		updateSummaryInfo(summary, grade);

		writeQuizResultsToFile(outputFile, name, questionCount, correctCount, grade);

		// Determine if user would like to retake quiz
		retake = getCharData("Do you want to take the quiz again (Y/N)? ");

		if (retake == 'Y')
		{
			asked.clear();
			questionCount = 0;
			correctCount = 0;
			continue;
		}
		break;

	}// end of while - Quiz Run Loop

	displayQuizAttemptsSummary(failed, summary, name);

	writeQuizAttemptsSummaryToFile(outputFile, name, summary, failed);

	outputFile.close();

	projectEnd();

} // end of main

// This function writes a summary of all quiz attempts to a file
void writeQuizAttemptsSummaryToFile(std::ofstream& outputFile, std::string& name, QuizAttemptSummary& summary, int failed)
{
	// Verify file is open
	if (outputFile.is_open())
	{
		outputFile << endl;
		outputFile << "----------------------------------------------------------------" << endl;
		outputFile << "Overall Quiz Attempts Summary" << endl;
		outputFile << "----------------------------------------------------------------" << endl;
		outputFile << "\tStudent Name: " << name << endl;
		outputFile << endl;
		outputFile << "\tQuiz Info" << endl;
		outputFile << "\t\tAttempted " << summary.Attempted << endl;
		outputFile << "\t\tPassed " << summary.Passed << endl;
		outputFile << "\t\tFailed " << failed << endl;
		outputFile << "\t\tHighest " << summary.Highest << "%" << endl;
		outputFile << "----------------------------------------------------------------" << endl;
	}
	else
	{
		// Error in case of failure to open file
		cout << "\t\t\tError opening quiz summary file" << endl;
		exit(1);
	}
} // end of writeQuizAttemptsSummaryToFile


// This function displays a summary of quiz attempts
void displayQuizAttemptsSummary(int& failed, QuizAttemptSummary& summary, std::string& name)
{
	// calculate # of failed attempts
	failed = summary.Attempted - summary.Passed;

	cout << "----------------------------------------------------------------" << endl;
	cout << "Overall Quiz Attempts Summary" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "\tStudent Name: " << name << endl;
	cout << endl;
	cout << "\tQuiz Info" << endl;
	cout << "\t\tAttempted " << summary.Attempted << endl;
	cout << "\t\tPassed " << summary.Passed << endl;
	cout << "\t\tFailed " << failed << endl;
	cout << "\t\tHighest " << summary.Highest << "%" << endl;
} // end of displayQuizAttemptsSummary


// This function writes the results of the last completed quiz to a file
void writeQuizResultsToFile(std::ofstream& outputFile, std::string& name, int questionCount, int correctCount, float grade)
{
	// Verify that the file is open
	if (outputFile.is_open())
	{
		outputFile << "--------------------------------------------" << endl;
		outputFile << "Quiz Summary " << endl;
		outputFile << "--------------------------------------------" << endl;
		outputFile << "Name: " << name << endl;
		outputFile << "\tQuestion Count: " << questionCount << endl;
		outputFile << "\tCorrect Answers: " << correctCount << endl;
		outputFile << "\tGrade: " << grade << "%" << endl;
		outputFile << "--------------------------------------------" << endl;
		outputFile << endl;
	}
	else
	{
		// Error in case of failure to open file
		cout << "\t\t\tError opening quiz summary file" << endl;
		exit(1);
	}
}

// This function updates info related the quiz attempts
void updateSummaryInfo(QuizAttemptSummary& summary, float grade)
{
	summary.Attempted++;

	if (grade > summary.Highest)
	{
		summary.Highest = grade;
	}
} // end of updateSummaryInfo

// This function displays a summary of the most recently completed quiz
void displayQuizSummary(float& grade, int correctCount, int questionCount, std::string& name, float passingScore, QuizAttemptSummary& summary)
{
	// Calculate quiz grade
	grade = (float)correctCount / questionCount * 100.f;

	// Display quiz info
	cout << "Quiz Summary" << endl;
	cout << "Name: " << name << endl;
	cout << "\tQuestion Count: " << questionCount << endl;
	cout << "\tCorrect Answers: " << correctCount << endl;
	cout << "\tGrade: " << grade << "%" << endl;

	// Determine if grade is passing
	if (grade >= passingScore)
	{
		cout << "\tDecision: PASSED" << endl;
		summary.Passed++;
	}
	else
	{
		cout << "\tDecision: FAILED - Passing score is " << passingScore << endl;
	}

	cout << "----------------------------------------------------------------" << endl;
} // end of displayQuizSummary


// This function writes the results of each question to a file
void writeQuestionResultsToFile(std::ofstream& outputFile, int ctr, Question& question, std::string& answer)
{
	// Verify that the file is open
	if (outputFile.is_open())
	{
		outputFile << "Question " << ctr + 1 << endl;
		outputFile << "\tEnglish word: " << question.english << endl;
		outputFile << "\tYour answer: " << answer << endl;
		outputFile << "\tCorrect answer: " << question.french << endl;
		outputFile << "---------------------------------------------" << endl;
		outputFile << endl;
	}
	else
	{
		// Error in case of failure to open file
		cout << "\t\t\tError opening quiz summary file" << endl;
		exit(1);
	}
} // end of writeQuestionResultsToFile


// This function asks the user a quiz question
void AskNextQuestion(int ctr, Question& question, std::string& answer, int& correctCount)
{
	// Pose question
	cout << "Question " << ctr + 1 << endl;
	cout << "\tEnglish word: " << question.english << endl;

	// Obtain user response
	answer = getStringData("\tFrench answer: ");

	cout << endl;

	// Determine if question is correct
	if (answer == question.french)
	{
		cout << "\tCorrect!" << endl;
		correctCount++;
	}
	else
	{
		cout << "\tWrong!" << endl;
	}

	cout << "----------------------------------------------------------------" << endl;
} // end of AskNextQuestion


// This function uses a random number generator to ask questions based on the data provided
void GenerateNextQuestion(int questionCount, std::vector<int>& asked, Question& question, std::string  english[100], std::string  french[100])
{
	// Loop to ensure randomNumber is a unique value
	while (true)
	{
		// Declare and Initialize variables
		int randomNumber;
		int min = 0;
		int max = questionCount - 1;
		bool repeatQuestion = false;

		// Seed the number generator
		srand(time(NULL));

		// Retrieve the random number
		randomNumber = 0 + rand() % (max - min + 1);

		// Don't need to check random Number on first question
		if (asked.size() > 0)
		{
			for (int i = 0; i < asked.size(); i++)
			{
				// Search asked array for repeated question
				if (asked[i] == randomNumber)
				{
					repeatQuestion = true;
					break;
				}
			}

			// Restart loop if question has been asked
			if (repeatQuestion)
			{
				continue;
			}
			else
			{
				// Initialize quiz question
				question = { english[randomNumber], french[randomNumber] };
				asked.push_back(randomNumber);
				break;
			}

		}
		else
		{
			// Initialize quiz question
			question = { english[randomNumber], french[randomNumber] };
			asked.push_back(randomNumber);
			break;
		}

	} // end of while(true)
} // end of GenerateNextQuestion


// This function writes quiz number to file
void writeQuizNumberToFile(std::ofstream& outputFile, QuizAttemptSummary& summary)
{
	if (outputFile.is_open())
	{
		outputFile << "Quiz " << summary.Attempted + 1 << endl;
		outputFile << "--------------------------------------------" << endl;
	}
	else
	{
		cout << "\t\t\tError opening quiz summary file" << endl;
		exit(1);
	}
} // end of writeQuizNumberToFile


// This function displays the quiz header
void displayQuizHeader()
{
	cout << "----------------------------------------------------------------" << endl;
	cout << "QUIZ" << endl;
	cout << "----------------------------------------------------------------" << endl;
} // end of displayQuizHeader


// Load english - french vocab words from data.txt
void loadDictionary(string* english, string* french, int& wordCount)
{
	// Load data file
	std::ifstream inputFile("data.txt");
	std::string line;

	// Verify file is open
	if (!inputFile.is_open())
	{
		cout << "Error opening data file" << endl;
		exit(1);
	}

	// Loop through lines in file
	while (std::getline(inputFile, line))
	{
		std::stringstream ss(line);

		// Find the delimiter position in line
		size_t delimiterPos = line.find('|');

		// Verify the delimiter exists in string
		if (delimiterPos != std::string::npos)
		{
			// Set english and french word
			english[wordCount] = line.substr(0, delimiterPos);
			french[wordCount] = line.substr(delimiterPos + 1, line.size());
		}

		// Increment word count
		wordCount++;

	} // end of while

	inputFile.close();
} // end of loadDictionary



// This function greets the user
void greetUser()
{
	std::cout << "WELCOME TO LEON'S FRENCH QUIZ" << std::endl;
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

		if (value != 'N' && value != 'Y')
		{
			cout << "Invalid entry. Try again." << endl;
			continue;
		}

		break;
	}

	

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
int getIntegerData(std::string prompt, int max)
{
	int value;

	while (true)
	{
		std::cout << prompt;
		if (!(std::cin >> value))
		{
			std::cout << "\t\t\tError Message. Non numeric is entered" << std::endl;
			

		}
		else if (value < 0)
		{
			std::cout << "\t\t\tERROR. Value can not be negative" << std::endl;
		}
		else if (value > max)
		{
			std::cout << "\t\t\tERROR. Value can not be greater than " << max << std::endl;
		}
		else
		{
			break;
		}

		clearCin();

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
