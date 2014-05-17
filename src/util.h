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

#pragma once

#ifndef __BASM_UTIL_H__
#define __BASM_UTIL_H__

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool is_alpha(const char &c);
bool is_digit(const char &c);
bool is_alphanum(const char &c);
bool is_space(const char &c);
bool is_delim(const char &c);
bool is_delim(const string &s);
bool is_sign(const char &c);

string to_lower(const string &s);
string to_upper(const string &s);

bool is_comment(const string &s);
bool is_name(const string &s);
bool is_dec(const string &s, bool forced_prefix=false);
bool is_hex(const string &s, bool forced_prefix=false);
bool is_bin(const string &s, bool forced_prefix=false);
bool is_data(const string &s);

int parse_dec(const string &s);
int parse_hex(const string &s);
int parse_bin(const string &s);
int parse_data(const string &s);

string get_file_path_no_ext(const string &s);
string hex_to_str(int hex, int len);
string bin_to_str(int bin, int len);
string pad_str(int num, int pad);
string pad_str(string str, int pad);

class tokenizer
{
public:
	string data;
	int pos;

	tokenizer();
	tokenizer(string data_);
	void set(string data_);
	string next();
	bool has();
	bool operator!();
};

// does exactly what tokenizer::next() does
// note: unlike standard stream extraction operations, in
// case of reaching the end of stream, 'str' is set to ""
tokenizer& operator>>(tokenizer &tok, string &str);
vector<string> tokenize(string str, int token_count);

#endif
