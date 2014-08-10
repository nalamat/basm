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

#pragma once

#ifndef __BASM_IO_H__
#define __BASM_IO_H__

extern int io_obj_pos, io_obj_size;
extern int io_line_num, io_line_count;
extern string io_line;
extern string io_src_file, io_obj_file, io_lst_file, io_hex_file;


bool io_init();
bool io_src_open();
void io_src_close();
bool io_clear();
bool io_line_read();
bool io_write();
bool io_write(int code, string label="");
bool io_obj_write();
bool io_lst_write();
bool io_hex_write();

#endif
