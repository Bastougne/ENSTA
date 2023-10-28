#ifndef __HUFFTREE_H__
#define __HUFFTREE_H__


struct huff_node_t {
  int data ;
  unsigned char letter ;
  struct huff_node_t* left ; 
  struct huff_node_t* right ;
};

void free_tree(struct huff_node_t* arbre);

#endif