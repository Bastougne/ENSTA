#ifndef __DECODE_H__
#define __DECODE_H__
#include <stdbool.h>
#include "hufftree.h"

bool decode (char *in_fname, char *out_fname, struct huff_node_t *tree) ;
#endif
