
#include "help.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ver = "bitlife v0.0.1";

const char *feature_titles[] = {
	"---- Synchronize relevant ----",
	"---- Outlook relevant ----",
	"---- Miscellaneous relevant ----",
};

const char *features[][3] = {
	{"", "", ""},
	
	{"Synchronize directories skeleton only.", "\t\t\t", "-d"},
	{"Synchronize those files that match the pattern given only.", "\t\t", "-P pattern"},
	
	{"Synchronize skip files that match the pattern given only.", "\t\t", "-I xpattern"},
	{"Synchronize descend level directories deep", "\t\t", "-L level"},
	{"", "", ""},
	
	{"List the protection.", "\t\t\t", "-p"},
	{"List the size in bytes.", "\t\t\t", "-s"},
	{"List the size in human way.", "\t\t\t", "-h"},
	{"List the full path for each file.", "\t\t\t", "-f"},
	{"Log to file instead of stdout.", "\t\t\t", "-o"},
	{"", "", ""},
	
	{"Print version and exit.", "\t\t\t", "-V"},
	{"Print usage and help message and exit.", "\t\t\t", "-H"},
	
	{"", "", ""},
};

void version(void)
{
	fprintf(stderr, "%.*s\n\n", (int)strlen(ver), ver);
	exit(0);
}

/*
 * CMD_ERR for help when command error
 * CMD_HELP for ordinary info
 */
void usage(usage_opt opt)
{
	int i;
	
	/* abstract usage */
	fprintf(stderr, "usage : ");
	for(i = FEATURE_START + 1; i < FEATURE_END; i++)
		fprintf(stderr, "[%s] ", features[i][FEATURE_CMD]);
	fprintf(stderr, "\n");
	
	if(CMD_ERR == opt)
		exit(0);

	/* synchronize relevant command */
	fprintf(stderr, "\n%s\n", feature_titles[TITLE_SYNC]);
	for(i = FEATURE_START + 1; i < FEATURE_SYNC_END; i++)
		fprintf(stderr, "\n%s%s%s\n", features[i][FEATURE_CMD], features[i][FEATURE_GAP], features[i][FEATURE_DESC]);
	fprintf(stderr, "\n");
	
	/* outlook relevant command */
	fprintf(stderr, "\n%s\n", feature_titles[TITLE_OUTLOOK]);
	for(i = FEATURE_SYNC_END + 1; i < FEATURE_LIST_END; i++)
		fprintf(stderr, "\n%s%s%s\n", features[i][FEATURE_CMD], features[i][FEATURE_GAP], features[i][FEATURE_DESC]);
	fprintf(stderr, "\n");
	
	/* miscellaneous command */
	fprintf(stderr, "\n%s\n", feature_titles[TITLE_MISC]);
	for(i = FEATURE_LIST_END + 1; i < FEATURE_END; i++)
		fprintf(stderr, "\n%s%s%s\n", features[i][FEATURE_CMD], features[i][FEATURE_GAP], features[i][FEATURE_DESC]);
	fprintf(stderr, "\n");
	
	exit(0);
}

