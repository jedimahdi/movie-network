#ifndef USER_HANDLERS_H_
#define USER_HANDLERS_H_

#include "../controllers/Admin.h"
#include "../controllers/UserController.h"
#include "../server/server.hpp"
#include <iostream>

class ShowSignup : public TemplateHandler {
public:
    ShowSignup(std::string file_path, UserController *uc) : TemplateHandler(file_path), user_controller(uc) {}
    std::map<std::string, std::string> handle(Request *req);

private:
    UserController *user_controller;
};

class SignupHandler : public RequestHandler {
public:
    SignupHandler(UserController *uc) : user_controller(uc) {}
    Response *callback(Request *);

private:
    UserController *user_controller;
};

class ShowLogin : public TemplateHandler {
public:
    ShowLogin(std::string file_path, UserController *uc) : TemplateHandler(file_path), user_controller(uc) {}
    std::map<std::string, std::string> handle(Request *req);

private:
    UserController *user_controller;
};

class LoginHandler : public RequestHandler {
public:
    LoginHandler(UserController *uc) : user_controller(uc) {}
    Response *callback(Request *);

private:
    UserController *user_controller;
};

class LogoutHandler : public RequestHandler {
public:
    LogoutHandler(UserController *uc) : user_controller(uc) {}
    Response *callback(Request *);

private:
    UserController *user_controller;
};

#endif