#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int MAX_ROWS = 20;
const int MAX_COLS = 20;
int matrix[MAX_ROWS][MAX_COLS];
int solution[MAX_ROWS][MAX_COLS];
int rows, cols;
int r, c;
int lives = 3;
int LEVEL = 5;

//we declare that functions because we use them inside each other
void validInputState(int x, int y);
void inValidInputState(int x, int y);

// Adds ".txt" extension to the username to create a valid filename.
void addTxtToFileName(char* username)
{
	int index = 0;

	while (username[index++]);

	username[--index] = '.';
	username[index + 1] = 't';
	username[index + 2] = 'x';
	username[index + 3] = 't';
}

// Checks if a file with the given filename already exists.
bool fileExists(const char* fileName)
{
	std::ifstream file(fileName);
	return file.is_open();
}

// Decrements the player's lives and returns the updated value.
int yourLives(int lives)
{
	return lives--;
}

// Returns the player's current level
int yourLevel()
{
	int level = 0;
	return 1;
}

//function to save the game data of each user
void saveProgressToFile(const char* filename)
{
	std::ofstream file(filename);

	file << rows << " " << cols << std::endl;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			file << matrix[i][j] << " ";
		}
		file << std::endl;
	}

	file.close();
}

// Handles the registration process, creating a new user or continuing an existing one.
void registration(char yesOrNo)
{
	char* username = new char[50] {};
	cin >> username;
	addTxtToFileName(username);
	if (!fileExists(username))
	{
		cout << "Your level is 1!" << endl;
	}
	else
	{
		cout << "Do you want to continue to where you are? [Y/N]" << endl;
		cin >> yesOrNo;
		if (yesOrNo == 'Y' || yesOrNo == 'y')
		{
			cout << "Your level is " << yourLevel() << "!" << endl;
		}
		else if (yesOrNo == 'N' || yesOrNo == 'n')
		{
			cout << "Your level is 1!" << endl;
		}
		else
		{
			cout << "Invalid input!" << endl;
			exit(0);
		}
	}

	saveProgressToFile(username);

	delete[] username;

}

// Initiates the game entrance, prompting the user to start or exit.
void entrance(char yesOrNo)
{
	cout << "Hello!" << endl << "Are you ready to start the nonogram game ? [Y]" << endl;
	cin >> yesOrNo;
	if (yesOrNo == 'Y' || yesOrNo == 'y')
	{
		cout << "Let's start the game! First enter a username:" << endl;
		registration(yesOrNo);
	}
	else
	{
		cout << "Invalid input!" << endl;
		exit(0);
	}
}

// Checks if coordinates are within valid boundaries.
bool areCoordinatesValid(int x, int y)
{
	return (x >= 0 && y >= 0);
}

// Checks if a point in the matrix corresponds to a filled square in the solution.
bool isPointInFile(int x, int y)
{
	return solution[x][y] == 1;
}

// Returns a randomly selected file from the provided array of filenames.
const char* getRandomFile(const char* files[])
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	int randomIndex = std::rand() % 2;

	return files[randomIndex];
}

// Displays the current state of the game board.
void displayBoard()
{
	std::cout << "-";
	for (int i = 0; i < rows; ++i)
	{
		std::cout << "--";
	}
	std::cout << "-" << std::endl;

	for (int i = 0; i < rows; ++i)
	{
		if (i == r)
		{
			std::cout << "-";
			for (int j = 0; j < rows; ++j)
			{
				std::cout << "--";
			}
			std::cout << "-" << std::endl;
		}
		for (int j = 0; j < cols; ++j)
		{
			if (matrix[i][j] == -1)
			{
				cout << "  ";
			}
			else
			{
				std::cout << matrix[i][j] << " ";
			}
			if (j == c - 1)
			{
				std::cout << "|";
			}

		}

		std::cout << "|" << std::endl;
	}

	std::cout << "-";
	for (int i = 0; i < rows; ++i)
	{
		std::cout << "--";
	}
	std::cout << "-" << std::endl;


}

//A function to find the length of a string
int myStrlen(const char* string)
{
	if (!string)
		return 0;

	unsigned result = 0;
	while (*string)
	{
		result++;
		string++;
	}
	return result;
}

//String copy function
void myStrcpy(const char* source, char* destination)
{
	if (!source || !destination)
		return;
	while (*source)
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
}

//Function to concatenate strings
void myStrcat(char* first, const char* second)
{
	if (!first || !second)
		return;

	int firstLen = myStrlen(first);
	first += firstLen;
	myStrcpy(second, first);
}

// Initializes the game board with data from a randomly selected file and its solution.
void initBoard(const char* filename, const char* files[])
{
	const char* file = getRandomFile(files);
	std::ifstream inputFile(file);

	if (!inputFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return;
	}

	inputFile >> rows >> cols;
	inputFile >> r >> c;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			inputFile >> matrix[i][j];
		}
	}
	inputFile.close();
	char solutionFileName[200];
	strncpy_s(solutionFileName, file, 9);

	myStrcat(solutionFileName, "-sol.txt");

	inputFile.open(solutionFileName);
	for (int i = 0; i < rows - r; ++i)
	{
		for (int j = 0; j < cols - c; ++j)
		{
			inputFile >> solution[i][j];
		}
	}
}

//function to fill all squares when a row or column is guessed
void fillRemainingWithZero(int x, int y)
{
	bool allCorrectRow = true;
	int iRow = x + r;
	int jRow = c;

	int iSolution = x;
	int jSolution = 0;

	while (jRow < cols)
	{
		if (matrix[iRow][jRow] != 1 && solution[iSolution][jSolution] == 1)
		{
			allCorrectRow = false;
			break;
		}

		jRow++;
		jSolution++;
	}

	if (allCorrectRow)
	{
		for (int j = c; j < cols; j++)
		{
			if (matrix[iRow][j] != 1)
			{
				matrix[iRow][j] = 0;
			}
		}
	}

	bool allCorrectCol = true;
	int iCol = r;
	int jCol = y + c;

	iSolution = 0;
	jSolution = y;

	while (iCol < rows)
	{
		if (matrix[iCol][jCol] != 1 && solution[iSolution][jSolution] == 1)
		{
			allCorrectCol = false;
			break;
		}

		iCol++;
		iSolution++;
	}

	if (allCorrectCol)
	{
		for (int i = r; i < rows; i++)
		{
			if (matrix[i][jCol] != 1)
			{
				matrix[i][jCol] = 0;
			}
		}
	}

}

// Handles the input state when the coordinates are valid.
void validInputState(int x, int y)
{
	while (isPointInFile(x, y))
	{
		matrix[x + r][y + c] = 1;
		fillRemainingWithZero(x, y);
		displayBoard();
		cout << "True, enter new coordinates:" << endl;

		cin >> x >> y;
	}
	inValidInputState(x, y);
}

// Handles the input state when the coordinates are invalid.
void inValidInputState(int x, int y)
{
	while (!isPointInFile(x, y) && lives >= 1)
	{
		displayBoard();
		cout << "Mistake, your lives are " << yourLives(--lives) << "!" << endl;
		if (lives <= 0)
		{
			cout << "GAME OVER!" << endl;
			exit(0);
		}
		else
		{
			cout << "Enter new coordinates:" << endl;
			cin >> x >> y;
		}
	}
	validInputState(x, y);

}

// Chooses a random file, initializes the board, and starts the game loop.
void chooseRandomFile(const char* file1, const char* file2)
{
	const char* fileList[] = { "Level 1.1.txt", "Level 1.2.txt" };

	const char* randomFile = getRandomFile(fileList);

	std::ifstream chosenFileStream(randomFile);

	if (chosenFileStream.is_open())
	{
		ifstream file(randomFile);

		if (!file.is_open())
		{
			cout << "Unable to open file" << randomFile << endl;
			return;
		}

		int x, y;
		initBoard(randomFile, fileList);
		displayBoard();

		cout << "Enter coordinates of a filled square!" << endl;
		cin >> x >> y;
		if (areCoordinatesValid(x, y))
		{
			validInputState(x, y);
		}
		else
		{
			cout << "Invalid input!" << endl;
			exit(0);
		}

		file.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
	}
}












