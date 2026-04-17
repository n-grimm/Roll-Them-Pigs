/*
    File: Roll'em Pigs!
    Author: Nathan Grimm
    Date: 2026-03-26



    Description: Plays the game of pig by rolling two dice and adding up the scores as long as there is no ones.
    The game ends when either the player or computer rolls at least 100 points
*/

#include<iostream>
#include<string>
#include<random>
using namespace std;

string start(void);

char getInput(void);

bool isWinningScore(int score);

bool isTurnPointsLost(int die1value, int die2value);

bool isGameScoreLost(int die1value, int die2value);

int rollDie(void);





int main()
{
    int p1_total = 0; // Holds the total amount of points for player
    int p2_total = 0;// Holds the total amount of points for computer
    int die1 = 0;// holds dice value for first dice
    int die2 = 0;// holds dice value for second dice
    int turnPoints = 0; // holds points per turn
    string Begin = "";// holds begin for starting
    char user_decision = ' '; // holds what user inputs
    bool gameOver = false; // holds whether game is over
    bool turnOver = false; // holds whether turn is over

    Begin = start();// asks user if they want to start or not

    if (Begin == "Begin") // Game starts if user gives correct input
    {

        while (!gameOver) // computes while gameOver is false
        {

            turnPoints = 0; // resets points
            bool turnOver = false; //starts turn again




            cout << "\n Your Turn: (Game score: " << p1_total << ")\n\n"; //shows total

            while (!turnOver) // computes while turn is still going
            {
                die1 = rollDie(); // make a random value for dice 1 value
                die2 = rollDie();// make a random value for dice 2 value
                cout << "You rolled: " << die1 << " and " << die2 << "\n\n"; // tells what player rolled

                if (isGameScoreLost(die1, die2)) //resets game points and ends turn if 2 dice rolls equal 1
                {
                    cout << "Double 1s! You lose your entire game score!\n\n";
                    p1_total = 0;
                    turnOver = true;
                }
                else if (isTurnPointsLost(die1, die2)) //resets turn points and ends turn if either dice roll equal 1 
                {
                    cout << "Rolled a 1! You lose your turn points.\n\n";
                    turnOver = true;
                }
                else // adds points if no ones are rolled and asks if user wants to roll again
                {
                    turnPoints += die1 + die2;
                    cout << "Turn points: " << turnPoints << " | Game score: " << p1_total << "\n\n";

                    user_decision = getInput();
                    if (user_decision == 'e') // end turn if user types e
                    {
                        p1_total += turnPoints;
                        turnOver = true;
                    }
                }
            }

            if (isWinningScore(p1_total)) // Player wins if their score is at leats 100
            {
                cout << "You win! Final score: " << p1_total << "\n\n";
                gameOver = true;
                break;
            }


            turnPoints = 0; // resets turnPoints
            turnOver = false;  // resets turn
            cout << "\n  Computer's Turn: (Game score: " << p2_total << ")" << "\n"; // shows computers score

            while (!turnOver)
            {
                die1 = rollDie();// gets value for computers dice 1
                die2 = rollDie();// gets value for computers dice 2
                cout << "Computer rolled: " << die1 << " and " << die2 << "\n"; // show what computer rolled

                if (isGameScoreLost(die1, die2)) //sees if both dice equals
                {
                    cout << "Computer rolled double 1s! Loses entire game score!\n\n";// removes all points and ends turn if two 1s are rolled
                    p2_total = 0;
                    turnOver = true;
                }
                else if (isTurnPointsLost(die1, die2)) //ends turn and no points are won if a 1 is rolled
                {
                    cout << "Computer rolled a 1! Loses turn points.\n\n";
                    turnOver = true;
                }
                else // adds points if no ones are rolled and asks if user wants to roll again
                {
                    turnPoints += die1 + die2;
                    cout << "Computer turn points: " << turnPoints << " | Game score: " << p2_total << "\n\n";

                    if (turnPoints >= 20 || isWinningScore(p2_total + turnPoints))//stops computer from rolling past 20 points
                    {
                        p2_total += turnPoints;
                        cout << "Computer ends turn. Game score: " << p2_total << "\n\n";
                        turnOver = true;
                    }
                }
            }


            if (isWinningScore(p2_total)) // ends game if computer rolls at least 100 points
            {
                cout << "Computer wins! Final score: " << p2_total << "\n\n";
                gameOver = true;
            }

        }
    }
    return 0;
}


/**
computes whether to start the program or not
@return "Begin" if the user enters a valid START phrase.
*/

string start(void)
{
    string starting = "";
    while (true)
    {
        cout << " Enter START to begin" << endl;
        cin >> starting;
        if ((starting == "start") || (starting == "START") || (starting == "Start"))
        {
            return "Begin";
        }
        else
        {
            cout << "Invalid Input - Try Again" << endl;
            return start();
        }
    }
}
/**
    computes whether to roll again or end turn
    @ return either r for roll again, e for end turn, or get Input
*/
char getInput(void)
{
    char userInput = ' ';
    while (true)
    {
        cout << " Would You Like to: Roll Again (r) or End Turn (e)?" << endl;
        cin >> userInput;
        if ((userInput == 'r') || (userInput == 'R'))
        {
            return 'r';
        }
        else if ((userInput == 'e') || (userInput == 'E'))
        {
            return 'e';
        }
        else
        {
            cout << "Invalid Input - Try Again" << endl;
            return getInput();
        }
    }
}
/**
    computes whether a player has a winning score
    @param score the score of a player
    @return a score greater than or equal to 100
*/

bool isWinningScore(int score)
{
    if (score >= 100)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/**
    computes whether any dice scores are ones
    @param dice1value holds value of first dice roll
    @param dice2value holds value of second dice roll
    @return that either dice is equal to one

*/

bool isTurnPointsLost(int die1value, int die2value)
{
    return (die1value == 1) || (die2value == 1);
}

/**
computes whether both dice scores are ones
@param die1value holds value of first dice roll
@param dice2value holds value of second dice roll
@return true if both dice equal 1, false if they don't
*/
bool isGameScoreLost(int die1value, int die2value)
{
    return (die1value == 1) && (die2value == 1);
}
/**
computes a random dice roll
@return a random number between 1 and 6
*/
int rollDie(void)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 6);
    return dist(gen);
}