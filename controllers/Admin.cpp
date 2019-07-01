#include "Admin.h"

Admin::Admin() {
    money = 0;
}

int Admin::get_money() {
    return money;
}

void Admin::add_money(int amount) {
    money += amount;
}