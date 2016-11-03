
#ifndef __BITLIFE_H_
#define __BITLIFE_H_

#define DEFAULT_DIR_SRC "."
#define DEFAULT_DIR_DST "."

#define DIR_LEVEL_MAX 4096

typedef enum {
	FALSE = 0,
	TRUE,
} bool;

void initialize(void);

void parse_args(int argc, char **argv, char ***dirname);

void log_open(char *filename);

void start_bitlife(char *dirname, int *pdtotal, int *pftotal);

void statistics(int dtotal, int ftotal);

void log_close(char *filename);

#endif

