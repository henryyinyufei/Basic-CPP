#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define MAX_ARRAY_SIZE 24
#define MIN_ARRAY_SIZE 8

const int NOPLAYER = 0;
const int WHITEPLAYER = 1;
const int BLACKPLAYER = 2;
const int FIRST_PIECE = 1;
const int SECOND_PIECE = 2;


bool PlacePiece(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int squarePlayed,
	int whichPiece, int& numberCaptured);
bool DisplayBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard);
bool InitialiizeBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard);
bool CheckLine(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int squarePlayed,
	int xDirection, int yDirection, int& numCaptured);
bool IsAnyMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int whichPiece);
bool IsThisMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int squarePlayed, int whichPiece);



int main()
{
	const int MAXTRYCOUNTS = 3;

	int myFlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	int numRowsInBoard = 0;
	int tryCount = 0;
	int moveCount = 0;
	int maxTurn = 0;
	bool whiteflag = true;
	bool blackflag = false;
	int mySquarePlayed = 0;
	int numberCaptured = 0;
	char choice= ' ';
	char endgame = ' ';
	
	//Prompt for and read the size of the board (numRowsInBoard)
	while (tryCount < MAXTRYCOUNTS)
	{
		cout << "Enter the number of squares along each edge of the board " << endl;
		if (!(cin >> numRowsInBoard))
		{
			cerr << "ERROR: Board size is not an integer" << endl;
			cout << "8 <= number of squares <= 24" << endl;
			cin.clear();
			cin.ignore(512, '\n');
			tryCount++;
		}
		else if (numRowsInBoard > MAX_ARRAY_SIZE)
		{
			cerr << "ERROR: Board size too large" << endl;
			cout << "8 <= number of squares <= 24" << endl;
			tryCount++;
		}
		else if (numRowsInBoard < MIN_ARRAY_SIZE)
		{
			cerr << "ERROR: Board size too small" << endl;
			cout << "8 <= number of squares <= 24" << endl;
			tryCount++;
		}
		else if (numRowsInBoard % 2 != 0)
		{
			cerr << "ERROR: Board size odd" << endl;
			cout << "8 <= number of squares <= 24" << endl;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	if (tryCount >= MAXTRYCOUNTS)
	{
		cerr << "ERROR: Too many errors entering the size of the board";
		return 1;
	}

	// Initialize the game board using the InitializeBoard function
	if (!(InitialiizeBoard(myFlipFlopBoard, numRowsInBoard)))
	{
		cerr << "ERROR: Could not initialize the game board" << endl;
		return 2;
	}

	// Print the initial board to the screen using the DisplayBoard funtion
	if (!(DisplayBoard(myFlipFlopBoard, numRowsInBoard)))
	{
		cerr << "ERROR: Could not print the game board" << endl;
	}

	maxTurn = numRowsInBoard * numRowsInBoard;

	while (moveCount < maxTurn && !(whiteflag == false && blackflag == false))
	{
		// white first piece
		while (whiteflag)
		{
			numberCaptured = 0;
			if (IsAnyMoveValid(myFlipFlopBoard, numRowsInBoard, WHITEPLAYER, FIRST_PIECE))
			{
				tryCount = 0;
				cout << "White takes a turn" << endl;

				while (tryCount < MAXTRYCOUNTS)
				{
					cout << "Enter the square number of the square you want to put your first piece on " << endl;
					if (!(cin >> mySquarePlayed))
					{
						cerr << "ERROR: square chosen not an integer" << endl;
						cin.clear();
						cin.ignore(512, '\n');
						tryCount++;
					}
					else if (mySquarePlayed < 0 || mySquarePlayed > maxTurn)
					{
						cerr << "ERROR: that square is not on the board" << endl;
						cout << "Try again" << endl;
						tryCount++;
					}
					else if (myFlipFlopBoard[mySquarePlayed / numRowsInBoard][mySquarePlayed % numRowsInBoard] != 0)
					{
						cerr << "ERROR: that square is already occupied" << endl;
						cout << "Try again" << endl;
						tryCount++;
					}
					else if (!(PlacePiece(myFlipFlopBoard, numRowsInBoard, WHITEPLAYER, mySquarePlayed, FIRST_PIECE, numberCaptured)))
					{
						cerr << "ERROR: illegal move" << endl;
						cout << "Try again" << endl;
						tryCount++;
					}
					else
					{
						moveCount++;
						if (!(DisplayBoard(myFlipFlopBoard, numRowsInBoard)))
						{
							cerr << "ERROR: Could not print the game board" << endl;
						}
						cout << "Your first piece captured " << numberCaptured << " opponent's pieces" << endl << endl;
						whiteflag = false;
						blackflag = true;
						break;
					}
				}
				if (tryCount >= MAXTRYCOUNTS)
				{
					cout << "White has forfeited a turn" << endl;
					whiteflag = false;
					blackflag = true;
				}
			}
			else
			{
				cout << "White is unable to move" << endl;
				whiteflag = false;
				blackflag = true;
				break;
			}
		}
		if (numberCaptured > 1)
		{
			cout << "Do you wish to play a second piece?  Y/N ";
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
				// white second piece
				whiteflag = true;
				while (whiteflag)
				{
					numberCaptured = 0;
					if (IsAnyMoveValid(myFlipFlopBoard, numRowsInBoard, WHITEPLAYER, SECOND_PIECE))
					{
						tryCount = 0;
						cout << "White takes a turn" << endl;

						while (tryCount < MAXTRYCOUNTS)
						{
							mySquarePlayed = -1;
							cout << "Enter the square number of the square you want to put your second piece on " << endl;
							if (!(cin >> mySquarePlayed))
							{
								cerr << "ERROR: square chosen not an integer" << endl;
								cin.clear();
								cin.ignore(512, '\n');
								tryCount++;
							}
							else if (mySquarePlayed < 0 || mySquarePlayed > maxTurn)
							{
								cerr << "ERROR: that square is not on the board" << endl;
								cout << "Try again" << endl;
								tryCount++;
							}
							else if (myFlipFlopBoard[mySquarePlayed / numRowsInBoard][mySquarePlayed % numRowsInBoard] != 0)
							{
								cerr << "ERROR: that square is already occupied" << endl;
								cout << "Try again" << endl;
								tryCount++;
							}
							else if (!(PlacePiece(myFlipFlopBoard, numRowsInBoard, WHITEPLAYER, mySquarePlayed, SECOND_PIECE, numberCaptured)))
							{
								cerr << "ERROR: illegal move" << endl;
								cout << "Try again" << endl;
								tryCount++;
							}
							else
							{
								moveCount++;
								if (!(DisplayBoard(myFlipFlopBoard, numRowsInBoard)))
								{
									cerr << "ERROR: Could not print the game board" << endl;
								}
								cout << "Your second piece captured " << numberCaptured << " opponent's pieces" << endl << endl;
								whiteflag = false;
								blackflag = true;
								break;
							}
						}
						if (tryCount >= MAXTRYCOUNTS)
						{
							cout << "White has forfeited a turn" << endl;
							whiteflag = false;
							blackflag = true;
						}
					}
					else
					{
						cout << "White is unable to move" << endl;
						whiteflag = false;
						blackflag = true;
						break;
					}
				}

			}
		}



		// black firt piece
		while (blackflag)
		{
			numberCaptured = 0;
			if (IsAnyMoveValid(myFlipFlopBoard, numRowsInBoard, BLACKPLAYER, FIRST_PIECE))
			{
				tryCount = 0;
				cout << "Black takes a turn" << endl;

				while (tryCount < MAXTRYCOUNTS)
				{
					mySquarePlayed = 0;
					cout << "Enter the square number of the square you want to put your first piece on " << endl;
					if (!(cin >> mySquarePlayed))
					{
						cerr << "ERROR: square chosen not an integer" << endl;
						cin.clear();
						cin.ignore(512, '\n');
						tryCount++;
					}
					else if (mySquarePlayed < 0 || mySquarePlayed > maxTurn)
					{
						cerr << "ERROR: that square is not on the board" << endl;
						cout << "Try again" << endl;
						tryCount++;
					}
					else if (myFlipFlopBoard[mySquarePlayed / numRowsInBoard][mySquarePlayed % numRowsInBoard] != 0)
					{
						cerr << "ERROR: that square is already occupied" << endl;
						cout << "Try again" << endl;
						tryCount++;
					}
					else if (!(PlacePiece(myFlipFlopBoard, numRowsInBoard, BLACKPLAYER, mySquarePlayed, FIRST_PIECE, numberCaptured)))
					{
						cerr << "ERROR: illegal move" << endl;
						cout << "Try again" << endl;
						tryCount++;
					}
					else
					{
						moveCount++;
						if (!(DisplayBoard(myFlipFlopBoard, numRowsInBoard)))
						{
							cerr << "ERROR: Could not print the game board" << endl;
						}
						cout << "Your first piece captured " << numberCaptured << " opponent's pieces" << endl << endl;
						blackflag = false;
						whiteflag = true;
						break;
					}
				}
				if (tryCount >= MAXTRYCOUNTS)
				{
					cout << "Black has forfeited a turn" << endl;
					blackflag = false;
					whiteflag = true;
				}
			}
			else
			{
				cout << "Black is unable to move" << endl;
				blackflag = false;
				whiteflag = true;
				break;
			}
		}
		if (numberCaptured > 1)
		{
			cout << "Do you wish to play a second piece?  Y/N ";
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
				// black second piece
				blackflag = true;
				while (blackflag)
				{
					numberCaptured = 0;
					if (IsAnyMoveValid(myFlipFlopBoard, numRowsInBoard, BLACKPLAYER, SECOND_PIECE))
					{
						tryCount = 0;
						cout << "Black takes a turn" << endl;

						while (tryCount < MAXTRYCOUNTS)
						{
							mySquarePlayed = -1;
							cout << "Enter the square number of the square you want to put your second piece on " << endl;
							if (!(cin >> mySquarePlayed))
							{
								cerr << "ERROR: square chosen not an integer" << endl;
								cin.clear();
								cin.ignore(512, '\n');
								tryCount++;
							}
							else if (mySquarePlayed < 0 || mySquarePlayed > maxTurn)
							{
								cerr << "ERROR: that square is not on the board" << endl;
								cout << "Try again" << endl;
								tryCount++;
							}
							else if (myFlipFlopBoard[mySquarePlayed / numRowsInBoard][mySquarePlayed % numRowsInBoard] != 0)
							{
								cerr << "ERROR: that square is already occupied" << endl;
								cout << "Try again" << endl;
								tryCount++;
							}
							else if (!(PlacePiece(myFlipFlopBoard, numRowsInBoard, BLACKPLAYER, mySquarePlayed, SECOND_PIECE, numberCaptured)))
							{
								cerr << "ERROR: illegal move" << endl;
								cout << "Try again" << endl;
								tryCount++;
							}
							else
							{
								moveCount++;
								if (!(DisplayBoard(myFlipFlopBoard, numRowsInBoard)))
								{
									cerr << "ERROR: Could not print the game board" << endl;
								}
								cout << "Your second piece captured " << numberCaptured << " opponent's pieces" << endl << endl;
								blackflag = false;
								whiteflag = true;
								break;
							}
						}
						if (tryCount >= MAXTRYCOUNTS)
						{
							cout << "Black has forfeited a turn" << endl;
							blackflag = false;
							whiteflag = true;
						}
					}
					else
					{
						cout << "Black is unable to move" << endl;
						blackflag = false;
						whiteflag = true;
						break;
					}
				}

			}
		}
	}	
	cout << "GAME OVER" << endl;
	cout << "Enter any character to close the game ";
	cin >> endgame;
	return 0;
}


bool CheckLine(int FlipFlopBoard[][MAX_ARRAY_SIZE], int numRowsInBoard,
	int player, int squarePlayed,
	int xDirection, int yDirection, int& numCaptured)
{
	// This function takes the FlipFlopBoard and calculates
	// how the board changes when player player
	// (player=1 for white, player=2 for black)
	// This function checks along a row in one direction for
	// al legal move. If no legal move is found this function
	// returns false, if a legal move is found this function
	// returns true.
	// Author Janice Regan; 2021
	int otherPlayer;
	char piece = 2;           // to compare for otherPlayers
	int xIndex = 0;
	int yIndex = 0;
	int xCoordinate = 0;
	int yCoordinate = 0;
	bool edge = true;
	numCaptured = 0;

	otherPlayer = WHITEPLAYER;
	if (player == WHITEPLAYER)
	{
		otherPlayer = BLACKPLAYER;
	}

	// find row and column were new piece may be placed
	xCoordinate = squarePlayed % numRowsInBoard;
	yCoordinate = squarePlayed / numRowsInBoard;

	//if the square selected is occupied return false
	if (FlipFlopBoard[yCoordinate][xCoordinate] == player ||
		FlipFlopBoard[yCoordinate][xCoordinate] == otherPlayer)
	{
		return false;
	}


	// find the square next to the location the piece may
	// be played. Next in the direction (xDirection,yDirection)
	yIndex = yCoordinate + yDirection;
	xIndex = xCoordinate + xDirection;

	// while the square to be checked is on the board 
	// continue looking for a legal move
	// If the square is not on the board then return false
	// there is no legal move in the indicated direction
	while ((xIndex < numRowsInBoard &&
		yIndex < numRowsInBoard) &&
		(xIndex >= 0 && yIndex >= 0))
	{
		//if the location where the piece is to be placed
		//is next to an empty square or to another of the
		//player's pieces, then the there is no legal
		// move in the direction indicated 
		// return false
		if (FlipFlopBoard[yIndex][xIndex] == NOPLAYER ||
			FlipFlopBoard[yIndex][xIndex] == player)
		{
			return false;
		}
		else
		{
			// The next piece in the direction indicated is a
			// opponent's piece. The move may be legal, proceed
			// in the indicated direction and try to find a players
			// piece.  If one is found before the edge of the board
			// is reached the move is legal
			// If a legal move is found, count the number of pieces
			// captured,  then return true.
			edge = true;
			while (yIndex < numRowsInBoard &&
				xIndex < numRowsInBoard &&
				yIndex >= 0 && xIndex >= 0)
			{
				edge = false;
				if (FlipFlopBoard[yIndex][xIndex] == NOPLAYER)
				{
					//next square along the indicated direction is empty
					//move is illegal
					return false;
				}
				if (FlipFlopBoard[yIndex][xIndex] == player)
				{
					//next square along the direction indicated hold
					//one of the players pieces.  The move is legal
					break;
				}
				else
				{
					//next square along the direction indicated holds
					//an opponents piece, continue along the same 
					//direction and try the next square
					numCaptured++;
					xIndex += xDirection;
					yIndex += yDirection;
					edge = true;
				}
			}


			if (edge == true)
			{
				//The edge of the board has been reached without 
				//finding a players piece, move is not legal
				return false;
			}
			return true;
		}
	}
	//The edge of the board has been reached,
	//no legal move.  return false
	return false;
}


// InitializeBoard() function
bool InitialiizeBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	if (numRowsInBoard < MIN_ARRAY_SIZE || numRowsInBoard>MAX_ARRAY_SIZE)
	{
		return false;
	}

	if (FlipFlopBoard == NULL)
	{
		return false;
	}

	// empty board
	for (int row = 0; row < numRowsInBoard; row++)
	{
		for (int col = 0; col < numRowsInBoard; col++)
		{
			FlipFlopBoard[row][col] = 0;
		}
	}

	// first four tiles
	FlipFlopBoard[numRowsInBoard / 2 - 1][numRowsInBoard / 2 - 1] = 1;
	FlipFlopBoard[numRowsInBoard / 2][numRowsInBoard / 2] = 1;
	FlipFlopBoard[numRowsInBoard / 2][numRowsInBoard / 2 - 1] = 2;
	FlipFlopBoard[numRowsInBoard / 2 - 1][numRowsInBoard / 2] = 2;

	return true;
}


// DisplayBoard() function
bool DisplayBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	for (int row = 0; row < numRowsInBoard; row++)
	{
		for (int col = 0; col < numRowsInBoard; col++)
		{
			if (FlipFlopBoard[row][col] == WHITEPLAYER)
			{
				cout << setw(4) << 'W';
			}
			else if (FlipFlopBoard[row][col] == BLACKPLAYER)
			{
				cout << setw(4) << 'B';
			}
			else
			{
				cout << setw(4) << row * numRowsInBoard + col;
			}
		}
		cout << endl;
	}
	cout << endl << endl << endl << endl;
	return true;
}


// IsAnyMoveValid() function
bool IsAnyMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int whichPiece)
{
	int squarePlayed = 0;

	for (int row = 0; row < numRowsInBoard; row++)
	{
		for (int col = 0; col < numRowsInBoard; col++)
		{
			squarePlayed = row * numRowsInBoard + col;
			if (IsThisMoveValid(FlipFlopBoard, numRowsInBoard, player, squarePlayed, whichPiece))
			{
				return true;
			}
		}
	}
	return false;
}

// IsThisMoveValid£¨£© function
bool IsThisMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int squarePlayed, int whichPiece)
{
	int row = 0;
	int col = 0;
	int numberCaptured = 0;
	
	if (whichPiece == FIRST_PIECE)
	{
		bool north = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 0, 1, numberCaptured);
		bool east = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, 0, numberCaptured);
		bool south = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 0, -1, numberCaptured);
		bool west = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, 0, numberCaptured);
		if (north == false && east == false && south && false && west == false)
		{
			return false;
		}
	}
	if (whichPiece == SECOND_PIECE)
	{
		bool northeast = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, 1, numberCaptured);
		bool southeast = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1,-1, numberCaptured);
		bool southwest = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed,-1,-1, numberCaptured);
		bool northwest = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed,-1, 1, numberCaptured);
		if (northeast == false && southeast == false && southwest == false && northwest == false)
		{
			return false;
		}
	}
	return true;
}

// PlacePiece() function
bool PlacePiece(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard,
	int player, int squarePlayed, int whichPiece, int& numberCaptured)
{
	int row = 0;
	int col = 0;
	int numCaptured = 0;
	
	

	row = squarePlayed / numRowsInBoard;
	col = squarePlayed % numRowsInBoard;

	if (whichPiece == FIRST_PIECE)
	{
		bool north = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 0, 1, numCaptured);
		bool east  = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, 0, numCaptured);
		bool south = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 0,-1, numCaptured);
		bool west = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, 0, numCaptured);
		
		if (north == false && east == false && south == false && west == false)
		{
			cout << "Illegal move" << endl;
			return false;
		}
		else 
		{
			numCaptured = 0;
			// north
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 0, 1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row + counter][col] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// east
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, 0, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row][col+counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// south
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 0, -1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row - counter][col] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// west
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, 0, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row][col - counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// northeast 
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, 1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row + counter][col + counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// southeast
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, -1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row - counter][col + counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// southwest
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, -1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row - counter][col - counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// northwest
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, 1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row + counter][col - counter] = player;
				}
				numberCaptured += numCaptured;
			}
			FlipFlopBoard[row][col] = player;


			if (player == WHITEPLAYER)
			{
				cout << "White has placed the first piece" << endl;
			}
			if (player == BLACKPLAYER)
			{
				cout << "Black has placed the first piece" << endl;
			}
		}
	}

	if (whichPiece == SECOND_PIECE)
	{
		bool northeast = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, 1, numCaptured);
		bool southeast = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, -1, numCaptured);
		bool southwest = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, -1, numCaptured);
		bool northwest = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, 1, numCaptured);

		if (northeast == false && southeast == false && southwest == false && northwest == false)
		{
			cout << "Illegal move" << endl;
			return false;
		}
		else
		{
			numCaptured = 0;
			// north
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 0, 1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row + counter][col] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// east
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, 0, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row][col + counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// south
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 0, -1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row - counter][col] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// west
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, 0, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row][col - counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// northeast 
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, 1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row + counter][col + counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// southeast
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, 1, -1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row - counter][col + counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// southwest
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, -1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row - counter][col - counter] = player;
				}
				numberCaptured += numCaptured;
			}

			numCaptured = 0;
			// northwest
			if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, -1, 1, numCaptured))
			{
				for (int counter = 1; counter <= numCaptured; counter++)
				{
					FlipFlopBoard[row + counter][col - counter] = player;
				}
				numberCaptured += numCaptured;
			}

			FlipFlopBoard[row][col] = player;
			if (player == WHITEPLAYER)
			{
				cout << "White has placed the second piece" << endl;
			}
			if (player == BLACKPLAYER)
			{
				cout << "Black has placed the second piece" << endl;
			}
		}
	}
	return true;
}