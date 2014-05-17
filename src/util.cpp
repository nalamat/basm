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

#include "util.h"

bool is_alpha(const char &c)
{
	return 'a'<=c&&c<='z' || 'A'<=c&&c<='Z' || c=='_';
}

bool is_digit(const char &c)
{
	return '0'<=c&&c<='9';
}

bool is_alphanum(const char &c)
{
	return '0'<=c&&c<='9' || 'a'<=c&&c<='z' || 'A'<=c&&c<='Z' || c=='_';
}

bool is_space(const char &c)
{
	return c==' ' || c=='\t';
}

bool is_delim(const char &c)
{
	return c==':' || c==',';
}

bool is_delim(const string &s)
{
	return s==":" || s==",";
}

bool is_sign(const char &c)
{
	return c=='+' || c=='-';
}

string to_lower(const string &s)
{
	string r(s);
	for ( int i=0; i<r.size(); ++i )
		if ( is_alpha(r[i]) )
			r[i] = tolower(r[i]);
	return r;
}

string to_upper(const string &s)
{
	string r(s);
	for ( int i=0; i<r.size(); ++i )
	{
		char c;
		if ( i>=64 )
			c = r[i];
		if ( is_alpha((unsigned char)r[i]) )
			r[i] = toupper(r[i]);
	}
	return r;
}

bool is_comment(const string &s)
{
	bool valid = !s.empty();
	if ( valid )
		valid = s[0]=='/' || s[0]==';' || s[0]=='!' || s[0]=='%';
	return valid;
}

bool is_name(const string &s)
{
	bool valid = !s.empty();
	for ( int i=0; i<s.size() && valid; ++i )
		if ( i==0 ) valid = is_alpha(s[i]);
		else valid = is_alphanum(s[i]);
	return valid;
}

bool is_dec(const string &s, bool forced_prefix)
{
	bool valid = !s.empty();
	int i = 0;
	if ( s[0]=='-' || s[0]=='+' ) i = 1;
	for ( ; i<s.size() && valid; ++i )
		valid = is_digit(s[i]);
	return valid;
}

bool is_hex(const string &s, bool forced_prefix)
{
	bool valid = !s.empty();
	int i = 0;
	if ( forced_prefix && valid ) valid = s.size()>2 && s[0]=='0' && toupper(s[1])=='X';
	if ( forced_prefix && valid ) i = 2;
	for ( ; i<s.size() && valid; ++i )
		valid = is_digit(s[i]) || 'a'<=tolower(s[i]) && tolower(s[i])<='f';
	return valid;
}

bool is_bin(const string &s, bool forced_prefix)
{
	bool valid = !s.empty();
	int i = 0;
	if ( forced_prefix && valid ) valid = s.size()>2 && s[0]=='0' && toupper(s[1])=='B';
	if ( forced_prefix && valid ) i = 2;
	for ( ; i<s.size() && valid; ++i )
		valid = s[i]=='0' || s[i]=='1';
	return valid;
}

bool is_data(const string &s)
{
	return is_dec(s,1) || is_hex(s,1) || is_bin(s,1);
}

int parse_dec(const string &s)
{
	int res = 0;
	int i = 0;
	bool positive = s[0]!='-';
	if ( s[0]=='-' || s[0]=='+' ) i = 1;
	for ( ; i<s.size(); i++ )
		res = res*10 + int(s[i]-'0');
	return positive ? res : -res;
}

int parse_hex(const string &s)
{
	int res = 0;
	int i = 0;
	if ( s.size()>2 && s[0]=='0' && toupper(s[1])=='X' ) i = 2;
	for ( ; i<s.size(); i++ )
		if ( is_digit(s[i]) )
			res = res*16 + int(s[i]-'0');
		else
			res = res*16 + int(tolower(s[i])-'a') + 10;
	return res;
}

int parse_bin(const string &s)
{
	int res=0;
	int i = 0;
	if ( s.size()>2 && s[0]=='0' && toupper(s[1])=='B' ) i = 2;
	for ( ; i<s.size(); i++ )
		res = res*2 + int(s[i]-'0');
	return res;
}

int parse_data(const string &s)
{
	if ( is_dec(s,1) )
		return parse_dec(s);
	else if ( is_hex(s,1) )
		return parse_hex(s);
	else if ( is_bin(s,1) )
		return parse_bin(s);
	else
		return 0;
}

string get_file_path_no_ext(const string &s)
{
	#ifdef WIN
		char dir_sep = '\\';
	#else
		char dir_sep = '/';
	#endif

	if ( s.empty() ) return string("");

	//size_t beg = s.find_last_of(dir_sep);
	//if ( beg == s.npos ) beg = 0;
	//else ++beg;

	size_t end = s.find_last_of('.');
	if ( end == s.npos ) end = s.size();

	return s.substr(0, end);
}

string hex_to_str(int hex, int len)
{
	string res(len, '0');
	int i=0;
	for ( int i=0; i<len; ++i )
	{
		int d = hex & 0xf;
		res[i] = ( d<10 ? '0'+d : 'A'+d-10 );
		hex >>= 4;
	}
	reverse(res.begin(), res.end());
	return res;
}

string bin_to_str(int bin, int len)
{
	string res(len, '0');
	int i=0;
	for ( int i=0; i<len; ++i )
	{
		res[i] = ( bin&1 ? '1' : '0' );
		bin >>= 1;
	}
	reverse(res.begin(), res.end());
	return res;
}

string pad_str(int num, int pad)
{
	stringstream ss;
	ss << num;
	return ss.str() + string(max(pad-(int)ss.str().length(),0), ' ');
}

string pad_str(string str, int pad)
{
	return str + string(max(pad-(int)str.length(),0), ' ');
}

tokenizer::tokenizer()
{
	set("");
}

tokenizer::tokenizer(string data_)
{
	set(data_);
}

void tokenizer::set(string data_)
{
	data = data_;
	pos = 0;
}

string tokenizer::next()
{
	for ( ; pos<data.size(); ++pos )
		if ( !is_space(data[pos]) )
			break;

	if ( pos>=data.size() ) return "";
	else if ( is_alphanum(data[pos]) || is_sign(data[pos]) )
	{
		int beg = pos++;

		for ( ; pos<data.size(); ++pos )
			if ( !is_alphanum(data[pos]) )
				break;

		return data.substr(beg, pos-beg);
	}
	else
	{
		return data.substr(pos++, 1);
	}
}

bool tokenizer::has()
{
	return pos<data.size();
}

bool tokenizer::operator!()
{
	return !has();
}

tokenizer& operator>>(tokenizer &tok, string &str)
{
	str = tok.next();
	return tok;
}

vector<string> tokenize(string str, int token_count)
{
	tokenizer tok(str);
	vector<string> tokens;
	tokens.reserve(token_count);
	for ( int i=0; i<token_count; ++i )
		tokens.push_back(tok.next());
	return tokens;
}
