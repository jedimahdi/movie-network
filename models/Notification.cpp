#include "Notification.h"

Notification::Notification(std::string _message) {
    message = _message;
    view = false;
}

std::string Notification::get_message() {
    return message;
}

void Notification::viewd() {
    view = true;
}

bool Notification::is_viewd() {
    return view;
}