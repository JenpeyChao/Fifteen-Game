/*
 *Name: Jenpey Chao
 *Date: 2/12/20
 *email: jchao1@umbc.edu
 *description: we're making a game called Fifteen. we're suppose to read a board from a txt file and be able to solve it
*/
//zero is considered a blank spot
#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

//function prototypes
void readBoard (const char* name, int board[][4], int numCol);
const char* chooseBoard ();
void printBoard (int board[][4], int numCol);
void switchSpot (int board[][4], int numCol);
bool checkWinner (int board[][4], int numCol);
bool playAgain();


int main() {

  bool answer = true;
  
  while(answer){
    
  
    bool trueOrFalse = false;
    int boardArray[4][4];


    const char* boardName = chooseBoard();
    

    readBoard(boardName, boardArray, 4);
    
    printBoard(boardArray, 4);
    
    while (trueOrFalse == false) {
      //if the board isnt complete then it will keep running
      //until checkWinner turns true
      
      switchSpot(boardArray, 4);
      
      printBoard(boardArray, 4);

      trueOrFalse = checkWinner(boardArray, 4);

      if (trueOrFalse == false)
	cout << "No winner" << endl;
      
    }
    
    answer = playAgain();
  }
  //if the user says no it will send out the msg and stop
  cout << "Thank you for playing the game of fifteen" << endl;
  
  return 0;
}


const char* chooseBoard() { //askes for the name of the board, and returns the name of the board
  
  int yesOrNo = 0;
  int test3 = 0;
  int test2 = 0;
  char test3Name[16] = "proj1_test3.txt";
  char test2Name[16] = "proj1_test2.txt";
  char fileName[16] = "proj1_test1.txt";
  
  
  cout << "Welcome to the Fifteen Game" << endl;
  cout << "Would you like to load a board?" << endl;
  cout << "1. Yes" << endl << "2. No" << endl;
  // asks if you wanna load a board

  cin >> yesOrNo;

  if (yesOrNo == 2){
    // if not then it loads the default (test1 board)

    cout << "Loading default" << endl;

    return "proj1_test1.txt";
    
  } else {

    cout << "What is the file name?" <<endl;
    
    
    cin >> fileName;
    
    
    for (int x = 0; x < 15; x++){
      //checks if the input is the same as the test 2 and 3 files

      if (fileName[x] == test3Name[x]){
	// it adds one for every right word, as it compares
	test3 += 1;

      }if (fileName[x] == test2Name[x]){
	// it adds one for every right word, as it compares
	test2 +=1;

      }
    }

    if (test3 == 15){
      //if the input is the same as the test3 file, then it will load the test3 
      return "proj1_test3.txt";
    
    }else if (test2 == 15){
      // if the input is the same as the test2 file, then it will load the test2
      return "proj1_test2.txt";

    }
    else{
      //if the input is something else it will just load the default board
      
      return "proj1_test1.txt";
    }
  }
}





void readBoard(const char* name, int board[][4], int numCol) { //reads the file and appends it to the board array
  
  ifstream textFile;

  textFile.open(name);

  if (textFile.is_open()) {
    //opens the file 

    for (int row = 0; row < 4; row++) {
      
      for (int column = 0; column < numCol; column++) {
	// it appends whats on the text file on to the board
	
	textFile >> board[row][column];
	
      }
    }
  }
  textFile.close();
  //after it appends it closes the file
}


void printBoard(int board[][4], int numCol) { // prints out the board

  
  for (int header = 1; header < numCol + 1; header++) 
    // prints the columns for the board
    
    cout <<"      " << header << " ";
	 
  for (int row = 0; row < 4; row++) {
    //prints the row then the 4 numbers on the board 
    
    cout  << endl << row + 1 << "| ";
    
    for (int column = 0; column < numCol; column++) {
      // prints the 4 nubmers in the row
      
      cout << "\t" << board[row][column] << "|";

    }
  }
  cout << endl;
}


void switchSpot(int board[][4], int numCol) {
  
  int row = 0;
  int column = 0;
  const int MAXROWANDCOL = 4;
  const int MINROWANDCOL = 1;

  cout << "What is the row (left) and column (top) to slide?" << endl;
  //asks for a row and column to swap
  cin >> row;

  cin >> column;
  

  while ((row == 0 && column == 0) || ((row > MAXROWANDCOL || row < MINROWANDCOL) || (column > numCol || column < MINROWANDCOL))) {
    // if the row and column isnt between 1-4 it will repromt the question to the user
    
    cout << "What is the row (left) and column (top) to slide?" << endl;
    
    cin >> row;
    
    cin >> column;
  }    

  row -= 1; //returns the right numbers for the row and column
  column -= 1;//wont swap the wrong thing

  
  if (board[row][column] == 0){ //if the spot, the user picked, is a blank it will do nothing
    cout << "This is the blank spot" << endl;
    cout << "That tile cannot slide" << endl; 
  }
   
   
  if ( (column > 0 && column <= 3) && (board[row][column - 1] == 0)) {
    //checks the left side of the board
    // if theres a blank spot it swtiches
    int temp = 0;
      
    temp = board[row][column];
    
    board[row][column] = board[row][column - 1];
    
    board[row][column - 1] = temp;

    cout << "The tile slide left" << endl;
    
    
  }else if ((column >= 0 && column < 3) && (board[row][column + 1] == 0)) {
    //checks the right side for the blank spot
    // if theres a blank spot it switches
    int temp = 0;

    temp = board[row][column];

    board[row][column] = board[row][column + 1];

    board[row][column + 1] = temp;

    cout << "The tile slid right" << endl;
    
    
  }else if ((row > 0 && row <= 3) && (board[row - 1][column] == 0)){
    // checks the above for the blank spot
    //if theres a blank spot it switches
 
    int temp = 0;

    temp = board[row][column];

    board[row][column] = board[row - 1][column];

    board[row - 1][column] = temp;

    cout << "The tile slid upward" << endl;
    

  }else if ((row >= 0 && row < 3) && (board[row + 1][column] == 0)){
    //checks the bottom for the blank spot
    //if theres a blank spot on the bottom
    //it will swap with the spot you chose
    
    int temp = 0;

    temp = board[row][column];

    board[row][column] = board[row + 1][column];

    board[row + 1][column] = temp;

    cout << "The board slid down" << endl;

  }

  
  else {
    //if theres no blank spots, it will say and do nothing
    if (board[row][column] != 0){
      cout << "Theres no blank spot near by" << endl;
      cout << "The tile cannot slide" << endl;
    }
  }
}

bool checkWinner(int board[][4], int numCol) {
  //checks if the board is in correct order

  int winBoard[4][4] = { // the correct order the board should be in
			      {1, 2, 3, 4},
			      {5, 6, 7, 8},
			      {9, 10, 11, 12},
			      {13, 14, 15, 0}};


  int need16ToWin = 0; //if the board is in order you will get the number 16

  
  for (int row = 0; row < 4; row++){
    
    for (int column = 0; column < numCol; column++){

      if (board[row][column] == winBoard[row][column]){
	//compares the board array to the correct board to see if they won
	//adds one each time they are correct
       
	need16ToWin += 1;
	
      }
    }
  }

  if (need16ToWin == 16) {
    // if all of the numbers are in the corect spot then it returns true
    
    return true;
  }
  //else it returns false
  
  return false;
}
    

bool playAgain() {
  char yesOrNo;

  
  cout << "Congrats you've won!" << endl;
  cout << "Play again? (y/n) ";
  cin >> yesOrNo;
  cout << endl;

  if (yesOrNo == 'y'){ //if the user says yes then it restarts 
    return true;
  }

   else{//anything else it closes
    return false;
  }
}
