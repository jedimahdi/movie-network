#ifndef ADMIN_H_
#define ADMIN_H_

class Admin {
public:
    Admin();
    int get_money();
    void add_money(int amount);

private:
    int money;
};

#endif