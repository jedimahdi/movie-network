#ifndef REPLY_H_
#define REPLY_H_

#include <iostream>

class Reply {
public:
    Reply(std::string _content);
    std::string get_content();

private:
    std::string content;
};

#endif