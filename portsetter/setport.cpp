// File Prolog
// Name: James LoForti
// Course: CS 3370 Section: 001
// Instructor: Wagstaff
// Project: Setport (Portsetter CO4)
// Date: 09/29/2016
// 
// I declare that the following code was written by me or provided 
// by the instructor for this project. I understand that copying source
// code from any other source constitutes cheating, and that I will receive
// a zero on this project if I am found in violation of this policy.
// ---------------------------------------------------------------------------
//									     ____.           .____             _____  _______   
//									    |    |           |    |    ____   /  |  | \   _  \  
//									    |    |   ______  |    |   /  _ \ /   |  |_/  /_\  \ 
//									/\__|    |  /_____/  |    |__(  <_> )    ^   /\  \_/   \
//									\________|           |_______ \____/\____   |  \_____  /
//									                             \/          |__|        \/ 
//
// ******************************************************************************************************************
//
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <array>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iterator>
using namespace std;

//The language function
//Purpose: To get the users lang from env vars, and set lang prompt output
int language();

//The getLangPrefix function
//Purpose: To get the language prefix
//Return: The language prefix in the form of a string, or "invalid"
string getLangPrefix(string _lang);

//The checkLangFiles function
//Purpose: To check if the specified language file is present
int checkLangFiles(string _lang);

//The getLangFiles function
//Purpose: To get the appropriate language files
vector<string> getLangFiles(string _lang);

//The readLangFiles function
//Purpose: To read the file of language specific prompts, and save to vector
int readLangFiles(vector<string> _langFiles);

//The portIsNum function
//Purpose: To check whether arg 2 is a number
//Parameters: A string represented as _portNum
//Return: True for yes, false for no
bool portIsNum(char* _portNum);

//The printUsage function
//Purpose: To print the help screen
//Return: O for success, nonzero for error
int printUsage();

//The printAbout function
//Purpose: To print the about screen
//Return: O for success, nonzero for error
int printAbout();

//The printFail function
//Purpose: To print an error message 
//Parameters: A string represented as _errorMsg
void printFail(string _errorMsg);

//The printSuccess function
//Purpose: To print a success message which includes the set port
//Parameters: A string represented as _successPort
void printSuccess(string _successPort);

//Define Globals:
const string VERSION_NUM = "1.4";
const int THREE_NUM = 3;
vector<string> usage;
vector<string> about;
vector<string> prompts;
enum {
	TOO_MANY_ARGS,
	SYNTAX_ERROR,
	INVALID_ENV_VAR,
	INVALID_SECOND_ARG,
	THIRD_ARG_NAN,
	PORT_OUT_BOUNDS,
	ERROR_USAGE_OPEN,
	ERROR_USAGE_CLOSE,
	ERROR_ABOUT_OPEN,
	ERROR_ABOUT_CLOSE,
	ERROR_LANG_CLOSE,
	SUCCESS,
	ERROR,
	FAILED,
	PASSED,
	MISSING_LANG,
	BAD_LANG
};

int main(int argc, char* args[]) {
	//Declare vars:
	const int MAX_ARGS = 4;
	const int MAX_PORT = 65535;
	vector<string> argsStr;
	char* envVar;
	
	//Convert c-strings into strings
	for (int i = 0; i < argc; ++i) { argsStr.push_back(args[i]); } // end for

	//Handle Internationalization
	language();

	//If more than 4 args are given
	if (argc > MAX_ARGS) {
		printFail(prompts[TOO_MANY_ARGS]);
		printUsage();
		return 1;
	} // end if
	
	//If 4 args are given
	if (argc == MAX_ARGS) {
		//If arg 3 is NOT -e, a 4 arg command is automatically bad
		if (argsStr[2].compare("-e") != 0) {
			printFail(prompts[SYNTAX_ERROR]);
			printUsage();
			return 1;
		} else { //all args are valid and env var is given
			//Get the specified env var
			envVar = getenv(args[3]);
			
			//If returned env var is NOT valid
			if (envVar == NULL || envVar == '\0') {
				printFail(prompts[INVALID_ENV_VAR]);
				printUsage();
				return 4;
			} else { // specified env var found
				printSuccess(envVar);
				return 0;
			} // end else
		} // end else
	} // end if
	
	//If 3 args are given
	if (argc == (MAX_ARGS - 1)) {
		//But arg 2 is invalid
		if ((argsStr[1].compare("-p") != 0) && (argsStr[1].compare("--port") != 0)) {
			printFail(prompts[INVALID_SECOND_ARG]);
			printUsage();
			return 1;
		} // end if
		
		//If environment option is NOT present
		if ((argsStr[2].compare("-e") != 0)) {
			//If port number is invalid
			if (!portIsNum(args[2])) {
				printFail(prompts[THIRD_ARG_NAN]);
				printUsage();
				return 1;
			} // end if
			
			//Port # IS a digit, but port # is out of bounds
			if (stoi(args[2]) > MAX_PORT || stoi(args[2]) < 1) {
				printFail(prompts[PORT_OUT_BOUNDS]);
				printUsage();
				return 2;
			} // end if
			
			printSuccess(args[2]); 
			return 0;
			
		} else { // Arg 3 is environment option
			//Get the default env var
			envVar = getenv("PORT");
			printSuccess(envVar);
		} // end else
	} // end if

	//If 2 args are given
	if (argc == 2) {
		if ((argsStr[1].compare("-h") == 0) || (argsStr[1].compare("--help") == 0) || (argsStr[1].compare("-?") == 0)) { 
			printUsage(); 
			return 0;
		} // end if
		
		//ABOUT
		if ((argsStr[1].compare("-!") == 0) || (argsStr[1].compare("--about") == 0)) { 
			printAbout(); 
			return 0;
		} // end if
		
		//VERSION
		if ((argsStr[1].compare("-v") == 0) || (argsStr[1].compare("--version") == 0)) { 
			cout << VERSION_NUM << endl; 
			return 0;
		} // end if
		
		//Arg 2 is invalid
		printFail(prompts[INVALID_SECOND_ARG]);
		printUsage();
		return 1;	
	} // end if
	
	//NO ARGS/OPTIONS are given
	if (argc == 1){ printUsage(); }

	return 0;
} // end main()

int language() {
	//Init vars:
	const char* langVarsCStr[] = {"LANGUAGE", "LC_ALL", "LC_MESSAGES", "LANG"};
	vector<string> langVars;
	vector<string> invalidLangReports;
	string langPrefix = "";
	int langFileStatus = 0;
	char* result = '\0';
	
	//Set language to english so prompts can be used
	readLangFiles(getLangFiles("en"));
	
	//Get and save all valid language environment variables
	//Ignorable values include: NULL, "", "C", "C.UTF-8"
	for (unsigned int i = 0; i < 4; ++i) {
		//If langVar exists, get it - was throwing segmentation fault if envVar DNE
		if (getenv(langVarsCStr[i])) { result = getenv(langVarsCStr[i]); } // end if

		//If returned env var is valid - save & convert to string
		if (result != NULL && result != '\0') { langVars.push_back(result); } // end if
		
		//If langVar is NOT ignorable
		if ((langVars[i].compare("C.UTF-8") != 0) && (langVars[i].compare("C") != 0)) {
			//Get first 2 chars of lang
			langPrefix = getLangPrefix(langVars[i]);
			
			//Check file availability
			langFileStatus = checkLangFiles(langPrefix);
			
			//If langFile is (1) missing, save report for printing
			if (langFileStatus == 1) { invalidLangReports.push_back(langPrefix + prompts[MISSING_LANG]); } 
			//If langFile is (2) invalid, save report for printing
			if (langFileStatus == 2) { invalidLangReports.push_back(langVars[i] + prompts[BAD_LANG]); }
			//If langFile is (0) GOOD, set it
			if (langFileStatus == 0) { 
				readLangFiles(getLangFiles(langPrefix)); 
				return 0;
			} // end if
		} // end if
	} // end for
	
	//Print any lang reports to inform user of missing or bad langs
	for (unsigned int k = 0; k < invalidLangReports.size(); ++k) {
		cout << invalidLangReports[k] << endl;
	} // end for
} // end function language()

string getLangPrefix(string _lang) {
	//Declare vars:
	string language = "";
	
	//Get first two chars
	language = _lang.substr(0, 2);
	
	//If language is alphas
	if ((isalpha(language[0]) != 0) && (isalpha(language[1]) != 0)) { return language; } 
	else { return "invalid"; } // language contains non-alphas
} // end function getLangPrefix()

int checkLangFiles(string _lang) {
	//If language is invalid
	if (_lang.compare("invalid") == 0) { return 2; } // end if
	
	//Create ifstream
	ifstream inStream;
	//Open the stream using the first file associated with _lang
	inStream.open(getLangFiles(_lang)[0]);
	
	//If language is NOT available
	if (inStream.fail()){
		inStream.close();
		return 1;
	} else { return 0; } // file is good
} // end checkLangFiles()

vector<string> getLangFiles(string _lang) {
	//Init vars:
	vector<string> langFiles;
	
	langFiles.push_back("/home/ubuntu/workspace/portsetter/langs/" + _lang + "/setport.prompts_" + _lang + ".txt");
	langFiles.push_back("/home/ubuntu/workspace/portsetter/langs/" + _lang + "/setport.usage_" + _lang + ".txt");
	langFiles.push_back("/home/ubuntu/workspace/portsetter/langs/" + _lang + "/setport.about_" + _lang + ".txt");
	
	return langFiles;
} // end function getLangFiles()

int readLangFiles(vector<string> _langFiles) {
	//Init vars:
	string data = "";
	vector<string> currVector;
	
	//Iterate through langFiles
	for (unsigned int i = 0; i < THREE_NUM; ++i) {
		//Create & open stream
		ifstream inStream;
		inStream.open(_langFiles[i]);
		
		//While data exists 
		while (!inStream.eof()) {
			getline(inStream, data); // read lang text
			currVector.push_back(data); // save data
		} // end while
		
		//Close the stream
		inStream.close();
		
		//SAVE PROMPTS
		if (i == 0) { prompts = currVector; }
		//SAVE USAGE
		if (i == 1) { usage = currVector; }
		//SAVE ABOUT
		if (i == 2) { about = currVector; }
		
		currVector.clear();
	} // end for
} // end function readLangFiles()

bool portIsNum(char* _portNum) {
	//Copy second argument to avoid changing original value
	char* charPtr = _portNum;
	
	//While charPtr is not null terminator
	while (*charPtr != 0) {
		//If the port # is not a digit
		if (!isdigit(*charPtr++)) {
			return false;
		} // end if
	} // end while
	
	return true;
} // end function portIsNum()

int printUsage() {
	for (unsigned int i = 0; i < usage.size(); ++i) {
		cout << usage[i] << endl;
	} // end for
} // end function printUsage()

int printAbout() {
	for (unsigned int i = 0; i < about.size(); ++i) {
		cout << about[i] << endl;
	} // end for
} // end function printAbout()

void printFail(string _errorMsg) {
	cout << prompts[ERROR];
	cout << _errorMsg << endl;
} // end function printFail()

void printSuccess(string _successPort) {
	cout << prompts[SUCCESS];
	cout << _successPort << endl;
} // end function printSuccess()