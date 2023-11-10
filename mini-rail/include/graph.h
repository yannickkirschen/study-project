#ifndef GRAPH_H
#define GRAPH_H

#include "stb_ds_helper.h"

typedef struct {
    int key;
    void *value;
} graph_vertex_t;

typedef struct {
    graph_vertex_t *vertices;
    graph_vertex_t *adjacency_list;
} graph_t;

void graph_init(graph_t *graph);
void graph_vertex_add(graph_t *graph, graph_vertex_t *vertex);
void graph_edge_add(graph_t *graph, graph_vertex_t *vertex1, graph_vertex_t *vertex2);
int **graph_find_paths(graph_t *graph, int from, int to);

typedef struct {
    graph_t *graph;

    int *visited;
    int *current_path;
    int **paths;
} depth_first_search_t;

void depth_first_search_init(depth_first_search_t *search, graph_t *graph);
void depth_first_search(depth_first_search_t *dfs, int from, int to);

#endif  // GRAPH_H
