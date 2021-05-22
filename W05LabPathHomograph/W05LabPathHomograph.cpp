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

using namespace std;

const int TEST_SIZE = 12;

const int FORBIDDEN_FILE_SIZE = 2;

const string CURRENT_PATH[1]{
    //This is the current path we are working from
    "C:\\Users\\user\\cse453\\"
};

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
    "..\\secret\\pasword.txt",
    "..\\..\\user\\secret\\password.txt",
    "..\\..\\user\\..\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\..\\secret\\password.txt",
    "~\\secret\\password.txt",
    "~\\..\\user\\secret\\password.txt",
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
    "\\..\\user\\secret\\password.txt",
    "..\\..\\user\\..\\..\\user\\secret\\password.txt",
    "..\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\Users\\..\\Users\\user\\secret\\password.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\secret\\password.txt",
    "~\\..\\secret\\password.txt",
    "~\\..\\..\\user\\secret\\password.txt",
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


void runTests() {

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

    if (passedAllHomographTest && passedAllNonHomographTest) {

        cout << "Success in all tests";
    }
    return;
}

std::string get_current_dir() {
	char buff[FILENAME_MAX]; //create string buffer to hold path
	//GetCurrentDir(buff, FILENAME_MAX);
	string current_working_dir(buff);
	return current_working_dir;
}

string GetFullPathFromPartial(char* partialPath)
{
	char full[_MAX_PATH];
	if (_fullpath(full, partialPath, _MAX_PATH) != NULL)
	{
		return full;
	}
	else
	{
		return "Invalid path\n";
	}
}

bool checkPath()
{
	string fName1 = "";
	string fName2 = "";
	string fFullPath1 = "";
	string fFullPath2 = "";

	// Retrieving Full path of file 1
	cin.ignore();
	cout << "File name 1> ";
	std::getline(std::cin, fName1); //changed from simple std::cin to std::getline to allow user to input whitespaces
	fFullPath1 = get_current_dir() + "\\" + fName1;


	//Retrieving Full path of file 2
	cout << "File name 2> ";
	std::getline(std::cin, fName2); //changed from simple std::cin to std::getline to allow user to input whitespaces
	char* c = const_cast<char*>(fName2.c_str());
	fFullPath2 = GetFullPathFromPartial(c);

	if (fFullPath1 == fFullPath2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


string canonicalize(string encoding) {

	std::vector<char> canon{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
										  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
										   'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
										   'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
										   'w', 'x', 'y', 'z', '.', '<', '>', ':', '\'', '/', '\\',
										   '|', '*', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
										   '!', '@', '#', '$', '%', '^', '&', '(', ')', '-', '_', '=', '+',
										   '`', '~', ',', '[', ']', '{', '}', '\"' };

	//Loop through each character in the string and check to see if the
	//character is contained within the canon. If it isn't in the canon,
	//print a message to the user.
	for (int i = 0; i < encoding.size(); i++)
	{

		auto result = std::find(canon.begin(), canon.end(), encoding[i]);

		if (result == end(canon)) {
			std::cout << "There is an invalid character ";
			std::cout << encoding[i];
			std::cout << " at position ";
			std::cout << (i + 1);
			std::cout << endl;
		}

	}


	return encoding;
   //might need to add an ambiguous case, in other words, it depends on
   // real folder and file structure that will vary system to system.
   //
   // https://docs.microsoft.com/en-us/dotnet/standard/io/file-path-formats
   //
   // TODO:
   // 2. replace "/" with "\"
   // 2. handle drive letters, unc paths, as root
   // 3. handle ".", "..", and "~". ^
   //      a. look up ~ value, or write the code in a comment and put that. Since we are working with theoritical paths,
   //          running homograph tests based on a real value that changes from machine to machine will yeild inconsistent
   //          results. However if this program were put into practice, this is the code you would use.
   // 4. convert the handling of the symbols to a map include all
   //
   // 1. convert escaped charachters to real ones and remove quotes. ^ ' " I think
   // 2. replace "/" with "\"
   // 3. identify path type
   // 4. replace environmental variables split paths into components
   // 5. Resolve paths to fully qualified, UNC, or device paths
   // 6. check if unc paths are pointing to self and resolve, check if device paths are pointing to a drive or UNC and resolve. 127.0.0.1, c$, etc
   // 7. loop through until no resolutions are needed.
   // 4. convert the handling of the symbols to a map include all
   // resolution needed unordered set.
   //
   //
   //
   //
}

bool prompt()
{
	char answer = 'q'; // initialized on the off chance that an unitialized variable would be y or n.

	// this while loop makes sure that only y or n is accepted.
	while (tolower(answer) != 'y' && tolower(answer) != 'n')
	{
		std::cout << "Would you like to do a homograph test? (y/n): ";
		std::cin >> answer;
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

bool isHomograph(string path1, string path2) {
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
   return false;}

int main(int argc, char* argv[]) {

	while (prompt())
	{
		if (checkPath() == true) {
			cout << "This is Homograph\n";
		}
		else {
			cout << "Not a Homograph\n";
		}
	}

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
