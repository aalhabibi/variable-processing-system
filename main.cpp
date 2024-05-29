#include <iostream>
#include <list>
#include <fstream>

using namespace std;

struct Variable
{
    string name, datatype, value;
};

class Stack
{
public:
    list<Variable> stack;

    bool isEmpty()
    {
        return stack.empty();
    }
    void clear()
    {
        stack.clear();
    }
    void push(Variable var)
    {
        stack.push_back(var);
    }
    void pop()
    {
        if (stack.empty())
            cout << "Stack is empty, nothing to pop" << endl;
        else
            stack.pop_back();
    }
    Variable top()
    {
        if (stack.empty())
            cout << "Stack is empty" << endl;
        else
            return stack.back();
    }
    int getSize()
    {
        return stack.size();
    }
    void displayStack()
    {
        cout << "Stack Contents:\n";
        for (auto element = stack.rbegin(); element != stack.rend(); ++element)
        {
            cout << "Name: " << element->name << ", Type: " << element->datatype << ", Value: " << element->value << ';' << endl;
        }
        cout << endl;
    }
};

void removeWhiteSpace(string &s) // To remove white space before the line of code
{
    int position = s.find_first_not_of(' '); // Find the position of the first non-whitespace character
    s = s.substr(position);
}

void processLine(string line, Stack myStack)
{

    removeWhiteSpace(line);

    string firstWord = line.substr(0, line.find(" "));

    if (line == "return 0;")
    {
        cout << "Reached return 0\n";
        myStack.displayStack();
        myStack.clear();
    }

    if (firstWord == "int" || firstWord == "double" || firstWord == "float" || firstWord == "char")
    {

        Variable *var = new Variable;

        var->datatype = firstWord;

        if ((line.find('=') != string::npos)) // Checks if line contains '=' (has initialization)
        {
            var->name = line.substr(line.find(" ") + 1, (line.find('=') - line.find(" ")) - 1);
            //          Start index of name              Length of name
            if (firstWord == "char")
            {
                // cout << "da5al\n";
                var->value = line.substr(line.find('\''), line.substr(line.find('\''), line.find(';')).length() - 1);
                //           Start index of value         Length of value
            }
            else
            {
                var->value = line.substr(((line.find('=')) + 1), line.find(';') - (line.find('=')) - 1);
                //           Start index of value                Length of value
            }
        }
        else // Assign name only with no value in case of not finding '=' in line
        {
            var->name = line.substr(line.find(" ") + 1, (line.find(';') - line.find(" ")) - 1);
        }

        myStack.push(*var);
        delete var;
        myStack.displayStack();
    }
    else if ((line.find('=') != string::npos))
    {
        string varName = line.substr(0, (line.find('=')));
        //                              Length of name
        string varValue = line.substr(((line.find('=')) + 1), line.find(';') - (line.find('=')) - 1);
        //                Start index of value                Length of value

        for (auto element = myStack.stack.begin(); element != myStack.stack.end(); ++element)
        {
            if (element->name == varName)
            {
                element->value = varValue;
                break;
            }
        }
        myStack.displayStack();
    }
}

void processFile()
{
    Stack myStack;

    ifstream inputFile("code.txt");
    string line;

    getline(inputFile, line);
    removeWhiteSpace(line);

    if (line != "int main()") // Check if theres the main header "int main()"
        cout << "No header found\n";

    else
    {
        while (getline(inputFile, line))
        {
            processLine(line, myStack);
        }
    }
}

int main()
{

    Stack myStack;

    ifstream inputFile("code.txt");
    string line;
    getline(inputFile, line);
    removeWhiteSpace(line);

    if (line != "int main()")
        cout << "Invalid code file\n";

    else
    {
        while (getline(inputFile, line))
        {
            removeWhiteSpace(line);

            string firstWord = line.substr(0, line.find(" "));

            if (line == "return 0;")
            {
                cout << "Reached return 0\n";
                myStack.displayStack();
                myStack.clear();
                break;
            }

            if (firstWord == "int" || firstWord == "double" || firstWord == "float" || firstWord == "char")
            {

                Variable *var = new Variable;

                var->datatype = firstWord;

                if ((line.find('=') != string::npos)) // Checks if line contains '=' (has initialization)
                {
                    var->name = line.substr(line.find(" ") + 1, (line.find('=') - line.find(" ")) - 1);
                    //          Start index of name              Length of name
                    if (firstWord == "char")
                    {
                        // cout << "da5al\n";
                        var->value = line.substr(line.find('\''), line.substr(line.find('\''), line.find(';')).length() - 1);
                        //           Start index of value         Length of value
                    }
                    else
                    {
                        var->value = line.substr(((line.find('=')) + 1), line.find(';') - (line.find('=')) - 1);
                        //           Start index of value                Length of value
                    }
                }
                else // Assign name only with no value in case of not finding '=' in line
                {
                    var->name = line.substr(line.find(" ") + 1, (line.find(';') - line.find(" ")) - 1);
                }

                myStack.push(*var);
                delete var;
                myStack.displayStack();
            }
            else if ((line.find('=') != string::npos))
            {
                string varName = line.substr(0, (line.find('=')));
                //                              Length of name
                string varValue = line.substr(((line.find('=')) + 1), line.find(';') - (line.find('=')) - 1);
                //                Start index of value                Length of value

                for (auto element = myStack.stack.begin(); element != myStack.stack.end(); ++element)
                {
                    if (element->name == varName)
                    {
                        element->value = varValue;
                        break;
                    }
                }
                myStack.displayStack();
            }
        }
    }
}
