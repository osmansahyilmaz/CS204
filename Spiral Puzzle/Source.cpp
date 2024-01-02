/*
			FALL 2023-2024, CS-204 HOMEWORK#1
			    OSMAN SAH YILMAZ, 31316
						  ©
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

#define debug 0

// clockwise dimensions for steps
// [0,0] --> right 
// [1,1] --> down 
// [2,2] --> left 
// [3,3] --> up
const int dimensionX[] = { 0, 1, 0, -1 };
const int dimensionY[] = { 1, 0, -1, 0 };

// counter clockwise dimensions for steps
// [0,0] --> left
// [1,1] --> down 
// [2,2] --> right 
// [3,3] --> up
const int counterDimensionX[] = { 0, 1, 0, -1 };
const int counterDimensionY[] = { -1, 0, 1, 0 };


// returns true if index is not out of matrix (protect from crashes)
bool isSafe(int x, int y, int matrixSize ) {
	return (x >= 0 && x <  matrixSize && y >= 0 && y < matrixSize);
}

/*
							*****************
							CLOCKWISE SEARCHS
							*****************
*/
void rightDownSearch(vector<vector<char>>& matrix, int matrixSize, int i, int j, const string& word, set<string> &foundWordsSet, bool& found) {
	int checkedChar = 3, wordLen = word.length();
	int direction = 2;
	int stepSize = 2;
	bool notHere = false;
	while (checkedChar < wordLen)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int madeStep = 0; madeStep < stepSize; madeStep++)
			{
				if (isSafe((i + dimensionX[direction]), j + dimensionY[direction], matrixSize) && matrix[(i + dimensionX[direction])][(j + dimensionY[direction])] == word[checkedChar])
				{
					i += dimensionX[direction];
					j += dimensionY[direction];
					checkedChar++;
				}
				else if (!isSafe((i + dimensionX[direction]), j + dimensionY[direction], matrixSize) || checkedChar > wordLen || matrix[(i + dimensionX[direction])][(j + dimensionY[direction])] != word[checkedChar]) {
					notHere = true;
					break;
				}
			}
			if (notHere) {
				break;
			}
			direction = (direction + 1) % 4;
		}
		if (notHere) {
			break;
		}
		stepSize++;
	}
	if (checkedChar == wordLen) {
		foundWordsSet.insert(word);
		found = true;
	}
}


void downLeftSearch(vector<vector<char>>& matrix, int matrixSize, int i, int j, const string& word, set<string>& foundWordsSet, bool& found)
{
	int checkedChar = 3, wordLen = word.length();
	int direction = 3;
	int stepSize = 2;
	bool notHere = false;
	while (checkedChar < wordLen)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int madeStep = 0; madeStep < stepSize; madeStep++)
			{
				if (isSafe((i + dimensionX[direction]), j + dimensionY[direction], matrixSize) && matrix[(i + dimensionX[direction])][(j + dimensionY[direction])] == word[checkedChar])
				{
					i += dimensionX[direction];
					j += dimensionY[direction];
					checkedChar++;
				}
				else if (!isSafe((i + dimensionX[direction]), j + dimensionY[direction], matrixSize) || checkedChar > wordLen || matrix[(i + dimensionX[direction])][(j + dimensionY[direction])] != word[checkedChar]) {
					notHere = true;
					break;
				}
			}
			if (notHere) {
				break;
			}
			direction = (direction + 1) % 4;
		}
		if (notHere) {
			break;
		}
		stepSize++;
	}
	if (checkedChar == wordLen) {
		foundWordsSet.insert(word);
		found = true;
	}
}


void leftUpSearch(vector<vector<char>>& matrix, int matrixSize, int i, int j, const string& word, set<string>& foundWordsSet, bool& found)
{
	int checkedChar = 3, wordLen = word.length();
	int direction = 0;
	int stepSize = 2;
	bool notHere = false;
	while (checkedChar < wordLen)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int madeStep = 0; madeStep < stepSize; madeStep++)
			{
				if (isSafe((i + dimensionX[direction]), j + dimensionY[direction], matrixSize) && matrix[(i + dimensionX[direction])][(j + dimensionY[direction])] == word[checkedChar])
				{
					i += dimensionX[direction];
					j += dimensionY[direction];
					checkedChar++;
				}
				else if (!isSafe((i + dimensionX[direction]), j + dimensionY[direction], matrixSize) || checkedChar > wordLen || matrix[(i + dimensionX[direction])][(j + dimensionY[direction])] != word[checkedChar]) {
					notHere = true;
					break;
				}
			}
			if (notHere) {
				break;
			}
			direction = (direction + 1) % 4;
		}
		if (notHere) {
			break;
		}
		stepSize++;
	}
	if (checkedChar == wordLen) {
		foundWordsSet.insert(word);
		found = true;
	}
}

void upRightSearch(vector<vector<char>>& matrix, int matrixSize, int i, int j, const string& word, set<string>& foundWordsSet, bool& found)
{
	int checkedChar = 3, wordLen = word.length();
	int direction = 1;
	int stepSize = 2;
	bool notHere = false;
	while (checkedChar < wordLen)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int madeStep = 0; madeStep < stepSize; madeStep++)
			{
				if (isSafe((i + dimensionX[direction]), j + dimensionY[direction], matrixSize) && matrix[(i + dimensionX[direction])][(j + dimensionY[direction])] == word[checkedChar])
				{
					i += dimensionX[direction];
					j += dimensionY[direction];
					checkedChar++;
				}
				else if (!isSafe((i + dimensionX[direction]), j + dimensionY[direction], matrixSize) || checkedChar > wordLen || matrix[(i + dimensionX[direction])][(j + dimensionY[direction])] != word[checkedChar]) {
					notHere = true;
					break;
				}
			}
			if (notHere) {
				break;
			}
			direction = (direction + 1) % 4;
		}
		if (notHere) {
			break;
		}
		stepSize++;
	}
	if (checkedChar == wordLen) {
		foundWordsSet.insert(word);
		found = true;
	}
}

//							*****************
//					     COUNTER CLOCKWISE SEARCHS
//							*****************

void rightUpSearch(vector<vector<char>>& matrix, int matrixSize, int i, int j, const string& word, set<string>& foundWordsSet, bool& found)
{
	int checkedChar = 3, wordLen = word.length();
	int direction = 0;
	int stepSize = 2;
	bool notHere = false;
	while (checkedChar < wordLen)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int madeStep = 0; madeStep < stepSize; madeStep++)
			{
				if (isSafe((i + counterDimensionX[direction]), j + counterDimensionY[direction], matrixSize) && matrix[(i + counterDimensionX[direction])][(j + counterDimensionY[direction])] == word[checkedChar])
				{
					i += counterDimensionX[direction];
					j += counterDimensionY[direction];
					checkedChar++;
				}
				else if (!isSafe((i + counterDimensionX[direction]), j + counterDimensionY[direction], matrixSize) || checkedChar > wordLen || matrix[(i + counterDimensionX[direction])][(j + counterDimensionY[direction])] != word[checkedChar]) {
					notHere = true;
					break;
				}
			}
			if (notHere) {
				break;
			}
			direction = (direction + 1) % 4;
		}
		if (notHere) {
			break;
		}
		stepSize++;
	}
	if (checkedChar == wordLen) {
		foundWordsSet.insert(word);
		found = true;
	}
}

void downRightSearch(vector<vector<char>>& matrix, int matrixSize, int i, int j, const string& word, set<string>& foundWordsSet, bool& found)
{
	int checkedChar = 3, wordLen = word.length();
	int direction = 3;
	int stepSize = 2;
	bool notHere = false;
	while (checkedChar < wordLen)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int madeStep = 0; madeStep < stepSize; madeStep++)
			{
				if (isSafe((i + counterDimensionX[direction]), j + counterDimensionY[direction], matrixSize) && matrix[(i + counterDimensionX[direction])][(j + counterDimensionY[direction])] == word[checkedChar])
				{
					i += counterDimensionX[direction];
					j += counterDimensionY[direction];
					checkedChar++;
				}
				else if (!isSafe((i + counterDimensionX[direction]), j + counterDimensionY[direction], matrixSize) || checkedChar > wordLen || matrix[(i + counterDimensionX[direction])][(j + counterDimensionY[direction])] != word[checkedChar]) {
					notHere = true;
					break;
				}
			}
			if (notHere) {
				break;
			}
			direction = (direction + 1) % 4;
		}
		if (notHere) {
			break;
		}
		stepSize++;
	}
	if (checkedChar == wordLen) {
		foundWordsSet.insert(word);
		found = true;
	}
}

void leftDownSearch(vector<vector<char>>& matrix, int matrixSize, int i, int j, const string& word, set<string>& foundWordsSet, bool& found)
{
	int checkedChar = 3, wordLen = word.length();
	int direction = 2;
	int stepSize = 2;
	bool notHere = false;
	while (checkedChar < wordLen)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int madeStep = 0; madeStep < stepSize; madeStep++)
			{
				if (isSafe((i + counterDimensionX[direction]), j + counterDimensionY[direction], matrixSize) && matrix[(i + counterDimensionX[direction])][(j + counterDimensionY[direction])] == word[checkedChar])
				{
					i += counterDimensionX[direction];
					j += counterDimensionY[direction];
					checkedChar++;
				}
				else if (!isSafe((i + counterDimensionX[direction]), j + counterDimensionY[direction], matrixSize) || checkedChar > wordLen || matrix[(i + counterDimensionX[direction])][(j + counterDimensionY[direction])] != word[checkedChar]) {
					notHere = true;
					break;
				}
			}
			if (notHere) {
				break;
			}
			direction = (direction + 1) % 4;
		}
		if (notHere) {
			break;
		}
		stepSize++;
	}
	if (checkedChar == wordLen) {
		foundWordsSet.insert(word);
		found = true;
	}
}

void upLeftSearch(vector<vector<char>>& matrix, int matrixSize, int i, int j, const string& word, set<string>& foundWordsSet, bool& found)
{
	int checkedChar = 3, wordLen = word.length();
	int direction = 1;
	int stepSize = 2;
	bool notHere = false;
	while (checkedChar < wordLen)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int madeStep = 0; madeStep < stepSize; madeStep++)
			{
				if (isSafe((i + counterDimensionX[direction]), j + counterDimensionY[direction], matrixSize) && matrix[(i + counterDimensionX[direction])][(j + counterDimensionY[direction])] == word[checkedChar])
				{
					i += counterDimensionX[direction];
					j += counterDimensionY[direction];
					checkedChar++;
				}
				else if (!isSafe((i + counterDimensionX[direction]), j + counterDimensionY[direction], matrixSize) || checkedChar > wordLen || matrix[(i + counterDimensionX[direction])][(j + counterDimensionY[direction])] != word[checkedChar]) {
					notHere = true;
					break;
				}
			}
			if (notHere) {
				break;
			}
			direction = (direction + 1) % 4;
		}
		if (notHere) {
			break;
		}
		stepSize++;
	}
	if (checkedChar == wordLen) {
		foundWordsSet.insert(word);
		found = true;
	}
}

/*
		checking 2nd and 3rd chars ,
		and then routes to appropriate algo after 
*/
void router(vector<vector<char>>& matrix, int matrixSize, int i, int j, string word, set<string> &foundWordsSet, bool& found) {
	if (isSafe(i, (j + 1), matrixSize) && matrix[i][j + 1] == word[1]) //right
	{
		if (isSafe((i + 1), (j + 1), matrixSize) && matrix[i +1][j+1] == word[2]) // +down
		{
			rightDownSearch(matrix, matrixSize, i+1, j+1, word, foundWordsSet, found);
		}
		if (isSafe((i - 1), (j + 1), matrixSize) && matrix[i - 1][j + 1] == word[2]) // +up
		{
			rightUpSearch(matrix, matrixSize, i-1, j+1, word, foundWordsSet, found);
		}
	}
	if (isSafe((i+1), (j), matrixSize) && matrix[i+1][j] == word[1]) // down*
	{
		if (isSafe((i + 1), (j - 1), matrixSize) && matrix[i + 1][j - 1] == word[2]) // +left*
		{
			downLeftSearch(matrix, matrixSize, i + 1, j - 1, word, foundWordsSet, found);
		}
		if (isSafe((i + 1), (j + 1), matrixSize) && matrix[i + 1][j + 1] == word[2]) // +right*
		{
			downRightSearch(matrix, matrixSize, i+1, j+1, word, foundWordsSet, found);
		}
	}
	if (isSafe(i, (j - 1), matrixSize) && matrix[i][j - 1] == word[1]) // left*
	{
		if (isSafe((i + 1), (j - 1), matrixSize) && matrix[i + 1][j - 1] == word[2]) // +down*
		{
			leftDownSearch(matrix, matrixSize, i+1, j-1, word, foundWordsSet ,found);
		}
		if (isSafe((i - 1), (j - 1), matrixSize) && matrix[i - 1][j - 1] == word[2]) // +up*
		{
			leftUpSearch(matrix, matrixSize, i - 1, j - 1, word, foundWordsSet, found);
		}
	}
	if (isSafe( (i-1), (j), matrixSize) && matrix[i-1][j] == word[1]) // up*
	{
		if (isSafe((i - 1), (j + 1), matrixSize) && matrix[i - 1][j + 1] == word[2]) // +right*
		{
			upRightSearch(matrix, matrixSize, i - 1, j + 1, word, foundWordsSet, found);
		}
		if (isSafe((i - 1), (j - 1), matrixSize) && matrix[i - 1][j - 1] == word[2]) // +left
		{
			upLeftSearch(matrix, matrixSize, i-1, j-1, word, foundWordsSet, found);
		}
	}
}

int main() {
	//getting valid input
	string inputBoardName;
	ifstream boardFile;

	while (true) {
		cout << "Enter the name of the file" << endl;
		cin >> inputBoardName;
		boardFile.open(inputBoardName);
		if (boardFile.fail()) {
			cout << "Could not open the file " << inputBoardName << endl;
			boardFile.clear();
		}
		else {
			break;
		}
	}

	// reads first line and store size of matrix and first line skipped
	int matrixSize;
	boardFile >> matrixSize;

	
	vector<vector<char>> matrix(matrixSize, vector<char>(matrixSize));

	for (int i = 0; i < matrixSize; i++) {
		string row;
		boardFile >> row;

		// checks if the row length matches the expected matrix size
		if (row.length() != matrixSize) {
			cout << "Error: Input file is not in correct format!" << endl;
			return 0;
		}

		// puts chars to matrixes if they are just A-Z
		for (int j = 0; j < matrixSize; j++) {
			if (row[j] < 'A' || row[j] > 'Z') {
				cout << "Error: Input file is not in correct format!" << endl;
				return 0;
			}
			matrix[i][j] = row[j];
		}
	}

	// adding words to wordsVector
	int numWords;
	boardFile >> numWords;
	vector<string> wordsVector(numWords);
	for (int i = 0; i < numWords; i++) {
		boardFile >> wordsVector[i];
	}

	boardFile.close();
	
	// prints matrix and words,
	// *to see, change debug definition to 1 from line 14
#if debug == 1
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << numWords << endl;

	for (int i = 0; i < numWords; i++) {
		cout << wordsVector[i] << endl;
	}
#endif

	// checks first char of word through all matrix
	// if word is found -->  insert word to foundWordsSet & it stops the checking rest of the matrix ()
	set<string> foundWordsSet;
	for (const string& word : wordsVector) {
		bool found = false;
		for (int i = 0; i < matrixSize; i++) {
			for (int j = 0; j < matrixSize; j++) {
				// control #1
				if (matrix[i][j] == word[0]) {
					router(matrix, matrixSize, i, j, word, foundWordsSet, found);
				}
				if (found) {
					break;
				}
			}
			if (found) {
				break;
			}
		}
	}

	// prints found words
	cout << foundWordsSet.size() << " Words are Found:  ";
	for (const string& word : foundWordsSet) {
		cout << word << " ";
	}
	cout << endl;

	//		FINISH POINT
	return 0;
}