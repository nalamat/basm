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

#include <string>
#include <vector>
#include <map>
#include "glob.h"
#include "util.h"
#include "ui.h"
#include "io.h"

using namespace std;

map<string,int> label_map;
map<string,int> mri_map;
map<string,int> nonmri_map;
map<string,int> pseudo_map;

bool is_mri     (const string &s) { return mri_map.find(s) != mri_map.end(); }
bool is_nonmri  (const string &s) { return nonmri_map.find(s) != nonmri_map.end(); }
bool is_pseudo  (const string &s) { return pseudo_map.find(s) != pseudo_map.end(); }
bool is_reserved(const string &s) { return is_mri(s) || is_nonmri(s) || is_pseudo(s); }
bool is_label   (const string &s) { return label_map.find(s) != label_map.end(); }

bool parse_init()
{
	mri_map["AND"] = 0x0000;
	mri_map["ADD"] = 0x1000;
	mri_map["LDA"] = 0x2000;
	mri_map["STA"] = 0x3000;
	mri_map["BUN"] = 0x4000;
	mri_map["BSA"] = 0x5000;
	mri_map["ISZ"] = 0x6000;

	nonmri_map["CLA"] = 0x7800;
	nonmri_map["CLE"] = 0x7400;
	nonmri_map["CMA"] = 0x7200;
	nonmri_map["CME"] = 0x7100;
	nonmri_map["CIR"] = 0x7080;
	nonmri_map["CIL"] = 0x7040;
	nonmri_map["INC"] = 0x7020;
	nonmri_map["SPA"] = 0x7010;
	nonmri_map["SNA"] = 0x7008;
	nonmri_map["SZA"] = 0x7004;
	nonmri_map["SZE"] = 0x7002;
	nonmri_map["HLT"] = 0x7001;

	nonmri_map["INP"] = 0xF800;
	nonmri_map["OUT"] = 0xF400;
	nonmri_map["SKI"] = 0xF200;
	nonmri_map["SKO"] = 0xF100;
	nonmri_map["ION"] = 0xF080;
	nonmri_map["IOF"] = 0xF040;

	pseudo_map["ORG"] = 0;
	pseudo_map["END"] = 0;
	pseudo_map["DEC"] = 0;
	pseudo_map["HEX"] = 0;
	pseudo_map["BIN"] = 0;

	return true;
}

void parse_org(vector<string> s)
{
	if ( s[1].empty() || is_comment(s[1]) )
		ui_errorl("Origin not specified");
	else if ( !is_data(s[1]) )
		ui_errorl("Invalid origin, origin must be of numeric type, either decimal, hex or binary");
	else if ( !s[2].empty() && !is_comment(s[2]) )
		ui_errorl("The 'ORG' pseudo instruction doesn't accept extra parameters");
	else
	{
		int temp = parse_data(s[1]);
		if ( temp<0 )
			ui_errorl("Negative origins or not allowed");
		else
			io_obj_pos = temp-1;
	}
}

void parse_end(vector<string> s)
{
	if ( !s[1].empty() && !is_comment(s[1]) )
		ui_errorl("The 'END' pseudo instruction doesn't accept any parameters");
}

void parse_label(vector<string> s)
{
	if ( !is_name(s[0]) )
		ui_errorl("Invalid label name '" + s[0] + "', Labels must start with alphabet and only contain alphanumeric charactars");
	else if ( is_reserved(s[0]) )
		ui_errorl("Reserved word '" + s[0] + "' cannot be used as label");
	else if ( s[2].empty() || is_comment(s[2]) )
		ui_errorl("Empty lines cannot have a label");
	else if ( s[2]=="ORG" || s[2]=="END" )
		ui_errorl("Pseudo instruction '" + s[0] + "' cannot have a label.");
	else
	{
		if ( label_map.find(s[0]) != label_map.end() ) ui_warningl("Duplicated label '" + s[0] + "', previous one will be ignored");
		label_map[s[0]] = io_obj_pos;
	}
}

void parse_mri(vector<string> s)
{
	int instruction = mri_map[s[0]];
	int operand;

	if ( s[1].empty() || is_comment(s[1]) )
		ui_errorl("MRI '" + s[0] + "' requires address of the operand as parameter");
	else if ( is_name(s[1]) && !is_label(s[1]) )
		ui_errorl("Specified label '" + s[1] + "' was not found");
	else if ( is_label(s[1]) || is_data(s[1]) )
	{
		if ( is_data(s[1]) )
			operand = parse_data(s[1]);
		else
			operand = label_map[s[1]];

		if ( operand<0 )
			ui_errorl("Address of the operand cannot be negative");
		else if ( io_obj_size<=operand )
			ui_errorl("Address of the operand exceeds memory bounds (4096)");
		else if ( s[2].empty() || is_comment(s[2]) )
			io_write( instruction | operand );
		else if ( s[2]=="I" && !s[3].empty() && !is_comment(s[3]) )
			ui_errorl("Unexpected expression '" + s[3] + "' after 'I' specifier");
		else if ( s[2]=="I" )
			io_write( instruction | operand | 0x8000 );
		else
			ui_errorl("Unexpected expression '" + s[2] + "' after address of the operand");
	}
	else
		ui_errorl("Expected address of the operand after MRI '" + s[0] + "', either a label or a valid data type");
}

void parse_nonmri(vector<string> s)
{
	if ( s[1].empty() || is_comment(s[1]) )
		io_write( nonmri_map[s[0]] );
	else
		ui_errorl("Unexpected expression '" + s[1] + "' after Non MRI '" + s[0] + "', no parameter is required");
}

void parse_pseudo(vector<string> s)
{
	string type="";
	if ( s[0]=="DEC" ) type = "decimal";
	if ( s[0]=="HEX" ) type = "hexadecimal";
	if ( s[0]=="BIN" ) type = "binary";

	if ( s[1].empty() || is_comment(s[1]) || s[0]=="DEC"&&!is_dec(s[1]) || s[0]=="HEX"&&!is_hex(s[1]) || s[0]=="BIN"&&!is_bin(s[1]) )
		ui_errorl("Pseudo instruction '" + s[0] + "' needs a " + type + " data type as parameter");
	else if ( !s[2].empty() && !is_comment(s[2]) )
		ui_errorl("Unexpected expression '" + s[2] + "' after " + type + " data type, pseudo instruction '" + s[0] + "' doesn't accept anymore parameters");
	else if ( s[0] == "DEC" )
		io_write( parse_dec(s[1]) );
	else if ( s[0] == "HEX" )
		io_write( parse_hex(s[1]) );
	else if ( s[0] == "BIN" )
		io_write( parse_bin(s[1]) );
	else
		ui_errorl("This error should NEVER happen! Please report to software developers at http://sf.net/p/basm");
}

void parse_data(vector<string> s)
{
	if ( !s[1].empty() && !is_comment(s[1]) )
		ui_errorl("Unexpected expression '" + s[1] + "' after numeric data type");
	else
		io_write( parse_data(s[0]) );
}

bool parse_first_pass()
{
	vector<string> s;
	
	if ( !io_clear() )
		ui_error("An unexpected error occured during reading of the source file");
	else while ( io_line_read() )
	{
		io_line = to_upper(io_line);
		s = tokenize(io_line, 10);

		if ( s[0].empty() || is_comment(s[0]) )
			--io_obj_pos;
		else if ( !s[1].empty() && is_delim(s[1]) )
			parse_label(s);
		else if ( s[0]=="ORG" )
			parse_org(s);
		else if ( s[0]=="END" )
		{
			parse_end(s);
			break;
		}

		if ( io_obj_pos >= io_obj_size )
		{
			ui_errorl("Out of memory bound (4096 words)");
			break;
		}

		++io_obj_pos;
		++io_line_num;
	}

	io_line_count = io_line_num;
	return !ui_has_error();
}

bool parse_second_pass()
{
	vector<string> s;
	
	if ( !io_clear() )
		ui_error("An unexpected error occured during reading of the source file");
	else while ( io_line_read() )
	{
		io_line = to_upper(io_line);
		s = tokenize(io_line, 10);

		if ( s[0].empty() || is_comment(s[0]) )
		{
			--io_obj_pos;
			io_write();
		}
		// note: 'reserved word as label' error has been handled in the first pass
		else if ( s[0]=="ORG" )
		{
			parse_org(s);
			io_write();
		}
		else if ( s[0]=="END" )
		{
			parse_end(s);
			io_write();
			break;
		}
		else
		{
			if ( !s[1].empty() && is_delim(s[1]) ) s.erase(s.begin(), s.begin()+2);

			if ( is_delim(s[0]) )
				ui_errorl("Only one delimitter is required after a label");
			else if ( is_mri(s[0]) )
				parse_mri(s);
			else if ( is_nonmri(s[0]) )
				parse_nonmri(s);
			else if ( is_pseudo(s[0]) )
				parse_pseudo(s);
			else if ( is_data(s[0]) )
				parse_data(s);
			else if ( is_name(s[0]) && !s[1].empty() && is_delim(s[1]) )
				ui_errorl("Multiple labels are not allowed for a single line");
			else
				ui_errorl("Unexpected expression '" + s[0] + "'");
		}

		if ( io_obj_pos >= io_obj_size )
		{
			ui_errorl("Out of memory bound (4096 words)");
			break;
		}

		++io_obj_pos;
		++io_line_num;
	}

	return !ui_has_error();
}
