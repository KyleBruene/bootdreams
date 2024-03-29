/*
    This file is part of BootDreams.

    Copyright (C) 2010 Cyle Terry

    BootDreams is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BootDreams is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BootDreams.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mister.h"

typedef enum {
    unscrambled,
    sh_elf,
    scrambled
} enummbf;

typedef struct {
    char hardware_id[17]; /* always "SEGA SEGAKATANA " */
    char maker_id[17]; /* always "SEGA ENTERPRISES" */
    char checksum[5];
    char disc_info[12];
    char area_symbols[4];
    char peripherals[8];
    int mouse;
    int gun;
    int keyboard;
    int expand_analog_vert;
    int expand_analog_hor;
    int analog_vert_controller;
    int analog_hor_controller;
    int analog_l_trigger;
    int analog_r_trigger;
    int expand_dir_buttons;
    int z_button;
    int y_button;
    int x_button;
    int d_button;
    int c_button;
    int start_abdir_buttons;
    int memory_card;
    int microphone_card;
    int purupuru_card;
    int other;
    int vga_box;
    int windowsce;
    char product_id[11];
    char product_version[6];
    char release_date[9];
    char boot_filname[17];
    char company_name[17];
    char software_name[129];
    char mr_trademark[MR_TRADEMARK_SIZE];
    char mr_sega[MR_SEGA_SIZE];
    char mr_user[MR_USER_MAX_SIZE];
} typebsf;

enummbf read_mbf(char *mbf);
int read_bsf(char *bsf);
