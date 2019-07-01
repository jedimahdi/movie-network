#include "UserController.h"
#include "../exceptions/BadRequest.h"
#include "../exceptions/NotFound.h"
#include "../exceptions/PermissionDenied.h"
#include "../models/User.h"
#include "../server/server.hpp"
#include <sstream>

using namespace std;

UserController::UserController() {
    logged_user_id = 0;

    users.push_back(new User(ADMIN_EMAIL, ADMIN_USERNAME, ADMIN_PASSWORD, ADMIN_AGE, false));
}

UserController::~UserController() {
    for (size_t i = 0; i < users.size(); i++) {
        delete users[i];
    }
    users.clear();
}

int UserController::get_logged_user_id() { return logged_user_id; }

User *UserController::get_user(int id) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i]->get_id() == id) {
            return users[i];
        }
    }
    throw Server::Exception("User Not Found!");
}

User *UserController::find_by_username(std::string username) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i]->get_username() == username) {
            return users[i];
        }
    }
    throw Server::Exception("User Not Found!");
}

User *UserController::add_user(std::string email, std::string username,
                               std::string password, int age, bool publisher) {

    for (size_t i = 0; i < users.size(); i++) {
        if (users[i]->get_username() == username) {
            ostringstream err;
            err << "User with this username = " << username << " already exists";
            throw Server::Exception(err.str());
        }
    }
    User *new_user = new User(email, username, password, age, publisher);
    users.push_back(new_user);
    return new_user;
}

// bool UserController::can_login(std::string username, std::string password) {
//     User *user = find_by_username(username);
//     if (user->compare_password(password)) {
//         logged_user_id = user->get_id();
//     } else {
//         throw BadRequest();
//     }
// }

std::vector<User *> UserController::get_followers() {
    return get_user(get_logged_user_id())->get_followers();
}

vector<Film *> UserController::get_purchased_films(string name, string min_rate, string min_year, string price, string max_year, string director) {
    vector<Film *> user_films;

    vector<Film *> films = get_user(get_logged_user_id())->get_purchased_films();
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

void UserController::auth_guard() {
    if (logged_user_id == 0) {
        throw PermissionDenied();
    }
}

void UserController::publisher_guard() {
    if (!get_user(logged_user_id)->is_publisher()) {
        throw PermissionDenied();
    }
}

void UserController::add_wallet_money(int amount) {
    get_user(logged_user_id)->add_money(amount);
}

void UserController::follow_user(int user_id) {
    get_user(user_id)->add_follower(get_user(logged_user_id));
}

void UserController::logout() {
    if (logged_user_id == 0) {
        throw BadRequest();
    }
    logged_user_id = 0;
}