#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

// ----------------------------
// FUNCTION PROTOTYPES --------
// ----------------------------

void printHeader();
void printMenu();
int getUserChoice();
void inputSingleExpression(char expr[]);
void inputTwoExpressions(char expr1[], char expr2[]);
int detectvariables(char expr[], char vars[]);
void printVariables(int varCount, char vars[]);
int combineVariables(char expr1[], char expr2[], char vars[]);
void generateTruthTable(int varCount, int table[][1000]);
void printTruthTableSingle(int varCount, char vars[], char expr[], int table[][1000]);
void printTruthTableDouble(int varCount, char vars[], char expr1[], char expr2[], int table[][1000]);
int evaluateExpression(char expr[], char vars[], int varCount, int tablerow[]);
bool isValidExpression(char expr[]);
void printInstructionsmenu();
void clearBuffer();

int main()
{
    int option = 0;

    while (option != 4)
    {
        printHeader();
        printMenu();
        option = getUserChoice();

        if (option == 1)
        {
            char expr[100];      // A char Array is used to store sequence of chracters terminated by null '\0' chracter
            char vars[1000];       // 2D Array for storing unique variables
            static int table[2048][1000]; // A 2D Array for storing all possible Combinations
            cout << "\nSingle expression Selected\n " << endl;
            inputSingleExpression(expr);

            if (!isValidExpression(expr))
            {
                cout << "\n";
                cout << "Press any key to Try Again...";
                cin.get();
                continue;
            }

            int varCount = detectvariables(expr, vars); // Store number of variables for single Expression
            printVariables(varCount, vars);
            generateTruthTable(varCount, table);
            printTruthTableSingle(varCount, vars, expr, table);

            cout << "Process Complete. Press any key to return back to Menu...";
            cin.get();
        }
        else if (option == 2)
        {
            char expr1[100], expr2[100], vars[1000];
            static int table[2048][1000];

            cout << "\nTwo expressions Selected\n " << endl;
            inputTwoExpressions(expr1, expr2);

            if (!isValidExpression(expr1) || !isValidExpression(expr2))
            {
                cout << "\n";
                cout << "Press Enter to Try Again...";
                cin.get();
                continue;
            }
            int varCount = combineVariables(expr1, expr2, vars);
            printVariables(varCount, vars);
            generateTruthTable(varCount, table);
            printTruthTableDouble(varCount, vars, expr1, expr2, table);

            cout << "\nProcess Complete. \nPress any key to return back to Menu...";
            cin.get();
        }
        else if (option == 3)
        {
            system("cls");
            printInstructionsmenu();
            cout << "\nPress any key to return back to Menu...";
            cin.get();
        }
        else if (option == 4)
        {
            cout << "Exiting Program...\n\n";
            cout << "Thanks For Using Our Program !!!";
            return 0;
        }
    }
    return 0;
}

// -----------------------------
// FUNCTION DEFINITIONS --------
// -----------------------------

void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // For clearing all input buffers
}

void printHeader()
{
    system("cls");

    cout << "==============================================\n";
    cout << "||         LOGICAL ANALYZER                 ||\n";
    cout << "==============================================\n";
}

void printMenu()
{
    cout << "\n1. Press 1 to give Single Expression " << endl;
    cout << "2. Press 2 to give Two Expressions " << endl;
    cout << "3. Press 3 to See User's Manual " << endl;
    cout << "4. Press 4 to Exit the Program " << endl;
}

int getUserChoice()
{
    int choice;
    cout << "\nEnter your Choice: ";

    while (!(cin >> choice))
    {
        cout << "ERROR!! Please enter a Correct Choice (1, 2, or 3): ";
        clearBuffer();
    }
    clearBuffer();

    return choice;
}

void inputSingleExpression(char expr[])
{
    cout << "Enter the logical expression : ";
    cin.getline(expr, 100);
}

void inputTwoExpressions(char expr1[], char expr2[])
{
    cout << "Enter first Expression : ";
    cin.getline(expr1, 100);
    cout << "\nEnter second Expression : ";
    cin.getline(expr2, 100);
}

int detectvariables(char expr[], char vars[])
{
    int count = 0;
    for (int i = 0; expr[i] != '\0'; i++) // Read Expression till null Character
    {
        if (expr[i] >= 'a' && expr[i] <= 'z')
        {
            expr[i] = expr[i] - 32; // Convert LowerCase to UpperCase
        }

        if (expr[i] >= 'A' && expr[i] <= 'Z')
        {
            // Check to see if duplicate presents

            bool found = false;
            for (int j = 0; j < count; j++)
            {
                if (vars[j] == expr[i])
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                vars[count] = expr[i]; // If duplicate does'nt found store in vars[count]
                count++;
            }
        }
    }
    return count;
}

void printVariables(int varCount, char vars[])
{
    cout << "\nVariables Detected are : ";
    for (int i = 0; i < varCount; i++)
    {
        cout << vars[i] << " "; // Print No. of variables detected
    }
    cout << endl;
}

void generateTruthTable(int varCount, int table[][1000])
{
    int rows = pow(2, varCount); // Calculate total no. of rows = 2^varCount

    for (int i = 0; i < rows; i++)
    {
        int value = i;
        for (int j = varCount - 1; j >= 0; j--)
        {
            // Converting i to its binary representation

            table[i][j] = value % 2;
            value = value / 2;
        }
    }
}

int combineVariables(char expr1[], char expr2[], char vars[])
{
    int count = 0;
    char temp[10];

    int c1 = detectvariables(expr1, temp);
    for (int i = 0; i < c1; i++)
    {
        vars[count] = temp[i];
        count++;
    }

    int c2 = detectvariables(expr2, temp);
    for (int i = 0; i < c2; i++)
    {
        // To Check if any duplicate is present in 2nd expression array

        bool found = false;
        for (int j = 0; j < count; j++)
        {
            if (vars[j] == temp[i])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            vars[count] = temp[i];
            count++;
        }
    }

    return count;
}

int getVariableValue(char var, char vars[], int tableRow[], int varCount)
{
    for (int i = 0; i < varCount; i++)
    {
        if (vars[i] == var)
        {
            return tableRow[i];
        }
    }
    return 0;
}

int evaluateExpression(char expr[], char vars[], int varCount, int tableRow[])
{
    int result = -1;
    char op = 0;
    bool notApply = false;

    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (expr[i] == ' ')
        {
            continue;
        }
        // To store Operator

        if (expr[i] == '&' || expr[i] == '|' || expr[i] == '^' || expr[i] == '>' || expr[i] == '=')
        {
            op = expr[i];
        }
        if (expr[i] == '!' || expr[i] == '~')
        {
            notApply = true;
        }
        int value = -1;

        if (expr[i] >= 'A' && expr[i] <= 'Z') // To Handle Variables
        {
            value = getVariableValue(expr[i], vars, tableRow, varCount);
        }
        else if (expr[i] == '(') // If first Bracket detects find closing bracket
        {
            int j = i + 1; // Find Closing Bracket
            while (expr[j] != ')' && expr[j] != '\0')
            {
                j++;
            }
            char subExpr[50];
            int count = 0;
            for (int k = i + 1; k < j; k++)
            {
                subExpr[count] = expr[k];
                count++;
            }
            subExpr[count] = '\0';

            value = evaluateExpression(subExpr, vars, varCount, tableRow);
            i = j; // Skip Processed Bracket which ensures we do not repeat the bracket part
        }
        if (expr[i] == '0' || expr[i] == '1')
        {
            value = expr[i] - '0'; // Convert the Chracter '0' or '1' into 0 and 1 so they can combine with other variables
        }

        if (notApply && value != -1)
        {
            value = !value;
            notApply = false;
        }
        if (value != -1)
        {
            if (result == -1)
            {
                result = value;
            }
            else if (op == '&')
            {
                result = result & value;
            }
            else if (op == '|')
            {
                result = result | value;
            }
            else if (op == '^')
            {
                result = result ^ value;
            }
            else if (op == '>')
            {
                result = (!result) | value; // P -> Q = ~P | Q
            }
            else if (op == '=')
            {
                result = (result == value); // P <-> = (P == Q)
            }
        }
    }
    return result;
}

void printTruthTableSingle(int varCount, char vars[], char expr[], int table[][1000])
{
    bool allTrue = true;
    bool allFalse = true;

    cout << "\nTRUTH TABLE:\n";
    int rows = pow(2, varCount);
    for (int i = 0; i < varCount; i++)
        cout << vars[i] << " ";

    cout << "| R\n";
    cout << "------------------\n";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < varCount; j++)
        {
            cout << table[i][j] << " ";
        }
        int result = evaluateExpression(expr, vars, varCount, table[i]);

        cout << "| " << result << endl;

        // Checking whether the statement is Tautology / Contradiction or Contigency

        if (result == 0)
        {
            allTrue = false;
        }
        if (result == 1)
        {
            allFalse = false;
        }
    }
    cout << "\nLOGICAL STATUS: \n";
    if (allTrue)
    {
        cout << "\nThis Expression is Tautology.\n";
    }
    else if (allFalse)
    {
        cout << "\nThis Expression is Contradiction/Absurdity.\n";
    }
    else
    {
        cout << "\nThis Expression is Contigency.\n";
    }
}

void printTruthTableDouble(int varCount, char vars[], char expr1[], char expr2[], int table[][1000])
{
    int rows = pow(2, varCount);
    bool equivalent = true;
    bool allTrue1 = true, allFalse1 = true;
    bool allTrue2 = true, allFalse2 = true;

    for (int i = 0; i < varCount; i++)
        cout << vars[i] << " ";
    cout << "| R1 R2\n";
    cout << "------------------\n";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < varCount; j++)
            cout << table[i][j] << " ";

        int result1 = evaluateExpression(expr1, vars, varCount, table[i]);
        int result2 = evaluateExpression(expr2, vars, varCount, table[i]);

        cout << "| " << result1 << " " << result2 << endl;

        if (result1 != result2)
            equivalent = false;

        if (result1 == 0)
        {
            allTrue1 = false;
        }
        if (result1 == 1)
        {
            allFalse1 = false;
        }
        if (result2 == 0)
        {
            allTrue2 = false;
        }
        if (result2 == 1)
        {
            allFalse2 = false;
        }
    }

    // Check equivalence

    cout << "\nEQUIVALENCE CHECK: \n";

    if (equivalent)
        cout << "\nThe two Statements are Equivalent.\n";
    else
        cout << "\nThe two Statements are NOT Equivalent.\n";

    // Check whether both statements are tautology / contigency / contradiction
    cout << "\nLOGICAL STATUS: \n";
    cout << "\nExpression 1 is : "; // For Expression 1
    if (allTrue1)
    {
        cout << "Tautology\n";
    }
    else if (allFalse1)
    {
        cout << "Contradiction / Absurdity\n";
    }
    else
    {
        cout << "Contigency\n";
    }

    cout << "\nExpression 2 is : "; // For Expression 2
    if (allTrue2)
    {
        cout << "Tautology\n";
    }
    else if (allFalse2)
    {
        cout << " Contradiction / Absurdity\n";
    }
    else
    {
        cout << "Contigency\n";
    }
}

bool isValidExpression(char expr[])
{
    int brackets = 0;
    char prev = '\0';

    for (int i = 0; expr[i] != '\0'; i++)
    {
        char c = expr[i];

        if (c == ' ') // Ignore Spaces
            continue;

        // Check if user enter Invalid Character

        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '!' || c == '~' || c == '&' || c == '|' || c == '^' || c == '>' || c == '=' || c == '(' || c == ')'))
        {
            cout << " \nError: Invalid character " << c << "\n";
            return false;
        }

        // Bracket count

        if (c == '(')
        {
            brackets++;
        }
        if (c == ')')
        {
            brackets--;
        }
        if (brackets < 0)
        {
            cout << " \nError: Extra closing bracket ')'\n";
            return false;
        }

        // Two operators together
        if ((c == '&' || c == '|' || c == '^' || c == '>' || c == '=') &&
            (prev == '&' || prev == '|' || prev == '^' || prev == '>' || prev == '='))
        {
            cout << " \nError: Two operators together\n";
            return false;
        }

        prev = c;
    }

    // Unbalanced brackets
    if (brackets != 0)
    {
        cout << " \nError: Brackets are not balanced\n";
        return false;
    }

    // Expression ends with operator
    if (prev == '&' || prev == '|' || prev == '^' || prev == '>' || prev == '=')
    {
        cout << " \nError: Expression ends with operator\n";
        return false;
    }

    return true;
}

void printInstructionsmenu()
{
    cout << endl
         << endl;
    cout << "1. This program generates Truth Tables for Logical Expressions.\n";
    cout << "2. You can input either a Single Expression or Two Expressions.\n";
    cout << "3. Supported Logical Operators:\n";
    cout << "   - ! or ~ : NOT\n";
    cout << "   - &      : AND\n";
    cout << "   - |      : OR\n";
    cout << "   - ^      : XOR\n";
    cout << "   - >      : IMPLICATION (P -> Q)\n";
    cout << "   - =      : BICONDITIONAL / EQUIVALENCE (P <-> Q)\n";
    cout << "4. Variables should be single letters (A-Z or a-z).\n";
    cout << "5. Expressions can include parentheses '()' for grouping.\n";
    cout << "6. After entering expressions, the program:\n";
    cout << "   - Detects all unique variables.\n";
    cout << "   - Generates a Truth Table for all possible combinations.\n";
    cout << "   - Evaluates the expression(s) and shows results.\n";
    cout << "7. For two expressions, it also checks whether the two are Equivalent.\n";
    cout << "8. Expression Results:\n";
    cout << "   - Tautology: True for all combinations\n";
    cout << "   - Contradiction / Absurdity: False for all combinations\n";
    cout << "   - Contingency: True for some and False for some combinations\n";
    cout << endl;
}