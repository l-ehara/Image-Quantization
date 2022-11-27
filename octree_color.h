#ifndef __OCTREE__
#define __OCTREE__

#include <stdlib.h>
#include <stdio.h>
#include "opengl.h"

typedef struct octree
{
    RGB8 *color;
    int count, heap_idx;
    struct octree *children[8];
    unsigned char n_kids, kid_idx, flags, depth;
} Octree;


Octree *construct();
Octree *construct2(unsigned char r_min, unsigned char g_min, unsigned char b_min,
                  unsigned char r_max, unsigned char g_max, unsigned char b_max);
                  
void insert(Octree *octree, RGB8 *color);
bool inBoundary(RGB8 min, RGB8 max, RGB8 *color);
void dfs(Octree *octree);
void free_octree(Octree *octree);


#endif // OCTREE
