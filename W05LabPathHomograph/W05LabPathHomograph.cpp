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
    "..\\..\\user\\..\\user\\secret\\pasword.txt",
    "..\\..\\..\\Users\\user\\secret\\pasword.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\pasword.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\..\\secret\\pasword.txt",
    "~\\secret\\password.txt",
    "~\\..\\user\\secret\\pasword.txt",
    "C:\\Users\\..\\Users\\user\\secret\\pasword.txt",
    "C:\\Users\\user\\..\\..\\Users\\user\\secret\\pasword.txt",
    "C:\\Users\\user\\..\\..\\Users\\user\\secret\\..\\secret\\pasword.txt",
    "c:\\users\\user\\..\\..\\users\\user\\secret\\..\\secret\\pasword.txt"
};


const string TEST_NON_HOMOGRAPHS[TEST_SIZE] = {
    //change these. include multiple path symbols: "..", "~" etc. 
    //Also, some of the characters will have to be escaped. I don't remember which ones in c++
    //".\non-homograph1\example.txt",
    //".\non-homograph2\example.txt"
    "password.txt",
    "secret\\pasword.txt",
    "\\..\\user\\secret\\password.txt",
    "..\\..\\user\\..\\..\\user\\secret\\pasword.txt",
    "..\\..\\Users\\user\\secret\\pasword.txt",
    "..\\..\\Users\\..\\Users\\user\\secret\\pasword.txt",
    "..\\..\\..\\Users\\..\\Users\\user\\secret\\secret\\pasword.txt",
    "~\\..\\secret\\password.txt",
    "~\\..\\..\\user\\secret\\pasword.txt",
    "C:\\Users\\..\\Users\\..\\user\\secret\\pasword.txt",
    "C:\\Users\\user\\..\\Users\\user\\secret\\..\\secret\\pasword.txt",
    "c:\\users\\user\\..\\users\\user\\secret\\..\\secret\\pasword.txt"
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

bool isHomograph(string path1, string path2){
// This is just an example on how it should be done
	if (canonicalizedFile1 == canonicalizedFile2) {
		cout << "The paths are homographs.\n";
	}
	else {
		cout << "The paths are not homographs.\n";
	}
};
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

string canonicalize(string path) {
    return "";
}

bool isHomograph(string path1, string path2) {
    return false;
}

int main(int argc, char* argv[]) {
	//if statement to call runTests if an argument like "--run-tests" is passed

	// Get the files
	string file1;
	string file2;
	cout << "Specify the first filename: ";
	cin >> file1;
	cout << "Specify the second filename: ";
	cin >> file2;

	string canonicalizedFile1;
	string canonicalizedFile2;
	canonicalizeFilePath(file1, canonicalizedFile1);
	canonicalizeFilePath(file2, canonicalizedFile2);

	cout << "File 1: " << canonicalizedFile1 << endl;
	cout << "File 2: " << canonicalizedFile2 << endl;


	//need to reads to get paths from user and pass them to isHomograph then display the result

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
