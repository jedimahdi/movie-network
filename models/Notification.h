#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include <iostream>

class Notification {
public:
    Notification(std::string _message);
    std::string get_message();
    void viewd();
    bool is_viewd();

private:
    std::string message;
    bool view;
};

#endif