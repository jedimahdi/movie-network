#ifndef FILM_CONTROLLER_H_
#define FILM_CONTROLLER_H_

#include "../models/Film.h"
#include <iostream>
#include <vector>

class FilmController {
public:
    FilmController();
    ~FilmController();
    Film *get_film(int id);
    void create_film(int user_id, std::string name, int year, int length, int price,
                     std::string summary, std::string director);
    std::vector<Film *> get_all_films(std::string name = "", std::string min_rate = "",
                                      std::string min_year = "", std::string price = "",
                                      std::string max_year = "", std::string director = "");
    std::vector<Film *> get_user_films(int user_id, std::string name = "", std::string min_rate = "",
                                       std::string min_year = "", std::string price = "", std::string max_year = "", std::string director = "");
    std::vector<Film *> get_recommendation_films(int film_id, std::vector<Film *> purchased_films);
    void update_film(int film_id, std::string name, std::string year, std::string length, std::string price,
                     std::string summary, std::string director);
    void delete_film(int film_id, int logged_user_id);
    float get_max_rate(float max_range);

private:
    std::vector<Film *> films;
};

#endif