#include <stdio.h>

#include "graph.h"
#include "stb_ds_helper.h"

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
