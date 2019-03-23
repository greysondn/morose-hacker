/**
 * @file fibRecurse.cpp
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/**
 * Calculates a fibonnaci number using recursion
 *
 * @param index the index of the fibonnaci number to calculate, starting with 1
 * 
 * @return the fibonacci number at index. If you gave too large an index or a
 *              bad one, odds are good you're getting back a negative number.
 */
int fibRecurse(int index)
{
    // bad default deliberately
    int ret = -42;
    
    if (index <= 0)
    {
        // still pass, user's still an idiot
    }
    else if ((index == 1) || (index == 2))
    {
        // still handle first two the same way
        ret = 1;
    }
    else
    {
        // here's where it gets interesting
        // a fibonacci number is just the sum of the preceeding two fibonacci
        // numbers... right? So then we can just add those together.
        ret = (fibRecurse(index -1) + fibRecurse(index -2));
    }
    
    // end
    return ret;
}

/**
 * main program entry point
 */
int main()
{
    int userIndex = -1;
    
    cout << endl <<
    "Hi! This calculates a fibonacci number using recursion. Please" << endl <<
    "input the index you'd like to have the number for! The index" << endl <<
    "must be greater than or equal to 1, and due to how this is" << endl <<
    "programmed I can only do to the 23rd index accurately." << endl << endl <<
    "> ";
    
    cin >> userIndex;
    
    cout << "The fibonnacci number for index " << userIndex << " is:" << endl <<
         fibRecurse(userIndex) << endl;
}