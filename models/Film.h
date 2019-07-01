#ifndef FILM_H
#define FILM_H

#include "Comment.h"
#include <iostream>
#include <vector>

class Film {
public:
    Film(int _user_id, std::string _name, int _year, int _length,
         int _price, std::string _summary, std::string _director);
    ~Film();

    void update(std::string _name, int _year, int _length, int _price,
                std::string _summary, std::string _director);
    int get_id();
    int get_user_id();
    std::string get_name();
    std::string get_director();
    std::string get_summary();
    int get_length();
    int get_year();
    int get_rate();
    int get_price();
    Comment *get_comment(int comment_id);
    void set_name(std::string _name);
    void set_year(int _year);
    void set_price(int _price);
    void set_summary(std::string _summary);
    void set_director(std::string _director);
    void rate_film(int score);
    std::vector<Comment *> get_comments();
    bool is_member_of(std::vector<Film *>);
    void add_comment(int user_id, std::string conent);
    void delete_comment(int comment_id);
    void add_reply(int comment_id, std::string content);
    void sell();
    int get_publisher_earned_money();
    void reset_earned_money();

    friend std::ostream &operator<<(std::ostream &out, const Film *film);

protected:
    int id;
    int user_id;
    std::string name;
    int year;
    int length;
    int price;
    std::string summary;
    std::string director;
    float rate;
    std::vector<Comment *> comments;
    static int new_id;
    int comment_new_id;
    int publisher_earned_money;
};

#endif