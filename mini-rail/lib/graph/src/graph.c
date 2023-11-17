#include "graph.h"

#include <stdlib.h>

void graph_init(graph_t *graph) {
    graph->vertices = NULL;
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
    hmput(graph->vertices, vertex->key, vertex);

    graph_vertex_t *vertices = hmget(graph->adjacency_list, vertex->key);
    if (vertices == NULL) {
        hmput(graph->adjacency_list, vertex->key, NULL);
    }
}

void graph_edge_add(graph_t *graph, graph_vertex_t *vertex1, graph_vertex_t *vertex2) {
    graph_vertex_t **vertices1 = (graph_vertex_t **)&hmget(graph->adjacency_list, vertex1->key);
    graph_vertex_t v1 = {.key = vertex2->key, .value = (void *)vertex2};
    arrput(*vertices1, v1);

    graph_vertex_t **vertices2 = (graph_vertex_t **)&hmget(graph->adjacency_list, vertex2->key);
    graph_vertex_t v2 = {.key = vertex1->key, .value = (void *)vertex1};
    arrput(*vertices2, v2);
}

int **graph_find_paths(graph_t *graph, int from, int to) {
    depth_first_search_t *dfs = malloc(sizeof(depth_first_search_t));
    depth_first_search_init(dfs, graph);
    depth_first_search(dfs, from, to);
    return dfs->paths;
}
