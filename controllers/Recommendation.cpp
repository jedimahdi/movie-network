#include "Recommendation.h"
#include <algorithm>

using namespace std;

Recommendation::Recommendation() {
    films_graph = new Graph(0);
}

Recommendation::~Recommendation() {
    delete films_graph;
}

void Recommendation::on_add_film() {
    Graph *g = new Graph(films_graph->get_size() + 1);
    g->fill_with_graph(films_graph);
    delete films_graph;
    films_graph = g;
}

void Recommendation::on_buy_film(int film_id) {
    for (int i = 0; i < films_graph->get_size(); i++) {
        films_graph->add_edge(film_id - 1, i);
    }
}

int get_max_index(vector<int> array) {
    int max_index = 0;
    for (size_t i = 1; i < array.size(); i++) {
        if (array[i] > array[max_index])
            max_index = i;
    }
    return max_index;
}

bool Recommendation::is_deleted_film(int id) {
    for (size_t i = 0; i < deleted_films_id.size(); i++) {
        if (deleted_films_id[i] == id)
            return true;
    }
    return false;
}

vector<int> Recommendation::get_films(int film_id) {
    vector<int> result;
    vector<int> row = films_graph->get_row(film_id - 1);

    int i = 0, j = 0;
    int max_index;
    while (row.size() - i > 0 && j < 4) {
        max_index = get_max_index(row);
        i++;
        row[max_index] = -1;
        if (is_deleted_film(max_index + 1) || film_id == max_index + 1) {
            continue;
        }
        result.push_back(max_index + 1);
        j++;
    }

    return result;
}
void Recommendation::on_delete_film(int film_id) {
    deleted_films_id.push_back(film_id);
}