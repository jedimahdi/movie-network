#include "Reply.h"

Reply::Reply(std::string _content) {
    content = _content;
}

std::string Reply::get_content() {
    return content;
}