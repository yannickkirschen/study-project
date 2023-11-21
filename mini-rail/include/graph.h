#ifndef GRAPH_H
#define GRAPH_H

#include "stb_ds_helper.h"

typedef struct {
    int key;
    void *value;
} graph_vertex_t;

typedef struct {
    graph_vertex_t *adjacency_list;
} graph_t;

void graph_init(graph_t *graph);
void graph_print(graph_t *graph);
bool graph_edge_contains(graph_vertex_t *vertices, graph_vertex_t vertex);
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

#ifdef GRAPH_IMPLEMENTATION

void graph_init(graph_t *graph) {
    graph->adjacency_list = NULL;
}

void graph_print(graph_t *graph) {
    printf("graph_t{adjacency_list=[\n");
    for (int i = 0; i < hmlen(graph->adjacency_list); i++) {
        graph_vertex_t *vertex = &graph->adjacency_list[i];
        printf("    %d: [", vertex->key);

        graph_vertex_t *vertices = vertex->value;
        for (int j = 0; j < arrlen(vertices); j++) {
            graph_vertex_t *value = &vertices[j];
            printf("%d", value->key);

            if (j < arrlen(vertices) - 1) {
                printf(", ");
            }
        }

        printf("]");
        if (i < hmlen(graph->adjacency_list) - 1) {
            printf(",\n");
        }
    }
    printf("\n}\n");
}

bool graph_edge_contains(graph_vertex_t *vertices, graph_vertex_t vertex) {
    for (int i = 0; i < arrlen(vertices); i++) {
        if (vertices[i].key == vertex.key) {
            return true;
        }
    }

    return false;
}

void graph_vertex_add(graph_t *graph, graph_vertex_t *vertex) {
    graph_vertex_t *vertices = hmget(graph->adjacency_list, vertex->key);
    if (vertices == NULL) {
        hmput(graph->adjacency_list, vertex->key, NULL);
    }
}

void graph_edge_add(graph_t *graph, graph_vertex_t *vertex1, graph_vertex_t *vertex2) {
    graph_vertex_t **vertices1 = (graph_vertex_t **)&hmget(graph->adjacency_list, vertex1->key);
    graph_vertex_t v1 = {.key = vertex2->key, .value = (void *)vertex2};

    if (!graph_edge_contains(*vertices1, v1)) {
        arrput(*vertices1, v1);
    }

    graph_vertex_t **vertices2 = (graph_vertex_t **)&hmget(graph->adjacency_list, vertex2->key);
    graph_vertex_t v2 = {.key = vertex1->key, .value = (void *)vertex1};

    if (!graph_edge_contains(*vertices2, v2)) {
        arrput(*vertices2, v2);
    }
}

int **graph_find_paths(graph_t *graph, int from, int to) {
    depth_first_search_t *dfs = malloc(sizeof(depth_first_search_t));
    depth_first_search_init(dfs, graph);
    depth_first_search(dfs, from, to);
    return dfs->paths;
}

void depth_first_search_init(depth_first_search_t *search, graph_t *graph) {
    search->graph = graph;

    search->visited = NULL;
    search->current_path = NULL;
    search->paths = NULL;
}

void depth_first_search(depth_first_search_t *dfs, int from, int to) {
    if (stb_ds_array_contains(dfs->visited, from)) {
        return;
    }

    arrput(dfs->visited, from);
    arrput(dfs->current_path, from);

    if (from == to) {
        int *current_path = stb_ds_array_copy(dfs->current_path);
        arrput(dfs->paths, current_path);

        stb_ds_array_remove(&dfs->visited, from);
        stb_ds_array_remove_last(&dfs->current_path);
        return;
    }

    graph_vertex_t *vertices = hmget(dfs->graph->adjacency_list, from);
    if (vertices != NULL) {
        for (int i = 0; i < arrlen(vertices); i++) {
            depth_first_search(dfs, (&vertices[i])->key, to);
        }
    }

    stb_ds_array_remove_last(&dfs->current_path);
    stb_ds_array_remove(&dfs->visited, from);
}

#endif  // GRAPH_IMPLEMENTATION

#endif  // GRAPH_H
