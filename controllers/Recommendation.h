#ifndef RECOMMENDATION_H_
#define RECOMMENDATION_H_

#include "../models/Graph.h"
#include <iostream>
#include <vector>

class Recommendation {
public:
    Recommendation();
    ~Recommendation();
    void on_add_film();
    void on_buy_film(int film_id);
    bool is_deleted_film(int film_id);
    void on_delete_film(int film_id);
    std::vector<int> get_films(int film_id);

private:
    Graph *films_graph;
    std::vector<int> deleted_films_id;
};

#endif