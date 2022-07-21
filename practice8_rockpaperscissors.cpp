//these are our headers.  In C++, headers are like game DLC.  They add extra tools.  C++ is modular like that.
#include <random> //random provides the random generation stuff used in roller().
#include <iostream>
#include <algorithm>//algorithm provides the stuff for converting to lowercase in int main().
using namespace std;

//the purpose here is to practice with arrays and functions in C++.  Well, it was.  But I guess I didn't actually end up using arrays that much.
//Anyway, this is a Rock, Paper, Scissors game.

//the roller function accepts a minimum and maximum range as integers and returns a random number within that range.
int roller(int min, int max)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

//function computerPlay() selects either rock (r), paper (p), or scissors (s) at random and returns the result.
char computerPlay()
{
    char compHand[3] = {'r', 'p', 's'}; //declare an array consisting of each of the possible results.  We use char instead of string because switch constructs don't work with strings in C++ like they do in JavaScript
    int compChoice = roller(0, 2);    
    return compHand[compChoice];
}

int main()
{
    /* Psuedocode:
    the program greets the player
    the program requests input from the player
    the player gives input
    the program validates input
    if the input is good, the program then creates a result for the CPU
    if the input is not good, the program declares to the player that the input is not good
        it asks if the player would like to try again.
    the CPU chooses an option randomly
    the CPU's choice is declared to the player
    the player's input is compared to the CPU's
    the results are then declared to the player, based on the comparison.
    the program then asks if the player would like to try again. */

    string playerChoice = "empty"; //it's considered best practice to give your variables some kind of initial value when you declare them, instead of leaving them empty.
    string gameResult = "empty";
    string tryAgain = "y";
    char playerInput = 'c';
    char compInput = 'c';
    while (tryAgain == "y")
    {
        cout << "Welcome to Rock, Paper, Scissors!  Please enter your choice for the game and press Enter.\n";
        cin >> playerChoice; //record player's input and store it in playerChoice
        std::transform(playerChoice.begin(), playerChoice.end(), playerChoice.begin(), [](unsigned char c){ return std::tolower(c); });//so first for simplicity, we want to make make all the characters the same case, for input validation purposes.  This is more annoying to do in C++ than it is in JavaScript, and tbh I'm not entirely sure what's going on here.  The goal is to covert the input entirely to lowercase.
        if ((playerChoice == "rock") || (playerChoice == "paper") || (playerChoice == "scissors"))// input validation.  we need to check if the player's input is usable.  interestingly, compared to JavaScript C++ is more strict about how it interprets logical expressions.  In JavaScript, if(playerChoice == "rock" || "paper" || "scissors") would validate the same way, but here that creates a problem.
        {
            if (playerChoice == "rock") //switch constructs in C++ dont work with strings, so we need to take an extra step and convert to something compatible.  in this case we'll use char.
            {
                playerInput = 'r';                
            }
            else if (playerChoice == "paper")
            {
                playerInput = 'p';
            }
            else if (playerChoice == "scissors")
            {
                playerInput = 's';
            }

            compInput = computerPlay(); //once the player results are accepted and prepared, we run computerPlay to get the CPU's choice.

            if (compInput == 'r')//now we declare to the player what the CPU chose.
            {
                cout << "The computer chose rock.\n";
            }
            else if (compInput == 'p')
            {
                cout << "The computer chose paper.\n";
            }
            else if (compInput == 's')
            {
                cout << "The computer chose scissors.\n";
            }
            
            switch (playerInput)//next comes the part where we figure out who won by comparing the two results.  switch seemed like the most efficient way to do this, as i don't like using a bunch of if+else if statements if i dont need to.
            {
                case 'r':
                    switch (compInput)
                    {
                        case 'r':
                            gameResult = "Interesting, you tied!";
                            break;
                        case 'p':
                            gameResult = "Sorry, you lost!";
                            break;
                        case 's':
                            gameResult = "Congratulations, you won!";
                            break;
                    }
                    break;

                case 'p':
                    switch (compInput)
                    {
                        case 'r':
                            gameResult = "Congratulations, you won!";
                            break;
                        case 'p':
                            gameResult = "Interesting, you tied!";
                            break;
                        case 's':
                            gameResult = "Sorry, you lost!";
                            break;
                    }
                    break;

                case 's':
                    switch (compInput)
                    {
                        case 'r':
                            gameResult = "Sorry, you lost!";
                            break;
                        case 'p':
                            gameResult = "Congratulations, you won!";
                            break;
                        case 's':
                            gameResult = "Interesting, you tied!";
                            break;        
                    }
                    break;
            }
            cout << gameResult; //truthfully, i could have just had this cout at the end of every switch branch above, but i prefer it this way.
            cout << "\nDo you want to play again?  Please enter 'y' and press Enter if so.  Otherwise, input any other letter and press Enter to exit.\n";
            cin >> tryAgain;
        }
        else
        {
            cout << "Sorry, I don't understand that input. Would you like to try again?  Please enter 'y' if so, or anything else if not.\n";//if the player input is not good, this is what they get, and for now the program ends.  it would be cool if i could get it to loop back so they can input something else.
            cin >> tryAgain;            
        }
    }
}