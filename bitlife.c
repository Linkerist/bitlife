
#include "bitlife.h"
#include <stdio.h>

/*
 * synchronize directories skeleton only
 */
int dflag, sflag, hflag;

/* the probable log file */
char *filename_log = NULL;
FILE *file_log;

/*
 * list the directories name, relative or full
 */
void dir_list(char *str)
{
	for(; *str; str++) {
		c = (unsigned char)*str;
		if(ASCII_ESC_START <= c && c <= ASCII_ESC_END || '\\' == c || ' ' == c) {
			putc('\\', file_log);
		}
	}
}

/* start synchronize directories */
start_bitlife(char **dirname, int *dtotal, int *ftotal)
{
	int i, j;
	if(dirname) {
		for(i = 0; dirname[i]; i++) {
			/* eat the '/' in the tail */
			j = strlen(dirname[i]);
			while(0 < j && '/' == dirname[i][--j])
				;
			dirname[i][j + 1] = '\0';
			dir_list(dirname[i]);
		}
	} else {
		fprintf(file_log, DEFAULT_DIR_SRC);
		//dir_parse_top(DEFAULT_DIR_SRC, )
	}
}

/*
 * initialize some global variables
 * use default their value
 */
void initialize(void)
{
	/*
	 * default synchronize options
	 * synchronize files and directories
	 * do not list file size, event it be a human way
	 */
	dflag = sflag = hflag = FALSE;
	dir_level_max = DIR_LEVEL_MAX;
}

void parse_args(int argc, char **argv, char ***dirname)
{
	int i = 0;
	for(i = 0;i < argc; i++) {
		if('-' == argv[i][0] && argv[i][1]) {
			switch(argv[i][1]) {
			case 'd':
				dflag = TRUE;
				break;
			case 's':
				sflag = TRUE;
				break;
			case 'h':
				hflag = TRUE;
				break;
			default:
				break;
			}
		}
	}
}

/*
 * open a probable log file
 */
void log_open(char *filename)
{
	if(NULL == filename)
		file_log = stdout;
	else {
		if(NULL == (file_log = fopen(filename, "w"))) {
			fprintf(stderr, "invalid filename, log to stdout as default\n");
			file_log = stdout;
		}
	}
}

/*
 * close a probable log file
 */
void log_close(char *filename)
{
	if(NULL != filename)
		fclose(file_log);
}

void statistics(int dtotal, int ftotal)
{
	if(dflag)
		fprintf(file_log, "%d director%s synchronized .\n\n", dtotal, 1 == dtotal ? "y" : "ies");
	else
		fprintf(file_log, "%d director%s, %d file%s synchronized .\n\n",
				dtotal, 1 == dtotal ? "y" : "ies", ftotal, 1 == ftotal ? "" : "s");
}

int main(int argc, char **argv)
{
	char **dirname = NULL;
	
	int dtotal, ftotal;
	dtotal = ftotal = 0;

	initialize();

	parse_args(argc, argv, &dirname);

	log_open(filename_log);

	start_bitlife(dirname, &dtotal, &ftotal);

	statistics(dtotal, ftotal);

	log_close(filename_log);

	return 0;
}
