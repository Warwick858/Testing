# CS3370_Setport
Port-setting Linux utility emulator.

Setport Testing Instructions: testsetport.cpp
Steps:

1) Open a command line.

2) Navigate to parent directory of testsetport.cpp.o

3) Enter command: testsetport

The results of each test case, along with its description, will be printed to the console.

Note: The alias features have been deprecated due to bash shell re-initialization.
If you would like to run setport or testsetport commands from any directory, append the following to ~/.bash_aliases:
alias setport='~/workspace/portsetter/setport.cpp.o'
alias testsetport='~/workspace/portsetter/testsetport.cpp.o'

Note: The language feature cannot be tested from within testsetport due to bash shell re-initialization.
If you would like to test the language feature, set one or more of the language environment variables below as follows:
$ LANGUAGE=[VALUE]
$ LC_ALL=[VALUE]
$ LC_MESSAGES=[VALUE]
$ LANG=[VALUE]

**Omit the brackets [] from VALUE
