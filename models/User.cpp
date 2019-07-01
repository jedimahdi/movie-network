#include "User.h"
#include "../utils/md5.h"

int User::new_id = 1;

User::User(std::string _email, std::string _username, std::string _password,
           int _age, bool _publisher) {
    id = new_id++;
    email = _email;
    username = _username;
    password = md5(_password);
    age = _age;
    publisher = _publisher;
    wallet = 0;
}

User::~User() {
    followers.clear();
    purchased_films.clear();
    clear_notifications();
}

int User::get_id() { return id; }

std::string User::get_username() { return username; }

bool User::compare_password(std::string _password) {
    if (password == md5(_password)) {
        return true;
    }
    return false;
}

void User::add_follower(User *user) { followers.push_back(user); }

bool User::is_publisher() {
    return publisher;
}

std::vector<User *> User::get_followers() { return followers; }

std::vector<Film *> User::get_purchased_films() {
    return purchased_films;
}

std::vector<Notification *> User::get_new_notifications() {
    std::vector<Notification *> new_notifies;
    for (size_t i = 0; i < notifications.size(); i++) {
        if (!notifications[i]->is_viewd())
            new_notifies.push_back(notifications[i]);
    }
    return new_notifies;
}

std::vector<Notification *> User::get_old_notifications() {
    std::vector<Notification *> old_notifies;
    for (size_t i = 0; i < notifications.size(); i++) {
        if (notifications[i]->is_viewd())
            old_notifies.push_back(notifications[i]);
    }
    return old_notifies;
}

int User::get_money() {
    return wallet;
}

void User::add_money(int amount) {
    wallet += amount;
}

void User::add_purchased_film(Film *film) {
    purchased_films.push_back(film);
}

std::ostream &operator<<(std::ostream &out, const User *user) {
    out << user->id << " | ";
    out << user->username << " | ";
    out << user->email;
    return out;
}

void User::notify(std::string message) {
    notifications.push_back(new Notification(message));
}

void User::clear_notifications() {
    for (size_t i = 0; i < notifications.size(); i++) {
        delete notifications[i];
    }
    notifications.clear();
}

void User::view_notifications() {
    for (size_t i = 0; i < notifications.size(); i++) {
        notifications[i]->viewd();
    }
}

int User::pay(int money, float rate) {
    int user_share;
    if (rate < 5) {
        user_share = 0.8 * money;
    } else if (rate >= 5 && rate < 8) {
        user_share = 0.9 * money;
    } else {
        user_share = 0.95 * money;
    }

    wallet += user_share;

    return money - user_share;
}