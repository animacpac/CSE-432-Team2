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
// Todo: EVERYONE create one of each of these test cases by your name.
//  this needs to be done after the generateQuery function
const string TESTS_VALID[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"spottenn",  "secret_Buffalo7"}, // Nathan
        {"vbarret", "nothingTolose1"}, // Valter
        {"prbowler", "bowler123"}, // Phillip
        {"markw", "smashingPumpkins"}, // Mark
        {"itsMeMario", "Luigi123"} // Everton
};

const string TESTS_TAUTOLOGY[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"user OR 'gotcha' = 'gotcha'", "doesn_tmatter OR 'cantstopme' = 'cantstopme'"}, // Nathan
        {"vbarret", "ask' OR 1=1"}, // Valter
        {"prbowler", "non' or 'x' = 'x"}, // Phillip
        {"Jill", "something' OR '4' = 4"}, // Mark
        {"itsMeMario", " ' OR '1' = '1"} // Everton
};

const string TESTS_UNION[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"spottenn", "UNION SELECT * FROM administrators"}, // Nathan
        {"vbarret", "Gimme' UNION ALL SELECT * from users WHERE username = 'admin'"}, // Valter
        {"username1", "non'; UNION SELECT * from users WHERE password = 'password'; UPDATE users SET password = 'password' WHERE id = 1"}, // Phillip
        {"John", "so' UNION SELECT autenticate FROM passwordList"}, // Mark
        {"istMeMario", " ' UNION SELECT * FROM users;"} // Everton
};

const string TESTS_ADD_STATE[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"spottenn", "insignificant; INSERT INTO administrators (username, password) VALUES 'attacker', 'mypassword'"}, // Nathan
        {"vbarret", "1'; DELETE FROM users WHERE 1=1 nothing'; INSERT INTO users (name, passwd) VALUES 'Awesome', '1234'"}, // Valter
        {"prbowler", "non'; INSERT INTO users (username, password) VALUES 'hacker', 'password'"}, // Phillip
        {"Bob", "something' ; DELETE row25 "}, // Mark
        {"itsMeMario", " '; DROP TABLE users;"} // Everton
};

const string TESTS_ADD_COMMENT[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"spottenn /*", "*/"}, // Nathan
        {"vbarret';--", " DROP users"}, // Valter
        {"prbowler';--", "SELECT * FROM users"}, // Phillip
        {"markw--", "yes"}, // Mark
        {"itsMeMario'; --", "thanks"} // Everton
};

/******************** Function Declarations ***************/
string generateQuery(string username, string password);

void demonstrateTest(string testName,
                     const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]);

void demonstrateWeakMitigation();

void weakMitigation(string &username, string &password);

void demonstrateStrongMitigation();

bool strongMitigation(string &username, string &password);

/******************** Function Definitions ***************/
string generateQuery(string username, string password)
{
   return "SELECT * FROM users WHERE username=" + username + " AND Password=" + password + ";";
}

void demonstrateTest(string testName,
                     const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]){
   cout << testName << endl;
   //todo: loop through all cases and cout generateQuery results. Like this
   cout << generateQuery(cases[0/*replace with i*/][USERNAME_INDEX],
                         cases[0/*replace with i*/][PASS_INDEX]);
   cout << endl;
}

void demonstrateWeakMitigation(string testName,
    const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]) {
    string username;
    string password;

    for (int i = 0; i < TESTS_SIZE; i++) {
        string username = cases[i][USERNAME_INDEX];
        string password = cases[i][PASS_INDEX];
  

 
    return weakMitigation(username, password);
    
}

/**********************************************
 * function: removeCaracter
 * purpose: remove caracters from a given text.
 *******************************************
void removeCaracter(string & text, char caracter){
    text.erase(remove(text.begin(), text.end(), caracter), text.end());	
}
*/
void weakMitigation(string &username, string &password)
{
   // Instructions: This function accepts the input as a parameter (or two!) and
   // returns the sanitized input.
   // Todo: alter password and username, by escaping out (insert \ before) characters like ";", "--", " ", "\"

    //regex("[a-z]\\:.*"),

    for (int i = 0, username.length(); i++) {
        //if (username[i] = regex("[a-z]\\:.*")){
        //    _username[i] = "_";
        //else
        if (username[i] = regex("[a-z]\\:.*")) {
        i = "";
        else if (i = "--")
        i = "_";
        else if (i = " ")
        i = "_";
        else if (i = "\"")
        i = "_";
        else i = i;

        for (int i = 0, password.length(); i++) {
            //if (username[i] = regex("[a-z]\\:.*")){
            //    _username[i] = "_";
            //else

            i = "";
        else if (i = "--")
        i = "_";
        else if (i = " ")
        i = "_";
        else if (i = "\"")
        i = "_";
        else i = i;

    }
}
    

void demonstrateStrongMitigation(string testName,
    const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]) {
    cout << testName << endl;
    //todo: loop through all cases and cout generateQuery results. Like this
    for (int i = 0; i < TESTS_SIZE; i++) {
        string username = cases[i][USERNAME_INDEX];
        string password = cases[i][PASS_INDEX];
        if (!strongMitigation(username, password)) {
            cout << generateQuery(cases[i][USERNAME_INDEX],
                cases[i][PASS_INDEX]) << endl;
        }
    }
    // Todo: Read instructions and see if this is required. I would assume so,
    //  but I can't tell. If it is, maybe show the alteration of one test
    //  case from each type of vulnerability.
    cout << endl;
}

bool strongMitigation(string &username, string &password)
// Todo: look at the book strong mitigation definition along with instructions
//  to see if we are supposed to alter the invalid input, or just not run it
//  all together. We could return a boolean that shows if the input is invalid
//  if that's all we need to do.
{
   // Todo: Alter username and password to only allow letters, numbers, and underscores.
   // note: If we want to just throw out any invalid input that does not include the correct
   // characters then the regex is "^[a-zA-Z0-9_]*". If we want to remove all
   // but correct characters then we need to do it slightly differently.
    if (!regex_match(username, regex("^[a-zA-Z0-9_]*")) || !regex_match(password, regex("^[a-zA-Z0-9_]*"))) {
        cout << "Username or password are not valid\n";
        return 1;
    }
    return 0;
}

/******************** Main ***************/
int main() {
   // From instructions. It should be possible to execute any of the test cases in the report.
   // A simple menu structure should be provided to facilitate this.
   // todo: create a menu to call correct function: The demonstrateTest function
   //  with the correct parameters. Also maybe include options for calling the
   //  mitigation demonstration functions depending on if we figure out it's
   //  required.
   // todo: call it like this.

   //valid cases
    int menuChoice;
    cout << "******MENU*********\n";
    cout << "1. Test Vulnerabilities\n";
    cout << "2. Test Weak Mitigation\n";
    cout << "3. Test Strong Mitigation\n";
    cout << "Please select the test you wish to preform.\n";
    cin >> menuChoice;

    switch (menuChoice) {
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
        cout << "Invalid Input";
    }

   return 0;
}
