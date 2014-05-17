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

#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <numeric>
#include "glob.h"
#include "util.h"
#include "ui.h"

int io_obj_pos, io_obj_size = 4*1024;
int io_line_num, io_line_count;
string io_line;

string io_src_file, io_obj_file, io_lst_file, io_hex_file;
fstream io_src_stream, io_obj_stream, io_lst_stream, io_hex_stream;
char io_obj_array[4*1024*2];
vector<string> io_lst_vector;

bool io_init()
{
	memset(io_obj_array, 0, sizeof io_obj_array);
	return true;
}

bool io_src_open()
{
	io_src_stream.open(io_src_file.data(), fstream::in);
	if ( !io_src_stream || io_src_stream.bad() || io_src_stream.fail() )
		ui_error("Cannot open specified source file: '" + io_src_file + "'");
	return !ui_has_error();
}

void io_src_close()
{
	if ( io_src_stream.is_open() )
		io_src_stream.close();
}

bool io_clear()
{
	io_src_stream.clear();
	io_src_stream.seekg(0);
	if ( !io_src_stream ) return false;

	io_obj_pos = 0;
	io_line_num = 1;

	io_lst_vector.clear();
	io_lst_vector.reserve(io_line_count);
	return true;
}

bool io_line_read()
{
	return getline(io_src_stream, io_line);
}

bool io_write()
{
	stringstream ss;
	//ss << pad_str(io_line_num,8) << pad_str("",20) << '\t' << io_line;
	ss << pad_str("",32) << "--\t" << io_line;
	//ss << pad_str(io_line_num,8) << pad_str("",41) << '\t' << io_line;
	io_lst_vector.push_back(ss.str());
	return true;
}

bool io_write(int code, string label)
{
	stringstream ss;
	//ss << pad_str(io_line_num,8) << pad_str(io_obj_pos,5) << "(" << hex_to_str(io_obj_pos,3) << ")   " << hex_to_str(code,4) << "   \t" << io_line;
	ss << pad_str(io_obj_pos,5) << " => \"" << bin_to_str(code,16) << "\",    --\t" << io_line;
	//ss << pad_str(io_line_num,8) << pad_str(io_obj_pos,5) << "(" << bin_to_str(io_obj_pos,12) << ")   " << bin_to_str(code,16) << "   \t" << io_line;
	io_obj_array[2*io_obj_pos] = ((char*)&code)[0];
	io_obj_array[2*io_obj_pos+1] = ((char*)&code)[1];
	io_lst_vector.push_back(ss.str());
	return true;
}

bool io_obj_write()
{
	io_obj_stream.open(io_obj_file.data(), fstream::binary | fstream::out);
	if ( !io_obj_stream || io_obj_stream.bad() )
		ui_error("Cannont open specified object file: '" + io_obj_file + "'");
	else
	{
		if ( !io_obj_stream.write( io_obj_array, io_obj_size*2 ) || !io_obj_stream.flush() )
			ui_error("Something weird has happened during writing of the object file, please report to software developers at " + glob_app_web);
	}
	io_obj_stream.close();
	return !ui_has_error();
}

bool io_lst_write()
{
	io_lst_stream.open(io_lst_file.data(), fstream::out);
	if ( !io_lst_stream || io_lst_stream.bad() )
		ui_error("Cannon open sepcified list file: '" + io_lst_file + "'");
	else
	{
		for ( vector<string>::iterator it=io_lst_vector.begin(); it!=io_lst_vector.end(); ++it )
			io_lst_stream << *it << "\n";
		if ( !io_lst_stream.flush() )
			ui_error("Something weird has happened during writing of the list file, please report to software developers at " + glob_app_web);
	}
	io_lst_stream.close();
	return !ui_has_error();
}

bool io_hex_write()
{
	// TODO: a clean up!
	io_hex_stream.open(io_hex_file.data(), fstream::out);
	if ( !io_hex_stream || io_hex_stream.bad() )
		ui_error("Cannon open sepcified hex file: '" + io_hex_file + "'");
	else
	{
		int i, j, k;
		for ( i=0; i<io_obj_size; i+=8 )
		{
			for ( j=i+7; j>=i && !io_obj_array[2*j] && !io_obj_array[2*j+1]; --j );
			if ( j+1-i>0 )
			{
				string s = hex_to_str((j+1-i)*2,2) + hex_to_str(i*2,4) + "00";
				for ( k=2*i; k<2*j+2; ++k ) s += hex_to_str(io_obj_array[k],2);

				int sum = ((j+1-i)*2) + ((i*2)&0xff) + (((i*2)>>8)&0xff);
				for ( k=2*i; k<2*j+2; ++k ) sum += io_obj_array[k];
				sum = (~sum+1)&0xff;

				io_hex_stream << ":" << s << hex_to_str(sum, 2) << "\n";
			}
		}

		io_hex_stream << ":00000001FF\n";

		if ( !io_hex_stream.flush() )
			ui_error("Something weird has happened during writing of the hex file, please report to software developers at " + glob_app_web);
	}
	io_hex_stream.close();
	return !ui_has_error();
}
