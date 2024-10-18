#include "quadtree.h"
#include <stdio.h>

QTNode *create_qtnode(float x, float y, void *data){
    QTNode *node = malloc(sizeof(QTNode));
    if (!node) return 0;
    node->x = x;
    node->y = y;
    node->data = data;
    return node;
}

Quadtree *create_quadtree(float mx, float my, float w, float h, void *data){
    Quadtree *quadtree = malloc(sizeof(Quadtree));
    if (!quadtree){
        fprintf(stderr, "Fatal: cannot allocate memory in create_quadtree");
        exit(1);
    }
    quadtree->mx = mx;
    quadtree->my = my;
    quadtree->width = w;
    quadtree->height = h;
    if (data) quadtree->data = data;

    return quadtree;
}

void insert_node(Quadtree *quadtree, QTNode *node){


        if (quadtree->is_leaf && !quadtree->data){
            quadtree->data = node;
            return;
        }

        quadtree->is_leaf = false;
        direction new_node_quadrant = get_quadrant(quadtree, node);
        direction curr_node_direction;
        if (quadtree->data)
            curr_node_direction = get_quadrant(quadtree, quadtree->data);

    switch (new_node_quadrant) {
        case NW:
            if (!quadtree->nw)
                quadtree->nw = create_quadtree(quadtree->mx - quadtree->width/4,
                                               quadtree->my - quadtree->height/4,
                                               quadtree->width / 2,
                                               quadtree->height / 2,
                                               node);
            else
                insert_node(quadtree->nw, node);
            break;
        case NE:
            if (!quadtree->ne)
                quadtree->ne = create_quadtree(quadtree->mx + quadtree->width/4,
                                               quadtree->my - quadtree->height/4,
                                               quadtree->width / 2,
                                               quadtree->height / 2,
                                               node);
            else
                insert_node(quadtree->ne, node);
            break;
        case SW:
            if (!quadtree->sw)
                quadtree->sw = create_quadtree(quadtree->mx - quadtree->width/4,
                                               quadtree->my + quadtree->height/4,
                                               quadtree->width / 2,
                                               quadtree->height / 2,
                                               node);
            else
                insert_node(quadtree->sw, node);
            break;
        case SE:
            if (!quadtree->se)
                quadtree->se = create_quadtree(quadtree->mx + quadtree->width/4,
                                               quadtree->my + quadtree->height/4,
                                               quadtree->width / 2,
                                               quadtree->height / 2,
                                               node);
            else
                insert_node(quadtree->se, node);
            break;
    }

    if (quadtree->data){
        switch (curr_node_direction){
            case NW:
                if (!quadtree->nw)
                    quadtree->nw = create_quadtree(quadtree->mx - quadtree->width/4,
                                                   quadtree->my - quadtree->height/4,
                                                   quadtree->width / 2,
                                                   quadtree->height / 2,
                                                   quadtree->data);
                else
                    insert_node(quadtree->nw, quadtree->data);
                break;
            case NE:
                if (!quadtree->ne)
                    quadtree->ne = create_quadtree(quadtree->mx + quadtree->width/4,
                                                   quadtree->my - quadtree->height/4,
                                                   quadtree->width / 2,
                                                   quadtree->height / 2,
                                                   quadtree->data);
                else
                    insert_node(quadtree->ne, quadtree->data);
                break;
            case SW:
                if (!quadtree->sw)
                    quadtree->sw = create_quadtree(quadtree->mx - quadtree->width/4,
                                                   quadtree->my + quadtree->height/4,
                                                   quadtree->width / 2,
                                                   quadtree->height / 2,
                                                   quadtree->data);
                else
                    insert_node(quadtree->sw, quadtree->data);
                break;
            case SE:
                if (!quadtree->se)
                    quadtree->ne = create_quadtree(quadtree->mx + quadtree->width/4,
                                                   quadtree->my + quadtree->height/4,
                                                   quadtree->width / 2,
                                                   quadtree->height / 2,
                                                   quadtree->data);
                else
                    insert_node(quadtree->se, quadtree->data);
                break;
        }
    }
    quadtree->data = NULL;
}



direction get_quadrant(Quadtree *quadtree, QTNode *node){
    if (node->x <= quadtree->mx && node->y <= quadtree->my) return NW;
    if (node->x >  quadtree->mx && node->y <= quadtree->my) return NE;
    if (node->x <= quadtree->mx && node->y > quadtree->my)  return SW;
    if (node->x > quadtree->mx && node->y > quadtree->my) return SE;
    fprintf(stderr, "Fatal - cannot determine direction");
    exit(1);
}