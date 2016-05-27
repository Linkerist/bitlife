
#include "help.h"

char *ver = "bitlife v0.0.1";

const char *features[][3] = {
	{"", "", ""},
	
	{"Synchronize directories skeleton only.", "\t\t\t", "-d"},
	{"Synchronize those files that match the pattern given only.", "\t\t", "-P pattern"},
	{"Synchronize skip files that match the pattern given only.", "\t\t", "-I xpattern"},
	{"", "", ""},
};

void version(void)
{
	fprintf(stderr, "%.*s\n\n", (int)strlen(ver), ver);
	exit(0);
}

void usage(usage_opt opt)
{
	/* abstract usage */
	fprintf(stderr, "usage : ");
	for(i = FEATURE_START + 1; i < FEATURE_END; i++)
		fprintf(stderr, "[%s] ", features[i][FEATURE_CMD])
	if(CMD_ERR == opt)
		exit(0);
}
