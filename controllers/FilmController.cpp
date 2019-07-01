#include "FilmController.h"
#include "../exceptions/NotFound.h"
#include "../exceptions/PermissionDenied.h"
#include "../models/Film.h"
#include "../models/User.h"
#include "../server/server.hpp"
#include <string>

using namespace std;

FilmController::FilmController() {}

FilmController::~FilmController() {
    for (size_t i = 0; i < films.size(); i++) {
        delete films[i];
    }
    films.clear();
}

Film *FilmController::get_film(int id) {
    for (size_t i = 0; i < films.size(); i++) {
        if (films[i]->get_id() == id) {
            return films[i];
        }
    }
    throw Server::Exception("Film Not Found!");
}

void FilmController::create_film(int user_id, string name, int year,
                                 int length, int price, string summary,
                                 string director) {
    films.push_back(
        new Film(user_id, name, year, length, price, summary, director));
}

vector<Film *> FilmController::get_all_films(string name, string min_rate, string min_year, string price, string max_year, string director) {
    vector<Film *> user_films;
    for (int i = 0; i < films.size(); i++) {
        if (name != "" && films[i]->get_name() != name)
            continue;

        if (min_rate != "" && films[i]->get_rate() < stoi(min_rate))
            continue;

        if (min_year != "" && films[i]->get_year() < stoi(min_year))
            continue;

        if (price != "" && films[i]->get_price() != stoi(price))
            continue;

        if (max_year != "" && films[i]->get_year() > stoi(max_year))
            continue;

        if (director != "" && films[i]->get_director() != director)
            continue;

        user_films.push_back(films[i]);
    }
    return user_films;
}

vector<Film *> FilmController::get_user_films(int user_id, string name, string min_rate, string min_year, string price, string max_year, string director) {
    vector<Film *> user_films;
    for (int i = 0; i < films.size(); i++) {
        if (name != "" && films[i]->get_name() != name)
            continue;

        if (min_rate != "" && films[i]->get_rate() < stoi(min_rate))
            continue;

        if (min_year != "" && films[i]->get_year() < stoi(min_year))
            continue;

        if (price != "" && films[i]->get_price() != stoi(price))
            continue;

        if (max_year != "" && films[i]->get_year() > stoi(max_year))
            continue;

        if (director != "" && films[i]->get_director() != director)
            continue;

        if (films[i]->get_user_id() == user_id) {
            user_films.push_back(films[i]);
        }
    }
    return user_films;
}

void FilmController::update_film(int film_id, string name, string year, string length, string price,
                                 string summary, string director) {
    Film *film = get_film(film_id);
    if (name != "")
        film->set_name(name);
    if (year != "")
        film->set_year(stoi(year));
    if (price != "")
        film->set_price(stoi(price));
    if (summary != "")
        film->set_summary(summary);
    if (director != "")
        film->set_director(director);
}

void FilmController::delete_film(int film_id, int logged_user_id) {
    for (size_t i = 0; i < films.size(); i++) {
        if (film_id == films[i]->get_id()) {
            if (films[i]->get_user_id() != logged_user_id) {
                throw Server::Exception("You cant delete this films");
            }
            delete films[i];
            films.erase(films.begin() + i);
        }
    }
}

float FilmController::get_max_rate(float max_range) {
    float max = 0;
    float rate;
    for (size_t i = 0; i < films.size(); i++) {
        rate = films[i]->get_rate();
        if (rate > max && rate < max_range) {
            max = rate;
        }
    }
    return max;
}

vector<Film *> FilmController::get_recommendation_films(int film_id, vector<Film *> purchased_films) {
    vector<Film *> recommended_films;
    float max_range = 11;
    float max_rate;

    while (recommended_films.size() < 4 && max_rate > 0) {
        max_rate = get_max_rate(max_range);
        for (size_t i = 0; i < films.size(); i++) {
            if (films[i]->get_rate() == max_rate && !films[i]->is_member_of(purchased_films) && films[i]->get_id() != film_id) {
                recommended_films.push_back(films[i]);
                max_range = films[i]->get_rate();
            }
        }
    }
    return recommended_films;
}