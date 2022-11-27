#include <stdlib.h>
#include <stdio.h>
// #include "opengl.h"
#include "octree.h"

// Implementation of Octree in C

Octree *construct()
{
    Octree *octree = malloc(sizeof(Octree));
    octree->color = NULL;
    // Min Bound
    octree->min.r = 0;
    octree->min.g = 0;
    octree->min.b = 0;
    // Max Bound
    octree->max.r = 255;
    octree->max.g = 255;
    octree->max.b = 255;
    // Set root children to NULL
    for (int i = 0; i < 8; i++)
    {
        octree->children[i] = NULL;
    }
    return octree;
}

Octree *construct2(unsigned char r_min, unsigned char g_min, unsigned char b_min,
                   unsigned char r_max, unsigned char g_max, unsigned char b_max)
{
    Octree *octree = malloc(sizeof(Octree));
    octree->color = NULL;
    // Min Bound
    octree->min.r = r_min;
    octree->min.g = g_min;
    octree->min.b = b_min;
    // Max Bound
    octree->max.r = r_max;
    octree->max.g = g_max;
    octree->max.b = b_max;
    // Set root children to NULL
    for (int i = 0; i < 8; i++)
    {
        octree->children[i] = NULL;
    }
    return octree;
}

bool inBoundary(RGB8 current_min, RGB8 current_max, RGB8 *color)
{
    // printf("In Boundary\n");
    return (color->r >= current_min.r && color->g >= current_min.g && color->b >= current_min.b &&
            color->r <= current_max.r && color->g <= current_max.g && color->b <= current_max.b);
}

void insert(Octree *octree, RGB8 *color)
{
    // if (octree == NULL)
    //     printf("NULL\n");
    // return;

    // Current Limits of the cube
    RGB8 current_min = octree->min;
    RGB8 current_max = octree->max;

    if (!inBoundary(current_min, current_max, color))
    {
        printf("color: (%x%x%x)\n", color->r, color->g, color->b);
        printf("Does't Fit Anymore\n");
        octree->color = color;
        colors++;
        return;
    }


    // TOP LEFT FRONT
    if (color->r >= current_max.r / 2 && color->g >= current_min.g && color->b >= current_min.b &&
        color->r <= current_max.r && color->g <= current_max.g / 2 && color->b <= current_max.b / 2)
    {
        printf("TLF\n");
        if (octree->children[TopLeftFront] == NULL)
        {
            // Allocate memory for new octree
            Octree *topLeftFront = construct2(current_max.r / 2, current_min.g, current_min.b,
                                              current_max.r, current_max.g / 2, current_max.b / 2);
            size++;
            octree->children[TopLeftFront] = topLeftFront;
            // Keep dividing
            insert(topLeftFront, color);
        }
    }
    else
    {
        // TOP RIGHT FRONT
        if (color->r >= current_max.r / 2 && color->g >= current_min.g && color->b >= current_max.b / 2 &&
            color->r <= current_max.r && color->g <= current_max.g / 2 && color->b <= current_max.b)
        {
            printf("TRF\n");
            if (octree->children[TopRightFront] == NULL)
            {
                // Allocate memory for new octree
                Octree *topRightFront = construct2(current_max.r / 2, current_min.g, current_max.b,
                                                   current_max.r, current_max.g / 2, current_max.b);
                size++;
                octree->children[TopRightFront] = topRightFront;
                // Keep dividing
                insert(topRightFront, color);
            }
        }
        else
        {
            // BOTTOM LEFT FRONT
            if (color->r >= current_min.r && color->g >= current_min.g && color->b >= current_min.b &&
                color->r <= current_max.r / 2 && color->g <= current_max.g / 2 && color->b <= current_max.b / 2)
            {
                printf("BLF\n");
                if (octree->children[BottomLeftFront] == NULL)
                {
                    // Allocate memory for new octree
                    Octree *bottomLeftFront = construct2(current_min.r, current_min.g, current_min.b,
                                                         current_max.r / 2, current_max.g / 2, current_max.b / 2);
                    size++;
                    octree->children[BottomLeftFront] = bottomLeftFront;
                    // Keep dividing
                    insert(bottomLeftFront, color);
                }
            }
            else
            {
                // BOTTOM RIGHT FRONT
                if (color->r >= current_min.r && color->g >= current_min.g && color->b >= current_max.b / 2 &&
                    color->r <= current_max.r / 2 && color->g <= current_max.g / 2 && color->b <= current_max.b)
                {
                    printf("BRF\n");
                    if (octree->children[BottomRightFront] == NULL)
                    {
                        // Allocate memory for new octree
                        Octree *bottomRightFront = construct2(current_min.r, current_min.g, current_max.b / 2,
                                                              current_max.r / 2, current_max.g / 2, current_max.b);
                        size++;
                        octree->children[BottomRightFront] = bottomRightFront;
                        // Keep dividing
                        insert(bottomRightFront, color);
                    }
                }
                else
                {
                    // TOP LEFT BACK
                    if (color->r >= current_max.r / 2 && color->g >= current_max.g / 2 && color->b >= current_min.b &&
                        color->r <= current_max.r && color->g <= current_max.g && color->b <= current_max.b / 2)
                    {
                        printf("TLB\n");
                        if (octree->children[TopLeftBack] == NULL)
                        {
                            // Allocate memory for new octree
                            Octree *topLeftBack = construct2(current_max.r / 2, current_max.g / 2, current_min.b,
                                                             current_max.r, current_max.g, current_max.b / 2);
                            size++;
                            octree->children[TopLeftBack] = topLeftBack;
                            // Keep dividing
                            insert(topLeftBack, color);
                        }
                    }
                    else
                    {
                        // TOP RIGHT BACK
                        printf("TRB");
                        if (color->r >= current_max.r / 2 && color->g >= current_max.g / 2 && color->b >= current_max.b / 2 &&
                            color->r <= current_max.r && color->g <= current_max.g && color->b <= current_max.b)
                        {
                            // printf("TRB\n");
                            // printf("WHITE ");
                            if (octree->children[TopRightBack] == NULL)
                            {
                                // printf("TRB ");
                                // Allocate memory for new octree
                                Octree *topRightBack = construct2(current_max.r / 2, current_max.g / 2, current_max.b / 2,
                                                                  current_max.r, current_max.g, current_max.b);
                                size++;
                                octree->children[TopRightBack] = topRightBack;
                                // Keep dividing
                                insert(topRightBack, color);
                            }
                        }
                        else
                        {
                            // BOTTOM LEFT BACK
                            if (color->r >= current_min.r && color->g >= current_max.g / 2 && color->b >= current_min.b &&
                                color->r <= current_max.r / 2 && color->g <= current_max.g && color->b <= current_max.b / 2)
                            {
                                printf("BLB\n");
                                if (octree->children[BottomLeftBack] == NULL)
                                {
                                    // Allocate memory for new octree
                                    Octree *bottomLeftBack = construct2(current_min.r, current_max.g / 2, current_min.b,
                                                                        current_max.r / 2, current_max.g, current_max.b / 2);
                                    size++;
                                    octree->children[BottomLeftBack] = bottomLeftBack;
                                    // Keep dividing
                                    insert(bottomLeftBack, color);
                                }
                            }
                            else
                            {
                                // BOTTOM RIGHT BACK
                                if (color->r >= current_min.r && color->g >= current_max.g / 2 && color->b >= current_max.b / 2 &&
                                    color->r <= current_max.r / 2 && color->g <= current_max.g && color->b <= current_max.b)
                                {
                                    printf("BRB\n");
                                    if (octree->children[BottomRightBack] == NULL)
                                    {
                                        // Allocate memory for new octree
                                        Octree *bottomRightBack = construct2(current_min.r, current_max.g / 2, current_max.b / 2,
                                                                             current_max.r / 2, current_max.g, current_max.b);
                                        size++;
                                        octree->children[BottomRightBack] = bottomRightBack;
                                        // Keep dividing
                                        insert(bottomRightBack, color);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void dfs(Octree *octree)
{
    // if (octree->color != NULL)
    // {
    //     printf("data: (%x%x%x)\n", octree->color->r, octree->color->g, octree->color->b);
    // }
    if (octree == NULL)
    {
        // printf("NULL\n");
        return;
    }
    else
    {
        dfs(octree->children[0]);
        dfs(octree->children[1]);
        dfs(octree->children[2]);
        dfs(octree->children[3]);
        dfs(octree->children[4]);
        dfs(octree->children[5]);
        dfs(octree->children[6]);
        dfs(octree->children[7]);
        if (octree->color != NULL)
        {
            leaves_count++;
        }
    }
}

void free_octree(Octree *octree)
{
    if (octree == NULL)
    {
        // printf("NULL\n");
        return;
    }
    else
    {
        free_octree(octree->children[0]);
        free_octree(octree->children[1]);
        free_octree(octree->children[2]);
        free_octree(octree->children[3]);
        free_octree(octree->children[4]);
        free_octree(octree->children[5]);
        free_octree(octree->children[6]);
        free_octree(octree->children[7]);
    }
    free(octree);
}

int main()
{
    // Create a new octree with three generations
    Octree *octree = construct();
    printf("CREATED\n");

    RGB8 *color1 = malloc(sizeof(RGB8));
    color1->r = 255;
    color1->g = 255;
    color1->b = 255;

    // printf("color1: RGB (#%x%x%x)\n", color1->r, color1->g, color1->b);

    insert(octree, color1);
    printf("INSERTED\n");

    dfs(octree);

    // Octree info
    printf("Octree --------------------------\n");
    printf("Size: %d\n", size);
    printf("Leaves: %d\n", leaves_count);

    // Free memory
    free_octree(octree);
    free(color1);
    printf("Freed");

    // return 0;
}