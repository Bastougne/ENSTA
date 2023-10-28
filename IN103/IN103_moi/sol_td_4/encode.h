#ifndef __ENCODE_H__
#define __ENCODE_H__
#include <stdbool.h>
#include "hufftree.h"

int* nb_occurence(char *fname) ;

struct huff_node_t* build_tree(char *fname) ;

bool encode(char* src, char* dest, char** codes) ;

#endif
