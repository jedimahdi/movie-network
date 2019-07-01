#ifndef FILM_HANDLERS_H_
#define FILM_HANDLERS_H_

#include "../controllers/Admin.h"
#include "../controllers/FilmController.h"
#include "../controllers/Recommendation.h"
#include "../controllers/UserController.h"
#include "../server/server.hpp"
#include <iostream>

class ShowCreateFilm : public TemplateHandler {
public:
    ShowCreateFilm(std::string file_path, UserController *uc) : TemplateHandler(file_path), user_controller(uc) {}
    std::map<std::string, std::string> handle(Request *req);

private:
    UserController *user_controller;
};

class CreateFilmHandler : public RequestHandler {
public:
    CreateFilmHandler(FilmController *fc, UserController *uc, Recommendation *rc);
    Response *callback(Request *);

private:
    FilmController *film_controller;
    UserController *user_controller;
    Recommendation *recommendation;
};

class ShowFilms : public RequestHandler {
public:
    ShowFilms(FilmController *fc, UserController *uc, Recommendation *rc) : film_controller(fc), user_controller(uc), recommendation(rc) {}
    Response *callback(Request *);

private:
    FilmController *film_controller;
    UserController *user_controller;
    Recommendation *recommendation;
};

class ShowFilmDetails : public RequestHandler {
public:
    ShowFilmDetails(FilmController *fc, UserController *uc, Recommendation *rc) : film_controller(fc), user_controller(uc), recommendation(rc) {}
    Response *callback(Request *);

private:
    FilmController *film_controller;
    UserController *user_controller;
    Recommendation *recommendation;
};

class DeleteFilmHandler : public RequestHandler {
public:
    DeleteFilmHandler(FilmController *fc, UserController *uc, Recommendation *rc) : film_controller(fc), user_controller(uc), recommendation(rc) {}
    Response *callback(Request *);

private:
    FilmController *film_controller;
    UserController *user_controller;
    Recommendation *recommendation;
};

class ShowPurchasedFilms : public RequestHandler {
public:
    ShowPurchasedFilms(FilmController *fc, UserController *uc) : film_controller(fc), user_controller(uc) {}
    Response *callback(Request *);

private:
    FilmController *film_controller;
    UserController *user_controller;
};

class BuyFilmHandler : public RequestHandler {
public:
    BuyFilmHandler(FilmController *fc, UserController *uc, Recommendation *rc) : film_controller(fc), user_controller(uc), recommendation(rc) {}
    Response *callback(Request *);

private:
    FilmController *film_controller;
    UserController *user_controller;
    Recommendation *recommendation;
};

class RateFilmHandler : public RequestHandler {
public:
    RateFilmHandler(FilmController *fc, UserController *uc) : film_controller(fc), user_controller(uc) {}
    Response *callback(Request *);

private:
    FilmController *film_controller;
    UserController *user_controller;
};

class MoneyHandler : public RequestHandler {
public:
    MoneyHandler(FilmController *fc, UserController *uc, Admin *a) : film_controller(fc), user_controller(uc), admin(a) {}
    Response *callback(Request *);

private:
    UserController *user_controller;
    FilmController *film_controller;
    Admin *admin;
};

#endif