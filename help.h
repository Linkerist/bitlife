
#ifndef __HELP_H__
#define __HELP_H__

enum feature_titles_idx {
	TITLE_SYNC = 0,
	TITLE_OUTLOOK,
	TITLE_MISC,
};

/* some features index of bitlife */
enum features_idx {
	FEATURE_START = 0,
	
	FEATURE_DIR_ONLY,
	FEATURE_PATT_MATCH,
	FEATURE_PATT_MISMATCH,
	FEATURE_ASSIGN_LEVEL,
	
	FEATURE_SYNC_END,
	
	FEATURE_LIST_PROT,
	FEATURE_LIST_BSIZE,
	FEATURE_LIST_KSIZE,
	FEATURE_LIST_FULL,
	FEATURE_OUT_FILE,
	FEATURE_LIST_END,
	
	FEATURE_VERSION,
	FEATURE_HELP,
	
	FEATURE_END,
};

typedef enum {
	CMD_ERR = 0,
	CMD_HELP,
}usage_opt;

enum features_internal {
	FEATURE_DESC = 0,
	FEATURE_GAP,
	FEATURE_CMD,
};

void version(void);
void usage(usage_opt opt);

#endif
