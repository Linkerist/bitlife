
#include "bitlife.h"
#include "xmalloc.h"
#include "hash.h"
#include "help.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>

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

/* get top directory index and name */
void dir_parse_top(const char *dirname)
{
	char top[DEFAULT_PATH_SIZE];
	char origin[DEFAULT_PATH_SIZE];
	
	top_idx = strlen(dirname) + 1;
	
	/* record original work directory */
	if(NULL == getcwd(origin, DEFAULT_PATH_SIZE)) {
		perror("getcwd()");
		exit(1);
	}
	
	/* get into target directory */
	if(-1 == chdir(dirname)) {
		perror("chdir()");
		exit(1);
	}
	
	/* get absolute path of target directory */
	if(NULL == getcwd(top, DEFAULT_PATH_SIZE)) {
		perror("getcwd()");
		exit(1);
	}
	
	/* once it is root directory */
	if(!strcmp(top, "/")) {
		/* get hostname for this synchronization */
		if(-1 == gethostname(top, DEFAULT_HOSTNAME_SIZE)) {
			fprintf(file_log, "cannot get hostname, / use %s as alias\n", TAG_ROOTFS_ALIAS);
		} else {
			strncat(top, TAG_LINKER, strlen(TRG_LINKER));
			strncat(top, TAG_ROOTFS_ALIAS, strlen(TAG_ROOTFS_ALIAS));
			dir_top = top;
		}
	} else {
		dir_top = strrchr(top, '/');
		dir_top++;
	}
	
	if(-1 == chdir(dirname)) {
		perror("chdir()");
		exit(1);
	}
	printf("fasdfasdfa\n");
	printf("%s - %s\n", dir_top, dir_dst);
	fflush(stdout);
	dir_dst_init();
}

/*
 * start synchronize directories
 * dirname - directories will be synchronize
 */
start_bitlife(char **dirname, int *dtotal, int *ftotal)
{
	int i, j;
	if(dirname) {
		for(i = 0; dirname[i]; i++) {
			if(fflag) {
				/* eat the '/' in the tail */
				j = strlen(dirname[i]);
				while(0 < j && '/' == dirname[i][--j])
					;
				dirname[i][j + 1] = '\0';
			}
			
			dir_list(dirname[i]);
			dir_parse_top(dirname[i]);
			fprintf(file_log, "start synchronize .\n");
			dir_sync_recur(dirname[i], pdtotal, pftotal, 0);
		}
	/* synchronize current directory as default */
	} else {
		fprintf(file_log, DEFAULT_DIR_SRC);
		dir_parse_top(DEFAULT_DIR_SRC);
		dir_sync_recur(DEFAULT_DIR_SRC, pdtotal, pftotal, 0);
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

void dirname_alloc(int p, int q, char ***dirname)
{
	if(!*dirname)
		*dirname = (char **)xmalloc(sizeof(char *) * MEM_INIT);
	else if(q - 2 == p)
		*dirname = (char **)xrealloc(sizeof(char *)(q += MEM_INC_STEP));
}

void parse_args(int argc, char **argv, char ***dirname)
{
	int i, j = 0, n;
	int p = q = 0;
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
				pflag = TRUE;
				break;
			case 'P':
				if(NULL == argv[n]) {
					fprintf(stderr, "bitlife : missing pattern to -P option.\n");
					exit(1);
				}
				pattern = argv[n++];
				break;
			case 'T':
				if(NULL == argv[n]) {
					fprintf(stderr, "bitlife : missing target directory to -T option.\n");
					exit(1);
				}
				dir_dst = argv[n++];
				break;
			case 't':
				if(NULL == argv[n]) {
					fprintf(stderr, "bitlife : missing tag to -t option.\n");
					exit(1);
				}
				sync_tag = argv[n++];
				break;
			case 'X':
				if(NULL == argv[n]) {
					fprintf(stderr, "bitlife : missing pattern to -X option.\n");
					exit(1);
				}
				xpattern = argv[n++];
				break;
			case 'L':
				if(NULL == (levelstr = argv[n++])) {
					fprintf(stderr, "bitlife : missing target directory to -L option.\n");
					exit(1);
				}
				level = strtoul(levelstr, NULL, 0) - 1;
				if(0 > level) {
					fprintf(stderr, "bitlife : Invalid level, must be greater than 0.\n");
					exit(1);
				}
				break;
			case 'o':
				if(NULL == argv[n]) {
					fprintf(stderr, "bitlife : missing filename to -o option.\n");
					exit(1);
				}
				filename_log = argv[n++];
				break;
			case 's':
				sflag = TRUE;
				break;
			case 'h':
				hflag = TRUE;
				sflag = TRUE;
				break;
			case 'H':
				usage(CMD_HELP);
				break;
			case 'V':
				version();
				break;
			default:
				fprintf(stderr, "bitlife : Invalid argument - `c' .\n", argv[i][j]);
				usage(CMD_ERR);
				exit(1);
				break;
			}
		} else {
			dirname_alloc(p, q, dirname);
			(*dirname)[p++] = argv[i];
		}
	}
	if(p)
		(*dirname)[p] = NULL;
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

/* statistics after synchronization */
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
