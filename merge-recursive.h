#ifndef MERGE_RECURSIVE_H
#define MERGE_RECURSIVE_H

#include "string-list.h"

struct merge_options {
	const char *branch1;
	const char *branch2;
	unsigned subtree_merge : 1;
	unsigned buffer_output : 1;
	int verbosity;
	int diff_rename_limit;
	int merge_rename_limit;
	int call_depth;
	struct strbuf obuf;
	struct string_list current_file_set;
	struct string_list current_directory_set;
};

/* merge_trees() but with recursive ancestor consolidation */
int merge_recursive(struct merge_options *o,
		    struct commit *h1,
		    struct commit *h2,
		    struct commit_list *ancestors,
		    struct commit **result);

/* rename-detecting three-way merge, no recursion */
int merge_trees(struct merge_options *o,
		struct tree *head,
		struct tree *merge,
		struct tree *common,
		struct tree **result);

/*
 * "git-merge-recursive" can be fed trees; wrap them into
 * virtual commits and call merge_recursive() proper.
 */
int merge_recursive_generic(struct merge_options *o,
			    const unsigned char *head,
			    const unsigned char *merge,
			    int num_ca,
			    const unsigned char **ca,
			    struct commit **result);

void init_merge_options(struct merge_options *o);
struct tree *write_tree_from_memory(struct merge_options *o);

#endif
