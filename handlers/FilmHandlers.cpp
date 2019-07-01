#include "FilmHandlers.h"
#include "../exceptions/BadRequest.h"
#include "../exceptions/PermissionDenied.h"
#include "../models/Comment.h"
#include "../models/Film.h"
#include <sstream>
#include <vector>

using namespace std;

map<string, string> ShowCreateFilm::handle(Request *req) {
    map<string, string> context;
    if (req->getSessionId() == "") {
        throw Server::Exception("Permission Denied!");
    } else {
        User *user = user_controller->get_user(stoi(req->getSessionId()));
        if (user->is_publisher()) {
            context["is_publisher"] = "1";
        } else {
            context["is_publisher"] = "0";
        }
        context["logged_user_name"] = user->get_username();
    }

    return context;
}

CreateFilmHandler::CreateFilmHandler(FilmController *fc, UserController *uc, Recommendation *rc)
    : film_controller(fc), user_controller(uc), recommendation(rc) {}

Response *CreateFilmHandler::callback(Request *req) {
    if (req->getSessionId() == "")
        return Response::redirect("/login");
    int logged_user_id = stoi(req->getSessionId());
    User *user = user_controller->get_user(logged_user_id);

    if (!user->is_publisher()) {
        Response *res = Response::redirect("/");
        res->setStatus(403);
        return res;
    }

    film_controller->create_film(
        logged_user_id, req->getBodyParam("name"),
        stoi(req->getBodyParam("year")), stoi(req->getBodyParam("length")),
        stoi(req->getBodyParam("price")), req->getBodyParam("summary"),
        req->getBodyParam("director"));

    recommendation->on_add_film();

    ostringstream message;
    message << "Publisher " << user->get_username() << " with id " << user->get_id() << "register new film." << endl;
    vector<User *> followers = user->get_followers();
    for (size_t i = 0; i < followers.size(); i++) {
        followers[i]->notify(message.str());
    }

    return Response::redirect("/films/add");
}

Response *ShowFilms::callback(Request *req) {
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    ostringstream body;

    if (req->getSessionId() == "")
        return Response::redirect("/login");

    User *user = user_controller->get_user(stoi(req->getSessionId()));
    vector<Film *> films;
    if (user->is_publisher()) {
        films = film_controller->get_user_films(user->get_id(), req->getQueryParam("name"), req->getQueryParam("rate"),
                                                req->getQueryParam("min_year"), req->getQueryParam("price"),
                                                req->getQueryParam("max_year"), req->getQueryParam("director"));
    } else {
        films = film_controller->get_all_films(req->getQueryParam("name"), req->getQueryParam("rate"),
                                               req->getQueryParam("min_year"), req->getQueryParam("price"),
                                               req->getQueryParam("max_year"), req->getQueryParam("director"));
    }

    body << "<!DOCTYPE html>" << endl;
    body << "<html lang='en'>" << endl;
    body << "<head>" << endl;
    body << "   <meta charset='UTF-8'>" << endl;
    body << "   <meta name='viewport' content='width=device-width, initial-scale=1.0'>" << endl;
    body << "   <meta http-equiv='X-UA-Compatible' content='ie=edge'>" << endl;
    body << "   <link rel='stylesheet' href='bootstrap.css'>" << endl;
    body << "   <title>Home | Movie Network</title>" << endl;
    body << "</head>" << endl;
    body << "<body>" << endl;
    body << "   <div style='margin-bottom: 0 !important;' class='d-flex flex-column flex-md-row align-items-center p-3 px-md-4 mb-3 bg-white border-bottom shadow-sm'>" << endl;
    body << "       <h5 class='my-0 mr-md-auto font-weight-normal'>Movie Network</h5>" << endl;
    body << "       <nav class='my-2 my-md-0 mr-md-3'>" << endl;
    body << "           <a class='p-2 text-dark' href='/'>Home</a>" << endl;
    if (user->is_publisher()) {
        body << "       <a class='p-2 text-dark' href='/films/add'>Add Film</a>" << endl;
    }
    body << "           <a class='p-2 text-dark' href='/profile'>Profile</a>" << endl;
    body << "       </nav>" << endl;
    body << "       <a class='btn btn-outline-primary' href='/logout'>Logout</a>" << endl;
    body << "   </div>" << endl;

    body << "   <div class='album py-5 bg-light'>" << endl;
    body << "       <div class='container'>" << endl;
    body << "<form method='GET' action='/'>" << endl;
    body << "           <div class='row'>" << endl;
    body << "<div class='col-md-10 mb-4'><input name='director' type='text' class='form-control' placeholder='Search by director name'> </div>" << endl;
    body << "<div class='col-md-2 mb-4'><button class='btn btn-secondary' type='submit'>Search</button> </div>" << endl;
    body << "</div>" << endl;
    body << "</form>" << endl;

    body << "           <div class='row'>" << endl;
    for (size_t i = 0; i < films.size(); i++) {
        body << "<div class='col-md-4'>" << endl;
        body << "<div class='card mb-4 shadow-sm'>" << endl;
        body << "<div class='card-body'>" << endl;
        body << "<h5 class='card-title'>" << films[i]->get_name() << "</h5>" << endl;
        body << "<p class='card-text'>"
             << "Director : " << films[i]->get_director() << "<br />"
             << "Price : " << films[i]->get_price() << "<br />"
             << "Rate : " << films[i]->get_rate() << "<br />"
             << "Year : " << films[i]->get_year() << "<br />"
             << "</p>" << endl;
        body << "<div class='d-flex justify-content-between align-items-center'>" << endl;
        body << "<div class='btn-group'>" << endl;
        body << "<a href='/film?id=" << films[i]->get_id() << "' class='btn btn-sm btn-outline-secondary'>View</a>" << endl;
        if (user->is_publisher()) {
            body << "<a href='/delete_film?id=" << films[i]->get_id() << "' class='btn btn-sm btn-outline-secondary'>Delete</a>" << endl;
        }
        body << "</div>" << endl;
        body << "<small class='text-muted'>" << films[i]->get_length() << " mins</small>" << endl;
        body << "</div>" << endl;
        body << "</div>" << endl;
        body << "</div>" << endl;
        body << "</div>" << endl;
    }
    body << "           </div>" << endl;
    body << "       </div>" << endl;
    body << "   </div>" << endl;

    body << "</body>" << endl;
    body << "</html>" << endl;

    res->setBody(body.str());
    return res;
}

Response *ShowFilmDetails::callback(Request *req) {
    if (req->getSessionId() == "")
        return Response::redirect("/login");
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    ostringstream body;

    Film *film = film_controller->get_film(stoi(req->getQueryParam("id")));
    User *user = user_controller->get_user(stoi(req->getSessionId()));
    vector<int> film_ids = recommendation->get_films(film->get_id());

    body << "<!DOCTYPE html>" << endl;
    body << "<html lang='en'>" << endl;
    body << "<head>" << endl;
    body << "   <meta charset='UTF-8'>" << endl;
    body << "   <meta name='viewport' content='width=device-width, initial-scale=1.0'>" << endl;
    body << "   <meta http-equiv='X-UA-Compatible' content='ie=edge'>" << endl;
    body << "   <link rel='stylesheet' href='bootstrap.css'>" << endl;
    body << "   <title>Home | Movie Network</title>" << endl;
    body << "</head>" << endl;
    body << "<body class='bg-light'>" << endl;
    body << "   <div style='margin-bottom: 0 !important;' class='d-flex flex-column flex-md-row align-items-center p-3 px-md-4 mb-3 border-bottom shadow-sm'>" << endl;
    body << "       <h5 class='my-0 mr-md-auto font-weight-normal'>Movie Network</h5>" << endl;
    body << "       <nav class='my-2 my-md-0 mr-md-3'>" << endl;
    body << "           <a class='p-2 text-dark' href='/'>Home</a>" << endl;
    if (user->is_publisher()) {
        body << "       <a class='p-2 text-dark' href='/films/add'>Add Film</a>" << endl;
    }
    body << "           <a class='p-2 text-dark' href='/profile'>Profile</a>" << endl;
    body << "       </nav>" << endl;
    body << "       <a class='btn btn-outline-primary' href='/logout'>Logout</a>" << endl;
    body << "   </div>" << endl;

    body << "       <div class='container'>" << endl;
    body << "<div class='d-flex align-items-center p-3 my-3 rounded shadow-sm bg-white'>" << endl;
    body << "<div class='lh-100'>" << endl;
    body << "<h2 class='lh-100'>" << film->get_name() << "</h2>" << endl;
    body << "<p>Production Year: " << film->get_year() << "</p>" << endl;
    body << "<p>Director: " << film->get_director() << "</p>" << endl;
    body << "<p>Rate: " << film->get_rate() << "</p>" << endl;
    body << "<p>Length: " << film->get_length() << " min</p>" << endl;
    body << "<p>Price: " << film->get_price() << "</p>" << endl;
    body << "<p>Summary: " << film->get_summary() << "</p>" << endl;

    if (!film->is_member_of(user->get_purchased_films())) {
        body << "<form method='POST' action='/buy'>" << endl;
        body << "<input type='hidden' name='film_id' value='" << film->get_id() << "'>" << endl;
        body << "<button type='submit' class='btn btn-primary'>Buy</button>" << endl;
        body << "</form>" << endl;
    } else {
        body << "<form method='POST' action='/rate'>" << endl;
        body << "<input type='hidden' name='film_id' value='" << film->get_id() << "'>" << endl;
        body << "<input type='text' name='score' class='form-control' placeholder='Score'>" << endl;
        body << "<button type='submit' class='btn btn-block btn-primary'>Rate</button>" << endl;
        body << "</form>" << endl;
    }

    body << "</div>" << endl;
    body << "</div>" << endl;

    body << "<div class='my-3 p-3 bg-white rounded shadow-sm'>" << endl;
    body << "<h6 class='border-bottom border-gray pb-2 mb-0'>Suggestions</h6>" << endl;

    Film *f;
    for (size_t i = 0; i < film_ids.size(); i++) {
        f = film_controller->get_film(film_ids[i]);
        body << "<div class='media text-muted pt-3'>" << endl;
        body << "<div class='media-body pb-3 mb-0 small lh-125 border-bottom border-gray'>" << endl;
        body << "<div class='d-flex justify-content-between align-items-center w-100'>" << endl;
        body << "<strong class='text-gray-dark'>" << f->get_name() << " (" << f->get_director() << ")</strong>" << endl;
        body << "<a href='/film?id=" << f->get_id() << "'>View</a>" << endl;
        body << "</div>" << endl;
        body << "<span class='d-block'>" << f->get_length() << " mins</span>" << endl;
        body << "</div>" << endl;
        body << "</div>" << endl;
    }

    body << "</div>" << endl;
    body << "   </div>" << endl;
    body << "</body>" << endl;
    body << "</html>" << endl;

    res->setBody(body.str());
    return res;
}

Response *DeleteFilmHandler::callback(Request *req) {
    if (req->getSessionId() == "")
        return Response::redirect("/login");
    int logged_user_id = stoi(req->getSessionId());
    User *user = user_controller->get_user(logged_user_id);

    if (!user->is_publisher()) {
        Response *res = Response::redirect("/");
        res->setStatus(403);
        return res;
    }

    int film_id = stoi(req->getQueryParam("id"));

    film_controller->delete_film(film_id, logged_user_id);
    recommendation->on_delete_film(film_id);

    return Response::redirect("/");
}

Response *ShowPurchasedFilms::callback(Request *req) {
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    ostringstream body;

    if (req->getSessionId() == "")
        return Response::redirect("/login");

    User *user = user_controller->get_user(stoi(req->getSessionId()));
    vector<Film *> films = user->get_purchased_films();

    body << "<!DOCTYPE html>" << endl;
    body << "<html lang='en'>" << endl;
    body << "<head>" << endl;
    body << "   <meta charset='UTF-8'>" << endl;
    body << "   <meta name='viewport' content='width=device-width, initial-scale=1.0'>" << endl;
    body << "   <meta http-equiv='X-UA-Compatible' content='ie=edge'>" << endl;
    body << "   <link rel='stylesheet' href='bootstrap.css'>" << endl;
    body << "   <title>Home | Movie Network</title>" << endl;
    body << "</head>" << endl;
    body << "<body>" << endl;
    body << "   <div style='margin-bottom: 0 !important;' class='d-flex flex-column flex-md-row align-items-center p-3 px-md-4 mb-3 bg-white border-bottom shadow-sm'>" << endl;
    body << "       <h5 class='my-0 mr-md-auto font-weight-normal'>Movie Network</h5>" << endl;
    body << "       <nav class='my-2 my-md-0 mr-md-3'>" << endl;
    body << "           <a class='p-2 text-dark' href='/'>Home</a>" << endl;
    if (user->is_publisher()) {
        body << "       <a class='p-2 text-dark' href='/films/add'>Add Film</a>" << endl;
    }
    body << "           <a class='p-2 text-dark' href='/profile'>Profile</a>" << endl;
    body << "       </nav>" << endl;
    body << "       <a class='btn btn-outline-primary' href='/logout'>Logout</a>" << endl;
    body << "   </div>" << endl;

    body << "   <div class='album py-5 bg-light'>" << endl;
    body << "       <div class='container'>" << endl;
    body << "           <form method='POST' action='/money'>" << endl;
    body << "           <div class='row'>" << endl;
    body << "               <div class='col-md-6 mb-4'>" << endl;
    body << "                   <h4>Add Money : </h4>" << endl;
    body << "                   <div class='row'><div class='col-md-8'>" << endl;
    body << "                       <input class='form-control' type='text' name='amount' placeholder='Amount'>" << endl;
    body << "                       </div><div class='col-md-4'>" << endl;
    body << "                       <button type='submit' class='btn btn-dark'>Add</button>" << endl;
    body << "                       </div>" << endl;
    body << "                   </div>" << endl;
    body << "               </div>" << endl;
    body << "               <div class='col-md-6 mb-4'>" << endl;
    body << "                   <h4>Your Money : </h4>" << user->get_money() << endl;
    body << "               </div>" << endl;
    body << "           </div>" << endl;
    body << "            </form>" << endl;
    body << "           <hr />" << endl;
    body << "           <div class='row'>" << endl;
    for (size_t i = 0; i < films.size(); i++) {
        body << "<div class='col-md-4'>" << endl;
        body << "<div class='card mb-4 shadow-sm'>" << endl;
        body << "<div class='card-body'>" << endl;
        body << "<h5 class='card-title'>" << films[i]->get_name() << "</h5>" << endl;
        body << "<p class='card-text'>"
             << "Director : " << films[i]->get_director() << "<br />"
             << "Price : " << films[i]->get_price() << "<br />"
             << "Rate : " << films[i]->get_rate() << "<br />"
             << "Year : " << films[i]->get_year() << "<br />"
             << "</p>" << endl;
        body << "<div class='d-flex justify-content-between align-items-center'>" << endl;
        body << "<div class='btn-group'>" << endl;
        body << "<a href='/film?id=" << films[i]->get_id() << "' class='btn btn-sm btn-outline-secondary'>View</a>" << endl;
        body << "</div>" << endl;
        body << "<small class='text-muted'>" << films[i]->get_length() << " mins</small>" << endl;
        body << "</div>" << endl;
        body << "</div>" << endl;
        body << "</div>" << endl;
        body << "</div>" << endl;
    }
    body << "           </div>" << endl;
    body << "       </div>" << endl;
    body << "   </div>" << endl;

    body << "</body>" << endl;
    body << "</html>" << endl;

    res->setBody(body.str());
    return res;
}

Response *BuyFilmHandler::callback(Request *req) {
    if (req->getSessionId() == "")
        return Response::redirect("/login");
    User *user = user_controller->get_user(stoi(req->getSessionId()));
    Film *film = film_controller->get_film(stoi(req->getBodyParam("film_id")));

    if (user->get_money() < film->get_price()) {
        throw Server::Exception("You don't have enough money to buy this film!");
    }
    user->add_money(-film->get_price());
    user->add_purchased_film(film);
    film->sell();

    recommendation->on_buy_film(film->get_id());

    ostringstream message;
    message << "User " << user->get_username() << " with id " << user->get_id() << " buy your film "
            << film->get_name() << " with id " << film->get_id() << "." << endl;
    user_controller->get_user(film->get_user_id())->notify(message.str());

    return Response::redirect("/film?id=" + req->getBodyParam("film_id"));
}

Response *RateFilmHandler::callback(Request *req) {
    if (req->getSessionId() == "")
        return Response::redirect("/login");
    User *user = user_controller->get_user(stoi(req->getSessionId()));
    Film *film = film_controller->get_film(stoi(req->getBodyParam("film_id")));

    if (film->is_member_of(user->get_purchased_films())) {
        film->rate_film(stoi(req->getBodyParam("score")));

        ostringstream message;
        message << "User " << user->get_username() << " with id " << user->get_id() << " rate your film "
                << film->get_name() << " with id " << film->get_id() << "." << endl;
        user_controller->get_user(film->get_user_id())->notify(message.str());
    } else {
        throw Server::Exception("You must first buy this film to rate.");
    }

    return Response::redirect("/film?id=" + req->getBodyParam("film_id"));
}

Response *MoneyHandler::callback(Request *req) {
    if (req->getSessionId() == "")
        return Response::redirect("/login");
    User *user = user_controller->get_user(stoi(req->getSessionId()));
    user->add_money(stoi(req->getBodyParam("amount")));
    return Response::redirect("/profile");
}