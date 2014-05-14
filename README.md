# BASM

The Basic Computer Assembler


## What is BASM?

BASM is a user friendly and easy to use assembler for The Basic Computer,
capable of creating the object, list and hex file and giving detailed error
reports. It's more of academic use for students who wish to understand how
does The Basic Computer actually work. Alongside this assembler, soon a
simulator will also be available at BASM's GitHub page.


## Legal note

BASM is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or any later version.

BASM is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
BASM. If not, see <http://www.gnu.org/licenses/>.


## How to use?

It is much more preferable to add BASM's 'bin' folder location to 'PATH'
environment variable for both MS Windows and Linux users. You can also do it
the easy way by copying the executable into a folder that is already added to
'PATH', like 'C:\Windows\' or '/bin/' (Windows users should also copy
two .dll files). Then simply open a terminal and type:

    $ basm test.asm

The output will be written to files 'test.obj', 'test.lst' and 'test.hex',
respective to their source file name. You may want to change them:

    $ basm test.asm -o objectfile.obj -l listfile.lst -h hexfile.hex

Follow these links and see how to add a location to the 'PATH': 
http://windows7hacker.com/index.php/2010/05/how-to-addedit-environment-variables-in-windows-7/
http://linuxheadquarters.com/howto/basic/path.shtml


## How to compile from source?

Windows users can open 'basm.sln' under 'prj\vs10' with Visual Studio 2010 or
later (either the express or full version), and simply compile the solution.
The executable output will be saved as 'bin\basm.exe'.
Under linux, if you have g++ (GNU C++ Compiler), just run 'compile.sh' script:

    $ ./compile.sh

In case something went wrong, change the script's permissions:

    $ chmod 755 compile.sh

Then try running it again. The executable output will be 'bin/basm'.


## Web and contact

Visit BASM's page at SourceForge:
    http://github.com/nalamat/basm

Ask questions, report bugs and give suggestions here:
    http://github.com/nalamat/basm/issues

Feel free to email me about anything:
    nnalamat@gmail.com
