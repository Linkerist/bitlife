
#include "format.h"

#include <stdio.h>

/*
 * list the directories name, relative or full
 */
void dir_list(char *str)
{
	for(; *str; str++) {
		c = (unsigned char)*str;
		/* is there ESC characters in path ? */
		if(ASCII_ESC_START <= c && c <= ASCII_ESC_END || '\\' == c || ' ' == c)
			putc('\\', file_log);
	}
}
