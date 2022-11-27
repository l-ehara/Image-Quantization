#ifndef __OCTREE__
#define __OCTREE__

#include <stdlib.h>
#include <stdio.h>
#include "opengl.h"

// Implementation of Octree in c
#define TopLeftFront 0
#define TopRightFront 1
#define BottomRightFront 2
#define BottomLeftFront 3
#define TopLeftBack 4
#define TopRightBack 5
#define BottomRightBack 6
#define BottomLeftBack 7

#define bool int

const RGB8 MIN;
unsigned int size = 0;
unsigned int colors = 0;
unsigned int leaves_count = 0;

typedef struct octree
{
    RGB8 min;
    RGB8 max;
    RGB8 *color;
    struct octree *children[8];
} Octree;


Octree *construct();
Octree *construct2(unsigned char r_min, unsigned char g_min, unsigned char b_min,
                  unsigned char r_max, unsigned char g_max, unsigned char b_max);
                  
void insert(Octree *octree, RGB8 *color);
bool inBoundary(RGB8 min, RGB8 max, RGB8 *color);
void dfs(Octree *octree);
void free_octree(Octree *octree);


#endif // OCTREE
