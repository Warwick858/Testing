# CS3370_Setport

Changes Made!!!!!!!!!!!!!!!

Welcome to setport, a port-setting Linux utility emulator.

Cloud9 Setup Instructions:

	1) create new workspace

	2) once the new workspace is created, right-click your home directory, and click on "new folder"

	3) name this new folder "portsetter"   (omit quotations)

	4) right-click the "portsetter" directory and click, "new folder", and name it "langs"   (omit quotations)
	
	5) right-click the "langs" directory and click, "new file"

	6) name the file the exact name of one of the lang files located on GitHub, Example: setport.about_en.txt

	7) repeat steps 5-6 for every lang file located on GitHub

	8) right-click the "portsetter" directory and click, "new file", and name it "setport.cpp", 
		then copy and paste the file contents of the "setport" file from GitHub into this new file.

	9) right-click the "portsetter" directory and click, "new file", and name it "testsetport.cpp", 
		then copy and paste the file contents of the "testsetport" file from GitHub into this new file.

	10) right-click the "portsetter" directory and click, "new file", and name it "Makefile", 
		then copy and paste the file contents of the "Makefile" file from GitHub into this new file.


Setport.cpp Instructions:

	1) from the bash shell, navigate to the portsetter directory

	2) once the portsetter directory is the current directory, type: "make"   (omit quotations)

	3) then, type your desired command, Example: "./setport -p 8080"    (omit quotations)
		Note: If you would like to setup an alias for setport and testsetport, you can omit the "./" from
		the command above.  For instructions on alias setup, see below for the section marked "ALIASES".

Setport Testing (testsetport.cpp) Instructions:

	1) from the bash shell, navigate to the portsetter directory

	2) once the portsetter directory is the current directory, type: "make"   (omit quotations)
	Step 2 can be omitted if already performed for setport.cpp

	3) Enter command: "./testsetport"
		Note: If you would like to setup an alias for setport and testsetport, you can omit the "./" from
		the command above.  For instructions on alias setup, see below for the section marked "ALIASES".

	The results of each test case, along with its description, will be printed to the console.

	ALIASES: The alias features have been deprecated due to bash shell re-initialization. 
	If you would like to run setport or testsetport commands from any directory, 
	append the following to ~/.bash_aliases: 
	alias setport='~/workspace/portsetter/setport.cpp.o' 
	alias testsetport='~/workspace/portsetter/testsetport.cpp.o'

	Note: The language feature cannot be tested from within testsetport due to bash shell re-initialization. 
	If you would like to test the language feature, set one or more of the language environment variables 
	below as follows: $ LANGUAGE=[VALUE] $ LC_ALL=[VALUE] $ LC_MESSAGES=[VALUE] $ LANG=[VALUE]

	**Omit the brackets [] from VALUE
