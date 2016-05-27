
#include "bitlife.h"
#include "xmalloc.h"
#include "hash.h"
#include <stdio.h>
#include <locale.h>

/*
 * dflag - synchronize directories skeleton only
 * fflag - list full path
 * pflag - list permission
 * sflag - list object size
 * hflag - list object size in human way
 */
int dflag, fflag, pflag, sflag, hflag;

/* the probable log file */
char *filename_log = NULL;
FILE *file_log;

/* dir_ops.c : listing when synchronize */
extern int level, *dirs, dir_level_max;

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
	 * do not list full path
	 * do not list permission
	 * do not list file size, event it be a human way
	 */
	dflag = fflag = pflag = sflag = hflag = FALSE;
	dir_level_max = DIR_LEVEL_MAX;
	int alloc_size = dir_level_max * sizeof(int);
	dirs = xmalloc(alloc_size);
	memset(dirs, 0, alloc_size);
	
	dirs[0] = 0;
	level = -1;
	
	/* set locale here */
	setlocale(LC_CTYPE, "");
	setlocale(LC_COLLATE, "");
	
	/* initialize several hashtable */
	memset(utable, 0, sizeof(utable));
	memset(gtable, 0, sizeof(gtable));
}

void parse_args(int argc, char **argv, char ***dirname)
{
	int i, j = 0;
	for(n = i = 1; i < argc; i = n) {
		n++;
		if('-' == argv[i][0] && argv[i][1]) {
			switch(argv[i][1]) {
			case 'd':
				dflag = TRUE;
				break;
			case 'f':
				fflag = TRUE;
				break;
			case 'p':
				fflag = TRUE;
				break;
			case 's':
				sflag = TRUE;
				break;
			case 'h':
				hflag = TRUE;
				sflag = TRUE;
				break;
			default:
				fprintf(stderr, "bitlife : Invalid argument - `c' .\n", argv[i][j])
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
