/************************************************************
** FileName: W06LabSqlInjectionMitigation.cpp
** Authors: Valter Barreto, Nathan Spotten, Phillip Bowler
** , Everton Alves, Mark Wright
** Purpose: To demonstrate SQL injection attacks and vulnerabilities
***********************************************************/

#include <iostream>

using namespace std;


const int TESTS_SIZE = 5;
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
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
};

const string TESTS_TAUTOLOGY[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"username1", "password1"}, // Nathan
        {"vbarret", "' OR 1=1"}, // Valter
        {"prbowler", "non' or 'x' = 'x"}, // Phillip
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
};

const string TESTS_UNION[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"username1", "password1"}, // Nathan
        {"vbarret", "1\'; DELETE FROM users WHERE 1=1","nothing\'; INSERT INTO users (name, passwd) VALUES \'Awesome\', \'1234",
                                "WHERE id = \'username\' UNION SELECT Username, Password FROM users;",
                                "\'; SELECT * FROM users WHERE user_id = Username; DROP TABLE users",
                                "\'; SELECT * FROM users WHERE id = 0 OR 1=1"}, // Valter
        {"username1", "password1"}, // Phillip
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
};

const string TESTS_ADD_STATE[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"username1", "password1"}, // Nathan
        {"vbarret", "password1"}, // Valter
        {"prbowler", "non' INSERT INTO passwordlist (username, password) VALUES 'hacker', 'password'"}, // Phillip
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
};

const string TESTS_ADD_COMMENT[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"username1", "password1"}, // Nathan
        {"vbarret", "password1"}, // Valter
        {"prbowler", "//"}, // Phillip
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
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
   // todo: create a query that could be vulnerable to the 4 types of attacks in
   //  the instuctions
   return "Some query part" + username + "other query part" + password;

   // "SELECT * FROM users where Username=" + username + " password=" + password;
}

void demonstrateTest(string testName,
                     const string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]){
   cout << testName << endl;
   //todo: loop through all cases and cout generateQuery results. Like this
   cout << generateQuery(cases[0/*replace with i*/][USERNAME_INDEX],
                         cases[0/*replace with i*/][PASS_INDEX]);
   cout << endl;
}

void demonstrateWeakMitigation() {
   // Todo: Read instructions and see if this is required. I would assume so,
   //  but I can't tell. If it is, maybe show the alteration of one test
   //  case from each type of vulnerability.
}


void weakMitigation(string &username, string &password)
{
   // Instructions: This function accepts the input as a parameter (or two!) and
   // returns the sanitized input.
   // Todo: alter password and username, by escaping out (insert \ before) characters like ";", "--", " "
}

void demonstrateStrongMitigation() {
   // Todo: Read instructions and see if this is required. I would assume so,
   //  but I can't tell. If it is, maybe show the alteration of one test
   //  case from each type of vulnerability.
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
   demonstrateTest("Valid Cases", TESTS_VALID);

   return 0;
}