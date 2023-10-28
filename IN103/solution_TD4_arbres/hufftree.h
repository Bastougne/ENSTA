#ifndef __HUFFTREE_H__
#define __HUFFTREE_H__

struct huff_node_t {
  unsigned char letter ;
  unsigned int nb_occs ;
  struct huff_node_t *left ;
  struct huff_node_t *right ;
};

void free_tree (struct huff_node_t *tree) ;
struct huff_node_t* build_tree (char *fname) ;
#endif
