#include "Film.h"
#include "../exceptions/NotFound.h"

int Film::new_id = 1;

Film::Film(int _user_id, std::string _name, int _year, int _length,
           int _price, std::string _summary, std::string _director) {
    id = new_id++;
    user_id = _user_id;
    name = _name;
    year = _year;
    length = _length;
    price = _price;
    summary = _summary;
    director = _director;
    rate = 0;
    comment_new_id = 1;
    publisher_earned_money = 0;
}

Film::~Film() {
    for (size_t i = 0; i < comments.size(); i++) {
        delete comments[i];
    }
    comments.clear();
}

int Film::get_id() { return id; }

int Film::get_user_id() { return user_id; }
int Film::get_length() { return length; }
int Film::get_price() { return price; }
int Film::get_rate() { return rate; }
int Film::get_year() { return year; }
std::string Film::get_director() { return director; }
std::string Film::get_summary() { return summary; }

Comment *Film::get_comment(int comment_id) {
    for (size_t i = 0; i < comments.size(); i++) {
        if (comments[i]->get_id() == comment_id) {
            return comments[i];
        }
    }
    throw NotFound();
}

std::string Film::get_name() {
    return name;
}

std::ostream &operator<<(std::ostream &out, const Film *film) {
    out << film->id << " | ";
    out << film->name << " | ";
    out << film->length << " | ";
    out << film->price << " | ";
    out << film->rate << " | ";
    out << film->year << " | ";
    out << film->director;
    return out;
}

void Film::set_name(std::string _name) {
    name = _name;
}
void Film::set_year(int _year) {
    year = _year;
}
void Film::set_price(int _price) {
    price = _price;
}
void Film::set_summary(std::string _summary) {
    summary = _summary;
}
void Film::set_director(std::string _director) {
    director = _director;
}

std::vector<Comment *> Film::get_comments() {
    return comments;
}

void Film::update(std::string _name, int _year, int _length, int _price,
                  std::string _summary, std::string _director) {
    if (_name != "")
        name = _name;
    if (_year != 0)
        year = _year;
    if (_length != 0)
        length = _length;
    if (_price != 0)
        price = _price;
    if (_summary != "")
        summary = _summary;
    if (_director != "")
        director = _director;
}

void Film::rate_film(int score) {
    if (rate == 0) {
        rate = score;
    } else {
        rate = (rate + score) / 2;
    }
}

bool Film::is_member_of(std::vector<Film *> films) {
    for (size_t i = 0; i < films.size(); i++) {
        if (id == films[i]->id) {
            return true;
        }
    }
    return false;
}

void Film::add_comment(int user_id, std::string content) {
    comments.push_back(new Comment(comment_new_id++, user_id, content));
}

void Film::delete_comment(int comment_id) {
    for (size_t i = 0; i < comments.size(); i++) {
        if (comment_id == comments[i]->get_id()) {
            delete comments[i];
            comments.erase(comments.begin() + i);
        }
    }
}

void Film::add_reply(int comment_id, std::string content) {
    for (size_t i = 0; i < comments.size(); i++) {
        if (comments[i]->get_id() == comment_id) {
            comments[i]->add_reply(content);
            break;
        }
    }
}

void Film::sell() {
    publisher_earned_money += price;
}

int Film::get_publisher_earned_money() {
    return publisher_earned_money;
}

void Film::reset_earned_money() {
    publisher_earned_money = 0;
}