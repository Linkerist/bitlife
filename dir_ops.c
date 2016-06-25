
#include "dir_ops.h"

#include <time.h>

int level, *dirs, dir_level_max;

/* source directory */
char *dir_src;
/* destinate directory */
char *dir_dst = DEFAULT_DIR_DST;

void dir_dst_init(void)
{
	char buf_time[TIME_SIZE];
	time_t cur_time;
	struct tm *tm;
	tm = localtime(&cur_time);
	strftime(buf_time, TIME_SIZE, "%Y-%m-%d-%H-%M", tm);
	dir_dst = strdup(dir_dst);
}
