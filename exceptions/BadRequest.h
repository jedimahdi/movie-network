#ifndef BAD_REQUEST_H_
#define BAD_REQUEST_H_

#include "../server/server.hpp"

class BadRequest : public Server::Exception {
public:
    BadRequest() : Server::Exception("Bad Request") {}
};

#endif