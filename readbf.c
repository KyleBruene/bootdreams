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

#include <stdio.h>

#include "readbf.h"

/*
// ELF file header
struct elf_hdr_t {
	unsigned char	ident[16];	// For elf32-shl, 0x7f+"ELF"+1+1
	uint16		type;		// 0x02 for ET_EXEC
	uint16		machine;	// 0x2a for elf32-shl
	uint32		version;
	uint32		entry;		// Entry point
	uint32		phoff;		// Program header offset
	uint32		shoff;		// Section header offset
	uint32		flags;		// Processor flags
	uint16		ehsize;		// ELF header size in bytes
	uint16		phentsize;	// Program header entry size
	uint16		phnum;		// Program header entry count
	uint16		shentsize;	// Section header entry size
	uint16		shnum;		// Section header entry count
	uint16		shstrndx;	// String table section index
}
*/

enummbf read_mbf(char *mbf)	{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz"; /* UC & LC */
    char number0[] = "0123456789";
    char number1[] = "1234567890";
/*  char sh_elf[] = 0x127 & "ELF"; */
    char netbsd[] = "$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    char dreamsnes[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.0123456789-";
/*  char temp[] = "#...'...*...-.../...2...4...7...9...;...=...?...A...C...E...G...I...J...L...N...O...Q...R...T...U...W...X...Z..."; */
/*  char temp2[] = "0123456789abcdef....(null)..0123456789ABCDEF"; */
/*  char punch[] = "PORTDEV INFOENBLSTATRADRTOUTDRQCFUNCEND"; */
/*  char tetris[] = "abcdefghijklEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()"; */
/*  char bortmnt[] = "0123456789ABCDEF....Inf.NaN.0123456789abcdef....(null)..."; */

    return 0;
}

int read_bsf_peripheral(int ascii, int *FLAG1, int *FLAG2, int *FLAG3,
      int *FLAG4)	{
    switch(ascii)	{
        case '1': /* 10001100 */
            *FLAG1 = 1;
            if(FLAG2 != NULL)
                *FLAG2 = 0;
            if(FLAG3 != NULL)
                *FLAG3 = 0;
            if(FLAG4 != NULL)
                *FLAG4 = 0;
            break;
        case '2': /* 01001100 */
            *FLAG1 = 0;
            *FLAG2 = 1;
            *FLAG3 = 0;
            *FLAG4 = 0;
            break;
        case '3': /* 11001100 */
            *FLAG1 = 1;
            *FLAG2 = 1;
            *FLAG3 = 0;
            *FLAG4 = 0;
            break;
        case '4': /* 00101100 */
            *FLAG1 = 0;
            *FLAG2 = 0;
            *FLAG3 = 1;
            *FLAG4 = 0;
            break;
        case '5': /* 10101100 */
            *FLAG1 = 1;
            *FLAG2 = 0;
            *FLAG3 = 1;
            *FLAG4 = 0;
            break;
        case '6': /* 01101100 */
            *FLAG1 = 0;
            *FLAG2 = 1;
            *FLAG3 = 1;
            *FLAG4 = 0;
            break;
        case '7': /* 11101100 */
            *FLAG1 = 1;
            *FLAG2 = 1;
            *FLAG3 = 1;
            *FLAG4 = 0;
            break;
        case '8': /* 00011100 */
            *FLAG1 = 0;
            *FLAG2 = 0;
            *FLAG3 = 0;
            *FLAG4 = 1;
            break;
        case '9': /* 10011100 */
            *FLAG1 = 1;
            *FLAG2 = 0;
            *FLAG3 = 0;
            *FLAG4 = 1;
            break;
        case 'A': /* 10000010 */
            *FLAG1 = 0;
            *FLAG2 = 1;
            *FLAG3 = 0;
            *FLAG4 = 1;
            break;
        case 'B': /* 01000010 */
            *FLAG1 = 1;
            *FLAG2 = 1;
            *FLAG3 = 0;
            *FLAG4 = 1;
            break;
        case 'C': /* 11000010 */
            *FLAG1 = 0;
            *FLAG2 = 0;
            *FLAG3 = 1;
            *FLAG4 = 1;
            break;
        case 'D': /* 00100010 */
            *FLAG1 = 1;
            *FLAG2 = 0;
            *FLAG3 = 1;
            *FLAG4 = 1;
            break;
        case 'E': /* 10100010 */
            *FLAG1 = 0;
            *FLAG2 = 1;
            *FLAG3 = 1;
            *FLAG4 = 1;
            break;
        case 'F': /* 01100010 */
            *FLAG1 = 1;
            *FLAG2 = 1;
            *FLAG3 = 1;
            *FLAG4 = 1;
            break;
        default: /* 0000110 or other */
            *FLAG1 = 0;
            if(FLAG2 != NULL)
                *FLAG2 = 0;
            if(FLAG3 != NULL)
                *FLAG3 = 0;
            if(FLAG4 != NULL)
                *FLAG4 = 0;
            break;
    }

    return 0;
}

int read_bsf(char *bsf)	{
    FILE *fp;
    typebsf bs;

    fp = fopen(bsf, "r");
    if(!fp)
        return -1;

    fread(bs.hardware_id, sizeof(bs.hardware_id) - 1, 1, fp);
    fread(bs.maker_id, sizeof(bs.maker_id) - 1, 1, fp);
    fread(bs.checksum, sizeof(bs.checksum) - 1, 1, fp);
    fseek(fp, 1, SEEK_CUR);
    fread(bs.disc_info, sizeof(bs.disc_info) - 1, 1, fp);
    fread(bs.area_symbols, sizeof(bs.area_symbols) - 1, 1, fp);
    fseek(fp, 5, SEEK_CUR);
    fread(bs.peripherals, sizeof(bs.peripherals) - 1, 1, fp);
    read_bsf_peripheral(bs.peripherals[0], &bs.expand_analog_vert,
          &bs.keyboard, &bs.gun, &bs.mouse);
    read_bsf_peripheral(bs.peripherals[1], &bs.analog_l_trigger,
          &bs.analog_vert_controller, &bs.analog_hor_controller,
          &bs.expand_analog_hor);
    read_bsf_peripheral(bs.peripherals[2], &bs.y_button,
          &bs.expand_dir_buttons, &bs.z_button, &bs.analog_r_trigger);
    read_bsf_peripheral(bs.peripherals[3], &bs.start_abdir_buttons,
          &bs.d_button, &bs.c_button, &bs.x_button);
    read_bsf_peripheral(bs.peripherals[4], &bs.other, &bs.microphone_card,
          &bs.purupuru_card, &bs.memory_card);
    read_bsf_peripheral(bs.peripherals[5], &bs.vga_box, NULL, NULL, NULL);
    read_bsf_peripheral(bs.peripherals[6], &bs.windowsce, NULL, NULL, NULL);
    fseek(fp, 1, SEEK_CUR);
    fread(bs.product_id, sizeof(bs.product_id) - 1, 1, fp);
    fseek(fp, 1, SEEK_CUR);
    fread(bs.product_version, sizeof(bs.product_version) - 1, 1, fp);
    fread(bs.release_date, sizeof(bs.release_date) - 1, 1, fp);
    fseek(fp, 8, SEEK_CUR);
    fread(bs.boot_filname, sizeof(bs.boot_filname) - 1, 1, fp);
    fread(bs.company_name, sizeof(bs.company_name) - 1, 1, fp);
    fread(bs.software_name, sizeof(bs.software_name) - 1, 1, fp);
    fseek(fp, 8556, SEEK_CUR);
    fread(bs.mr_trademark, sizeof(bs.mr_trademark), 1, fp);
    fread(bs.mr_sega, sizeof(bs.mr_sega), 1, fp);
    fseek(fp, 946, SEEK_CUR);
    fread(bs.mr_user, sizeof(bs.mr_user), 1, fp);

    fclose(fp);

    return 0;
}
