#ifndef USER_H_
#define USER_H_

#include "Film.h"
#include "Notification.h"
#include <iostream>
#include <vector>

class User {
public:
    User(std::string _email, std::string _username,
         std::string _password, int _age, bool _publisher);
    ~User();
    int get_id();
    std::string get_username();
    bool compare_password(std::string _password);
    void add_follower(User *user);
    std::vector<User *> get_followers();
    std::vector<Film *> get_purchased_films();
    std::vector<Notification *> get_old_notifications();
    std::vector<Notification *> get_new_notifications();
    bool is_publisher();
    int get_money();
    void add_money(int amount);
    void add_purchased_film(Film *film);
    void notify(std::string message);
    void clear_notifications();
    void view_notifications();
    int pay(int money, float rate);

    friend std::ostream &operator<<(std::ostream &out, const User *user);

private:
    int id;
    std::string email;
    std::string username;
    std::string password;
    int age;
    std::vector<User *> followers;
    std::vector<Film *> purchased_films;
    std::vector<Notification *> notifications;
    bool publisher;
    static int new_id;
    int wallet;
};

#endif