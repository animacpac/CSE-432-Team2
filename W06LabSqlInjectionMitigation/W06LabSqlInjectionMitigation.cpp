/************************************************************
** FileName: W06LabSqlInjectionMitigation.cpp
** Authors: Valter Barreto, Nathan Spotten, Phillip Bowler
** , Everton Alves, Mark Wright
** Purpose: To demonstrate SQL injection attacks and vulnerabilities
***********************************************************/

#include <iostream>
#include <regex>
#include <algorithm>
#include <string>
using namespace std;

const int TESTS_SIZE = 5;
const int NUM_TEST_ARRAYS = 5;
const int TEST_PARAMETERS_SIZE = 2;
const int USERNAME_INDEX = 0;
const int PASS_INDEX = 1;

/******************** Constant Declarations ***************/

const string TEST_NAMES[NUM_TEST_ARRAYS] = {
    "Valid",
    "Tautology",
    "Union",
    "Add Statement",
    "Add Comment"};

const string TESTS_VALID[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
    {"spottenn", "secret_Buffalo7"}, // Nathan
    {"vbarret", "nothingTolose1"},   // Valter
    {"prbowler", "bowler123"},       // Phillip
    {"markw", "smashingPumpkins"},   // Mark
    {"itsMeMario", "Luigi123"}       // Everton
};

const string TESTS_TAUTOLOGY[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
    {"user' OR 'gotcha' = 'gotcha", "doesn_tmatter' OR 'cantstopme' = 'cantstopme"}, // Nathan
    {"vbarret", "ask' OR 1=1"},                                                      // Valter
    {"prbowler", "non' or 'password' = 'password"},                                  // Phillip
    {"Jill", "something' OR '4' = 4"},                                               // Mark
    {"itsMeMario", " ' OR '1' = '1"}                                                 // Everton
};

const string TESTS_UNION[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
    {"spottenn", "' UNION SELECT * FROM administrators WHERE 1='1"},                                                                                // Nathan
    {"vbarret", "Gimme' UNION ALL SELECT * from users WHERE username = 'admin"},                                                      // Valter
    {"username1", "non' UNION SELECT * FROM users"},                                              // Phillip
    {"John", "so' UNION SELECT authenticate FROM passwordList WHERE 'a'='a"},                                                                        // Mark
    {"istMeMario", " ' UNION SELECT * FROM users"}                                                                                    // Everton
};

const string TESTS_ADD_STATE[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
    {"spottenn", "insignificant'; INSERT INTO administrators (username, password) VALUES 'attacker', 'mypassword'"},     // Nathan
    {"vbarret", "1'; DELETE FROM users WHERE 1=1 nothing'; INSERT INTO users (name, passwd) VALUES 'Awesome', '1234'"}, // Valter
    {"prbowler", "non'; INSERT INTO users (username, password) VALUES 'hacker', 'password'"},                           // Phillip
    {"Bob", "something' ; DELETE row25 "},                                                                              // Mark
    {"itsMeMario", " '; DROP TABLE users;"}                                                                             // Everton
};

const string TESTS_ADD_COMMENT[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
    {"spottenn/*", "*/"},                   // Nathan
    {"vbarret'--", "DROP users just kidding, this is just a comment"},          // Valter
    {"prbowler'--", "a hacker was here"}, // Phillip
    {"markw'--", "yes"},                      // Mark
    {"itsMeMario'; --", "thanks"}            // Everton
};

/******************** Function Declarations ***************/
string generateQuery(string username, string password);

void demonstrateTest(string testName,
                     const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]);

void demonstrateWeakMitigation(string testName,
                               const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]);

string weakMitigation(string userInput);

void demonstrateStrongMitigation(string testName,
                                 const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]);

bool strongMitigation(string &username, string &password);

void runAllCases(int testTypeChoice);

/******************** Function Definitions ***************/
string generateQuery(string username, string password)
{
    return "SELECT * FROM users WHERE username=\'" + username + "\' AND password=\'" + password + "\';";
}

void demonstrateTest(string testName,
                     const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE])
{
    cout << testName << endl;
    for (int i = 0; i < TESTS_SIZE; ++i)
    {
        cout << generateQuery(cases[i][USERNAME_INDEX],
                              cases[i][PASS_INDEX]);
        cout << endl;
    }
}

void demonstrateWeakMitigation(string testName,
                               const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE])
{
    string username;
    string password;

    for (int i = 0; i < TESTS_SIZE; i++)
    {
        string username = weakMitigation(cases[i][USERNAME_INDEX]);
        string password = weakMitigation(cases[i][PASS_INDEX]);
        cout << generateQuery(username, password) << endl;
    }
}

/**********************************************
 * function: weakMitigation
 * purpose: alter password and username, by
 * replacing invalid characters with an underscore.
 *******************************************/
string weakMitigation(string userInput)
{
    for (int i = 0; i < userInput.length(); i++)
    {
        switch (userInput[i])
        {
        case '-':
           userInput[i] = '_';
            break;
        case ';':
           userInput[i] = '_';
            break;
        case '\\':
           userInput[i] = '_';
            break;
        case '\'':
           userInput[i] = '_';
            break;
        case '/':
           userInput[i] = '_';
            break;
        case '*':
           userInput[i] = '_';
            break;
        }
    }
    return userInput;
}

void demonstrateStrongMitigation(string testName,
                                 const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE])
{
    cout << testName << endl;
    for (int i = 0; i < TESTS_SIZE; i++)
    {
        string username = cases[i][USERNAME_INDEX];
        string password = cases[i][PASS_INDEX];
        if (strongMitigation(username, password))
        {
            cout << generateQuery(cases[i][USERNAME_INDEX],
                                  cases[i][PASS_INDEX])
                 << endl;
        }
        else
        {
            cout << "Did not generate query.\n";
        }
    }
    cout << endl;
}

bool strongMitigation(string &username, string &password)
{
    if (!regex_match(username, regex("^[a-zA-Z0-9_]*"))
    || !regex_match(password, regex("^[a-zA-Z0-9_]*")))
    {
        cout << "Username or password are not valid\n";
        return false;
    }
    return true;
}

void runAllCases(int testTypeChoice)
{
    switch (testTypeChoice)
    {
    case 1:
        demonstrateTest("Valid Cases", TESTS_VALID);
        demonstrateTest("Tautology", TESTS_TAUTOLOGY);
        demonstrateTest("Union", TESTS_UNION);
        demonstrateTest("Add State", TESTS_ADD_STATE);
        demonstrateTest("Add Comment", TESTS_ADD_COMMENT);
        break;
    case 2:
        demonstrateWeakMitigation("Valid Cases", TESTS_VALID);
        demonstrateWeakMitigation("Tautology", TESTS_TAUTOLOGY);
        demonstrateWeakMitigation("Union", TESTS_UNION);
        demonstrateWeakMitigation("Add State", TESTS_ADD_STATE);
        demonstrateWeakMitigation("Add Comment", TESTS_ADD_COMMENT);
        break;
    case 3:
        demonstrateStrongMitigation("Valid Cases", TESTS_VALID);
        demonstrateStrongMitigation("Tautology", TESTS_TAUTOLOGY);
        demonstrateStrongMitigation("Union", TESTS_UNION);
        demonstrateStrongMitigation("Add State", TESTS_ADD_STATE);
        demonstrateStrongMitigation("Add Comment", TESTS_ADD_COMMENT);
        break;
    default:
        cout << "Invalid Input" << endl;
    }
}

void fillArray(string destination[TESTS_SIZE][TEST_PARAMETERS_SIZE], const string SOURCE[TESTS_SIZE][TEST_PARAMETERS_SIZE])
{
    for (int i = 0; i < TESTS_SIZE; i++)
    {
        for (int j = 0; j < TEST_PARAMETERS_SIZE; j++)
        {
            destination[i][j] = SOURCE[i][j];
        }
    }
}

/******************** Main ***************/
int main()
{
    while (true)
    {
        cout << "******MENU*********\n";
        int testTypeChoice;
        cout << "Select the type of test to run by typing the number and hitting enter.\n";
        cout << "[1]. Test Vulnerabilities\n";
        cout << "[2]. Test Weak Mitigation\n";
        cout << "[3]. Test Strong Mitigation\n";
        cout << "[0]. to quit\n";
        cin >> testTypeChoice;
        if (testTypeChoice == 0)
        {
            return 0;
        }

        int testCasesChoice;
        cout << "Select the specific type of cases to run by typing the number and hitting enter.\n";
        cout << "[1]. Use Valid Cases\n";
        cout << "[2]. Use Tautology Cases\n";
        cout << "[3]. Use Union Cases\n";
        cout << "[4]. Use Add Statement Cases\n";
        cout << "[5]. Use Add Comment Cases\n";
        cout << "[6]. Use All Cases\n";
        cout << "[0]. to quit\n";
        cin >> testCasesChoice;
        if (testCasesChoice == 0)
        {
            return 0;
        }

        string selectedCases[TESTS_SIZE][TEST_PARAMETERS_SIZE];

        switch (testCasesChoice)
        {
        case 1:
            fillArray(selectedCases, TESTS_VALID);
            break;
        case 2:
            fillArray(selectedCases, TESTS_TAUTOLOGY);
            break;
        case 3:
            fillArray(selectedCases, TESTS_UNION);
            break;
        case 4:
            fillArray(selectedCases, TESTS_ADD_STATE);
            break;
        case 5:
            fillArray(selectedCases, TESTS_ADD_COMMENT);
            break;
        case 6:
			runAllCases(testTypeChoice);
			continue;
        default:
            cout << "Invalid Input";
              continue;
        }

        string testName =
            "Running " + TEST_NAMES[testCasesChoice - 1] + " Test Cases";

        switch (testTypeChoice)
        {
        case 1:
            demonstrateTest(testName, selectedCases);
            break;
        case 2:
            demonstrateWeakMitigation(testName, selectedCases);
            break;
        case 3:
            demonstrateStrongMitigation(testName, selectedCases);
            break;
        default:
            cout << "Invalid Input";
              continue;
        }
    }
    return 0;
}
