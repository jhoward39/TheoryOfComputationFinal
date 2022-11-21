// Program to detect if a string is in the language a^nb^n

#include <iostream>
#include <stack>
#include <string>

using namespace std;

string input = "aaaabbbb$"; // edit to accept user input
string state = "p";
stack<char> s;
int place = 0; // indicates the current place in the string

void checkStates()
{
    cout << "input[place]: " << input[place] << " State: " << state;

    if (!s.empty())
        cout << " s.top(): " << s.top() << endl;
    else
        cout << endl;
}

int main()
{

    time_t start, end;

    time(&start);

    while (state != "q$")
    {

        // Rule 1
        if (state == "p")
        {
            state = "q";
            s.push('S');

            cout << "rule 1";

            checkStates();
        }

        // Rule 2
        else if (state == "q" && input[place] == 'a')
        {
            state = "qa";
            place++;

            cout << "rule 2";

            checkStates();
        }

        // Rule 3
        else if ((state == "qa") && (s.top() == 'a'))
        {
            state = "q";
            s.pop();

            cout << "rule 3";

            checkStates();
        }

        // Rule 4
        else if (state == "q" && input[place] == 'b')
        {
            state = "qb";
            place++;

            cout << "rule 4";

            checkStates();
        }

        // Rule 5
        else if ((state == "qb") && (s.top() == 'b'))
        {
            state = "q";
            s.pop();

            cout << "rule 5";

            checkStates();
        }

        // Rule 6
        else if (state == "q" && input[place] == '$')
        {
            state = "q$";

            cout << "rule 6";

            checkStates();
        }

        // Rule 7
        else if ((state == "qa") && (s.top() == 'S'))
        {
            // S -> aSb
            s.pop();
            s.push('b');
            s.push('S');
            s.push('a');

            cout << "rule 7";

            checkStates();
        }

        // Rule 8
        else if ((state == "qb") && (s.top() == 'S'))
        {
            s.pop();

            cout << "rule 8";
            checkStates();
        }

        // // Rule 9
        // else if ((input[place] == 'b') && (s.top() == 'b'))
        // {
        //     cout << "hello scum" << endl;
        // }

        else // No rules can be followed
        {
            cout << input << " is not in the language";

            checkStates();
            return 0;
        }
    }
    if (s.empty())
        cout << input << " is in the language" << endl;
    else
        cout << input << " is not in the language" << endl;

    time(&end);

    double runTime = double(end - start);

    cout << "Run Time: " << runTime;

    return 0;
}
