#ifndef PERMISSION_DENIED_H_
#define PERMISSION_DENIED_H_

#include <exception>
#include <iostream>

class PermissionDenied : public std::exception {
public:
    virtual const char *what() const throw() { return "Permission Denied"; }
};

#endif