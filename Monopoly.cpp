// Kyle Fraser
// p4.cpp
// 12/6/18

// Purpose: The purpose is to create a monopoly game that allows 2 to 6
// players to buy and sell property until a player goes broke or
// forfeits

// Description: The game of monopoly is a retail-based board game.
// The user will let the game know if they want to play.
// The user will input the number of players, and then names
// for the corresponding number of players.
// The players will roll dice in order to move along the gameboard.
// Each space on the game board is either a property to buy, sell,
// and rent for the players, or a special space that has a specific
// purpose. the game is over once a player runs out of money
// or forfeits. The winnner is the player with the most money
// at the end of the game. 


// Input: prompt to begin game, prompt to play again,
// names from the user, number of players, prompt for forfeit decision,
// decision to buy property, and press enter to continue

// Process: input will set up the board if the user decides
// to play the game. The number of players inputted is the number of players
// in the game.
// inputted names will appear for individuals throughout
// the game.
// A player will decide whether they want to buy a certain property.
// players use ownership of property to take money from other
// players if another players lands on a property owned by them.
// if a player forfeits then this player loses and the game is over


// Output: Messages to update the game, the winner of the game, the loser
// of the game, a welcome message, and a goodbye message.

// example:
// kevin, you have $1500
// You are currently on Go
// kevin, press enter to roll the dice...

// rolling dice... press enter for result...
// kevin, you rolled a 6

// you landed on James tower
// this building is unowned and costs $500 to buy
// you have 1500

// would you like to purchase this property?(y/n)y

// kevin, you now own James tower
// you now have $1000

#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

struct Property
{
  string name;
  int owner;
  int cost;
  int rent;
};

struct PlayerDetails
{
  string name;
  int location;
  int wealth;
}; 

const int MAX_SPIN = 6;
const int ARRAYSIZE = 7;
const int MIN_SPIN = 1;
const int START = 0;
const char YES = 'y';
const int MAX = 45;
const int startBalance = 1500;
const string FILEN = "/home/fac/sreeder/class/cs1420/p4input.dat";
const string GO = "Go";
const string CHAPEL = "Chapel of St. Ignatius";
const string CHANCE = "Chance";
const string FEES = "Fees";
const string TAX = "Income Tax";
const string DEAN = "Dean Jacob Diaz Office";
const char BUY = 'y';
const char QUIT = 'y';



void welcome();
// Outputs a welcome message

int rollDie();
// rolls the dice

int setup(Property spot[], PlayerDetails players[], int& count);
// sets up the game
// gets number of players and names of players
// initialized player money and location
void takeTurn(Property spot[], PlayerDetails players[],
              int count, int playerNumber);
// takes a turn for each player
int checkLocation(Property spot[], PlayerDetails players[], int count,
                  int playerNumber, int playerI);
// checks the location of the player

int findWinner(PlayerDetails players[], int playerNumber);
// finds the winner of the game

int findChapel(PlayerDetails players[], Property spot[], int count,
               int playerI);
// finds the chapel if needed for chance

void goodbye();
// Outputs a goodbye message

int main()
{
  int count = 0;
  char ans;
  Property property[MAX];
  PlayerDetails players[ARRAYSIZE];
  int playerNumber;
  
  
  welcome();
  
  cout << endl;
  cout << "Would you like to play?(y/n) ";
  cin >> ans;
  cin.ignore();
  cout << endl;
  
  while(tolower(ans) == YES){
    
    playerNumber = setup(property, players, count);
    takeTurn(property, players, count, playerNumber);
      

    cout << endl;
    cout << "Would you like to play again?(y/n) ";
    cin >> ans;
    cout << endl;
    cin.ignore();
  }
  
  goodbye();
  
  return 0;
  
}


void welcome()
{
  cout << endl;
  cout << "Welcome to the game of Monopoly! " << endl;
  cout << "Challenge your friends in this exciting " << endl;
  cout << "retail-based board game." << endl;
  
}

int rollDie()
{
  

  int random = (rand() % (MAX_SPIN - MIN_SPIN + 1)) + MIN_SPIN;
  
  return random;
}

int setup(Property property[], PlayerDetails Players[], int& count)
{
  ifstream infile;
  infile.open(FILEN.c_str());
  int playerNum;
  int name;

  if(infile.fail()){
    cout << endl << endl;
    cout << "File Failed to open...";
    cout << "Press enter to continue...";
    cin.get();
    cout << endl << endl;
    return 0;

  }
   
  while(count < MAX && getline(infile, property[count].name)){
    infile >> property[count].owner
           >> property[count].cost
           >> property[count].rent;
    infile.ignore();
    count++;
  }
  
  infile.close();
  
  cout << endl << endl;
  cout << "How many players?(2-6) ";
  cin >> playerNum;
  cin.ignore();
  cout << endl;
  cout << "Turns will be in the order of players entered... ";
  cout << endl;
  cout << "Press enter to continue...";
  cin.get();
  while(playerNum > 6 || playerNum < 2){
    cout << endl << endl;
    cout << "Must have between 2 and 6 players " << endl;
    cout << "How many players?(2-6)";
    cin >> playerNum;
    cin.ignore();
  }
    
  cout << endl;
  cout << "There are " << playerNum << " players in the game!";
  cout << endl;
  for(name = 1; name <= playerNum; name++){
    cout << endl;
    cout << "Please enter a name: ";
    cin >> Players[name].name;
    cin.ignore();
    cout << Players[name].name << ", welcome to Monopoly." << endl;
    Players[name].wealth = startBalance;
    Players[name].location = START;
    cout << endl;
  }
  cout << "All players will start on " << GO;
  cout << " with $" << startBalance << endl;
  return playerNum;  
}
void takeTurn(Property property[], PlayerDetails players[], int count,
              int playerNumber)
{
  int winnerIndex;
  char forfeit;
  int playerI;
  bool gameOver = false;
  int bothRoll;
  srand(time(0));
  cout << endl << endl;
  cout << " Press enter to continue...";
  cin.get();
 
  while(gameOver == false){
    
    for(playerI = 1; playerI <= playerNumber; playerI++){
      srand(time(0));
       bothRoll = rollDie() + rollDie();
      cout << endl << endl;
      cout << players[playerI].name << ", You have $";
      cout << players[playerI].wealth << ". " << endl;
      cout << "You are currently on ";
      cout << property[players[playerI].location].name << endl;
      cout << players[playerI].name;
      cout << ", Press enter to roll the dice... ";
      cin.get();
      cout << endl;
      cout << "Rolling dice... Press enter for result...";
      cin.get();
      cout << endl;
      cout << players[playerI].name << ", you rolled a " << bothRoll;
      cout << endl << endl;
      players[playerI].location += bothRoll;
      players[playerI].wealth = checkLocation(property, players,
                                              count, playerNumber, playerI);
      cout << endl;
      cout << "Would you like to forfeit?(y/n) ";
      cin >> forfeit;
      cin.ignore();
        if(tolower(forfeit) == QUIT){
        cout << endl << endl;
        players[playerI].wealth = 0;
        cout << players[playerI].name << " forfeited. Gameover! " << endl;
        winnerIndex = findWinner(players, playerNumber);
        cout << endl;
        cout << "The winner is " << players[winnerIndex].name << "! ";
        cout << endl;
        gameOver = true;
        
      }
       if(players[playerI].wealth <= 0){
        cout << endl << endl;
        cout << players[playerI].name << " lost. Gameover! " << endl;
        winnerIndex = findWinner(players, playerNumber);
        cout << endl;
        cout << "The winner is " << players[winnerIndex].name << "! ";
        cout << endl;
        gameOver = true;
         
      }
      else if(players[playerI].wealth > 0){
        gameOver = false;
      }
      
    }
    
  }

  
  
}


int checkLocation(Property property[], PlayerDetails players[], int count,
                  int playerNumber, int playerI)
{
  int unowned = 0;
  int cannotOwn = -1;
  char decision;
  int position = players[playerI].location;
  int owned;
  int bothRoll1 = rollDie() + rollDie();
  int temporary;
  int singleRoll;
  
  if((position + bothRoll1) > count){
    temporary = position + bothRoll1;
    temporary = temporary - count;
    position = temporary;
    players[playerI].location = position;
    cout << endl << endl;
    cout << "You have passed go! Collect $200 " << endl;
    players[playerI].wealth += 200;
  }
  if(property[position].owner == playerI){
    cout << endl;
    cout << "You landed on " << property[position].name << endl;
    cout << "You own this property, take a rest. " << endl;
    cout << "Press enter to continue...";
    cin.get();
  }
  else if(property[position].owner == unowned){
    cout << endl << endl;
    cout << "You landed on " << property[position].name << endl;
    cout << "This Building is unowned and costs $";
    cout << property[position].cost << " to buy ";
    cout << endl;
    cout << "You have $" << players[playerI].wealth << endl;
    cout << "Would you like to purchase this property?(y/n)";
    cin >> decision;
    cin.ignore();
    if(tolower(decision) == BUY){
      if(players[playerI].wealth <= property[position].cost){
        cout << endl;
        cout << "Sorry, this property is too expensive." << endl;
        cout << "Press enter to continue...";
        cin.get();
        
      }
      else{
        cout << endl << endl;
        players[playerI].wealth -= property[position].cost;
        cout << players[playerI].name << ", you now own ";
        cout << property[position].name;
        cout << endl;
        cout << "You now have $" << players[playerI].wealth;
        property[position].owner = playerI;
        cout << endl << endl;
       
          
      }
    }
    
    
  }
  if(property[position].owner != playerI
     && property[position].owner > unowned){
    cout << endl << endl;
    owned = property[position].owner;
    cout << "You landed on " << property[position].name << ". " << endl;
    cout << "This building is owned by " << players[owned].name << endl;
    cout << "Pay " << property[position].rent << " to ";
    cout << players[owned].name;
    cout << endl;
    players[playerI].wealth -= property[position].rent;
    players[owned].wealth += property[position].rent;
    cout << endl;
    cout << players[playerI].name << " has " << "$";
    cout << players[playerI].wealth;
    cout << endl << endl;
    cout << players[owned].name << " has " << "$";
    cout << players[owned].wealth;
    cout << endl << endl;
  }

  else if(property[position].owner == cannotOwn){
    if(property[position].name == CHAPEL){
        
      cout << endl << endl;
      cout << "You've landed on the Chapel of St. Ignatius, ";
      cout << "take a rest " << endl << endl;
    }
    else if(property[position].name == DEAN){
      cout << endl << endl;
      cout << "You've landed on the Deans office, take a rest.";
      cout << endl << endl;
    }
    
    else if(property[position].name == CHANCE){
      cout << endl << endl;
      cout << "You must roll a 1, 2, or 3 for a bonus of $50" << endl;
      cout << endl;
      singleRoll = rollDie();
      cout << "Press enter to roll the dice... ";
      cin.get();
      cout << endl << endl;
      cout << "You rolled a " << singleRoll << endl;
      if(singleRoll >= 1 && singleRoll <= 3){
        players[playerI].wealth += 50;
        cout << "Your new balance is $" << players[playerI].wealth;
        cout << endl;
        
      }
      else if(singleRoll >= 4 && singleRoll <= 6){
        cout << endl;
        cout << "Move to the Chapel of St. Ignatius and take a rest. ";
        cout << endl;
        cout << "Do not collect $200 if go is passed " << endl;
        position = findChapel(players, property, count, playerI);
        cout << "You are on ";
        cout << property[findChapel(players, property, count, playerI)].name;
        cout << endl << endl;
        
        
      }
    }
  
    else if(property[position].name == FEES){
      cout << endl << endl;
      cout << "You landed on fees! You owe $400 to the bank " << endl;
      players[playerI].wealth -= 400;
      cout << "You now have $" << players[playerI].wealth;
      cout << endl;
      
    }
    else if(property[position].name == TAX){
      cout << endl << endl;
      cout << "You landed on income tax! You owe $200 to the bank " << endl;
      players[playerI].wealth -= 200;
      cout << endl;
    }
  }
  
      
  return players[playerI].wealth;
}

   
int findWinner(PlayerDetails players[], int playerNumber)
{
  int indexOfMax = 1;
  
  for(int i = 1; i < playerNumber; i++){
    if(players[i].wealth >= players[indexOfMax].wealth){
      indexOfMax = i;
    }
    
  }
  return indexOfMax;  
  
}

int findChapel(PlayerDetails players[], Property property[],
               int count, int playerI)
{
  int  position = players[playerI].location;
  for(int chapelIndex = 0; chapelIndex < count; chapelIndex++){
    if(property[chapelIndex].name == CHAPEL){
      position = chapelIndex;
    }
  }
  
  return position;
      

}


void goodbye()
{
  cout << endl;
  cout << "Thank you for playing Monopoly! " << endl;
  cout << "Goodbye ";
  cout << endl << endl;

}


