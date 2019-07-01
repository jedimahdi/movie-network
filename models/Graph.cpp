#include "Graph.h"

Graph::Graph(int _rows) {
    rows = _rows;
    adj = new int *[rows];
    for (int i = 0; i < rows; i++) {
        adj[i] = new int[rows];
        for (int j = 0; j < rows; j++) {
            adj[i][j] = 0;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < rows; i++) {
        delete[] adj[i];
    }
    delete[] adj;
}

void Graph::add_edge(int u, int v) {
    if (u != v) {
        adj[u][v]++;
        adj[v][u]++;
    }
}

void Graph::fill_with_graph(Graph *graph) {
    if (graph->rows <= this->rows) {
        for (int i = 0; i < graph->rows; i++) {
            for (int j = 0; j < graph->rows; j++) {
                this->adj[i][j] = graph->adj[i][j];
            }
        }
    }
}

int Graph::get_size() {
    return rows;
}

std::vector<int> Graph::get_row(int row_id) {
    std::vector<int> weights;
    for (int i = 0; i < rows; i++) {
        weights.push_back(adj[row_id][i]);
    }

    return weights;
}

void Graph::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            std::cout << (adj[i][j] < 10 ? "0" : "") << adj[i][j] << " ";
        }
        std::cout << std::endl;
    }
}