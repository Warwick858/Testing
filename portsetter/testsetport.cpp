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
#include <string>
#include <cctype>
#include <array>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;

//The checkAlias function
//Purpose: To check the .bash_aliases file for existing setport & testsetport aliases
//Return: A boolean value indicating whether the aliases are already present
bool checkAlias();

//The createAlias function
//Purpose: To create an alias for setport & testsetport commands
void createAlias();

//The runTests function
//Purpose: To run all test cases
void runTests();

//The print function
//Purpose: To print the test results
void print(int _result);

//Declare Globals
int i = 0;
int result = 0;
string testCasesStrings[] = {
    "setport",
    "setport -h",
    "setport --help",
    "setport -p 4040",
    "setport --port 4040",
    "setport help",
    "setport -help",
    "setport --h",
    "setport -h --help",
    "setport -hs",
    "setport -p --port 9",
    "setport -p 77 33",
    "setport -p -21",
    "setport -p 0",
    "setport --port",
    "setport -p 90642",
    "setport -x 45321",
    "setport -P 714",
    "setport -?",
    "setport -!",
    "setport --about",
    "setport -v",
    "setport --version",
    "setport -p -e",
    "setport --port -e",
    "setport -p -e MY_PORT",
    "setport --port -e YOUR_PORT"
}; // end array

int main(){
    //Declare vars:
    bool aliasCheck = false;
    
    //***Deprecated due to bash shell re-initialization
    //***The precise commands found in checkAlias() and createAlias() 
    //***work as expected from within bash shell
    //If alias was NOT found
    //if (!checkAlias()){createAlias();} 
    
    //Run test cases
    runTests();
    
    return 0;
} // end main()

bool checkAlias(){
    //Enable access to .bash_aliases
    result = system("chmod u+x ~/.bash_aliases");
    
    //If read/write access modification was successful
    if (result == 0){
        //Save contents of .bash_aliases to txt file
        system("cat ~/.bash_aliases >my_aliases.txt");
        
        //Search txt file for setport alias
        result = system("grep 'setport' my_aliases.txt") / 256;
        
        if (result == 0){return true;} // alias was found
        else{return false;} // alias was NOT found
    } // end if
} // end function checkAlias()

void createAlias(){
    //Append aliases to .bash_aliases
    system("echo alias setport='~/workspace/portsetter/setport.cpp.o' >> .bash_aliases");
    system("echo alias testsetport='~/workspace/portsetter/testsetport.cpp.o' >> .bash_aliases");
    
    //Update .bash_aliases
    system("source ~/.bash_aliases");
} // end function createAlias()

void runTests(){
    //Run each test, then print results
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -h >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o --help >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -p 4040 >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o --port 4040 >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o help >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -help >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o --h >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -h --help >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -hs >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -p --port 9 >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -p 77 33 >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -p -21 >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -p 0 >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o --port >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -p 90642 >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -x 45321 >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -P 714 >test.txt") / 256;
    print(result);
    //CO2
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -? >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -! >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o --about >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -v >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o --version >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -p -e >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o --port -e >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o -p -e MY_PORT >test.txt") / 256;
    print(result);
    result = system("/home/ubuntu/workspace/portsetter/setport.cpp.o --port -e YOUR_PORT >test.txt") / 256;
    print(result);
    cout << "See readme.txt if you would like to test the language feature. " << endl;
} // end function runTests()

void print(int _result){
    if (_result != 0){cout << testCasesStrings[i++] + ": failed. " << endl; } // test failed
    else {cout << testCasesStrings[i++] + ": passed. " << endl; } // test passed
} // end function print()