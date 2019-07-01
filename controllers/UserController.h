#ifndef USER_CONTROLLER_H_
#define USER_CONTROLLER_H_

#include "../models/Film.h"
#include "../models/User.h"
#include <iostream>
#include <string>

const std::string ADMIN_USERNAME = "admin";
const std::string ADMIN_PASSWORD = "admin";
const std::string ADMIN_EMAIL = "admin@gmail.com";
const int ADMIN_AGE = 40;

class UserController {
public:
    UserController();
    ~UserController();
    int get_logged_user_id();
    User *get_user(int id);
    User *find_by_username(std::string useranme);
    User *add_user(std::string email, std::string username, std::string password,
                   int age, bool publisher = false);

    // void login(std::string username, std::string password);
    void logout();
    std::vector<User *> get_followers();
    void follow_user(int user_id);
    std::vector<Film *> get_purchased_films(std::string name = "", std::string min_rate = "",
                                            std::string min_year = "", std::string price = "",
                                            std::string max_year = "", std::string director = "");
    void add_wallet_money(int amount);

    void auth_guard();
    void publisher_guard();

private:
    std::vector<User *> users;
    int logged_user_id;
};

#endif