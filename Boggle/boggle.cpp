#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include <Dictionary.h>

//variables used in all method but did not need to be declared a lot
string board;
const int XMOVES [8] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int YMOVES [8] = {-1, -1, -1, 0, 0, 1, 1, 1};
vector<string> solutions;
Dictionary d;

void findWords(string letters, int position, vector<int> positions) {
  //I translated the system over to act as a fake 2D array so the logic would be easier
  //The system then checks if the new posisiton is in bounds and not previously crossed
  //if the spot can be used the system uses it and adds it to the sequence of letters
  //the equence of letters is then checked during every new move to see if it is a word
  
  //declaring basic variables
  int xPos, yPos, xNewPos, yNewPos; 
  positions.push_back(position);
  letters.append(board.substr(position, 1));

  //loops through the 8 different moves
  for(int i = 0; i < 8; i++) {
    xPos = position % 4;
    yPos = position / 4;
    xNewPos = xPos + XMOVES[i];
    yNewPos = yPos + YMOVES[i];
    
    //converting the fake 2D to a single number
    int newPos = yNewPos * 4 + xNewPos;

    //checks the spot has been used before
    bool contains = false;
    for(unsigned int j = 0; j < positions.size() && !contains; j++) {
      if(positions[j] == newPos) {
        contains = true;
      }
    }

    //checks if the movement will keep in the bound of the board
    bool inBounds = false;
    if(xNewPos < 4 && yNewPos < 4 && xNewPos > -1 && yNewPos > -1) {
      inBounds = true;
    }

    //checks if the two just determined parameters are as wanted
    if(inBounds && !contains) { 
      //checks if the letters are a word and adds if it has not already been
      if(d.isWord(letters)) {
        bool alreadyIn = false;

        for(unsigned int k = 0; k < solutions.size(); k++) {
          if(solutions[k] == letters) {
            alreadyIn = true;
          }
        }
        if (!alreadyIn) {
          solutions.push_back(letters);
        }
      }

      //makes a recursive call so the method moves from the new position
      findWords(letters, newPos, positions);
    }
  }
}

void sortSolutions() {
///selects the highest value and put it at the bottom until the whole vector is sorted.
  for(unsigned int i = 0; i < solutions.size(); i++) {
    //grab the first location
    int loc = 0;
    string bigOne = solutions[0];

    for(unsigned int j = 1; j < solutions.size() - i; j++) {
      //checks how the strings compare and changes the saved one if larger
      if(solutions[j].compare(bigOne) > 0) {
        bigOne = solutions[j];
        loc = j;
      }
    }

    //moves around the pieces
    string save;
    save = solutions[solutions.size() - (1 + i)];
    solutions[solutions.size() - (1 + i)] = bigOne;
    solutions[loc] = save;
  }
}

int main() {  
  //asks the user to imput a board and confirms the code has started running
  cout << "enter board: ";
  cin >> board;
  cout << "starting solve." << endl;
  vector<int> pos;
  
  //calls fin words for every location
  for(unsigned int starts = 0; starts < 16; starts++) {
    findWords("", starts, pos);
  }

  //sorts the set of solutions
  sortSolutions();


  //output
  cout << "Found: " <<  solutions.size() << " words." << endl;
  sortSolutions();
  for(unsigned int i = 0; i < solutions.size(); i++) {
    cout << solutions[i] << endl;
  }

}
