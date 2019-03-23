/**
 * @file ackermann.cpp
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/**
 * Ackermann's function.
 *
 * @param m M see ackermann's function elsewhere
 * @param n N see ackermann's function elsewhere
 *
 * @return A(m, n)
 */
unsigned long ackermann(unsigned long m, unsigned long n)
{
    // eventual return
    unsigned long ret = -1;
    
    // ackermann's function has only three clauses
    if (0 == m)
    {
        // m = 0 is our limit clause, where this stops recursing
        ret = n + 1;
    }
    else if (0 == n)
    {
        // n = 0 is just a special recursive case.
        ret = ackermann((m - 1), 1);
    }
    else
    {
        // in every other case is just recursion
        ret = ackermann((m -1), ackermann(m, (n - 1)));
    }
    
    // end
    return ret;
}

int main()
{
    unsigned long m = 0;
    unsigned long n = 0;
    
    cout << "This calculates ackermann numbers! Be aware your" << endl <<
            "machine isn't going to be useful for much while this is" << endl <<
            "running! THIS CAN TAKE LONGER THAN YOU REALIZE!" << endl <<
            endl <<
            "Ackermann's function has two inputs. This program" << endl <<
            "calls them by their traditional names." << endl <<
            endl <<
            "Please insert an integer value 0 or greater for m" << endl <<
            "> ";
            
    cin >> m;
            
    cout << endl <<
            "Please insert an integer value 0 or greater for n" << endl <<
            "> ";
    
    cin >> n;
    
    cout << "Calculating, will not give updates as it goes." << endl;
    
    unsigned long answer = ackermann(m, n);
    
    cout << endl <<
            "Ackermann number A(" << m << ", " << n << ") is:" << endl <<
            answer << endl << endl;
            
     return 0;
}