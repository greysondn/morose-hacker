/**
 * @file hangman.cpp
 */

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <chrono>

int randNumber(int max) {
    //Generate a number at random between 0 and max
    int ret = -1;
    unsigned rngSeed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(rngSeed);

    uniform_int_distribution<int> die(0, max);
    ret = die(generator);

    return ret;
}

void txtOutput(string output, bool endLine) {
    //Send output to the console. Only really useful this way if we wanted to change from using cout to something else

    /*
     * Can't use this function with what I know about C++
     * cannot use << as part of an arg
     * cannot convert int to string
    */

    cout << output;
    if (endLine) {
        cout << endl;
    }
}

string getFromConsole() {
    //Get input from the console, setting this up to allow the player to attempt to guess the whole word
    string txtInput;

    getline(cin,txtInput);

    return txtInput;
}

/**
 * Gets a string from a user, with prompt
 * 
 * @param prompt text to prompt the user with
 * 
 * @return the user's response to prompt
 */
string getStringFromConsole(string prompt) {
    string ret;
    cout << prompt << endl << "> ";
    getline(cin,ret);
    return ret;
}

/**
 * checks whether a string has a given character
 * 
 * @param character the character we're checking for
 * @param searchString the string we'd like to search in
 * 
 * @return true if character in searchString, false otherwise.
 */
bool hasChar(char character, string searchString) {
    // default to false in this case
    bool ret = false;
    
    // actual search
    for (int i = 0; i < searchString.length(); i++) {
        if (searchString[i] == character) {
            // we've found it, it exists in search string
            ret = true;
        }
    }
    
    // end
    return ret;
}

/**
 * Reveals character in a way similar to Wheel of Fortune, I guess.
 * 
 * @param solution     what a solved board would look like
 * @param currentBoard what our current in-game board looks like
 * @param charToReveal character we'd like to reveal in currentBoard
 * 
 * @return basically, currentBoard with charToReveal revealed.
 */
string revealChar(string solution, string currentBoard, char charToReveal) {
    // truth be told, we just need to start with current board.
    string ret = currentBoard;
    
    // and now, we reveal it
    for (int i = 0; i < solution.length(); i++) {
        if (solution[i] == charToReveal) {
            // flip the panel please, Vanna.
            ret[i] = solution[i];
        }
    }
    
    // done
    return ret;
}


void indexesOf(char search, string source, int (&ret)[10]) {
    // your comments are now outdated I'm afraid - greyson
    // also remember that I asked you to not use this - greyson
    
    // My understanding is that this won't work, but this is how I'd do this
    // indexOf and lastIndexOf are nice, but don't work if there's more then 1
    // instance of a character in the string to search, I want to know all of them
    // So ret[0] will tell us how many elements were found
    // ret[1]...ret[9] will actually have the found indexes in them
    char chrSource;

    for (int i = 0; i < source.length(); i++) {
        chrSource = source[i];
        if (search == chrSource) {
            ret[0] += 1;
            ret[ret[0]] = i;
        }
    }
}

int main() {
    //main game loop goes here
    //Need to do:
    //1. define a list of words to choose from
    //2. pick one of them
    //3. start the loop
    //4. display the current state of the game
    //5. wait for the player to input a guess (a-z)
    //6. check if the guess is found in the word
    //7. if it is, update the on screen word to match, if it isn't add the next part to the 'man
    //8. check if the word is solved or the 'man has been completed (the player has run out of guesses)
    //8a. end the game with either a win or loss if one of the above is true
    //8b. loop back to the start if the above is not true

    //Define a list of words;
    string possibleWords[10] = { "hello", "wolf", "steel", "pray", "launch", "drag", "rain", "rabbit", "tough", "include" };

    //Pick a word at random, stupid 'random' system...
    string correctWord = possibleWords[randNumber(9)];

    int guessesRemain = 6; //Starts with 6, counts down from there
    string correctGuess = " "; //Tracking what the player has gotten right so far
    string lettersGuessed = " "; //Tracking what the player has guessed
    string playerGuess;

    // whether the game is over
    bool gameEnd = false;
    
    // whether the player won
    bool playerWon = false;
    
    // whether player chose to quit early instead of finishing the game
    bool playerQuit = false;

    //Gameplay Loop
    while (!gameEnd) {
        //Display the current state of the game
        cout << "You currently have " << guessesRemain << " guesses." << endl;
        cout << "You have guessed; " + lettersGuessed << endl;
        cout << "You have correctly guessed; " << correctGuess << endl;
        cout << "Your next guess? ";

        playerGuess = getFromConsole();

        // I went ahead and rewrapped this if/else-if/else.
        // I think this is wrong - you want to handle checking for win AFTER you
        // handle checking player's guess. A win state can come only after
        // a turn. However, I'll leave that as an exercise to you. ~greyson
        if ("QUIT" == playerGuess) {
            //Player chooses to quit early. Programs should always be exable by a "clean" means
            gameEnd = true;
            playerQuit = true;
        } else if (correctWord == playerGuess) {
            //Player has guessed the word correctly
            gameEnd = true;
            playerWon = true;
        } else {
            playerGuess = playerGuess[0]; //Only care about the first letter. Everything else is garbage
        }
    }
    return 0;
}