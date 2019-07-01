#include "Comment.h"

Comment::Comment(int _id, int _user_id, std::string _content) {
    id = _id;
    content = _content;
    user_id = _user_id;
}

Comment::~Comment() {
    for (size_t i = 0; i < replies.size(); i++) {
        delete replies[i];
    }
    replies.clear();
}

int Comment::get_id() { return id; }
int Comment::get_user_id() { return user_id; }

void Comment::add_reply(std::string content) {
    replies.push_back(new Reply(content));
}

std::ostream &operator<<(std::ostream &out, const Comment *comment) {
    out << comment->id << ". " << comment->content << std::endl;
    for (size_t i = 0; i < comment->replies.size(); i++) {
        out << comment->id << "." << i + 1 << ". " << comment->replies[i]->get_content() << std::endl;
    }

    return out;
}