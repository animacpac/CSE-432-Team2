/************************************************************
** FileName: W05LabPathHomograph.cpp
** Authors: Valter Barreto, Nathan Spotten, Phillip Bowler
** , Everton Alves, Mark Wright
** Purpose: It checks the path Homographs
***********************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <filesystem>

using namespace std;
using std::filesystem::current_path;

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

string canonicalize(string path)
{


   // 1. convert escaped characters to real ones and remove quotes. ^ ' " and make lowercase
   path.replace(path.begin(), path.end(), "^","");
   path.replace(path.begin(), path.end(), "'","");
   path.replace(path.begin(), path.end(), "\"","");
   //path.tolower(); NEEDS DONE

   // 2. replace "/" with "\"
   path.replace(path.begin(), path.end(), '/', '\\');

   // a. get the current directory from windows
   char currentDirectory[256];
    getcwd(currentDirectory, 256);

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
           regex("[a-z]\\:\\\\.*"),
           // RelativeToRoot,
           regex("\\\\.*"),
           // RelativeToCurrent,
           regex("\\.*")
   };

   if (path.size() == 0) {
      return path;
   }
   for (int i = 0; i < regexsSize; ++i)
   {
      if(regex_match(path, regexs[i])) {
         pathType = i;
      }
   }

   // c. if it's relative, prepend it with the drive letter or current directory
   if (pathType == RELATIVE_TO_ROOT) {
       //relative to root. add name of drive and :
       path += currentDirectory.substr(0, 1);
   }
       
   if (pathType == RELATIVE_TO_CURRENT) {
       if (path.size >= 3 && path.substr(0, 1) == ".\\") {
           path = path.substr(2, path.end());
       }
       path += currentDirectory;
   }
       
   // d. split into strings using "\" as delimiter
   vector<string> splitPath;
   int j = 0;
   for (i = 0; i < path.size(); i++) {
       if (path[i] == '\\' || i == path.size()) {
           splitPath.push_back(path.substr(j, i - j));
           j = i + 1;
       }
   }
   // e. handle going up ".."

   // f. concat into one string and return








    // 3 replace environmental variables
//    string key = "%WINDIR%";
//    string get_env_var(key);

//   // 4. identify path type
//   enum type { Device, Unc, FullDos, RelativeToRoot, RelativeToSameDirectorySpecificDrive, RelativeToCurrent, EnvShortcut };
//   type pathType;
//   string regexs[] = {
//           // Device
//           "\\\\\\\\(\\.|\\?).*",
//           // Unc,
//           "\\\\\\\\.*",
//           // FullDos
//           "[a-z]\\:\\\\.*"
//           // RelativeToRoot,
//           "\\\\.*",
//           // RelativeToSameDirectorySpecificDrive
//           "[a-z]\\:\\.*"
//           // RelativeToCurrent,
//           "\\.*"
//           // EnvShortcut
//           "\\%.*\\%.*"
//           //C:\windows\%appdata%\password.txt
//           //%appdata%\password.txt
//   };
//
//   int length = path.size();
//   if (length == 0) {
//      return path;
//   }
//   for (int i = 0; i < regexs->size(); ++i)
//   {
//
//   }
   // 4. replace environmental variables
   

   // 5. split paths into components


   // 6. Resolve paths to fully qualified, UNC, or device paths
   // 6.4
   // 6.5 get computer name for unc

   // 7. check if unc paths are pointing to self and resolve, check if device paths are pointing to a drive or UNC and resolve. 127.0.0.1, c$, etc

   // 8. loop through until no resolutions are needed.

   // 9. convert the handling of the symbols to a map include all


   // might need to add an ambiguous case, in other words, it depends on
   // real folder and file structure that will vary system to system.
   //
   // https://docs.microsoft.com/en-us/dotnet/standard/io/file-path-formats
   //
   // TODO:

   // 1. convert escaped characters to real ones and remove quotes. ^ ' " I think
   // 2. replace "/" with "\"
   // 3. identify path type
   // 4. replace environmental variables
   // 5. split paths into components
   // 6. Resolve paths to fully qualified, UNC, or device paths
   // 7. check if unc paths are pointing to self and resolve, check if device paths are pointing to a drive or UNC and resolve. 127.0.0.1, c$, etc
   // 8. loop through until no resolutions are needed.
   // 9. convert the handling of the symbols to a map include all
   // resolution needed unordered set.
   //
   //
   //
   //
   return path;
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
