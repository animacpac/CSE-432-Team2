/************************************************************
** FileName: W05LabPathHomograph.cpp
** Authors: Valter Barreto, Nathan Spotten, Phillip Bowler
** , Everton Alves, Mark Wright
** Purpose: It checks the path Homographs
***********************************************************/
#include <direct.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>

#define GetCurrentDir _getcwd


using namespace std;

const int TEST_SIZE = 10;

const int FORBIDDEN_FILE_SIZE = 1;



const string TEST_FORBIDDEN_FILES[FORBIDDEN_FILE_SIZE]{
    // Test for a forbidden.
    "C:\\Users\\user\\secret\\password.txt"
};

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


const string TEST_NON_HOMOGRAPHS[TEST_SIZE] = {

    "password.txt",
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
string canonicalize(string path); // Nathan
bool prompt();
bool isHomograph(string path1, string path2);


void runTests()
{

    bool passedAllHomographTest = true;
    bool passedAllNonHomographTest = true;

    //Loop and tests  all homograph examples
    for (int h = 0; h < TEST_SIZE; h++) {
        for (int f = 0; f < FORBIDDEN_FILE_SIZE; f++) {
            if (isHomograph(TEST_HOMOGRAPHS[h], TEST_FORBIDDEN_FILES[f]) == false) {


                cout << "Failed Homograph Examples at test line: "
                    << h + 1 << " at the Forbidden line: " << f + 1 << endl;
                passedAllHomographTest = false;
            }
        }
    }

    //Loop and tests all Non-Homograph examples
    for (int n = 0; n < TEST_SIZE; n++) {
        for (int f = 0; f < FORBIDDEN_FILE_SIZE; f++) {
            if (isHomograph(TEST_NON_HOMOGRAPHS[n], TEST_FORBIDDEN_FILES[f])) {

                cout << "Failed Non-Homograph Examples at test line: "
                    << n + 1 << " at the Forbidden line: " << f + 1 << endl;
                passedAllNonHomographTest = false;
            }
        }
    }

    if (passedAllHomographTest && passedAllNonHomographTest)
    {

        cout << "Success in all tests";
    }
    return;
}
/**********************************************************************
 * GetCurrentPath
 * The function which gets current Path
 ***********************************************************************/
std::string get_current_dir() {
	char buff[FILENAME_MAX]; //create string buffer to hold path
	GetCurrentDir(buff, FILENAME_MAX);
	string current_working_dir(buff);
	return current_working_dir;
}


string canonicalize(string path)
{


   // 1. convert escaped characters to real ones and remove quotes. ^ ' " and make lowercase
//   path.replace(path.begin(), path.end(), "^","");
//   path.replace(path.begin(), path.end(), "'","");
//   path.replace(path.begin(), path.end(), "\"","");
//
   //put all the path to lower case
   for (int i = 0; i < path.length(); i++) {
       path[i] = tolower(path[i]);
   }

   // 2. replace "/" with "\"
   //path.replace(path.begin(), path.end(), '/', '\\');

   // a. get the current directory from windows
    string currentDirectory = get_current_dir();
   currentDirectory =     "C:\\Users\\user\\secret";
   for (int i = 0; i < currentDirectory.length(); i++) {
      currentDirectory[i] = tolower(currentDirectory[i]);
   }
   // b. test to see if it's fully qualified(C:\etc), relative to root of drive or relative to current folder

   // 4. identify path type
   //enum typesOfPaths { FullDos, RelativeToRoot, RelativeToCurrent };
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
   for (int i = 0; i < regexsSize; ++i)
   {
      if(regex_match(path, regexs[i])) {
         pathType = i;
         break;
      }
   }

   // c. if it's relative, prepend it with the drive letter or current directory
   if (pathType == RELATIVE_TO_ROOT) {
       //relative to root. add name of drive and :
       path = currentDirectory.substr(0, 1) + '\\' + path;
   }
       
   if (pathType == RELATIVE_TO_CURRENT) {
       if (path.size() >= 3 && path.substr(0, 1) == ".\\") {
           path = path.substr(2, path.size()-1);
       }
       path = currentDirectory + '\\' + path;
   }
       
   // d. split into strings using "\" as delimiter
   vector<string> splitPath;
   int j = 0;
   for (int i = 0; i < path.size(); i++) {
       if (path[i] == '\\' || i == path.size()) {
           splitPath.push_back(path.substr(j, i - j));
           j = i + 1;
       }
   }
   splitPath.push_back(path.substr(j, path.size()));

   // e. handle going up ".."
	vector<string> newSplitPath;

	int newPathIterator = 0;
	for(int i = 0; i < splitPath.size(); i++){
		if(splitPath[i] != ".."){
			if(newPathIterator == 0){
				newSplitPath.push_back(splitPath[i]);
				++newPathIterator;				
			}
			else if(newSplitPath[newPathIterator - 1] != splitPath[i]){
				newSplitPath.push_back(splitPath[i]);
				++newPathIterator;
			}
		}
	}
   // f. concat into one string and return

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

bool isHomograph(string path1, string path2)
{
// This is just an example on how it should be done
   string canoncalizedFile1 = canonicalize(path1);
   string canoncalizedFile2 = canonicalize(path2);
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

int main(int argc, char* argv[]) {



    string file1;
    string file2;

	if (prompTest()){
        runTests();
    }

    cout << "Specify the first filename: ";
    cin >> file1;

    cout << "Specify the second filename: ";
    cin >> file2;

    isHomograph(file1, file2);

	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
