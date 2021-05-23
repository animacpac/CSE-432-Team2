/************************************************************
** FileName: W05LabPathHomograph.cpp
** Authors: Valter Barreto, Nathan Spotten, Phillip Bowler
** , Everton Alves, Mark Wright
** Purpose: It checks the path Homographs
***********************************************************/

#include <direct.h>     // for _getcwd
#include <iostream>     // for input and output functions
#include <vector>       // for vectorizing file paths
#include <algorithm>    // for the replace function
#include <regex>        // for sorting and modifying path name 

#define GetCurrentDir _getcwd

using namespace std;

const int TEST_SIZE = 10;

const int FORBIDDEN_FILE_SIZE = 1;

const string TEST_DIRECTORY = "C:\\Users\\user\\secret";


/************************************************************
* TEST_FORBIDDEN_FILES test the forbidden files
***********************************************************/
const string TEST_FORBIDDEN_FILES[FORBIDDEN_FILE_SIZE]{
    // Test for a forbidden.
    "C:\\Users\\user\\secret\\password.txt"
};

/************************************************************
* TEST_HOMOGRAPHS test the Homographs files
***********************************************************/
const string TEST_HOMOGRAPHS[TEST_SIZE] = {

    "..\\secret\\password.txt",
    "..\\..\\user\\secret\\password.txt",
    "..\\..\\user\\..\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\..\\secret\\password.txt",
    "C:\\Users\\..\\Users\\user\\secret\\password.txt",
    "C:\\Users\\user\\..\\..\\Users\\user\\secret\\password.txt",
    "C:\\Users\\user\\..\\..\\Users\\user\\secret\\..\\secret\\password.txt",
    "c:\\users\\user\\..\\..\\users\\user\\secret\\..\\secret\\password.txt"
};

/************************************************************
* TEST_NON_HOMOGRAPHS test the that are not Homographs files
***********************************************************/
const string TEST_NON_HOMOGRAPHS[TEST_SIZE] = {

    "passwordtxt",
    "secret\\password.txt",
    ".\\..\\user\\secret\\password.txt",
    "..\\..\\user\\..\\..\\user\\secret\\password.txt",
    "..\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\Users\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\secret\\password.txt",
    "C:\\Users\\..\\Users\\..\\user\\secret\\password.txt",
    "C:\\Users\\user\\..\\Users\\user\\secret\\..\\secret\\password.txt",
    "c:\\users\\user\\..\\users\\user\\secret\\..\\secret\\password.txt"
};

const string PATH_SYMBOLS[] = {
    "/",
    "`" 
};

void runTests();
string canonicalize(string path, string currentDirectory); 
bool prompt();
bool isHomograph(string path1, string path2, string currentDirectory);

/**********************************************************************
 * runTests
 * This functions will run the tests.
 ***********************************************************************/

void runTests()
{

    bool passedAllHomographTest = true;
    bool passedAllNonHomographTest = true;

    for (int h = 0; h < TEST_SIZE; h++) {
        for (int f = 0; f < FORBIDDEN_FILE_SIZE; f++) {
            if (isHomograph(TEST_HOMOGRAPHS[h], TEST_FORBIDDEN_FILES[f],TEST_DIRECTORY) == false) {


                cout << "Failed Homograph Examples at test line: "
                    << h + 1 << " at the Forbidden line: " << f + 1 << endl;
                passedAllHomographTest = false;
            }
        }
    }
    
    for (int n = 0; n < TEST_SIZE; n++) {
        for (int f = 0; f < FORBIDDEN_FILE_SIZE; f++) {
            if (isHomograph(TEST_NON_HOMOGRAPHS[n], TEST_FORBIDDEN_FILES[f], TEST_DIRECTORY) ){

                cout << "Failed Non-Homograph Examples at test line: "
                    << n + 1 << " at the Forbidden line: " << f + 1 << endl;
                passedAllNonHomographTest = false;
            }
        }
    }

    if (passedAllHomographTest && passedAllNonHomographTest)
    {

        cout << "Success in all tests" << endl;
    }
    return;
}

/**********************************************************************
 * GetCurrentPath
 * The function which gets current Path
 ***********************************************************************/
string get_current_dir() {
	char buff[FILENAME_MAX]; //create string buffer to hold path
	GetCurrentDir(buff, FILENAME_MAX);
	string current_working_dir(buff);
	return current_working_dir;
}

/**********************************************************************
 * canonicalize
 * This functions has all the homograph parameters and all the matching
 ***********************************************************************/
string canonicalize(string path, string currentDirectory)
{
    // Make everything lowercase
   for (int i = 0; i < path.length(); i++) {
       path[i] = tolower(path[i]);
   }

  
   replace(path.begin(), path.end(), '/', '\\');

    // Current Directory in lowercase
   for (int i = 0; i < currentDirectory.length(); i++) {
      currentDirectory[i] = tolower(currentDirectory[i]);
   }

   const int FULL_DOS = 0;
   const int RELATIVE_TO_ROOT = 1;
   const int RELATIVE_TO_CURRENT = 2;
   int pathType;
   int regexsSize = 3;
   regex regexs[3] = {
    // FullDos
           regex("[a-z]\\:.*"),
    // RelativeToRoot,
           regex("\\\\.*"),
    // RelativeToCurrent,
           regex(R"((\..*)||.*)")
   };
    
   if (path.size() == 0) {
      return path;
   }

   // Match the path and get the size
   for (int i = 0; i < regexsSize; ++i)
   {
      if(regex_match(path, regexs[i])) {
         pathType = i;
         break;
      }
   }
   
   if (pathType == RELATIVE_TO_ROOT) {
    //relative to root. add name of drive and :
       path = currentDirectory.substr(0, 1) + '\\' + path;
   }
    // gets the .\ of the path and remove it
   if (pathType == RELATIVE_TO_CURRENT) {
       if (path.size() >= 3 && path.substr(0, 2) == ".\\") {
           path = path.substr(2);
       }
       path = currentDirectory + '\\' + path;
   }
       
   //Takes the path and splits it into words in a vector
   vector<string> splitPath;
   int j = 0;
   for (int i = 0; i < path.size(); i++) {
       if (path[i] == '\\' || i == path.size()) {
           splitPath.push_back(path.substr(j, i - j));
           j = i + 1;
       }
   }
   splitPath.push_back(path.substr(j, path.size()));

   //Takes the vector of path words and takes out the .. of the paths
	vector<string> newSplitPath;

	int newPathIterator = 0;
	for(int i = 0; i < splitPath.size(); i++){
		if(splitPath[i] == ".."){
		   if(newSplitPath.size() > 1) {
		      newSplitPath.pop_back();
         }
		} else {
		   newSplitPath.push_back(splitPath[i]);
		}

	}
   
    //Takes a vector of the words in the path and puts them back into a path
    string newPath;
    for (int i = 0; i < newSplitPath.size(); i++) {
        if (i == 0) {
            newPath.append(newSplitPath[i]);
        }
        else {
            newPath.append("\\" + newSplitPath[i]);
        }
    }

   return newPath;
}

/**************************************************************************************************
* promptTest
* This function will prompt the user to see what they want to do.
**************************************************************************************************/
bool prompTest()
{
	char answer = 'q'; // initialized on the off chance that an unitialized variable would be y or n.

	// this while loop makes sure that only y or n is accepted.
	while (tolower(answer) != 'y' && tolower(answer) != 'n')
	{
		cout << "Would you like to do a homograph test? (y/n): ";
		cin >> answer;
	}

	if (tolower(answer) == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*******************************************************************
* isHomograph
* This function will take two paths and the current directory path 
* and compare the paths to see if they are homographs. It uses the
* canonicalization function.
*******************************************************************/
bool isHomograph(string path1, string path2, string currentDirectory)
{
// This is just an example on how it should be done
   string canoncalizedFile1 = canonicalize(path1, currentDirectory);
   string canoncalizedFile2 = canonicalize(path2, currentDirectory);
   if (canoncalizedFile1 == canoncalizedFile2) {
      cout << "The paths are homographs.\n";
      return true;
   }
   else {
      cout << "The paths are not homographs.\n";
      return false;
   }
   return false;
}

/******************************************************************
* Main Program
******************************************************************/
int main(int argc, char* argv[]) {

    string file1;               // file specified by the user
    string file2;               // file specified by the user

	if (prompTest()){           // promptTest() provides a bool if 
        runTests();             //    the user wants to run the test
    }

    cout << "Specify the first filename: ";
    cin >> file1;

    cout << "Specify the second filename: ";
    cin >> file2;

   isHomograph(file1, file2, get_current_dir());

	return 0;
}