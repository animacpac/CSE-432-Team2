// I answered the six questions and then wrote the stubs and hints to make sure everyone understands what they have to write
// The hints are with the declarations.
// I organized the code by const declarations and definitions, function declarations, then function definitions.
// Each of those sections is also organized by test code first then everything else alphabetically, with the exception of main(). 
// These comments should definitely be styled better and polished to be descriptive of what the code does.

// Recommended tasks to assign just for the code. I tried to do the time estimates for someone that understands C++ at a moderate level.
// 1. DO FIRST IF POSSIBLE: make sure the code design, structure, styling, and naming all follow good practice and 
//        conventions. Should probably be given to someone confident in good practice. Time estimate depends on experience.
// 2. write Canonicalize() Nathan 1 to 2 hours or more
// 3. write runTest(). This is a little tedious, but not super complex. Still second hardest. 30min to 1 hr
// 5. write main() to connect it all. We could also divide it into and write another function to prompt the user for the paths 30min to 1hr.
// 6. Polish comments into "Professional Writing" that follows "honors style guidelines" that is descriptive of what
//      the code does. Possibly a header comment with our names and the description. Should be given to someone confident in
//      writing and comments. I don't have a good time estimate, maybe 30min-2hrs depending on how confident you are and 
//      how much work you want to put into it


//When working through this problem, ask yourself six questions : what is e, r, R(), c, C(), and what is H() ?
//e : What is the encoding in this scenario ?
//answer: The encoding is the path symbols characters along with what they do
//r : This can be a bit difficult to figure out, so I will help.
//answer: The rendition is a file handle.In the case of C++, it would be ifstream fin; .This points to a given resource on the file system.
//R() : This is the rendering function.
//answer: In the case of our scenario, this might be fin.open(e); .In other words, it turns an encoding into a rendition.Note that we cannot use ifstream for this problem because it treats all paths the same that do not refer to resources on the system.In other words, it would report two non - homographs as the same even when they are obviously different.
//c: This is the canon.You need to identify an appropriate canon.
//answer: We're defining it as the absolute file path
    // //it's late. I just realized that an absolute path will not work as a canon because we're working on theoretical paths.
    //This will have to be adjusted. Maybe the absolute path if the path reaches uses the root and the relative path if not.
//C() : The bulk of your work will be to create an appropriate canonicalization function.This should be informed by the functionality of R() but should not use it.
//answer: turning the encoded path into an absolute path made lowercase(windows specific).
//H() : This is the homograph function. It determines if two encodings are the same. It should leverage the work done in C().Check the textbook for an idea of what this will look like.
//answer: simple string test 

#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>

using namespace std;
using std::filesystem::current_path;

const int TEST_SIZE = 10;

const int FORBIDDEN_FILE_SIZE = 1;



const string TEST_FORBIDDEN_FILES[FORBIDDEN_FILE_SIZE]{
    //change these. include multiple path symbols: "..", "~" etc. 
    //Also, some of the characters will have to be escaped. I don't remember which ones in c++
    //".\forbidden\example.txt",
    //".\forbidden2\example.txt"
    "C:\\Users\\user\\secret\\password.txt"
};

/*
    Everton: I put the test in multi-dimensional array
    because the isHomograph function gets 2 inputs to compare.
    For now I'll write the code to just test the homographs results.
*/

const string TEST_HOMOGRAPHS[TEST_SIZE] = {
    //change these. include multiple path symbols: "..", "~" etc. 
    //Also, some of the characters will have to be escaped. I don't remember which ones in c++
   //".\homograph1\example.txt",
    //".\homograph2\example.txt"
    "..\\secret\\password.txt",
    "..\\..\\user\\secret\\password.txt",
    "..\\..\\user\\..\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\..\\secret\\password.txt",
//    "~\\secret\\password.txt",
//    "~\\..\\user\\secret\\password.txt",
    "C:\\Users\\..\\Users\\user\\secret\\password.txt",
    "C:\\Users\\user\\..\\..\\Users\\user\\secret\\password.txt",
    "C:\\Users\\user\\..\\..\\Users\\user\\secret\\..\\secret\\password.txt",
    "c:\\users\\user\\..\\..\\users\\user\\secret\\..\\secret\\password.txt"
};


const string TEST_NON_HOMOGRAPHS[TEST_SIZE] = {
    //change these. include multiple path symbols: "..", "~" etc. 
    //Also, some of the characters will have to be escaped. I don't remember which ones in c++
    //".\non-homograph1\example.txt",
    //".\non-homograph2\example.txt"
    "password.txt",
    "secret\\password.txt",
    ".\\..\\user\\secret\\password.txt",
    "..\\..\\user\\..\\..\\user\\secret\\password.txt",
    "..\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\Users\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\secret\\password.txt",
//    "~\\..\\secret\\password.txt",
//    "~\\..\\..\\user\\secret\\password.txt",
    "C:\\Users\\..\\Users\\..\\user\\secret\\password.txt",
    "C:\\Users\\user\\..\\Users\\user\\secret\\..\\secret\\password.txt",
    "c:\\users\\user\\..\\users\\user\\secret\\..\\secret\\password.txt"
};


//for canon... function, Nathan will do it.
const string PATH_SYMBOLS[] = {
    "/",
    "`" //etc
};


//could return bool instead. needs to loop through all test forbidden files and loop all homographs
//then non-homographs. It should probably log if tests pass or not. This is probably the second most complex function
void runTests();


string canonicalize(string path); // Nathan
bool prompt();



bool isHomograph(string path1, string path2);
//probably should be the unaltered paths
//canonize each string and test if same
//it's late. I just realized that an absolute path will not work as a canon because we're working on theoretical paths.
//This will have to be adjusted.

//test


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
//
//string get_env_var(string const & key ) {
//    char * val;
//    val = getenv( key.c_str() );
//    string retval = "";
//    if (val != NULL) {
//        retval = val;
//    }
//    return retval;
//}


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
   current_path();
   // b. test to see if it's fully qualified(C:\etc), relative to root of drive or relative to current folder

   // 4. identify path type
   enum type { Device, Unc, FullDos, RelativeToRoot, RelativeToSameDirectorySpecificDrive, RelativeToCurrent, EnvShortcut };
   type pathType;
   string regexs[] = {
           // Device
           "\\\\\\\\(\\.|\\?).*",
           // Unc,
           "\\\\\\\\.*",
           // FullDos
           "[a-z]\\:\\\\.*"
           // RelativeToRoot,
           "\\\\.*",
           // RelativeToSameDirectorySpecificDrive
           "[a-z]\\:\\.*"
           // RelativeToCurrent,
           "\\.*"
           // EnvShortcut
           "\\%.*\\%.*"
           //C:\windows\%appdata%\password.txt
           //%appdata%\password.txt
   };

   int length = path.size();
   if (length == 0) {
      return path;
   }
   for (int i = 0; i < regexs->size(); ++i)
   {

   }

   // c. if it's relative, prepend it with the drive letter or current directory

   // d. split into strings using "\" as delimiter

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
