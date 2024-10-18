#include <stdio.h>

#include "quadtree.h"

int main(void) {
    Quadtree *tree = create_quadtree(400, 400, 800, 800, NULL);
    QTNode *node1 =  create_qtnode(200, 200, "test");
    QTNode *node2 =  create_qtnode(600, 200, "test2");
    QTNode *node3 =  create_qtnode(200, 600, "test3");
    QTNode *node4 =  create_qtnode(600, 600, "test4");


    QTNode *node5 =  create_qtnode(240, 190, "test1a");

    insert_node(tree, node1);
    insert_node(tree, node2);
    insert_node(tree, node3);
    insert_node(tree, node4);
    insert_node(tree, node5);
    printf("Done");


    return 0;
}
