/*************************************************************************
 *                                                                       *
 * This file is a part of the BASM project: The Basic Computer Assembler *
 * Copyright (C) 2012-2014 Nima Alamatsaz, All rights reserved           *
 * Email: nialamat@gmail.com                                             *
 * Web:   http://github.com/nalamat/basm                                 *
 *                                                                       *
 * BASM is free software: you can redistribute the software              *
 * and/or modify it under the terms of the GNU General Public License    *
 * version 3 as published by the Free Software Foundation                *
 *                                                                       *
 * BASM is distributed in the hope that it will be useful,               *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with BASM. If not, see <http://www.gnu.org/licenses/>.          *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include "glob.h"
#include "util.h"
#include "ui.h"
#include "io.h"

using namespace std;

queue<string> error_queue;
queue<string> warning_queue;
queue<string> message_queue;
bool has_error = false;

bool ui_has_error()
{
	return has_error;
}

void ui_error(string reason)
{
	//stringstream ss;
	cout << "ERROR: " << reason << endl;
	//error_queue.push( ss.str() );
	has_error = true;
}

void ui_errorl(string reason)
{
	//stringstream ss;
	cout << "ERROR on line " << io_line_num << ": " << reason << endl;
	//error_queue.push( ss.str() );
	has_error = true;
}

void ui_warning(string reason)
{
	//stringstream ss;
	cout << "WARNING: " << reason << endl;
	//warning_queue.push( ss.str() );
}

void ui_warningl(string reason)
{
	//stringstream ss;
	cout << "WARNING on line " << io_line_num << ": " << reason << endl;
	//warning_queue.push( ss.str() );
}

void ui_message(string text)
{
	cout << text << endl;
	//message_queue.push(text);
}

bool ui_input_args(int argc, char *args[])
{
	io_src_file = io_obj_file = io_lst_file = io_hex_file = "";
	bool runoption_help = false;
	bool runoption_version = false;

	for ( int i=1; i<argc; ++i )
	{
		string arg = args[i];

		if ( arg=="-o" )
		{
			if ( i+1<argc )
				io_obj_file = args[++i];
			else
				ui_error("Object file not specified after '-o' option");
		}
		else if ( arg=="-l" )
		{
			if ( i+1<argc )
				io_lst_file = args[++i];
			else
				ui_error("List file not specified after '-l' option");
		}
		else if ( arg=="-h" )
		{
			if ( i+1<argc )
				io_hex_file = args[++i];
			else
				ui_error("Intel HEX file not specified after '-h' option");
		}
		else if ( arg=="--help" )
			runoption_help = true;
		else if ( arg=="--version" )
			runoption_version = true;
		else if ( arg[0]=='-' || arg[0]=='-' && arg[1]=='-' )
			ui_error("Invalid option '" + arg + "'");
		else
		{
			if ( io_src_file.empty() )
				io_src_file = arg;
			else
			{
				ui_error("Assembling multiple files is not yet allowed");
				break;		// this break prevents multiple occurences of the invalid option error
			}
		}
	}

	if ( runoption_help )
	{
		ui_print_help();
		return false;
	}
	else if ( runoption_version )
	{
		ui_print_version();
		return false;
	}
	else if ( io_src_file.empty() )
	{
		ui_error("Source file not specified");
		ui_print_help();
		return false;
	}

	// user may provide any of the output file names
	// ungiven file names are determined by the priority list below
	string *files[] = { &io_obj_file, &io_lst_file, &io_hex_file, &io_src_file };
	string ext[] = { ".obj", ".lst", ".hex", ".xxx" };
	int n = 4;
	string def = "";

	for ( int i=0; i<n && def.empty(); ++i )
		def = get_file_path_no_ext(*files[i]);
	for ( int i=0; i<n; ++i )
		if ( files[i]->empty() )
			*files[i] = def + ext[i];

	return !ui_has_error();
}

//void ui_print_queues()
//{
//	while ( !error_queue.empty() )
//	{
//		cout << error_queue.front() << endl;
//		error_queue.pop();
//	}
//	while ( !warning_queue.empty() )
//	{
//		cout << warning_queue.front() << endl;
//		warning_queue.pop();
//	}
//	while ( !message_queue.empty() )
//	{
//		cout << message_queue.front() << endl;
//		message_queue.pop();
//	}
//}

void ui_print_help()
{
	cout
		<< "Usage: basm [options] sourcefile [outputoption outputfile]\n"
		<< "Options:\n"
		<< "  --help                 Display this help information\n"
		<< "  --version              Display assembler's version information\n"
		<< "  -o <file>              Place the object output into <objectfile>\n"
		<< "  -l <file>              Place the list output into <listfile>\n"
		<< "  -h <file>              Place the Intel HEX output into <listfile>"
		<< endl;
}

void ui_print_version()
{
	cout
		<< glob_app_fullname + ", version " << glob_app_version << "\n"
		<< "Copyright (C) 2012, Nima Alamatsaz, All rights reserved\n"
		<< "Email: " + glob_app_email + "\n"
		<< "Web:   " + glob_app_web   + "\n"
		<< "\n"
		<< "License GPLv3+: GNU General Public License version 3 or later\n"
		<< "<http://gnu.org/licenses/>. This is free software: you are free to\n"
		<< "change and redistribute it under terms of GNU General Public License\n"
		<< "as published by the Free Software Foundation either version 3 of the\n"
		<< "License, or any later version. There is NO WARRANTY, not even for\n"
		<< "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
		<< endl;
}
