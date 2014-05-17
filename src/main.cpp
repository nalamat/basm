/*************************************************************************
 *                                                                       *
 * This file is a part of the BASM project: The Basic Computer Assembler *
 * Copyright (C) 2012-2014, Nima Alamatsaz, All rights reserved          *
 * Email: nnalamat@gmail.com                                             *
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
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include "glob.h"
#include "ui.h"
#include "io.h"
#include "parse.h"

using namespace std;

string glob_app_shortname = "BASM";
string glob_app_fullname = "BASM: The Basic Computer Assembler";
string glob_app_version = "1.2.0";
string glob_app_email = "nnalamat@gmail.com";
string glob_app_web = "http://github.com/nalamat/basm";

int main(int argc, char *args[])
{
	io_init();
	parse_init();

	if      ( !ui_input_args(argc,args)        ) ;
	else if ( !io_src_open()                   ) ;
	else if ( !parse_first_pass()              ) ui_message("Failed on first pass");
	else if ( !parse_second_pass()             ) ui_message("Failed on second pass");
	else if ( !io_obj_write()                  ) ui_message("Failed on writing of the object file");
	else if ( !io_lst_write()                  ) ui_message("Failed on writing of the list file");
	else if ( !io_hex_write()                  ) ui_message("Failed on writing of the hex file");
	else                                         ui_message("Success");

	io_src_close();

	#if WIN && DEBUG
	system("pause");
	#endif

	return 0;
}
