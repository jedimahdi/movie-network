#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>

class Graph {
public:
    Graph(int _rows);
    ~Graph();
    void add_edge(int u, int v);
    void fill_with_graph(Graph *);
    int get_size();
    std::vector<int> get_row(int row_id);
    void print();

private:
    int **adj;
    int rows;
};

#endif