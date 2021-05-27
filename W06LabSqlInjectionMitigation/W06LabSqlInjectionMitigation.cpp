/************************************************************
** FileName: W06LabSqlInjectionMitigation.cpp
** Authors: Valter Barreto, Nathan Spotten, Phillip Bowler
** , Everton Alves, Mark Wright
** Purpose: To demonstrate SQL injection attacks and vulnerabilities
***********************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <regex>



using namespace std;

static vector<string> split(string value, char delimiter);
static string join(vector<string> values, char delimiter);
static string to_lower(string s);

const int TESTS_SIZE = 5;
const int TEST_PARAMETERS_SIZE = 2;
const int USERNAME_INDEX = 0;
const int PASS_INDEX = 1;

/******************** Constant Declarations ***************/
// Todo: EVERYONE create one of each of these test cases by your name.
//  this needs to be done after the generateQuery function
const string TESTS_VALID[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"spottenn",  "secret_Buffalo7"}, // Nathan
        {"vbarreto", "nothingtolose9"}, // Valter
        {"username1", "password1"}, // Phillip
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
};

const string TESTS_TAUTOLOGY[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"username1", "password1"}, // Nathan
        {"username1", "password1"}, // Valter
        {"username1", "password1"}, // Phillip
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
};

const string TESTS_UNION[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"username1", "password1"}, // Nathan
        {"username1", "password1"}, // Valter
        {"username1", "password1"}, // Phillip
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
};

const string TESTS_ADD_STATE[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"username1", "password1"}, // Nathan
        {"username1", "password1"}, // Valter
        {"username1", "password1"}, // Phillip
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
};

const string TESTS_ADD_COMMENT[TESTS_SIZE][TEST_PARAMETERS_SIZE] = {
        {"username1", "password1"}, // Nathan
        {"username1", "password1"}, // Valter
        {"username1", "password1"}, // Phillip
        {"username1", "password1"}, // Mark
        {"username2", "password2"} // Everton
};

/******************** Function Declarations ***************/
string generateQuery(string username, string password);

void displayTestQueries(string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]);

void demonstrateValidTests();

void demonstrateTautologyAttack();

void demonstrateUnionAttack();

void demonstrateAddStateAttack();

void demonstrateCommentAttack();

void demonstrateWeakMitigation();

void weakMitigation(string &username, string &password);

void demonstrateStrongMitigation();

void strongMitigation(string &username, string &password);

/******************** Function Definitions ***************/
string generateQuery(string username, string password)
{
   // todo: create a query that could be vulnerable to the 4 types of attacks in
   //  the instuctions
   return "Some Query" + username + password;
}

void displayTestQueries(string cases[TESTS_SIZE][TEST_PARAMETERS_SIZE]) {
   //todo: loop through all cases and cout generateQuery results. Like this
   cout << generateQuery(cases[0/*replace with i*/][USERNAME_INDEX],
                         cases[0/*replace with i*/][PASS_INDEX]);
   cout << endl;
}

void demonstrateValidTests() {

   cout << "Valid Cases:" << endl;
   //Todo: call displayTestQueries with correct array
}

void demonstrateTautologyAttack() {

   //Todo: like demonstrateValidTests
}

void demonstrateUnionAttack() {

   //Todo: like demonstrateValidTests
}
void demonstrateAddStateAttack() {

   //Todo: like demonstrateValidTests

}

void demonstrateCommentAttack() {

   //Todo: like demonstrateValidTests

}

void demonstrateWeakMitigation(string value) {
       // split the sql
    vector<string> splitValues = split(value, ' ');
    string cleanValue = "";

    // Look for dirtysql
    for (int i = 0; i < splitValues.size(); i++)
    {
        string segment = splitValues[i];
        
        if (segment.find(';') != string::npos)
        {
            // remove the semicolon
            segment = join(split(segment, ';'), '\0');
        }
        if (segment.find("'") != string::npos)
        {
            // remove the single quotes
            segment = join(split(segment, '\''), '\0');
        }
        if (to_lower(segment) == "union" || segment.find("--") != string::npos)
        {
            return cleanValue;
        }
        if (to_lower(segment) == "or")
        {
            continue;
        }

        cleanValue += segment;
        if (i < splitValues.size() - 1)
        {
            cleanValue += " ";
        }
    }

    return cleanValue;

}


void weakMitigation(string &username, string &password)
{
   // Instructions: This function accepts the input as a parameter (or two!) and
   // returns the sanitized input.
   // Todo: alter password and username, by escaping out (insert \ before) characters like ";", "--"
}

void demonstrateStrongMitigation() {
   // Todo: Read instructions and see if this is required. I would assume so,
   //  but I can't tell. If it is, maybe show the alteration of one test
   //  case from each type of vulnerability.
}

void strongMitigation(string &username, string &password)
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
   // todo: create a menu to call correct function: The 5 (maybe 7)
   //  demonstration functions.
   return 0;
}