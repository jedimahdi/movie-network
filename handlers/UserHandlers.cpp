#include "UserHandlers.h"
#include "../exceptions/BadRequest.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

map<string, string> ShowLogin::handle(Request *req) {
    map<string, string> context;
    if (req->getSessionId() == "") {
        context["is_logged_in"] = "0";
    } else {
        context["is_logged_in"] = "1";
        User *user = user_controller->get_user(stoi(req->getSessionId()));
        context["logged_user_name"] = user->get_username();
    }

    return context;
}

Response *LoginHandler::callback(Request *req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    User *user = user_controller->find_by_username(username);
    Response *res = Response::redirect("/");

    if (user->compare_password(password)) {
        res->setSessionId(to_string(user->get_id()));
    } else {
        throw Server::Exception("Wrong Password!");
    }
    return res;
}

Response *LogoutHandler::callback(Request *req) {
    Response *res = Response::redirect("/login");
    res->setSessionId("");

    return res;
}

map<string, string> ShowSignup::handle(Request *req) {
    map<string, string> context;
    if (req->getSessionId() == "") {
        context["is_logged_in"] = "0";
    } else {
        context["is_logged_in"] = "1";
        User *user = user_controller->get_user(stoi(req->getSessionId()));
        context["logged_user_name"] = user->get_username();
    }

    return context;
}

Response *SignupHandler::callback(Request *req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    bool publisher = false;
    if (req->getBodyParam("publisher") == "1") {
        publisher = true;
    }

    User *new_user = user_controller->add_user(req->getBodyParam("email"), username, password,
                                               stoi(req->getBodyParam("age")), publisher);

    Response *res = Response::redirect("/");
    res->setSessionId(to_string(new_user->get_id()));

    return res;
}