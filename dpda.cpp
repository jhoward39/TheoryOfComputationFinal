/*Program to detect if a string is in the language (a^nb^n)
    Created by Joseph Denham and Joseph Howard for CISC4090 */

#include <iostream>
#include <stack>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

// load 2048 a's to the string

string input = "";
string state = "p";
stack<char> s;
int place = 0; // indicates the current place in the string
int numa;
int numb;
int counter = 0;

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

    cout << "How many a's? ";
    cin >> numa;
    cout << endl
         << "How many b's?";
    cin >> numb;
    cout << endl;

    string str = "";
    for (int i = 0; i < numa; i++)
    {
        str += "a";
    }

    for (int j = 0; j < numb; j++)
    {
        str += "b";
    }
    str += "$";

    input = str;
    auto start = chrono::high_resolution_clock::now();

    while (state != "q$")
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

            cout << " rule 7" << endl;
        }

        // Rule 8
        else if ((state == "qb") && (s.top() == 'S'))
        {
            s.pop();

            checkStates();

            cout << " rule 8" << endl;
        }

        else // No rules can be followed
        {
            cout << input << " is not in the language";

            checkStates();
            return 0;
        }
    }

    // rule 9
    if (s.empty())
    {
        cout << input << " is in the language" << endl;
    }
    // rule 10
    else if (s.top() == 'S')
    {
        s.pop();

        checkStates();

        cout << " rule 10 " << endl;

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
