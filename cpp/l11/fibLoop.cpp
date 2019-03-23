/**
 * @file fibLoop.cpp
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/**
 * Calculates a fibonnaci number using loops
 *
 * @param index the index of the fibonnaci number to calculate, starting with 1
 * 
 * @return the fibonacci number at index. If you gave too large an index or a
 *              bad one, odds are good you're getting back a negative number.
 */
int fibLoop(int index)
{
    // can never be a negative 
    int ret = -42;
    
    // we need two numbers
    int first = 1;
    int second = 1;
    
    // check for special cases
    if (index <= 0)
    {
        // just return as is, user's an idiot
    }
    else if ((1 == index) || (2 == index))
    {
        // Those are both 1
        ret = 1;
    }
    else
    {
        // actually calculate for index.
        // next value
        int next = -1;
        
        for (int current=2; current < index; current++)
        {
            next = first + second;
            first = second;
            second = next;
        }
        
        // current is tracking where second is, so that will be our return
        ret = second;
    }
    
    // return
    return ret;
}

/**
 * main program entry point
 */
int main()
{
    int userIndex = -1;
    
    cout << endl <<
    "Hi! This calculates a fibonacci number using loops. Please" << endl <<
    "input the index you'd like to have the number for! The index" << endl <<
    "must be greater than or equal to 1, and due to how this is" << endl <<
    "programmed I can only do to the 23rd index accurately." << endl << endl <<
    "> ";
    
    cin >> userIndex;
    
    cout << "The fibonnacci number for index " << userIndex << " is:" << endl <<
         fibLoop(userIndex) << endl;
}