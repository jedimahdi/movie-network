#ifndef COMMENT_H_
#define COMMENT_H_

#include "Reply.h"
#include <iostream>
#include <vector>

class Comment {
public:
    Comment(int _id, int _user_id, std::string _content);
    ~Comment();
    int get_id();
    int get_user_id();
    void add_reply(std::string content);

    friend std::ostream &operator<<(std::ostream &out, const Comment *comment);

private:
    int id;
    int user_id;
    std::string content;
    std::vector<Reply *> replies;
};

#endif