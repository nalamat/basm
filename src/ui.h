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

#ifndef __BASM_UI_H__
#define __BASM_UI_H__

#include <string>

using namespace std;

bool ui_has_error();
void ui_error(string reason);
void ui_errorl(string reason);
void ui_warning(string reason);
void ui_warningl(string reason);
void ui_message(string text);
bool ui_input_args(int argc, char *args[]);
//void ui_print_queues();
void ui_print_help();
void ui_print_version();

#endif
