#ifndef QUADTREE
#define QUADTREE

#include <stdbool.h>
#include <stdlib.h>

typedef enum direction{
    NW, NE, SW, SE
}direction;

typedef struct{
    float x;
    float y;
    void *data;
}QTNode;

typedef struct Quadtree{
    float mx; // midpoint
    float my; // midpoint
    float width;
    float height;

    /*
     * Quadtree is a recursive structure. It will either contain data (in which case
     * it is essentially a leaf node, or will have quadtree children under. The idea
     * is: on the first insertion of data into the qtree, it will be pointed to by
     * the data pointer. However, if we need to insert additional data under this tree
     * we will first relocate what is in data to one of the quadtree subs (nw, ne, etc.)
     * and then go about inserting the new data accordingly.
     */

    bool is_leaf;
    QTNode *data;
    struct Quadtree *nw;
    struct Quadtree *ne;
    struct Quadtree *sw;
    struct Quadtree *se;

}Quadtree;

typedef struct QTNodePointer{
    QTNode *node;
    struct QTNodePointer *next;
};

typedef struct QTNode_vector{
    QTNode * node;
    size_t capacity;
    size_t number_of_nodes;
} QTNode_vector;


QTNode *create_qtnode(float x, float y, void *data);

Quadtree *create_quadtree(float mx, float my, float w, float h, void *data);
void insert_node(Quadtree *quadtree, QTNode *node);
QTNode_vector get_nodes_in_distance(Quadtree quadtree, float distance);
direction get_quadrant(Quadtree *quad, QTNode *node);




#endif