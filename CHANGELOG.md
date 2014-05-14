
---------------
BASM Change Log
---------------

1.2 (2012/02/01):
	* Reversed object file byte order, now low byte comes first
	* Added 'bin/msvcp100.dll', windows executable won't run without it
	* Added 'bin/msvcr100.dll', windows executable won't run without it
	* Added 'resource.rc', windows executable now contains version information
	* Another output format: Intel HEX files are now generated
	* '-h' option specifies the path of hex output

1.1 (2012/01/14):
	* A bit of code clean up
	* '--help' option prints a quick guide
	* '--version' option prints assembler's version information
	* On no input file, prints a quick guide
	* A runtime error on bad input file handled
	* 'README.TXT' added
	* 'clean.bat' added, removes unnecessary visual studio files
	* 'compile.sh' added, compiles the source with g++
