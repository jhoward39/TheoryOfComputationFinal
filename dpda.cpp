/*Program to detect if a string is in the language (a^nb^n)
    Created by Joseph Denham and Joseph Howard for CISC4090

This program acts as a push down automata that will recognize if a string is in the language L = a^nb^n.
Input: The user will be prompted to give a string.
Output: For each rule used by the push down automata, the step number, state, unread input, stack, and rule used will be printed to the terminal.
At the end of the program, a statement about whether or not the string is in L gets printed to the terminal
*/

#include <iostream>
#include <stack>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

string input = "";
string state = "p"; // initial state p
stack<char> s;
int place = 0; // indicates the current place in the string
string str;
int counter = 0;

/*This outputs the state, unread string, and top of stack*/
void checkStates()
{
    cout << "Step: " << counter;
    cout << " State: " << state << " Unread Input: " << input.substr(place, input.size() - place);

    if (!s.empty())
        cout << " Stack: " << s.top();

    counter++;
}

int main()
{

    cout << "string? ";
    cin >> str;
    cout << endl;

    input = str;
    auto start = chrono::high_resolution_clock::now();

    while (state != "q$") // continue while loop until state is q$
    {

        // Rule 1
        if (state == "p")
        {
            state = "q";
            s.push('S');

            checkStates();
            cout << " rule 1" << endl;
        }

        // Rule 2
        else if (state == "q" && input[place] == 'a')
        {
            state = "qa";
            place++;

            checkStates();

            cout << " rule 2" << endl;
        }

        // Rule 3
        else if ((state == "qa") && (s.top() == 'a'))
        {
            state = "q";
            s.pop();

            checkStates();

            cout << " rule 3" << endl;
        }

        // Rule 4
        else if (state == "q" && input[place] == 'b')
        {
            state = "qb";
            place++;

            checkStates();

            cout << " rule 4" << endl;
        }

        // Rule 5
        else if ((state == "qb") && (s.top() == 'b'))
        {
            state = "q";
            s.pop();

            checkStates();

            cout << " rule 5" << endl;
        }

        // Rule 6
        else if (state == "q" && input[place] == '$')
        {
            state = "q$";

            checkStates();

            cout << " rule 6" << endl;
        }

        // Rule 7
        else if ((state == "qa") && (s.top() == 'S'))
        {
            // S -> aSb
            s.pop();
            s.push('b');
            s.push('S');
            s.push('a');

            checkStates();

            cout << " rule 7"
                 << " S -> aSb" << endl;
        }

        // Rule 8
        else if ((state == "qb") && (s.top() == 'S'))
        {
            s.pop();

            checkStates();

            cout << " rule 8"
                 << " S -> e" << endl;
        }

        else // No rules can be followed
        {
            cout << input << " is not in the language";

            return 0;
        }
    }

    // check if (q$,e,e)
    if (s.empty())
    {
        cout << input << " is in the language" << endl;
    }
    // otherwise go to rule 9 to check if state is (q$, e, S)
    //  rule 9
    else if (s.top() == 'S')
    {
        s.pop();

        checkStates();

        cout << " rule 9 " << endl;

        if (s.empty())
        {
            cout << input << " is in the language" << endl;
        }
    }

    else
        cout << input << " is not in the language" << endl;

    auto end = chrono::high_resolution_clock::now();

    // Calculating total time taken by the program.
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    time_taken *= 1e-9;

    cout << "Time taken by program is: " << fixed
         << time_taken << setprecision(9);
    cout << " sec" << endl;

    return 0;
}
