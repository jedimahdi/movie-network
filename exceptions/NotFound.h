#ifndef NOT_FOUND_H_
#define NOT_FOUND_H_

#include <exception>
#include <iostream>

class NotFound : public std::exception {
public:
    virtual const char *what() const throw() { return "Not Found"; }
};

#endif